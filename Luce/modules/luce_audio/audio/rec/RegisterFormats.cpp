//#include "../JuceLibraryCode/JuceHeader.h"
#include "RegisterFormats.h"

namespace juce {

namespace {

void registerSoftwareFormats(AudioFormatManager* afm, ReadWrite rw) {
  afm->registerFormat(new WavAudioFormat(), true);
  afm->registerFormat(new AiffAudioFormat(), false);

#if JUCE_USE_MP3AUDIOFORMAT
  if (rw == READ || JUCE_USE_MP3AUDIOFORMAT_WRITE)
    afm->registerFormat(new MP3AudioFormat(), false);
#endif
}

void registerOptionalFormats(AudioFormatManager* afm) {
#if JUCE_USE_FLAC
  afm->registerFormat(new FlacAudioFormat(), false);
#endif

#if JUCE_USE_OGGVORBIS
  afm->registerFormat(new OggVorbisAudioFormat(), false);
#endif
}

}  // namespace

void registerFormats(AudioFormatManager* afm, ReadWrite rw) {
  registerOptionalFormats(afm);

#if (JUCE_MAC || JUCE_IOS)
  if (rw == READ || JUCE_USE_COREAUDIO_WRITE)
    afm->registerFormat(new CoreAudioFormat(), false);
  else

#elif JUCE_USE_WINDOWS_MEDIA_FORMAT
  if (rw == READ || JUCE_USE_WINDOWSMEDIA_WRITE)
    afm->registerFormat(new WindowsMediaAudioFormat(), false);
  else

#endif
    registerSoftwareFormats(afm, rw);
}

AudioFormatManager* createAudioFormatManager(ReadWrite rw) {
  ScopedPointer<AudioFormatManager> afm(new AudioFormatManager());
  registerFormats(afm, rw);
  return afm.release();
}

}  // namespace juce

