#include "LAppConfig.h"
#include "luce_audio.h"

#include "../../../JuceLibraryCode/modules/juce_core/juce_core.h"
#include "../../../JuceLibraryCode/modules/juce_core/native/juce_BasicNativeHeaders.h"

namespace juce
{
#include "audio/luce_WebBufferedInputStream.cpp"
#include "audio/luce_BufferingAudioInfiniteSource.cpp"
#include "audio/luce_AudioTransportInfiniteSource.cpp"
#include "audio/luce_MP3AudioFormatInfinite.cpp"

#if LUCE_MPG123
#include "audio/rec/mpg123/Copier.cpp"
#include "audio/rec/mpg123/CreateReader.cpp"
#include "audio/rec/mpg123/Mpg123.cpp"
#include "audio/rec/mpg123/NewHandle.cpp"
#include "audio/rec/mpg123/Reader.cpp"
#include "audio/rec/mpg123/Tags.cpp"
#endif

}

