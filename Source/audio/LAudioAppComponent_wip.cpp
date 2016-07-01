/************************************************************

 LAudioAppComponent.cpp

    @author Christophe Berbizier (cberbizier@peersuasive.com)
    @license GPLv3
    @copyright 


(c) 2014, Peersuasive Technologies

*************************************************************/

#include "LAudioAppComponent_inh.h"

const char LAudioAppComponent::className[] = "LAudioAppComponent";
const Luna<LAudioAppComponent>::PropertyType LAudioAppComponent::properties[] = {
    {"volume", &LAudioAppComponent::getVolume, &LAudioAppComponent::setVolume},
    {0,0}
};
const Luna<LAudioAppComponent>::FunctionType LAudioAppComponent::methods[] = {
    method( LAudioAppComponent, setAudioChannels ),
    method( LAudioAppComponent, prepareToPlay ),
    method( LAudioAppComponent, releaseResources ),
    method( LAudioAppComponent, getNextAudioBlock ),
    method( LAudioAppComponent, start ),
    method( LAudioAppComponent, close ),
    method( LAudioAppComponent, stop ),
    method( LAudioAppComponent, play ),
    method( LAudioAppComponent, pause ),
    method( LAudioAppComponent, setVolume ),
    method( LAudioAppComponent, getVolume ),
    method( LAudioAppComponent, isStopped ),
    {0,0}
};

const Luna<LAudioAppComponent>::StaticType LAudioAppComponent::statics[] = {
    {0,0}
};

LAudioAppComponent::LAudioAppComponent(lua_State *L)
    : LComponent(L, this),
      stopped(true),
      audioOpen(false),
      hasPlayer(false),
      totalLength(0),
      readerSource(nullptr),
      timeSlice("LAudioAppComponentTimeSlice"),
      volume(-1.0)
{
    Ls = L;

    REGISTER_CLASS(LAudioAppComponent);
}

LAudioAppComponent::~LAudioAppComponent() {
    if(!stopped)stopPlaying();
    shutdownAudio();
}

/////// callbacks
void LAudioAppComponent::prepareToPlay( int samplesPerBlockExpected, double sampleRate ) {
    if(hasPlayer) {
        transportSource.prepareToPlay(samplesPerBlockExpected, sampleRate);
    }
    if(hasCallback("prepareToPlay")) {
        callback("prepareToPlay", 0, {samplesPerBlockExpected, sampleRate});
    }
}
int LAudioAppComponent::prepareToPlay(lua_State*){
    set("prepareToPlay");
    return 0;
}

void LAudioAppComponent::getNextAudioBlock( const AudioSourceChannelInfo& bufferToFill ) {
    if(stopped || (audioOpen && audioSourcePlayer.getCurrentSource()==nullptr) ) {
        bufferToFill.clearActiveBufferRegion();
        return;
    } else if(hasPlayer) {
        if(transportSource.hasStreamFinished()) {
            bufferToFill.clearActiveBufferRegion();
            stopPlaying();
            return;
        }
        if(volume) {
            transportSource.getNextAudioBlock(bufferToFill);
            if(volume>0.0)bufferToFill.buffer->applyGain(volume);
        } else {
            bufferToFill.clearActiveBufferRegion();
        }
    }

    if(hasCallback("getNextAudioBlock")) {
        int currentPos = 0;
        if(hasPlayer) currentPos = transportSource.getCurrentPosition();
        //const MessageManagerLock mmLock;
        MessageManagerLock mml (Thread::getCurrentThread());
            if (! mml.lockWasGained()) {
                DBG("CAN'T GET LOCK");
                return; // another thread is trying to kill us!
            }
        LAudioSampleBuffer audioBuffer(Ls, *bufferToFill.buffer);
        callback("getNextAudioBlock", 0, {
                bufferToFill.startSample,
                bufferToFill.numSamples,
                bufferToFill.buffer->getNumChannels(),
                new LRefBase("AudioSampleBuffer", &audioBuffer),
                currentPos,
                totalLength
        });
    }
}
int LAudioAppComponent::getNextAudioBlock(lua_State*) {
    set("getNextAudioBlock");
    return 0;
}

void LAudioAppComponent::shutdownAudio() {
    if(!audioOpen)return;
    if(audioSourcePlayer.getCurrentSource()!=nullptr) {
        audioSourcePlayer.setSource (nullptr);
    }
    if(audioOpen) {
        deviceManager.removeAudioCallback (&audioSourcePlayer);
        deviceManager.closeAudioDevice();
    }
    audioOpen = false;
}
void LAudioAppComponent::stopPlaying(bool no_reset) {
    if(stopped)return;
    stopped = true;
    if(hasPlayer) {
        transportSource.stop();
        if(!no_reset) transportSource.setPosition(0.0);
    }
}
void LAudioAppComponent::togglePause() {
    if(!hasPlayer || !audioOpen) {
        DBG("missing player or audio's not opened!");
        return;
    }
    if(stopped) {
        transportSource.start();
        stopped = false;
    }
    else stopPlaying(true);
}

int LAudioAppComponent::isStopped( lua_State *L ) {
    lua_pushboolean(L, stopped);
    return 1;
}
int LAudioAppComponent::stop ( lua_State* ) {
    stopPlaying();
    return 0;
}

int LAudioAppComponent::pause( lua_State* ) {
    togglePause();
    return LUA::returnBoolean(!stopped);
}
int LAudioAppComponent::play(lua_State *L) {
    return pause(L);
}

int LAudioAppComponent::close(lua_State*) {
    shutdownAudio();
    if(!stopped)stopPlaying();
    if(hasPlayer) formatManager.clearFormats();
    return 0;
}

int LAudioAppComponent::getVolume(lua_State*) {
    return LUA::returnNumber(volume);
}
int LAudioAppComponent::setVolume(lua_State*) {
    volume = LUA::getNumber<float>(2);
    return 0;
}

int LAudioAppComponent::start(lua_State *L) {
    // on va accepter des paramètres: une string -> un fichier,
    // une URL, well, une URL
    // la différence: le fichier, on le lit avec un player cash,
    // voire même, on retourne une classe qui hérite du player
    // les URLs, on les lit avec notre classes modifiées pour accepter de flux infinis
    int n = lua_gettop(L)-1;
    if(!n) {
        stopped = false;
        audioSourcePlayer.setSource(this);
    } else {
        #if JUCE_USE_MP3AUDIOFORMAT
        formatManager.registerFormat(new MP3AudioFormatInfinite(), false);
        //#else
        //#if LUCE_MPG123
        //formatManager.registerFormat(new rec::mpg123::Format(), false);
        //#endif
        #endif
        formatManager.registerBasicFormats();
        int bufferSize = 0;
        TimeSliceThread *sliceBuffer = nullptr;
        ScopedPointer<AudioFormatReader> reader;

        if(lua_type(L,2)==LUA_TSTRING) {
            const char *filePath = lua_tostring(L,2); lua_remove(L,2);
            File file(filePath);
            #if LUCE_MPG123
            if (InputStream* const in = file.createInputStream())
                reader = rec::mpg123::Format().createReaderFor(in, true);
            #else
            reader = formatManager.createReaderFor(file);
            #endif
        } else if (LUCE::luce_isofclass(LURL,2)) {
            //bufferSize = 20480;
            //bufferSize = 32768;
            bufferSize = 8192;
            int webBufferSize = 65536;
            URL *url = LUA::from_luce<LURL>(2);
            ScopedPointer<InputStream> stream(url->createInputStream(false));
            ScopedPointer<WebBufferedInputStream> input(
                    new WebBufferedInputStream(stream.release(), webBufferSize, true, webBufferSize*2));
            #if LUCE_MPG123
            std::cout << "looking for reader..." << std::endl;
            reader = rec::mpg123::Format().createReaderFor(input.release(), true);
            std::cout << "reader found!" << std::endl;
            #else
            #if JUCE_USE_MP3AUDIOFORMAT
            //reader = MP3AudioFormatInfinite().createReaderFor(input.release(), true);
            //reader = MP3AudioFormat().createReaderFor(input.release(), true);
            reader = formatManager.createReaderFor(input.release());
            #else
            reader = formatManager.createReaderFor(input.release());
            #endif
            #endif
            //if(reader!=nullptr && bufferSize) {
            //    std::cout << "format name: " << reader->getFormatName() << std::endl;
            //    timeSlice.startThread(1);
            //    sliceBuffer = &timeSlice;
            //}
        } else {
            lua_pushnil(L);
            lua_pushfstring(L,"Unknown argument type for LAudioAppComponent::start: expected String or URL, got %s\n",
                    lua_typename(L,lua_type(L,2)));
            return 2;
        }
    
        if(reader!=nullptr) {
            double sampleRate = reader->sampleRate;
            ScopedPointer<AudioFormatReaderSource> newSource(new AudioFormatReaderSource(reader.release(), true));
            hasPlayer = true;
            //transportSource.setSource(newSource, bufferSize, sliceBuffer, sampleRate);
            transportSource.setSource(newSource, 0, nullptr, sampleRate);
            readerSource = newSource.release();
            audioSourcePlayer.setSource(this);
            totalLength = transportSource.getLengthInSeconds();
            //stopped = false;
            //transportSource.start();
        } else {
            lua_pushnil(L);
            lua_pushliteral(L, "ERROR: couldn't start reader");
            return 2;
        }
    }
    lua_pushboolean(L, true);
    return 1;
}

int LAudioAppComponent::setAudioChannels(lua_State *L) {
    if(audioOpen) {
        lua_pushnil(L);
        lua_pushliteral(L, "audio channels already set.");
        return 2;
    }
    int numInputChannels = LUA::checkAndGetNumber<int>(2, 0);
    int numOutputChannels = LUA::checkAndGetNumber<int>(2, 2);
    String audioError = deviceManager.initialise (numInputChannels, numOutputChannels, nullptr, true);
    jassert (audioError.isEmpty());
    if(audioError.isEmpty()) {
        deviceManager.addAudioCallback (&audioSourcePlayer);
        audioOpen = true;
        lua_pushboolean(L, true);
        return 1;
    }else{
        lua_pushnil(L);
        lua_pushstring(L, audioError.toRawUTF8());
        return 2;
    }
}

void LAudioAppComponent::releaseResources() {
    if(hasPlayer) {
        transportSource.releaseResources();
        hasPlayer = false;
    }
    if(hasCallback("releaseResources"))
        callback("releaseResources");
}
int LAudioAppComponent::releaseResources(lua_State*){
    set("releaseResources");
    return 0;
}
