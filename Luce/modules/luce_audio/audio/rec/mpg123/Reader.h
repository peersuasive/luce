#ifndef __REC_AUDIO_FORMAT_MPG123_READER__
#define __REC_AUDIO_FORMAT_MPG123_READER__

#include <stdlib.h>
#include <sys/types.h>

namespace rec {
namespace mpg123 {

class Reader : public AudioFormatReader {
public:
    ~Reader();

    virtual bool readSamples(int** destSamples, int numDestChannels,
            int startOffsetInDestBuffer,
            int64 startSampleInFile, int numSamples);

    juce_UseDebuggingNewOperator

private:
    Reader(InputStream* in, const String& name, mpg123_handle* mh, Copier copier);

    friend Error createReader(InputStream*, AudioFormatReader**, OutputFormat*, OutputFormat*);

    mpg123_handle* mh_;
    void* buffer_;
    size_t size_, allocated_;
    Copier copier_;


    DISALLOW_COPY_AND_ASSIGN(Reader);
};

}  // namespace mpg123
}  // namespace rec

#endif  // __REC_AUDIO_FORMAT_MPG123_READER__
