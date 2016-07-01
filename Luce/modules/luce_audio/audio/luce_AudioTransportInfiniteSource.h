/*
  ==============================================================================

   This file is part of the JUCE library.
   Copyright (c) 2015 - ROLI Ltd.

   Permission is granted to use this software under the terms of either:
   a) the GPL v2 (or any later version)
   b) the Affero GPL v3

   Details of these licenses can be found at: www.gnu.org/licenses

   JUCE is distributed in the hope that it will be useful, but WITHOUT ANY
   WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR
   A PARTICULAR PURPOSE.  See the GNU General Public License for more details.

   ------------------------------------------------------------------------------

   To release a closed-source product which uses JUCE, commercial licenses are
   available: visit www.juce.com for more information.

  ==============================================================================

  Modified by Peersuasive Technologies, (c) 2016

  ==============================================================================
*/

#ifndef __LUCE_AUDIOTRANSPORTNFINITESOURCE_H
#define __LUCE_AUDIOTRANSPORTNFINITESOURCE_H

class JUCE_API AudioTransportInfiniteSource : public AudioTransportSource
{
public:
    AudioTransportInfiniteSource();
    ~AudioTransportInfiniteSource();

    void setSource (PositionableAudioSource* newSource,
                    int readAheadBufferSize = 0,
                    TimeSliceThread* readAheadThread = nullptr,
                    double sourceSampleRateToCorrectFor = 0.0,
                    int maxNumChannels = 2);

    void setGain (float newGain) noexcept;
    void releaseResources(); // override;
    void getNextAudioBlock (const AudioSourceChannelInfo&); // override;

private:
    //==============================================================================
    PositionableAudioSource* source;
    float volatile gain, lastGain;
    CriticalSection callbackLock;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AudioTransportInfiniteSource)
};


#endif   // __LUCE_AUDIOTRANSPORTINFINITESOURCE_H
