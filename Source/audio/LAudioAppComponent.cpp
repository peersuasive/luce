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
    {0,0}
};
const Luna<LAudioAppComponent>::FunctionType LAudioAppComponent::methods[] = {
    method( LAudioAppComponent, setAudioChannels ),
    method( LAudioAppComponent, prepareToPlay ),
    method( LAudioAppComponent, releaseResources ),
    method( LAudioAppComponent, getNextAudioBlock ),
    method( LAudioAppComponent, start ),
    method( LAudioAppComponent, stop ),
    {0,0}
};

const Luna<LAudioAppComponent>::StaticType LAudioAppComponent::statics[] = {
    {0,0}
};

LAudioAppComponent::LAudioAppComponent(lua_State *L)
    : LComponent(L, this)
{
    Ls = L;
    REGISTER_CLASS(LAudioAppComponent);
}

LAudioAppComponent::~LAudioAppComponent() {
    shutdownAudio();
}

/////// callbacks
void LAudioAppComponent::prepareToPlay( int samplesPerBlockExpected, double sampleRate ) {
    if(hasCallback("prepareToPlay"))
        callback("prepareToPlay", 0, {samplesPerBlockExpected, sampleRate});
}
int LAudioAppComponent::prepareToPlay(lua_State*){
    set("prepareToPlay");
    return 0;
}

void LAudioAppComponent::getNextAudioBlock( const AudioSourceChannelInfo& bufferToFill ) {
    if(audioSourcePlayer.getCurrentSource()==nullptr) {
        bufferToFill.clearActiveBufferRegion();
        return;
    }
    LAudioSampleBuffer audioBuffer(Ls, *bufferToFill.buffer);
    callback("getNextAudioBlock", 0, {
            bufferToFill.startSample,
            bufferToFill.numSamples,
            bufferToFill.buffer->getNumChannels(),
            new LRefBase("AudioSampleBuffer", &audioBuffer),
    });
}
int LAudioAppComponent::getNextAudioBlock(lua_State*){
    set("getNextAudioBlock");
    return 0;
}

void LAudioAppComponent::shutdownAudio() {
    if(audioSourcePlayer.getCurrentSource()!=nullptr) {
        audioSourcePlayer.setSource (nullptr);
        deviceManager.removeAudioCallback (&audioSourcePlayer);
        deviceManager.closeAudioDevice();
    }
}
int LAudioAppComponent::stop ( lua_State* ) {
    shutdownAudio();
    return 0;
}

int LAudioAppComponent::start(lua_State *L) {
    audioSourcePlayer.setSource (this);
    return 0;
}

int LAudioAppComponent::setAudioChannels ( lua_State *L ) {
    int numInputChannels = LUA::checkAndGetNumber<int>(2, 0);
    int numOutputChannels = LUA::checkAndGetNumber<int>(2, 2);
    String audioError = deviceManager.initialise (numInputChannels, numOutputChannels, nullptr, true);
    jassert (audioError.isEmpty());
    if(audioError.isEmpty()) {
        deviceManager.addAudioCallback (&audioSourcePlayer);
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

// mouse...
/*
void LAudioAppComponent::mouseMove(const MouseEvent& e) {
    if(hasCallback("mouseMove"))
        LComponent::lmouseMove(e);
    else
        AudioAppComponent::mouseMove(e);
}

void LAudioAppComponent::mouseEnter(const MouseEvent& e) {
    if(hasCallback("mouseEnter"))
        LComponent::lmouseEnter(e);
    else
        AudioAppComponent::mouseEnter(e);
}

void LAudioAppComponent::mouseExit(const MouseEvent& e) {
    if(hasCallback("mouseExit"))
        LComponent::lmouseExit(e);
    else
        AudioAppComponent::mouseExit(e);
}

void LAudioAppComponent::mouseDown(const MouseEvent& e) {
    if(hasCallback("mouseDown"))
        LComponent::lmouseDown(e);
    else
        AudioAppComponent::mouseDown(e);
}

void LAudioAppComponent::mouseDrag(const MouseEvent& e) {
    if(hasCallback("mouseDrag"))
        LComponent::lmouseDrag(e);
    else
        AudioAppComponent::mouseDrag(e);
}

void LAudioAppComponent::mouseUp(const MouseEvent& e) {
    if(hasCallback("mouseUp"))
        LComponent::lmouseUp(e);
    else
        AudioAppComponent::mouseUp(e);
}

void LAudioAppComponent::mouseDoubleClick(const MouseEvent& e) {
    if(hasCallback("mouseDoubleClick"))
        LComponent::lmouseDoubleClick(e);
    else
        AudioAppComponent::mouseDoubleClick(e);
}

void LAudioAppComponent::mouseWheelMove(const MouseEvent& e, const MouseWheelDetails& wheel) {
    if(hasCallback("mouseWheelMove"))
        LComponent::lmouseWheelMove(e, wheel);
    else
        AudioAppComponent::mouseWheelMove(e, wheel);
}

void LAudioAppComponent::mouseMagnify(const MouseEvent& e, float scaleFactor) {
    if(hasCallback("mouseMagnify"))
        LComponent::lmouseMagnify(e, scaleFactor);
    else
        AudioAppComponent::mouseMagnify(e, scaleFactor);
}

bool LAudioAppComponent::keyPressed(const KeyPress& k) {
    if(hasCallback("keyPressed"))
        return LComponent::lkeyPressed(k);
    else
        return AudioAppComponent::keyPressed(k);
}
*/
