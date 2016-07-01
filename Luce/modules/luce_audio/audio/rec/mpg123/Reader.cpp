#include <stdlib.h>
#include <sys/types.h>

namespace rec {
namespace mpg123 {

#include <mpg123.h>

Reader::Reader(InputStream* in, const String& formatName, mpg123_handle* mh,
               Copier copier)
  : AudioFormatReader(in, formatName),
    mh_(mh),
    buffer_(NULL),
    size_(0),
    allocated_(0),
    copier_(copier) {
}

Reader::~Reader() {
    mpg123_close(mh_);
    mpg123_delete(mh_);
    free(buffer_);
}

bool Reader::readSamples(int** dest, int destChannels, int destOffset,
        int64 startSampleInFile, int numSamples) {
 
    std::cout << "start sample in file: " << startSampleInFile << std::endl;

    unsigned char tmp_buf[numSamples];
    int r = AudioFormatReader::input->read(tmp_buf, numSamples);
    std::cout << "read " << r << " on " << numSamples << ", pos: " 
        << AudioFormatReader::input->getPosition()
        << ", remaining: " << AudioFormatReader::input->getNumBytesRemaining()
        << ", exhausted: " << AudioFormatReader::input->isExhausted()
        << std::endl;
    if (mpg123_seek(mh_, startSampleInFile, SEEK_SET) < 0) {
        std::cout << "couldn't seek -- returning" << std::endl;
        return false;
    }

    int64 bytesPerSample = this->bitsPerSample / 8;
    size_ = numSamples * numChannels * bytesPerSample;

    if (allocated_ < size_) {
        if (buffer_)
            free(buffer_);

        buffer_ = malloc(size_);
        allocated_ = size_;
    }

    size_t bytesCopied;
    Error e = mpg123_read(mh_, (uchar*) buffer_, size_, &bytesCopied);
    if (e != MPG123_DONE && e != MPG123_OK)
        return false;

    int64 sourceSize = bytesCopied / (bytesPerSample * numChannels);
    copier_(dest, destChannels, destOffset, buffer_, numChannels, sourceSize);
    return (bytesCopied == size_);

#if 0
    if (AudioFormatReader::input->getTotalLength()<0) { // infinite stream
        std::cout << " INFINITE STREAM" << std::endl;
        if (mpg123_seek(mh_, startSampleInFile, SEEK_SET) < 0) {
            std::cout << "couldn't seek in data!" << std::endl;
            return false;
        }

        InputStream *in = AudioFormatReader::input;

        int64 bytesPerSample = this->bitsPerSample / 8;
        size_ = numSamples * numChannels * bytesPerSample;
        unsigned char buf[numSamples], out[size_];

        size_t writtenBytes;
        size_t bytesCopied = 0;
        int ret;
        mpg123_param(mh_, MPG123_VERBOSE, 2, 0); 
        while(ret!=MPG123_ERR && ret!=MPG123_NEED_MORE) {
            std::cout << "looping..." << std::endl;
            int len = in->read(buf, numSamples);
            if(len<=0) {
                std::cout << "no more data to read!..." << std::endl;
                return false;
            }
            ret = mpg123_decode(mh_, buf, len, out, size_, &writtenBytes);
            bytesCopied+=writtenBytes;
            if(ret==MPG123_OK) {
                std::cout << "OK!" << std::endl;
                break;
            } else {
                std::cout << "returned: " << mpg123_strerror(mh_) << std::endl;
            }
        }

        for (int i=0;i<10;++i) {
            std::cout << "out " << i << " -> " << (int)out[i] << std::endl;
        }
        int64 sourceSize = bytesCopied / (bytesPerSample * numChannels);
        copier_(dest, destChannels, destOffset, out, numChannels, sourceSize);
        std::cout << "infinite bytesCopied: " << bytesCopied 
            << ", size_: " << size_
            << ", startSampleInFile: " << startSampleInFile
            << std::endl;
        return (bytesCopied == size_);

        /*
        unsigned char buf[numSamples];
        int len, num;
        unsigned char *audio;
        Error ret, state;
        size_t bytes;
        off_t inoffset;
        while((ret = mpg123_feedseek(mh_, numSamples, SEEK_SET, &inoffset)) == MPG123_NEED_MORE)
        {
            std::cout << "need more..." << std::endl;
            int len = AudioFormatReader::input->read(buf, numSamples);
            if(len <= 0)
                break;
            state = mpg123_feed(mh_, buf, len);
            if(state == MPG123_ERR)
            {
                std::cout << "Error: " << mpg123_strerror(mh_) << std::endl;
                return -1; 
            }
        }
        if(ret == MPG123_ERR)
        {
            std::cout << "Feedseek failed: " << mpg123_strerror(mh_) << std::endl;
            return false;
        } else {
            std::cout << "well, feedseek succeeded ???? " << inoffset << ", " << mpg123_strerror(mh_) << std::endl;
        }
        AudioFormatReader::input->setPosition(inoffset);

        len = AudioFormatReader::input->read(buf, numSamples);
        if(len <= 0) {
            std::cout << "no data read from stream" << std::endl;
            return false;
        }
        ret = mpg123_feed(mh_, buf, len);
        if(ret == MPG123_ERR)
        {
            std::cout << "feed failed: " << mpg123_strerror(mh_) << std::endl;
            return false;
        }
        */
    } else {
        if (mpg123_seek(mh_, startSampleInFile, SEEK_SET) < 0)
            return false;
    }

    int64 bytesPerSample = this->bitsPerSample / 8;
    size_ = numSamples * numChannels * bytesPerSample;

    if (allocated_ < size_) {
        if (buffer_)
            free(buffer_);

        buffer_ = malloc(size_);
        allocated_ = size_;
    }

    size_t bytesCopied;
    Error e = mpg123_read(mh_, (uchar*) buffer_, size_, &bytesCopied);
    if (e != MPG123_DONE && e != MPG123_OK) {
        std::cout << "can't read data: " << mpg123_strerror(mh_) << std::endl;
        return false;
    }

    int64 sourceSize = bytesCopied / (bytesPerSample * numChannels);
    copier_(dest, destChannels, destOffset, buffer_, numChannels, sourceSize);
    std::cout << "bytesCopied: " << bytesCopied 
        << ", size_: " << size_
        << ", startSampleInFile: " << startSampleInFile
        << std::endl;
    return (bytesCopied == size_);
#endif

}

}  // namespace mpg123
}  // namespace rec

