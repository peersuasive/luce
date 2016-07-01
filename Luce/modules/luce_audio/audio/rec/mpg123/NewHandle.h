#ifndef __REC_AUDIO_FORMAT_MPG123_NEW_HANDLE__
#define __REC_AUDIO_FORMAT_MPG123_NEW_HANDLE__

namespace rec {
namespace mpg123 {

// Create a new mpg123_handle for a Juce InputStream.
Error newHandle(InputStream* in, mpg123_handle** mh);

}  // namespace mpg123
}  // namespace rec

#endif  // __REC_AUDIO_FORMAT_MPG123_NEW_HANDLE__
