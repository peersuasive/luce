#ifndef __LUCE_AUDIO
#define __LUCE_AUDIO

//#include "../../../JuceLibraryCode/modules/juce_audio_basics/juce_audio_basics.h"
//#include "../../../JuceLibraryCode/modules/juce_events/juce_events.h"
#include "../../../JuceLibraryCode/modules/juce_core/juce_core.h"
#include "../../../JuceLibraryCode/modules/juce_audio_devices/juce_audio_devices.h"

namespace juce
{

#include "audio/luce_WebBufferedInputStream.h"
#include "audio/luce_BufferingAudioInfiniteSource.h"
#include "audio/luce_AudioTransportInfiniteSource.h"
#include "audio/luce_MP3AudioFormatInfinite.h"

#if LUCE_MPG123
#include "audio/rec/base/Disallow.h"
#include "audio/rec/mpg123/Copier.h"
#include "audio/rec/mpg123/Mpg123.h"
#include "audio/rec/mpg123/CreateReader.h"
#include "audio/rec/mpg123/NewHandle.h"
#include "audio/rec/mpg123/Format.h"
#include "audio/rec/mpg123/Reader.h"
#include "audio/rec/mpg123/Tags.h"
#endif

}

#endif // __LUCE_AUDIO
