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
    : LComponent(L, this),
      timeSlice("TimeSlice")
{
    Ls = L;

    formatManager.registerBasicFormats();

    timeSlice.startThread();
    REGISTER_CLASS(LAudioAppComponent);
}

LAudioAppComponent::~LAudioAppComponent() {
    shutdownAudio();
}

/////// callbacks
void LAudioAppComponent::prepareToPlay( int samplesPerBlockExpected, double sampleRate ) {
    //if(hasCallback("prepareToPlay"))callback("prepareToPlay", 0, {samplesPerBlockExpected, sampleRate});

    std::cout << "prepare to play: " << samplesPerBlockExpected << ", " << sampleRate << std::endl;
    transport.prepareToPlay (samplesPerBlockExpected, sampleRate);

}
int LAudioAppComponent::prepareToPlay(lua_State*){
    set("prepareToPlay");
    return 0;
}

void LAudioAppComponent::getNextAudioBlock( const AudioSourceChannelInfo& bufferToFill ) {
    if (source == nullptr)
    {
        bufferToFill.clearActiveBufferRegion();
        return;
    }
    
    transport.getNextAudioBlock (bufferToFill);

    /*
    LAudioSampleBuffer audioBuffer(Ls, *bufferToFill.buffer);

    callback("getNextAudioBlock", 0, {
            bufferToFill.startSample,
            bufferToFill.numSamples,
            bufferToFill.buffer->getNumChannels(),
            new LRefBase("AudioSampleBuffer", &audioBuffer),
            //new LRefBase(idx)
            //new LRefBase("LTPointer", &channel1)
    });
    */

    /////////////////***************************************/////////////////////
    // on va passer
    // int bufferToFill.startSample
    // int ....numSamples
    // et
    // AudioBuffer ....buffer, à créer

    /*
    float *data = bufferToFill.buffer->getWritePointer( 0, bufferToFill.startSample );
    LPointerFloat channel1(Ls, bufferToFill.numSamples, data);
    channel1.__push_pointer(Ls);
    */
    //LPointerFloat channel1(Ls, 512);
    //channel1.__push_pointer(Ls);
    //int idx = lua_gettop(Ls);

    /*
    if(!lua_isnil(Ls,-1)) {
        int i = 0;
        for (int channel = 0; channel < bufferToFill.buffer->getNumChannels(); ++channel)
        {
            // Get a pointer to the start sample in the buffer for this audio output channel
            float* const buffer = bufferToFill.buffer->getWritePointer (channel, bufferToFill.startSample);
            
            // Fill the required number of samples with noise betweem -0.125 and +0.125
            for (int sample = 0; sample < bufferToFill.numSamples; ++sample) {
                //buffer[sample] = random.nextFloat() * 0.25f - 0.125f;
                lua_rawgeti(Ls, -1, ++i);
                buffer[sample] = (float)lua_tonumber(Ls,-1);
                lua_pop(Ls,1);
            }
            bufferToFill.buffer->applyGain(channel, bufferToFill.startSample, bufferToFill.numSamples, 0.1f);
        }
    } else {
        std::cout << "NO DATA RECEIVED !" << std::endl;
        //shutdownAudio();
        //LUCE::luce_error("Didn't receive any data from callback getNextAudioBlock!");
    }
    lua_pop(Ls,1);
    */
}
int LAudioAppComponent::getNextAudioBlock(lua_State*){
    set("getNextAudioBlock");
    return 0;
}

void LAudioAppComponent::shutdownAudio() {
    if(audioSourcePlayer.getCurrentSource()!=nullptr) {
        if(transport.isPlaying())
            transport.stop();
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
    if(lua_gettop(L)==1) {
        audioSourcePlayer.setSource (this);
    } else {
        int bufferSize = 131072;
        bufferSize = 20480;
        //bufferSize = 8192;
        // TODO: calculer le buffer minimum selon le débit/s du mp3, ie. freq, la taille du block (512) et le rate
        const char *url_source = lua_tostring(L,-1);

        ScopedPointer<InputStream> url(URL(url_source).createInputStream(false));
        ScopedPointer<BufferedInputStream> input(new BufferedInputStream(url.release(), bufferSize*2, true));
        AudioFormatReader *reader = mp3.createReaderFor(input.release(), true);
        //AudioFormatReader *reader = formatManager.createReaderFor(input.release());

        //File file(url_source);
        //ScopedPointer<MemoryInputStream> input(new MemoryInputStream(&file, file.getSize(), false));
        //AudioFormatReader *reader = formatManager.createReaderFor(file);

        if(!reader) {
            std::cout << "READER not initialised" << std::endl;
            return 0;
        }else{
            std::cout << "READER ready..." << std::endl;
        }

        audioSourcePlayer.setSource (this);
        ScopedPointer<AudioFormatReaderSource> newSource(new AudioFormatReaderSource(reader, true));

        //transport.setSource( newSource, 0, nullptr, reader->sampleRate);
        transport.setSource( newSource, bufferSize, &timeSlice, reader->sampleRate);
        source = newSource.release();

        transport.start();
    }
    return 0;
}

int LAudioAppComponent::setAudioChannels ( lua_State *L ) {
    String audioError = deviceManager.initialise (0, 2, nullptr, true);
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
/*
int LAudioAppComponent::setAudioChannels ( lua_State* ) {
    std::cout << "set audio channels..." << std::endl;
    int numInputChannels = LUA::getNumber<int>(2);
    int numOutputChannels = LUA::getNumber<int>(2);
    AudioAppComponent::setAudioChannels( numInputChannels, numOutputChannels );
    return 0;
}
*/

void LAudioAppComponent::releaseResources() {
    //if(hasCallback("releaseResources")) callback("releaseResources");

    transport.releaseResources();
}
int LAudioAppComponent::releaseResources(lua_State*){
    set("releaseResources");
    return 0;
}
