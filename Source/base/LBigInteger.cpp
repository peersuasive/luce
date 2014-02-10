/************************************************************

 LBigInteger.cpp

    @author Christophe Berbizier (cberbizier@peersuasive.com)
    @license GPLv3
    @copyright 


(c) 2014, Peersuasive Technologies

*************************************************************/

#include "LBigInteger_inh.h"

const char LBigInteger::className[] = "LBigInteger";
const Luna<LBigInteger>::PropertyType LBigInteger::properties[] = {
    {"negative", &LBigInteger::isNegative, &LBigInteger::setNegative},
    {"bitRangeAsInt", &LBigInteger::getBitRangeAsInt, &LBigInteger::setBitRangeAsInt},
    {0,0}
};
const Luna<LBigInteger>::FunctionType LBigInteger::methods[] = {
    method( LBigInteger, getBitRange ),
    method( LBigInteger, toInt64 ),
    method( LBigInteger, isOne ),
    method( LBigInteger, isZero ),
    method( LBigInteger, countNumberOfSetBits ),
    method( LBigInteger, findNextSetBit ),
    method( LBigInteger, getHighestBit ),
    method( LBigInteger, isNegative ),
    method( LBigInteger, setNegative ),
    method( LBigInteger, findNextClearBit ),
    method( LBigInteger, findGreatestCommonDivisor ),
    method( LBigInteger, getBitRangeAsInt ),
    method( LBigInteger, setBitRangeAsInt ),
    method( LBigInteger, toInteger ),
    method( LBigInteger, toMemoryBlock ),
    method( LBigInteger, compareAbsolute ),
    method( LBigInteger, toString ),
    method( LBigInteger, compare ),
    method( LBigInteger, loadFromMemoryBlock ),
    method( LBigInteger, exponentModulo ),
    method( LBigInteger, parseString ),
    method( LBigInteger, divideBy ),
    method( LBigInteger, insertBit ),
    method( LBigInteger, negate ),
    method( LBigInteger, inverseModulo ),
    method( LBigInteger, setBit ),
    method( LBigInteger, swapWith ),
    method( LBigInteger, clearBit ),
    method( LBigInteger, setRange ),
    method( LBigInteger, clear ),
    method( LBigInteger, shiftBits ),
    {0,0}
};

const Luna<LBigInteger>::StaticType LBigInteger::statics[] = {
    {0,0}
};

LBigInteger::LBigInteger(lua_State *L)
    : LBase(L, "LBigInteger", true),
      BigInteger( /* TODO: add args */ )
{
}

LBigInteger::LBigInteger(lua_State *L, const BigInteger& class_)
    : LBase(L, "LBigInteger", true),
      BigInteger( class_ )
{
}

LBigInteger::~LBigInteger() {}


/////// getters/setters
int LBigInteger::isNegative ( lua_State* ) {
    return LUA::returnBoolean( BigInteger::isNegative() );
}
int LBigInteger::setNegative ( lua_State* ) {
    BigInteger::setNegative(LUA::getBoolean());
    return 0;
}

int LBigInteger::getBitRangeAsInt ( lua_State* ) {
    int startBit = LUA::getNumber<int>(2);
    int numBits = LUA::getNumber<int>(2);
    return LUA::returnNumber( BigInteger::getBitRangeAsInt( startBit, numBits ) );
}
int LBigInteger::setBitRangeAsInt ( lua_State* ) {
    int startBit = LUA::getNumber<int>(2);
    int numBits = LUA::getNumber<int>(2);
    uint32 valueToSet = LUA::getNumber<uint32>(2);
    BigInteger::setBitRangeAsInt( startBit, numBits, valueToSet );
    return 0;
}

/////// getters
int LBigInteger::getBitRange ( lua_State *L ) {
    int startBit = LUA::getNumber<int>(2);
    int numBits = LUA::getNumber<int>(2);
    return LUA::storeAndReturnUserdata<LBigInteger>( new LBigInteger(L,
        BigInteger::getBitRange( startBit, numBits )
    ));
}

int LBigInteger::toInt64 ( lua_State* ) {
    return LUA::returnNumber( BigInteger::toInt64() );
}

int LBigInteger::isOne ( lua_State* ) {
    return LUA::returnBoolean( BigInteger::isOne() );
}

int LBigInteger::isZero ( lua_State* ) {
    return LUA::returnBoolean( BigInteger::isZero() );
}

int LBigInteger::countNumberOfSetBits ( lua_State* ) {
    return LUA::returnNumber( BigInteger::countNumberOfSetBits() );
}

int LBigInteger::findNextSetBit ( lua_State* ) {
    int startIndex = LUA::getNumber<int>(2);
    return LUA::returnNumber( BigInteger::findNextSetBit( startIndex ) );
}

int LBigInteger::getHighestBit ( lua_State* ) {
    return LUA::returnNumber( BigInteger::getHighestBit() );
}

int LBigInteger::findNextClearBit ( lua_State* ) {
    int startIndex = LUA::getNumber<int>(2);
    return LUA::returnNumber( BigInteger::findNextClearBit( startIndex ) );
}

int LBigInteger::findGreatestCommonDivisor ( lua_State *L ) {
    BigInteger other = *LUA::from_luce<LBigInteger>(2);
    return LUA::storeAndReturnUserdata<LBigInteger>( new LBigInteger(L,
        BigInteger::findGreatestCommonDivisor( other )
    ));
}

int LBigInteger::toInteger ( lua_State* ) {
    return LUA::returnNumber( BigInteger::toInteger() );
}

int LBigInteger::toMemoryBlock ( lua_State *L ) {
    return LUA::returnString( BigInteger::toMemoryBlock().toBase64Encoding() );
}

int LBigInteger::compareAbsolute ( lua_State* ) {
    BigInteger other = *LUA::from_luce<LBigInteger>(2);
    return LUA::returnNumber( BigInteger::compareAbsolute( other ) );
}

int LBigInteger::toString ( lua_State* ) {
    int base = LUA::getNumber<int>(2);
    int minimumNumCharacters = LUA::checkAndGetNumber<int>(2, 1);
    return LUA::returnString( BigInteger::toString( base, minimumNumCharacters ) );
}

int LBigInteger::compare ( lua_State* ) {
    BigInteger other = *LUA::from_luce<LBigInteger>(2);
    return LUA::returnNumber( BigInteger::compare( other ) );
}

/////// setters
int LBigInteger::loadFromMemoryBlock ( lua_State* ) {
    BigInteger::loadFromMemoryBlock( MemoryBlock().fromBase64Encoding( StringRef( LUA::getString(2) ) ) );
    return 0;
}

int LBigInteger::exponentModulo ( lua_State* ) {
    BigInteger exponent = *LUA::from_luce<LBigInteger>(2);
    BigInteger modulus = *LUA::from_luce<LBigInteger>(2);
    BigInteger::exponentModulo( exponent, modulus );
    return 0;
}

int LBigInteger::parseString ( lua_State* ) {
    StringRef text ( LUA::getString(2) );
    int base = LUA::getNumber<int>(2);
    BigInteger::parseString( text, base );
    return 0;
}

int LBigInteger::divideBy ( lua_State* ) {
    BigInteger divisor = *LUA::from_luce<LBigInteger>(2);
    BigInteger remainder = *LUA::from_luce<LBigInteger>(2);
    BigInteger::divideBy( divisor, remainder );
    return 0;
}

int LBigInteger::insertBit ( lua_State* ) {
    int bitNumber = LUA::getNumber<int>(2);
    bool shouldBeSet = LUA::getBoolean(2);
    BigInteger::insertBit( bitNumber, shouldBeSet );
    return 0;
}

int LBigInteger::negate ( lua_State* ) {
    BigInteger::negate();
    return 0;
}

int LBigInteger::inverseModulo ( lua_State* ) {
    BigInteger::inverseModulo(*LUA::from_luce<LBigInteger>(2));
    return 0;
}

int LBigInteger::setBit ( lua_State* ) {
    int bitNumber = LUA::getNumber<int>(2);
    bool shouldBeSet = LUA::checkAndGetBoolean(2, true);
    BigInteger::setBit( bitNumber, shouldBeSet );
    return 0;
}

int LBigInteger::swapWith ( lua_State* ) {
    BigInteger::swapWith(*LUA::from_luce<LBigInteger>(2));
    return 0;
}

int LBigInteger::clearBit ( lua_State* ) {
    BigInteger::clearBit(LUA::getNumber<int>());
    return 0;
}

int LBigInteger::setRange ( lua_State* ) {
    int startBit = LUA::getNumber<int>(2);
    int numBits = LUA::getNumber<int>(2);
    bool shouldBeSet = LUA::getBoolean(2);
    BigInteger::setRange( startBit, numBits, shouldBeSet );
    return 0;
}

int LBigInteger::clear ( lua_State* ) {
    BigInteger::clear();
    return 0;
}

int LBigInteger::shiftBits ( lua_State* ) {
    int howManyBitsLeft = LUA::getNumber<int>(2);
    int startBit = LUA::getNumber<int>(2);
    BigInteger::shiftBits( howManyBitsLeft, startBit );
    return 0;
}
