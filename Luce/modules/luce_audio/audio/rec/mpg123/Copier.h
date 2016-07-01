#ifndef __REC_AUDIO_FORMAT_MPG123_COPIER__
#define __REC_AUDIO_FORMAT_MPG123_COPIER__

#include <stddef.h>

namespace rec {
namespace mpg123 {

// A function that copies samples from source to destination.
typedef void (*Copier)(int** dest, int destChannels, int destOffset,
                       void* source, int sourceChannels, size_t sourceSize);

// Get a Copier that matches the mp3 encoding.
Copier getCopier(int encoding);

}  // namespace mpg123
}  // namespace rec

#endif  // __REC_AUDIO_FORMAT_MPG123_COPIER__
