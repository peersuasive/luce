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
    method( LAudioAppComponent, stop ),
    method( LAudioAppComponent, close ),
    method( LAudioAppComponent, setVolume ),
    method( LAudioAppComponent, getVolume ),
    {0,0}
};

const Luna<LAudioAppComponent>::StaticType LAudioAppComponent::statics[] = {
    {0,0}
};

LAudioAppComponent::LAudioAppComponent(lua_State *L)
    : LComponent(L, this),
      audioOpen(false),
      stopped(true),
      volume(-1.0)
{
    Ls = L;

    REGISTER_CLASS(LAudioAppComponent);
}

LAudioAppComponent::~LAudioAppComponent() {
    shutdownAudio();
}

/////// callbacks
void LAudioAppComponent::prepareToPlay( int samplesPerBlockExpected, double sampleRate ) {
    if(hasCallback("prepareToPlay")) {
        callback("prepareToPlay", 0, {samplesPerBlockExpected, sampleRate});
    }
}
int LAudioAppComponent::prepareToPlay(lua_State*){
    set("prepareToPlay");
    return 0;
}

void LAudioAppComponent::getNextAudioBlock( const AudioSourceChannelInfo& bufferToFill ) {
    if(stopped
            || !audioOpen
            || !hasCallback("getNextAudioBlock") 
            || (audioOpen && audioSourcePlayer.getCurrentSource()==nullptr) )
    {
        bufferToFill.clearActiveBufferRegion();
        return;
    }
    if(hasCallback("getNextAudioBlock")) {
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
                new LRefBase("AudioSampleBuffer", &audioBuffer)
        });
        if(volume>-1) {
            if(volume) bufferToFill.buffer->applyGain(volume);
            else bufferToFill.clearActiveBufferRegion();
        }
    }
}
int LAudioAppComponent::getNextAudioBlock(lua_State*) {
    set("getNextAudioBlock");
    return 0;
}

void LAudioAppComponent::stopPlaying() {
    stopped = true;
}
int LAudioAppComponent::stop(lua_State*) {
    stopPlaying();
    return 0;
}
void LAudioAppComponent::shutdownAudio() {
    stopPlaying();
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

int LAudioAppComponent::close(lua_State*) {
    shutdownAudio();
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
    if(!stopped) {
        lua_pushnil(L);
        lua_pushliteral(L, "player already started");
        return 2;
    }
    if(audioOpen && audioSourcePlayer.getCurrentSource()==nullptr) {
        audioSourcePlayer.setSource(this);
    }
    stopped = false;
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
    if(hasCallback("releaseResources"))
        callback("releaseResources");
}
int LAudioAppComponent::releaseResources(lua_State*){
    set("releaseResources");
    return 0;
}
