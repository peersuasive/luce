namespace rec {
namespace mpg123 {

#include <mpg123.h>

namespace {

template <typename Number>
Number average(Number x, Number y) { return (x + y) / 2; }

template <>
int average(int x, int y) { return int((x + (long)y)/ 2); }

template <typename In, typename Out>
struct Copy {
  static Out get(In* in, size_t pos, int channel, int channels) {
    return cast(in[pos * channels + channel % channels]);
  }

  static Out cast(In in) { return Out(in); }

  static void copy(int** destSamples, int destChannels, int destOffset,
                   void* source, int sourceChannels, size_t sourceSize) {
    Out** out = (Out**) destSamples;
    In* in = (In*) source;

    if (destChannels == 1 && sourceChannels == 2) {
      Out *o = out[0] + destOffset;
      for (size_t s = 0; s < sourceSize; ++s)
        o[s] = average(get(in, s, 0, 2), get(in, s, 1, 2));

    } else {
      for (size_t c = 0; c < destChannels; ++c) {
        Out *o = out[c] + destOffset;
        for (size_t s = 0; s < sourceSize; ++s)
          o[s] = get(in, s, c, sourceChannels);
      }
    }
  }
};

template<> int Copy<char,   int>::cast(char x)   { return 0x1000000 * int(x); }
template<> int Copy<short,  int>::cast(short x)  { return 0x10000 * int(x); }

template<> int Copy<uchar,  int>::cast(uchar x)  { return 0x1000000 * char(int(x) - 0x80); }
template<> int Copy<ushort, int>::cast(ushort x) { return 0x10000 * (int(x) - 0x8000); }
template<> int Copy<uint,   int>::cast(uint x)   { return int(int64(x) - 0x80000000L); }

}  // namespace

Copier getCopier(int encoding) {
  switch (encoding) {
   case MPG123_ENC_FLOAT_32:     return &Copy<float,  float>::copy;
   case MPG123_ENC_FLOAT_64:     return &Copy<double, float>::copy;

   case MPG123_ENC_SIGNED_16:    return &Copy<short,  int>::copy;
   case MPG123_ENC_SIGNED_32:    return &Copy<int,    int>::copy;
   case MPG123_ENC_SIGNED_8:     return &Copy<char,   int>::copy;

   case MPG123_ENC_UNSIGNED_16:  return &Copy<ushort, int>::copy;
   case MPG123_ENC_UNSIGNED_32:  return &Copy<uint,   int>::copy;
   case MPG123_ENC_UNSIGNED_8:   return &Copy<uchar,  int>::copy;

   default: return NULL;
  }
}

}  // namespace mpg123
}  // namespace rec
