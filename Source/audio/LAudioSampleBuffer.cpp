/************************************************************

 LAudioSampleBuffer.cpp

    @author Christophe Berbizier (cberbizier@peersuasive.com)
    @license GPLv3
    @copyright 


(c) 2014, Peersuasive Technologies

*************************************************************/

#include "LAudioSampleBuffer_inh.h"

const char LAudioSampleBuffer::className[] = "LAudioSampleBuffer";
const Luna<LAudioSampleBuffer>::PropertyType LAudioSampleBuffer::properties[] = {
    {"sample", &LAudioSampleBuffer::getSample, &LAudioSampleBuffer::setSample},
    {0,0}
};
const Luna<LAudioSampleBuffer>::FunctionType LAudioSampleBuffer::methods[] = {
    method( LAudioSampleBuffer, getNumChannels ),
    method( LAudioSampleBuffer, getNumSamples ),
    method( LAudioSampleBuffer, getReadPointer ),
    method( LAudioSampleBuffer, setData ), // getWritePointer
    method( LAudioSampleBuffer, getArrayOfReadPointers ),
    method( LAudioSampleBuffer, setArrayOfData ), // getArrayOfWritePointers
    method( LAudioSampleBuffer, setSize ),
    method( LAudioSampleBuffer, setDataToReferTo ),
    method( LAudioSampleBuffer, makeCopyOf ),
    method( LAudioSampleBuffer, clear ),
    method( LAudioSampleBuffer, hasBeenCleared ),
    method( LAudioSampleBuffer, getSample ),
    method( LAudioSampleBuffer, setSample ),
    method( LAudioSampleBuffer, addSample ),
    method( LAudioSampleBuffer, applyGain ),
    method( LAudioSampleBuffer, applyGainRamp ),
    method( LAudioSampleBuffer, addFrom ),
    method( LAudioSampleBuffer, addFromWithRamp ),
    method( LAudioSampleBuffer, copyFrom ),
    method( LAudioSampleBuffer, copyFromWithRamp ),
    method( LAudioSampleBuffer, findMinMax ),
    method( LAudioSampleBuffer, getMagnitude ),
    method( LAudioSampleBuffer, getRMSLevel ),
    method( LAudioSampleBuffer, reverse ),

    {0,0}
};

const Luna<LAudioSampleBuffer>::StaticType LAudioSampleBuffer::statics[] = {
    {0,0}
};

LAudioSampleBuffer::LAudioSampleBuffer(lua_State *L)
    : LBase(L, "LAudioSampleBuffer", true),
      AudioSampleBuffer()
{
}

LAudioSampleBuffer::LAudioSampleBuffer(lua_State *L, const AudioSampleBuffer& class_) noexcept
    : LBase(L, "LAudioSampleBuffer", true),
      AudioSampleBuffer( class_ )
{
}

LAudioSampleBuffer::LAudioSampleBuffer(lua_State *L, int numChannels_, int numSamples_) noexcept
    : LBase(L, "LAudioSampleBuffer", true),
      AudioSampleBuffer( numChannels_, numSamples_ )
{
}
LAudioSampleBuffer::LAudioSampleBuffer(lua_State *L, float *const *data, int numChannels_, int numSamples_) noexcept
    : LBase(L, "LAudioSampleBuffer", true),
      AudioSampleBuffer( data, numChannels_, numSamples_ )
{
}
LAudioSampleBuffer::LAudioSampleBuffer(lua_State *L, float *const *data, int numChannels_, int startSample_, int numSamples_) noexcept
    : LBase(L, "LAudioSampleBuffer", true),
      AudioSampleBuffer( data, numChannels_, startSample_, numSamples_ )
{
}
int LAudioSampleBuffer::lnew(lua_State *L) {
    int total = lua_gettop(L)-1;
    switch(total) {
        case 0: //
            return LUA::storeAndReturnUserdata<LAudioSampleBuffer>(new LAudioSampleBuffer(L));
        case 1: // &other
            if(LUCE::luce_isofclass(LAudioSampleBuffer,2))
                return LUA::storeAndReturnUserdata<LAudioSampleBuffer>(
                    new LAudioSampleBuffer(L, *LUA::from_luce<LAudioSampleBuffer>(2)) );
            break;
        case 2: {// int, int
            int numChannels_ = LUA::getNumber();
            int numSamples_ = LUA::getNumber();
            return LUA::storeAndReturnUserdata<LAudioSampleBuffer>( new LAudioSampleBuffer(L, numChannels_, numSamples_) );
            }
        case 3: // float *const *data, int, int; float *const *data, int, int, int
        case 4: {
            float *const *data = (float *const *)lua_touserdata(L,2); lua_remove(L,2);
            int numChannels_ = LUA::getNumber();
            int numSamples_ = LUA::getNumber();
            if(lua_isnoneornil(L,2))
                return LUA::storeAndReturnUserdata<LAudioSampleBuffer>( new LAudioSampleBuffer(L, data, numChannels_, numSamples_) );
            int startSample_ = numSamples_;
            numSamples_ = LUA::getNumber();
            return LUA::storeAndReturnUserdata<LAudioSampleBuffer>( new LAudioSampleBuffer(L, data, numChannels_, startSample_, numSamples_) );
            }
    }
    LUCE::luce_error("LAudioSampleBuffer: invalid constructor.");
    return 0;
}

LAudioSampleBuffer::~LAudioSampleBuffer() {}

int LAudioSampleBuffer::getNumChannels ( lua_State* ) {
    return LUA::returnNumber( AudioSampleBuffer::getNumChannels() );
}

int LAudioSampleBuffer::getNumSamples ( lua_State* ) {
    return LUA::returnNumber( AudioSampleBuffer::getNumSamples() );
}

int LAudioSampleBuffer::getReadPointer ( lua_State *L ) {
    int channelNumber = LUA::getNumber<int>(2);
    int sampleIndex = LUA::checkAndGetNumber<int>(2,0);
    const float *buffer = AudioSampleBuffer::getReadPointer(channelNumber, sampleIndex);
    int size = AudioSampleBuffer::getNumSamples() - sampleIndex;
    LUCE::luce_pushtable(buffer, size);
    buffer = nullptr;
    return 1;
}

// getWritePointer
int LAudioSampleBuffer::setData( lua_State *L ) {
    int channelNumber = LUA::getNumber(2);
    int sampleIndex = LUA::getNumber(2);
    if(!lua_istable(L,2)) {
        lua_pushnil(L);
        lua_pushliteral(L, "LAudioSampleBuffer: error: setData: no data provided");
        //lua_error(L);
        return 2;
    }
    int len = lua_objlen(L,2);
    int size = AudioSampleBuffer::getNumSamples() - sampleIndex;
    if(len!=size) {
        lua_pushnil(L);
        lua_pushfstring(L, "LAudioSampleBuffer: error: setData: expected array of size %d, got %d", size, len);
        //lua_error(L);
        return 2;
    }
    float *data = AudioSampleBuffer::getWritePointer(channelNumber, sampleIndex);
    for(int i=1,j=sampleIndex;i<=len;++i,++j) {
        lua_rawgeti(L, -1, i);
        data[j] = (float)lua_tonumber(L,-1);
        lua_pop(L,1);
    }
    data = nullptr;
    lua_pop(L,1);
    lua_pushboolean(L, true);
    return 1;
}

int LAudioSampleBuffer::getArrayOfReadPointers ( lua_State *L ) {
    int channels = AudioSampleBuffer::getNumChannels();
    int samples  = AudioSampleBuffer::getNumSamples();
    const float **array= AudioSampleBuffer::getArrayOfReadPointers();
    lua_createtable(L, channels, 0);
    for(int i=0,j=1;i<channels;++i,++j) {
        lua_pushnumber(L,j);
        LUCE::luce_pushtable( array[i], samples );
        lua_settable(L, -3);
    }
    return 1;
}

// getArrayOfWritePointers
int LAudioSampleBuffer::setArrayOfData ( lua_State *L ) {
    if(!lua_istable(L,2)) {
        lua_pushnil(L);
        lua_pushfstring(L,"LAudioSampleBuffer: error in setArrayOfData: expected table, got %s\n",
                lua_typename(L,lua_type(L,2)));
        return 2;
    }
    int channels = AudioSampleBuffer::getNumChannels();
    int samples = AudioSampleBuffer::getNumSamples();
    
    int dataSize = lua_objlen(L,2);
    if(dataSize != channels) {
        lua_pushnil(L);
        lua_pushfstring(L,"LAudioSampleBuffer: error in setArrayOfData: wrong number of elements in data: expected %d, got %d\n", 
                channels, dataSize);
        return 2;
    }

    float **array = AudioSampleBuffer::getArrayOfWritePointers();
    for(int channel = 0, i=1; channel<channels; ++channel, ++i) {
        lua_rawgeti(L, 2, i);
        // if(lua_isnoneornil(L,-1)) { ERROR; continue; }
        //int len = lua_objlen(L, -1); // should check array size vs numSamples... or let it to the user...
        //if(len!=samples) std::cout << "WARNING: provided number of samples differs with numSamples"a
        for (int sample = 0, j=1; sample<samples; ++sample, ++j) {
            lua_rawgeti(L,-1,j);
            float v = (float)lua_tonumber(L,-1); lua_pop(L,1);
            array[channel][sample] = v;
        }
        lua_pop(L,1);
    }
    lua_pop(L,1);
    lua_pushboolean(L,true);
    return 1;
}

int LAudioSampleBuffer::setSize ( lua_State* ) {
    int newNumChannels = LUA::getNumber<int>(2);
    int newNumSamples = LUA::getNumber<int>(2);
    bool keepExistingContent = LUA::checkAndGetBoolean(2, false);
    bool clearExtraSpace = LUA::checkAndGetBoolean(2, false);
    bool avoidReallocating = LUA::checkAndGetBoolean(2, false);
    AudioSampleBuffer::setSize( newNumChannels, newNumSamples, keepExistingContent, clearExtraSpace, avoidReallocating );
    return 0;
}

int LAudioSampleBuffer::setDataToReferTo ( lua_State *L ) {
    int newNumChannels = LUA::getNumber<int>(2);
    int newNumSamples = LUA::getNumber<int>(2);
    float ** dataToReferTo = (float**)lua_touserdata(L,2);

    AudioSampleBuffer::setDataToReferTo( dataToReferTo, newNumChannels, newNumSamples );
    return 0;
}

int LAudioSampleBuffer::makeCopyOf ( lua_State* ) {
    AudioSampleBuffer::makeCopyOf(*LUA::from_luce<LAudioSampleBuffer>(2));
    return 0;
}

int LAudioSampleBuffer::clear ( lua_State *L ) {
    int n = lua_gettop(L)-1;
    if(!n) {
        AudioSampleBuffer::clear();
    } else if(n==2) {
        int startSample = LUA::getNumber<int>(2);
        int numSamples = LUA::getNumber<int>(2);
        AudioSampleBuffer::clear(startSample, numSamples);
    } else if(n==3) {
        int channel = LUA::getNumber<int>(2);
        int startSample = LUA::getNumber<int>(2);
        int numSamples = LUA::getNumber<int>(2);
        AudioSampleBuffer::clear( channel, startSample, numSamples );
    } else {
        lua_pushnil(L);
        lua_pushliteral(L, "LAudioSampleBuffer::clear: wrong number of arguments");
        return 2;
    }
    lua_pushboolean(L,true);
    return 1;
}

int LAudioSampleBuffer::hasBeenCleared ( lua_State* ) {
    return LUA::returnBoolean( AudioSampleBuffer::hasBeenCleared() );
}

int LAudioSampleBuffer::getSample ( lua_State *L ) {
    int channel = LUA::getNumber<int>(2);
    int sampleIndex = LUA::getNumber<int>(2);
    lua_pushnumber(L, AudioSampleBuffer::getSample(channel, sampleIndex));
    return 1;
}
int LAudioSampleBuffer::setSample ( lua_State* ) {
    int destChannel = LUA::getNumber<int>(2);
    int destSample = LUA::getNumber<int>(2);
    float newValue = LUA::getNumber<float>(2);
    AudioSampleBuffer::setSample(destChannel, destSample, newValue);
    return 0;
}

int LAudioSampleBuffer::addSample ( lua_State* ) {
    int destChannel = LUA::getNumber<int>(2);
    int destSample = LUA::getNumber<int>(2);
    float newValue = LUA::getNumber<float>(2);
    AudioSampleBuffer::addSample(destChannel, destSample, newValue);
    return 0;
}

int LAudioSampleBuffer::applyGain ( lua_State *L ) {
    int n = lua_gettop(L)-1;
    if(n==1) {
        float gain = LUA::getNumber<float>(2);
        AudioSampleBuffer::applyGain( gain );
    }else if(n==3) {
        int channel = LUA::getNumber<int>(2);
        int startSample = LUA::getNumber<int>(2);
        float gain = LUA::getNumber<float>(2);
        AudioSampleBuffer::applyGain( channel, startSample, gain );
    }else if(n==4) {
        int channel = LUA::getNumber<int>(2);
        int startSample = LUA::getNumber<int>(2);
        int numSamples = LUA::getNumber<int>(2);
        float gain = LUA::getNumber<float>(2);
        AudioSampleBuffer::applyGain( channel, startSample, numSamples, gain );
    }else {
        lua_pushnil(L);
        lua_pushliteral(L, "LAudioSampleBuffer::applyGain: wrong number of arguments");
        return 2;
    }
    lua_pushboolean(L,true);
    return 1;
}

int LAudioSampleBuffer::applyGainRamp ( lua_State *L ) {
    int n = lua_gettop(L)-1;
    if(n==4) {
        int startSample = LUA::getNumber<int>(2);
        int numSamples = LUA::getNumber<int>(2);
        float startGain = LUA::getNumber<float>(2);
        float endGain = LUA::getNumber<float>(2);
        AudioSampleBuffer::applyGainRamp( startSample, numSamples, startGain, endGain );
    }else if(n==5) {
        int channel = LUA::getNumber<int>(2);
        int startSample = LUA::getNumber<int>(2);
        int numSamples = LUA::getNumber<int>(2);
        float startGain = LUA::getNumber<float>(2);
        float endGain = LUA::getNumber<float>(2);
        AudioSampleBuffer::applyGainRamp( channel, startSample, numSamples, startGain, endGain );
    } else {
        lua_pushnil(L);
        lua_pushliteral(L, "LAudioSampleBuffer::applyGain: wrong number of arguments");
        return 2;
    }
    lua_pushboolean(L,true);
    return 1;
}

int LAudioSampleBuffer::addFrom ( lua_State *L ) {
    int n = lua_gettop(L)-1;
    if (n>5) {
        int destChannel = LUA::getNumber<int>(2);
        int destStartSample = LUA::getNumber<int>(2);
        AudioSampleBuffer source = *LUA::from_luce<LAudioSampleBuffer>(2);
        int sourceChannel = LUA::getNumber<int>(2);
        int sourceStartSample = LUA::getNumber<int>(2);
        int numSamples = LUA::getNumber<int>(2);
        float gainToApplyToSource = LUA::checkAndGetNumber<float>(2,1.0);

        AudioSampleBuffer::addFrom( destChannel, destStartSample, source,
                sourceChannel, sourceStartSample, numSamples, gainToApplyToSource );

    } else if(n>3) {
        int destChannel = LUA::getNumber<int>(2);
        int destStartSample = LUA::getNumber<int>(2);
        int numSamples = LUA::getNumber<int>(3);
        float gainToApplyToSource = LUA::checkAndGetNumber<float>(3,1.0);

        float source[numSamples];
        for(int sample = 0, i=1; sample<numSamples;++sample,++i) {
            lua_rawgeti(L, 2, i);
            float v = (float)lua_tonumber(L,-1); lua_pop(L,1);
            source[sample] = v;
        }
        lua_remove(L,2);
        AudioSampleBuffer::addFrom( destChannel, destStartSample, source, numSamples, gainToApplyToSource);
    } else { // ERROR
        lua_pushnil(L);
        lua_pushliteral(L, "LAudioSampleBuffer::addFrom: wrong number of arguments.");
        return 2;
    }

    lua_pushboolean(L,true);
    return 1;
}

int LAudioSampleBuffer::addFromWithRamp ( lua_State *L ) {
    int destChannel = LUA::getNumber<int>(2);
    int destStartSample = LUA::getNumber<int>(2);
    int numSamples = LUA::getNumber<int>(3);
    float startGain = LUA::getNumber<float>(3);
    float endGain = LUA::getNumber<float>(3);

    float source[numSamples];
    for(int sample = 0, i=1; sample<numSamples;++sample,++i) {
        lua_rawgeti(L, 2, i);
        float v = (float)lua_tonumber(L,-1); lua_pop(L,1);
        source[sample] = v;
    }
    lua_remove(L,2);
    AudioSampleBuffer::addFromWithRamp( destChannel, destStartSample, source, numSamples, startGain, endGain );
    return 0;
}

int LAudioSampleBuffer::copyFrom ( lua_State *L ) {
    int n = lua_gettop(L)-1;
    if (n==4) {
        int destChannel = LUA::getNumber<int>(2);
        int destStartSample = LUA::getNumber<int>(2);
        AudioSampleBuffer source = *LUA::from_luce<LAudioSampleBuffer>(2);
        int sourceChannel = LUA::getNumber<int>(2);
        int sourceStartSample = LUA::getNumber<int>(2);
        int numSamples = LUA::getNumber<int>(2);
        AudioSampleBuffer::copyFrom( destChannel, destStartSample, source,
                sourceChannel, sourceStartSample, numSamples );

    } else if(n>4) {
        int destChannel = LUA::getNumber<int>(2);
        int destStartSample = LUA::getNumber<int>(2);
        int numSamples = LUA::getNumber<int>(3);
        float gain = LUA::checkAndGetNumber<float>(3,0);

        float source[numSamples];
        for(int sample = 0, i=1; sample<numSamples;++sample,++i) {
            lua_rawgeti(L, 2, i);
            float v = (float)lua_tonumber(L,-1); lua_pop(L,1);
            source[sample] = v;
        }
        lua_remove(L,2);
        if(gain) {
            AudioSampleBuffer::copyFrom( destChannel, destStartSample, source, numSamples, gain);
        }else{
            AudioSampleBuffer::copyFrom( destChannel, destStartSample, source, numSamples);
        }
    } else { // ERROR
        lua_pushnil(L);
        lua_pushliteral(L, "LAudioSampleBuffer::copyFrom: wrong number of arguments.");
        return 2;
    }
    lua_pushboolean(L,true);
    return 1;
}

int LAudioSampleBuffer::copyFromWithRamp ( lua_State *L ) {
    int destChannel = LUA::getNumber<int>(2);
    int destStartSample = LUA::getNumber<int>(2);
    int numSamples = LUA::getNumber<int>(3);
    float startGain = LUA::getNumber<float>(3);
    float endGain = LUA::getNumber<float>(3);

    float source[numSamples];
    for(int sample = 0, i=1; sample<numSamples;++sample,++i) {
        lua_rawgeti(L, 2, i);
        float v = (float)lua_tonumber(L,-1); lua_pop(L,1);
        source[sample] = v;
    }
    lua_remove(L,2);
    AudioSampleBuffer::copyFromWithRamp( destChannel, destStartSample, source, numSamples, startGain, endGain );
    return 0;
}

int LAudioSampleBuffer::findMinMax ( lua_State* ) {
    int channel = LUA::getNumber<int>(2);
    int startSample = LUA::getNumber<int>(2);
    int numSamples = LUA::getNumber<int>(2);
    return LUCE::luce_pushtable( AudioSampleBuffer::findMinMax( channel, startSample, numSamples ) );
}

int LAudioSampleBuffer::getMagnitude ( lua_State *L ) {
    int startSample = LUA::getNumber<int>(2);
    int numSamples = LUA::getNumber<int>(2);
    float mag;
    if(lua_isnoneornil(L,2)) {
        mag = AudioSampleBuffer::getMagnitude( startSample, numSamples );
    }else{
        int channel = startSample;
        startSample = numSamples;
        numSamples = LUA::getNumber<int>(2);
        mag = AudioSampleBuffer::getMagnitude( channel, startSample, numSamples );
    }
    lua_pushnumber(L, mag);
    return 1;
}

int LAudioSampleBuffer::getRMSLevel ( lua_State *L ) {
    int channel = LUA::getNumber<int>(2);
    int startSample = LUA::getNumber<int>(2);
    int numSamples = LUA::getNumber<int>(2);
    lua_pushnumber(L, AudioSampleBuffer::getRMSLevel( channel, startSample, numSamples ));
    return 1;
}

int LAudioSampleBuffer::reverse ( lua_State *L ) {
    int startSample = LUA::getNumber<int>(2);
    int numSamples = LUA::getNumber<int>(2);
    if(lua_isnoneornil(L,2)) {
        AudioSampleBuffer::reverse( startSample, numSamples );
    } else {
        int channel = startSample;
        startSample = numSamples;
        numSamples = LUA::getNumber<int>(2);
        AudioSampleBuffer::reverse( channel, startSample, numSamples );
    }
    return 0;
}
