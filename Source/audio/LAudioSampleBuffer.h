/************************************************************

 LAudioSampleBuffer.h

    @author Christophe Berbizier (cberbizier@peersuasive.com)
    @license GPLv3
    @copyright 


(c) 2014, Peersuasive Technologies

*************************************************************/

#ifndef __LUCE_LAUDIOSAMPLEBUFFER_H
#define __LUCE_LAUDIOSAMPLEBUFFER_H

class LAudioSampleBuffer
    : public LBase,
      public AudioSampleBuffer
{
public:
    LAudioSampleBuffer(lua_State*);
    LAudioSampleBuffer(lua_State*, const AudioSampleBuffer&) noexcept;
    LAudioSampleBuffer(lua_State*, int numChannels, int numSamples) noexcept;
    LAudioSampleBuffer(lua_State*, float *const *data, int numChannels, int numSamples) noexcept;
    LAudioSampleBuffer(lua_State*, float *const *data, int numChannels, int startSample, int numSamples) noexcept;

    static int lnew(lua_State*);
    ~LAudioSampleBuffer();

    //==============================================================================

    //==============================================================================
    int getNumChannels(lua_State*);
    int getNumSamples(lua_State*);
    int getReadPointer(lua_State*);
    int setDataToReferTo(lua_State*); // getWritePointer
    int getArrayOfReadPointers(lua_State*);
    int setArrayOfData(lua_State*); // getArrayOfWritePointer
    int setSize(lua_State*);
    int makeCopyOf(lua_State*);
    int clear(lua_State*);
    int hasBeenCleared(lua_State*);
    int getSample(lua_State*);
    int setSample(lua_State*);
    int addSample(lua_State*);
    int applyGain(lua_State*);
    int applyGainRamp(lua_State*);
    int addFrom(lua_State*);
    int addFromWithRamp(lua_State*);
    int copyFrom(lua_State*);
    int copyFromWithRamp(lua_State*);
    int findMinMax(lua_State*);
    int getMagnitude(lua_State*);
    int getRMSLevel(lua_State*);
    int reverse(lua_State*);

    //==============================================================================
    /** 
       Replacement for getWritePointer.

       Accepts an indexed table with numbers.a

       @param channelNum the channel number to set data to
       @param sampleIndex the sample to start from
       @param *data array of numbers

       @return [true],[nil,error]
    */
    int setData(lua_State*);

    //==============================================================================
    static const char className[];
    static const Luna<LAudioSampleBuffer>::Inheritence inherits[];
    static const Luna<LAudioSampleBuffer>::InheritenceF inheritsF[];
    static const Luna<LAudioSampleBuffer>::PropertyType properties[];
    static const Luna<LAudioSampleBuffer>::FunctionType methods[];
    static const Luna<LAudioSampleBuffer>::StaticType statics[];
    static const Luna<LAudioSampleBuffer>::Enum enums[];

private:
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (LAudioSampleBuffer)
};

#endif // __LUCE_LAUDIOSAMPLEBUFFER_H
