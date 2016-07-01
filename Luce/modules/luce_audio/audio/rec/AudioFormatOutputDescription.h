#ifndef __REC_AUDIO_FORMAT_AUDIOFORMATOUTPUTDESCRIPTION__
#define __REC_AUDIO_FORMAT_AUDIOFORMATOUTPUTDESCRIPTION__

namespace juce {

struct AudioFormatOutputDescription
{
    unsigned int channels;
    int bitsPerSample;
    int sampleRate;

    String encoderName;       // The name of the output encoder:  mp3, wav, aiff, etc.
    StringPair encoderHints;  // Name/value pairs which might be meaningful to the encoder.
};

}  // namespace juce

#endif  // __REC_AUDIO_FORMAT_AUDIOFORMATOUTPUTDESCRIPTION__
