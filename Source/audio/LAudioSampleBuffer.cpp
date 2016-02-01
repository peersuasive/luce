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
    method( LAudioSampleBuffer, getArrayOfReadPointers ),
    method( LAudioSampleBuffer, getSample ),
    method( LAudioSampleBuffer, setSample ),
    method( LAudioSampleBuffer, getMagnitude ),
    method( LAudioSampleBuffer, findMinMax ),
    method( LAudioSampleBuffer, getRMSLevel ),
    method( LAudioSampleBuffer, getNumChannels ),
    method( LAudioSampleBuffer, setData ),
    method( LAudioSampleBuffer, getNumSamples ),
    method( LAudioSampleBuffer, getReadPointer ),
    method( LAudioSampleBuffer, getArrayOfWritePointers ),
    method( LAudioSampleBuffer, hasBeenCleared ),
    method( LAudioSampleBuffer, applyGainRamp ),
    method( LAudioSampleBuffer, makeCopyOf ),
    method( LAudioSampleBuffer, reverse ),
    method( LAudioSampleBuffer, addFrom ),
    method( LAudioSampleBuffer, copyFromWithRamp ),
    method( LAudioSampleBuffer, copyFrom ),
    method( LAudioSampleBuffer, setSize ),
    method( LAudioSampleBuffer, setDataToReferTo ),
    method( LAudioSampleBuffer, addFromWithRamp ),
    method( LAudioSampleBuffer, addSample ),
    method( LAudioSampleBuffer, clear ),
    method( LAudioSampleBuffer, applyGain ),
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


/////// getters/setters
int LAudioSampleBuffer::getSample ( lua_State *L ) {
    int channel = LUA::getNumber<int>(2);
    int sampleIndex = LUA::getNumber<int>(2);
    // CHECK
    // return LUA::storeAndReturnUserdata<Lfloat>( new Lfloat(L,
    //     AudioSampleBuffer::getSample( channel, sampleIndex )
    // ));
    lua_settop(LUA::Get(), 1); // added by TODO
    return LUA::TODO_OBJECT( "float getSample( channel, sampleIndex )" );
}
int LAudioSampleBuffer::setSample ( lua_State* ) {
    int destChannel = LUA::getNumber<int>(2);
    int destSample = LUA::getNumber<int>(2);
    // float newValue = *LUA::from_luce<Lfloat>(2); // TODO;
    // AudioSampleBuffer::setSample( destChannel, destSample, newValue );
    LUA::TODO_OBJECT( "setSample,  destChannel, destSample, newValue " );
    lua_settop(LUA::Get(), 1); // added by TODO
    return 0;
}

/////// getters
int LAudioSampleBuffer::getArrayOfReadPointers ( lua_State *L ) {
    // CHECK
    // return LUA::storeAndReturnUserdata<Lfloat>( new Lfloat(L,
    //     AudioSampleBuffer::getArrayOfReadPointers()
    // ));
    lua_settop(LUA::Get(), 1); // added by TODO
    return LUA::TODO_OBJECT( "float getArrayOfReadPointers()" );
}

int LAudioSampleBuffer::getMagnitude ( lua_State *L ) {
    // override
    int channel = LUA::getNumber<int>(2);
    int startSample = LUA::getNumber<int>(2);
    int numSamples = LUA::getNumber<int>(2);
    // CHECK
    // return LUA::storeAndReturnUserdata<Lfloat>( new Lfloat(L,
    //     AudioSampleBuffer::getMagnitude( channel, startSample, numSamples )
    // ));
    lua_settop(LUA::Get(), 1); // added by TODO
    return LUA::TODO_OBJECT( "float getMagnitude( channel, startSample, numSamples )" );

    //// override
    //int startSample = LUA::getNumber<int>(2);
    //int numSamples = LUA::getNumber<int>(2);
    //// CHECK
    //// return LUA::storeAndReturnUserdata<Lfloat>( new Lfloat(L,
    ////     AudioSampleBuffer::getMagnitude( startSample, numSamples )
    //// ));
    lua_settop(LUA::Get(), 1); // added by TODO
    return LUA::TODO_OBJECT( "float getMagnitude( startSample, numSamples )" );
}

int LAudioSampleBuffer::findMinMax ( lua_State* ) {
    int channel = LUA::getNumber<int>(2);
    int startSample = LUA::getNumber<int>(2);
    int numSamples = LUA::getNumber<int>(2);
    return LUCE::luce_pushtable( AudioSampleBuffer::findMinMax( channel, startSample, numSamples ) );
}

int LAudioSampleBuffer::getRMSLevel ( lua_State *L ) {
    int channel = LUA::getNumber<int>(2);
    int startSample = LUA::getNumber<int>(2);
    int numSamples = LUA::getNumber<int>(2);
    // CHECK
    // return LUA::storeAndReturnUserdata<Lfloat>( new Lfloat(L,
    //     AudioSampleBuffer::getRMSLevel( channel, startSample, numSamples )
    // ));
    lua_settop(LUA::Get(), 1); // added by TODO
    return LUA::TODO_OBJECT( "float getRMSLevel( channel, startSample, numSamples )" );
}

int LAudioSampleBuffer::getNumChannels ( lua_State* ) {
    return LUA::returnNumber( AudioSampleBuffer::getNumChannels() );
}

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
    for(int i=1,j=sampleIndex;i<len;++i,++j) {
        lua_rawgeti(L, -1, i);
        data[j] = (float)lua_tonumber(L,-1);
        lua_pop(L,1);
    }
    lua_pop(L,1);
    return 0;
}

int LAudioSampleBuffer::getNumSamples ( lua_State* ) {
    return LUA::returnNumber( AudioSampleBuffer::getNumSamples() );
}

int LAudioSampleBuffer::getReadPointer ( lua_State *L ) {

    // override
    int channelNumber = LUA::getNumber<int>(2);
    // CHECK
    // return LUA::storeAndReturnUserdata<Lfloat>( new Lfloat(L,
    //     AudioSampleBuffer::getReadPointer( channelNumber )
    // ));
    lua_settop(LUA::Get(), 1); // added by TODO
    return LUA::TODO_OBJECT( "float getReadPointer( channelNumber )" );

    //// override
    //int channelNumber = LUA::getNumber<int>(2);
    //int sampleIndex = LUA::getNumber<int>(2);
    //// CHECK
    //// return LUA::storeAndReturnUserdata<Lfloat>( new Lfloat(L,
    ////     AudioSampleBuffer::getReadPointer( channelNumber, sampleIndex )
    //// ));
    lua_settop(LUA::Get(), 1); // added by TODO
    return LUA::TODO_OBJECT( "float getReadPointer( channelNumber, sampleIndex )" );
}

int LAudioSampleBuffer::getArrayOfWritePointers ( lua_State *L ) {
    // CHECK
    // return LUA::storeAndReturnUserdata<Lfloat>( new Lfloat(L,
    //     AudioSampleBuffer::getArrayOfWritePointers()
    // ));
    lua_settop(LUA::Get(), 1); // added by TODO
    return LUA::TODO_OBJECT( "float getArrayOfWritePointers()" );
}

int LAudioSampleBuffer::hasBeenCleared ( lua_State* ) {
    return LUA::returnBoolean( AudioSampleBuffer::hasBeenCleared() );
}

/////// setters
int LAudioSampleBuffer::applyGainRamp ( lua_State* ) {

    // override
    int channel = LUA::getNumber<int>(2);
    int startSample = LUA::getNumber<int>(2);
    int numSamples = LUA::getNumber<int>(2);
    // float startGain = *LUA::from_luce<Lfloat>(2); // TODO;
    // float endGain = *LUA::from_luce<Lfloat>(2); // TODO;
    // AudioSampleBuffer::applyGainRamp( channel, startSample, numSamples, startGain, endGain );
    LUA::TODO_OBJECT( "applyGainRamp,  channel, startSample, numSamples, startGain, endGain " );
    lua_settop(LUA::Get(), 1); // added by TODO
    return 0;

    //// override
    //int startSample = LUA::getNumber<int>(2);
    //int numSamples = LUA::getNumber<int>(2);
    //// float startGain = *LUA::from_luce<Lfloat>(2); // TODO;
    //// float endGain = *LUA::from_luce<Lfloat>(2); // TODO;
    //// AudioSampleBuffer::applyGainRamp( startSample, numSamples, startGain, endGain );
    //LUA::TODO_OBJECT( "applyGainRamp,  startSample, numSamples, startGain, endGain " );
    lua_settop(LUA::Get(), 1); // added by TODO
    return 0;
}

int LAudioSampleBuffer::makeCopyOf ( lua_State* ) {
    // AudioSampleBuffer::makeCopyOf(*LUA::from_luce<LAudioBuffer>(2); // TODO);
    LUA::TODO_OBJECT( "makeCopyOf, *LUA::from_luce<LAudioBuffer>(2); // TODO" );
    lua_settop(LUA::Get(), 1); // added by TODO
    return 0;
}

int LAudioSampleBuffer::reverse ( lua_State* ) {

    // override
    int channel = LUA::getNumber<int>(2);
    int startSample = LUA::getNumber<int>(2);
    int numSamples = LUA::getNumber<int>(2);
    AudioSampleBuffer::reverse( channel, startSample, numSamples );
    return 0;

    //// override
    //int startSample = LUA::getNumber<int>(2);
    //int numSamples = LUA::getNumber<int>(2);
    //AudioSampleBuffer::reverse( startSample, numSamples );
    return 0;
}

int LAudioSampleBuffer::addFrom ( lua_State* ) {

    // override
    int destChannel = LUA::getNumber<int>(2);
    int destStartSample = LUA::getNumber<int>(2);
    // AudioSampleBuffer source = *LUA::from_luce<LAudioBuffer>(2); // TODO;
    int sourceChannel = LUA::getNumber<int>(2);
    int sourceStartSample = LUA::getNumber<int>(2);
    int numSamples = LUA::getNumber<int>(2);
    // float gainToApplyToSource = *LUA::from_luce<Lfloat>(2); // TODO;
    // AudioSampleBuffer::addFrom( destChannel, destStartSample, source, sourceChannel, sourceStartSample, numSamples, gainToApplyToSource );
    LUA::TODO_OBJECT( "addFrom,  destChannel, destStartSample, source, sourceChannel, sourceStartSample, numSamples, gainToApplyToSource " );
    lua_settop(LUA::Get(), 1); // added by TODO
    return 0;

    //// override
    //int destChannel = LUA::getNumber<int>(2);
    //int destStartSample = LUA::getNumber<int>(2);
    //// float* source = LUA::from_luce<Lfloat>(2); // TODO;
    //int numSamples = LUA::getNumber<int>(2);
    //// float gainToApplyToSource = *LUA::from_luce<Lfloat>(2); // TODO;
    //// AudioSampleBuffer::addFrom( destChannel, destStartSample, source, numSamples, gainToApplyToSource );
    //LUA::TODO_OBJECT( "addFrom,  destChannel, destStartSample, source, numSamples, gainToApplyToSource " );
    lua_settop(LUA::Get(), 1); // added by TODO
    return 0;
}

int LAudioSampleBuffer::copyFromWithRamp ( lua_State* ) {
    int destChannel = LUA::getNumber<int>(2);
    int destStartSample = LUA::getNumber<int>(2);
    // float* source = LUA::from_luce<Lfloat>(2); // TODO;
    int numSamples = LUA::getNumber<int>(2);
    // float startGain = *LUA::from_luce<Lfloat>(2); // TODO;
    // float endGain = *LUA::from_luce<Lfloat>(2); // TODO;
    // AudioSampleBuffer::copyFromWithRamp( destChannel, destStartSample, source, numSamples, startGain, endGain );
    LUA::TODO_OBJECT( "copyFromWithRamp,  destChannel, destStartSample, source, numSamples, startGain, endGain " );
    lua_settop(LUA::Get(), 1); // added by TODO
    return 0;
}

int LAudioSampleBuffer::copyFrom ( lua_State* ) {

    // override
    int destChannel = LUA::getNumber<int>(2);
    int destStartSample = LUA::getNumber<int>(2);
    // AudioSampleBuffer source = *LUA::from_luce<LAudioBuffer>(2); // TODO;
    int sourceChannel = LUA::getNumber<int>(2);
    int sourceStartSample = LUA::getNumber<int>(2);
    int numSamples = LUA::getNumber<int>(2);
    // AudioSampleBuffer::copyFrom( destChannel, destStartSample, source, sourceChannel, sourceStartSample, numSamples );
    LUA::TODO_OBJECT( "copyFrom,  destChannel, destStartSample, source, sourceChannel, sourceStartSample, numSamples " );
    lua_settop(LUA::Get(), 1); // added by TODO
    return 0;

    //// override
    //int destChannel = LUA::getNumber<int>(2);
    //int destStartSample = LUA::getNumber<int>(2);
    //// float* source = LUA::from_luce<Lfloat>(2); // TODO;
    //int numSamples = LUA::getNumber<int>(2);
    //// AudioSampleBuffer::copyFrom( destChannel, destStartSample, source, numSamples );
    //LUA::TODO_OBJECT( "copyFrom,  destChannel, destStartSample, source, numSamples " );
    //lua_settop(LUA::Get(), 1); // added by TODO
    //return 0;

    //// override
    //int destChannel = LUA::getNumber<int>(2);
    //int destStartSample = LUA::getNumber<int>(2);
    //// float* source = LUA::from_luce<Lfloat>(2); // TODO;
    //int numSamples = LUA::getNumber<int>(2);
    //// float gain = *LUA::from_luce<Lfloat>(2); // TODO;
    //// AudioSampleBuffer::copyFrom( destChannel, destStartSample, source, numSamples, gain );
    //LUA::TODO_OBJECT( "copyFrom,  destChannel, destStartSample, source, numSamples, gain " );
    lua_settop(LUA::Get(), 1); // added by TODO
    return 0;
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

int LAudioSampleBuffer::setDataToReferTo ( lua_State* ) {
    // float** dataToReferTo = LUA::from_luce<Lfloat>(2); // TODO;
    int newNumChannels = LUA::getNumber<int>(2);
    int newNumSamples = LUA::getNumber<int>(2);
    // AudioSampleBuffer::setDataToReferTo( dataToReferTo, newNumChannels, newNumSamples );
    LUA::TODO_OBJECT( "setDataToReferTo,  dataToReferTo, newNumChannels, newNumSamples " );
    lua_settop(LUA::Get(), 1); // added by TODO
    return 0;
}

int LAudioSampleBuffer::addFromWithRamp ( lua_State* ) {
    int destChannel = LUA::getNumber<int>(2);
    int destStartSample = LUA::getNumber<int>(2);
    // float* source = LUA::from_luce<Lfloat>(2); // TODO;
    int numSamples = LUA::getNumber<int>(2);
    // float startGain = *LUA::from_luce<Lfloat>(2); // TODO;
    // float endGain = *LUA::from_luce<Lfloat>(2); // TODO;
    // AudioSampleBuffer::addFromWithRamp( destChannel, destStartSample, source, numSamples, startGain, endGain );
    LUA::TODO_OBJECT( "addFromWithRamp,  destChannel, destStartSample, source, numSamples, startGain, endGain " );
    lua_settop(LUA::Get(), 1); // added by TODO
    return 0;
}

int LAudioSampleBuffer::addSample ( lua_State* ) {
    int destChannel = LUA::getNumber<int>(2);
    int destSample = LUA::getNumber<int>(2);
    // float valueToAdd = *LUA::from_luce<Lfloat>(2); // TODO;
    // AudioSampleBuffer::addSample( destChannel, destSample, valueToAdd );
    LUA::TODO_OBJECT( "addSample,  destChannel, destSample, valueToAdd " );
    lua_settop(LUA::Get(), 1); // added by TODO
    return 0;
}

int LAudioSampleBuffer::clear ( lua_State* ) {

    // override
    AudioSampleBuffer::clear();
    return 0;

    //// override
    //int startSample = LUA::getNumber<int>(2);
    //int numSamples = LUA::getNumber<int>(2);
    //AudioSampleBuffer::clear( startSample, numSamples );
    //return 0;

    //// override
    //int channel = LUA::getNumber<int>(2);
    //int startSample = LUA::getNumber<int>(2);
    //int numSamples = LUA::getNumber<int>(2);
    //AudioSampleBuffer::clear( channel, startSample, numSamples );
    return 0;
}

int LAudioSampleBuffer::applyGain ( lua_State* ) {

    // override
    int channel = LUA::getNumber<int>(2);
    int startSample = LUA::getNumber<int>(2);
    int numSamples = LUA::getNumber<int>(2);
    // float gain = *LUA::from_luce<Lfloat>(2); // TODO;
    // AudioSampleBuffer::applyGain( channel, startSample, numSamples, gain );
    LUA::TODO_OBJECT( "applyGain,  channel, startSample, numSamples, gain " );
    lua_settop(LUA::Get(), 1); // added by TODO
    return 0;

    //// override
    //int startSample = LUA::getNumber<int>(2);
    //int numSamples = LUA::getNumber<int>(2);
    //// float gain = *LUA::from_luce<Lfloat>(2); // TODO;
    //// AudioSampleBuffer::applyGain( startSample, numSamples, gain );
    //LUA::TODO_OBJECT( "applyGain,  startSample, numSamples, gain " );
    //lua_settop(LUA::Get(), 1); // added by TODO
    //return 0;

    //// override
    //// AudioSampleBuffer::applyGain(*LUA::from_luce<Lfloat>(2); // TODO);
    //LUA::TODO_OBJECT( "applyGain, *LUA::from_luce<Lfloat>(2); // TODO" );
    lua_settop(LUA::Get(), 1); // added by TODO
    return 0;
}

