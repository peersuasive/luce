/************************************************************

 LBigInteger.h

    @author Christophe Berbizier (cberbizier@peersuasive.com)
    @license GPLv3
    @copyright 


(c) 2014, Peersuasive Technologies

*************************************************************/

#ifndef __LUCE_LBIGINTEGER_H
#define __LUCE_LBIGINTEGER_H

class LBigInteger
    : public LBase,
      public BigInteger
{
public:
    LBigInteger(lua_State*);
    LBigInteger(lua_State*, const BigInteger&);
    ~LBigInteger();

    //==============================================================================
    int setNegative(lua_State*);
    int isNegative(lua_State*);
    int setBitRangeAsInt(lua_State*);
    int getBitRangeAsInt(lua_State*);

    //==============================================================================
    int getBitRange(lua_State*);
    int toInt64(lua_State*);
    int isOne(lua_State*);
    int isZero(lua_State*);
    int countNumberOfSetBits(lua_State*);
    int findNextSetBit(lua_State*);
    int getHighestBit(lua_State*);
    int findNextClearBit(lua_State*);
    int findGreatestCommonDivisor(lua_State*);
    int toInteger(lua_State*);
    int toMemoryBlock(lua_State*);
    int compareAbsolute(lua_State*);
    int toString(lua_State*);
    int compare(lua_State*);

    //==============================================================================
    int loadFromMemoryBlock(lua_State*);
    int exponentModulo(lua_State*);
    int parseString(lua_State*);
    int divideBy(lua_State*);
    int insertBit(lua_State*);
    int negate(lua_State*);
    int inverseModulo(lua_State*);
    int setBit(lua_State*);
    int swapWith(lua_State*);
    int clearBit(lua_State*);
    int setRange(lua_State*);
    int clear(lua_State*);
    int shiftBits(lua_State*);

    //==============================================================================
    static const char className[];
    static const Luna<LBigInteger>::Inheritence inherits[];
    static const Luna<LBigInteger>::InheritenceF inheritsF[];
    static const Luna<LBigInteger>::PropertyType properties[];
    static const Luna<LBigInteger>::FunctionType methods[];
    static const Luna<LBigInteger>::StaticType statics[];
    static const Luna<LBigInteger>::Enum enums[];

private:
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (LBigInteger)
};

#endif // __LUCE_LBIGINTEGER_H
