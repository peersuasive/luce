/************************************************************

 LRandom.h

    @author Christophe Berbizier (cberbizier@peersuasive.com)
    @license GPLv3
    @copyright 


(c) 2014, Peersuasive Technologies

*************************************************************/

#ifndef __LUCE_LRANDOM_H
#define __LUCE_LRANDOM_H

class LRandom
    : public LBase,
      public Random
{
public:
    LRandom(lua_State*);
    LRandom(lua_State*, const Random&);
    ~LRandom();

    //==============================================================================
    static int s_getSystemRandom(lua_State*);

    //==============================================================================
    int setSeed(lua_State*);
    int getSeed(lua_State*);

    //==============================================================================
    int nextDouble(lua_State*);
    int nextFloat(lua_State*);
    int nextLargeNumber(lua_State*);
    int nextInt(lua_State*);
    int nextBool(lua_State*);
    int nextInt64(lua_State*);

    //==============================================================================
    int fillBitsRandomly(lua_State*);
    int setSeedRandomly(lua_State*);
    int combineSeed(lua_State*);

    //==============================================================================
    static const char className[];
    static const Luna<LRandom>::Inheritence inherits[];
    static const Luna<LRandom>::InheritenceF inheritsF[];
    static const Luna<LRandom>::PropertyType properties[];
    static const Luna<LRandom>::FunctionType methods[];
    static const Luna<LRandom>::StaticType statics[];
    static const Luna<LRandom>::Enum enums[];

private:
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (LRandom)
};

#endif // __LUCE_LRANDOM_H
