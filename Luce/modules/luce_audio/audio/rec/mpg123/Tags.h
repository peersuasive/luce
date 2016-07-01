#ifndef __REC_AUDIO_FORMAT_MPG123_TAGS__
#define __REC_AUDIO_FORMAT_MPG123_TAGS__

namespace rec {
namespace mpg123 {

#include <mpg123.h>

// Read mp3 tags into a StringPairArray.
Error getMp3Tags(mpg123_handle* mh, StringPairArray* metadata);

}  // namespace mpg123
}  // namespace rec

#endif // __REC_AUDIO_FORMAT_MPG123_TAGS__
