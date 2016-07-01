/*
  ==============================================================================

   This file is part of the juce_core module of the JUCE library.
   Copyright (c) 2015 - ROLI Ltd.

   Permission to use, copy, modify, and/or distribute this software for any purpose with
   or without fee is hereby granted, provided that the above copyright notice and this
   permission notice appear in all copies.

   THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES WITH REGARD
   TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS. IN
   NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL
   DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER
   IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN
   CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.

   ------------------------------------------------------------------------------

   NOTE! This permissive ISC license applies ONLY to files within the juce_core module!
   All other JUCE modules are covered by a dual GPL/commercial license, so if you are
   using any other modules, be sure to check that you also comply with their license.

   For more details, visit www.juce.com

  ==============================================================================
*/

namespace
{
    int webCalcBufferStreamBufferSize (int requestedSize, InputStream* const source) noexcept
    {
        // You need to supply a real stream when creating a WebBufferedInputStream
        jassert (source != nullptr);

        requestedSize = jmax (256, requestedSize);

        const int64 sourceSize = source->getTotalLength();
        if (sourceSize >= 0 && sourceSize < requestedSize)
            requestedSize = jmax (32, (int) sourceSize);

        return requestedSize;
    }
}

//==============================================================================
WebBufferedInputStream::WebBufferedInputStream (InputStream* const sourceStream, const int bufferSize_,
                                          const bool deleteSourceWhenDestroyed, const int backBufferSize_)
   : source (sourceStream, deleteSourceWhenDestroyed),
     bufferSize (webCalcBufferStreamBufferSize (bufferSize_, sourceStream)),
     backBufferSize(bufferSize),
     position (sourceStream->getPosition()),
     lastReadPos (0),
     bufferStart (position),
     backBufferStart (position),
     bufferOverlap (128),
     isInfinite(sourceStream->getTotalLength()<0)
{


    // TODO: ajouter un backBuffer, pour conserver les data précédentes,
    // ce qui peut être utilisé par les readers
    // quand ils ont fait une boucle pour chercher les headers
    // à chaque ensureBuffered,
    // on fait un memmove vers le tableau précédent
    // avant de le remplir avec les nouvelles data
    // on ajoute les variables backBufferStart, backBufferEnd,
    // bien que l'une comme l'autre soient un peu superflues,
    // mais ça évite le calcul (lastReadPos - bufferStart)
    // à chaque fois qu'on veut vérifier si la position est accessible
    //
    // donc, ce backBuffer est configurable, en fait il peut nous servir pour revenir
    // en arrière sur des flux continus
    //
    //

    buffer.calloc ((size_t) bufferSize + backBufferSize);
}

WebBufferedInputStream::WebBufferedInputStream (InputStream& sourceStream, const int bufferSize_)
   : source (&sourceStream, false),
     bufferSize (webCalcBufferStreamBufferSize (bufferSize_, &sourceStream)),
     backBufferSize(bufferSize),
     position (sourceStream.getPosition()),
     lastReadPos (0),
     bufferStart (position),
     backBufferStart (position),
     bufferOverlap (128)
{
    buffer.calloc ((size_t) bufferSize + backBufferSize);
}

WebBufferedInputStream::~WebBufferedInputStream()
{
}

//==============================================================================
int64 WebBufferedInputStream::getTotalLength()
{
    return isInfinite ? hugeFakeLength : source->getTotalLength();
}

int64 WebBufferedInputStream::getPosition()
{
    return position;
}

bool WebBufferedInputStream::setPosition (int64 newPosition)
{
    jassert(isInfinite ? newPosition >= bufferStart : true);
    if(isInfinite && newPosition < bufferStart) {
        std::cout << "new pos: " << newPosition << ", cur pos: " << position 
            << ", bufferStart: " << bufferStart 
            << ", backBufferStart: " << backBufferStart 
            << std::endl;
        return false;
    }

    position = jmax ((int64) 0, newPosition);
    return true;
}

bool WebBufferedInputStream::isExhausted()
{
    return position >= lastReadPos && source->isExhausted();
}

void WebBufferedInputStream::ensureBuffered()
{
    const int64 bufferEndOverlap = lastReadPos - bufferOverlap;

    if (position < bufferStart || position >= bufferEndOverlap)
    {
        int bytesRead;

        if (position < lastReadPos
             && position >= bufferEndOverlap
             && position >= bufferStart)
        {
            std::cout << "**first case**: " << position
                << ", lrp: " << lastReadPos
                << ", beo: " << bufferEndOverlap
                << ", bs: " << bufferStart
                << std::endl;
            const int bytesToKeep = (int) (lastReadPos - position);
            memmove (buffer, buffer + (int) (position - bufferStart), (size_t) bytesToKeep);

            bufferStart = position;

            bytesRead = source->read (buffer + bytesToKeep,
                                      (int) (bufferSize - bytesToKeep));

            lastReadPos += bytesRead;
            bytesRead += bytesToKeep;
        }
        else
        {
            std::cout << "++second case++: " << position
                << ", is lower than bs ? " << (position<bufferStart ? "!!!TRUE!!!" : "false")
                << ", lrp: " << lastReadPos
                << ", beo: " << bufferEndOverlap
                << ", bs: " << bufferStart
                << std::endl;

            bufferStart = position;
            source->setPosition (bufferStart);
            bytesRead = source->read (buffer, bufferSize);
            lastReadPos = bufferStart + bytesRead;
        }

        while (bytesRead < bufferSize)
            buffer [bytesRead++] = 0;
    }
}

int WebBufferedInputStream::read (void* destBuffer, int maxBytesToRead)
{
    jassert (destBuffer != nullptr && maxBytesToRead >= 0);

    if (position >= bufferStart
         && position + maxBytesToRead <= lastReadPos)
    {
        std::cout << "reading from buffered data" << std::endl;
        memcpy (destBuffer, buffer + (int) (position - bufferStart), (size_t) maxBytesToRead);
        position += maxBytesToRead;

        return maxBytesToRead;
    }
    else
    {
        if (position < bufferStart || position >= lastReadPos)
            ensureBuffered();

        int bytesRead = 0;

        while (maxBytesToRead > 0)
        {
            const int bytesAvailable = jmin (maxBytesToRead, (int) (lastReadPos - position));

            if (bytesAvailable > 0)
            {
                memcpy (destBuffer, buffer + (int) (position - bufferStart), (size_t) bytesAvailable);
                maxBytesToRead -= bytesAvailable;
                bytesRead += bytesAvailable;
                position += bytesAvailable;
                destBuffer = static_cast<char*> (destBuffer) + bytesAvailable;
            }

            const int64 oldLastReadPos = lastReadPos;
            ensureBuffered();

            if (oldLastReadPos == lastReadPos)
                break; // if ensureBuffered() failed to read any more data, bail out

            if (isExhausted())
                break;
        }

        return bytesRead;
    }
}

String WebBufferedInputStream::readString()
{
    if (position >= bufferStart
         && position < lastReadPos)
    {
        const int maxChars = (int) (lastReadPos - position);

        const char* const src = buffer + (int) (position - bufferStart);

        for (int i = 0; i < maxChars; ++i)
        {
            if (src[i] == 0)
            {
                position += i + 1;
                return String::fromUTF8 (src, i);
            }
        }
    }

    return isInfinite ? String() : InputStream::readString();
}
