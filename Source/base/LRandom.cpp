/************************************************************

 LRandom.cpp

    @author Christophe Berbizier (cberbizier@peersuasive.com)
    @license GPLv3
    @copyright 


(c) 2014, Peersuasive Technologies

*************************************************************/

#include "LRandom_inh.h"

const char LRandom::className[] = "LRandom";
const Luna<LRandom>::PropertyType LRandom::properties[] = {
    {"seed", &LRandom::getSeed, &LRandom::setSeed},
    {0,0}
};
const Luna<LRandom>::FunctionType LRandom::methods[] = {
    method( LRandom, nextDouble ),
    method( LRandom, getSeed ),
    method( LRandom, setSeed ),
    method( LRandom, nextFloat ),
    method( LRandom, nextLargeNumber ),
    method( LRandom, nextInt ),
    method( LRandom, nextBool ),
    method( LRandom, nextInt64 ),
    method( LRandom, fillBitsRandomly ),
    method( LRandom, setSeedRandomly ),
    method( LRandom, combineSeed ),
    {0,0}
};

const Luna<LRandom>::StaticType LRandom::statics[] = {
    smethod( LRandom, getSystemRandom ),
    {0,0}
};

LRandom::LRandom(lua_State *L)
    : LBase(L, "LRandom", true),
      Random( /* TODO: add args */ )
{
}

LRandom::LRandom(lua_State *L, const Random& class_)
    : LBase(L, "LRandom", true),
      Random( class_ )
{
}

LRandom::~LRandom() {}


/////// getters/setters
int LRandom::getSeed ( lua_State* ) {
    return LUA::returnNumber( Random::getSeed() );
}
int LRandom::setSeed ( lua_State* ) {
    Random::setSeed(LUA::getNumber<int64>());
    return 0;
}

/////// statics
int LRandom::s_getSystemRandom ( lua_State *L ) {
    return LUA::storeAndReturnUserdata<LRandom>( new LRandom(L,
        Random::getSystemRandom()
    ));
}

/////// getters
int LRandom::nextDouble ( lua_State* ) {
    return LUA::returnNumber( Random::nextDouble() );
}

int LRandom::nextFloat ( lua_State* ) {
    return LUA::returnNumber( Random::nextFloat() );
}

int LRandom::nextLargeNumber ( lua_State *L ) {
    return LUA::storeAndReturnUserdata<LBigInteger>( new LBigInteger(L,
        Random::nextLargeNumber( *LUA::from_luce<LBigInteger>(2) )
    ));
}

int LRandom::nextInt ( lua_State *L ) {
    if(lua_isnoneornil(L,2))
        return LUA::returnNumber( Random::nextInt() );
    
    if(lua_isnumber(L,2))
        return LUA::returnNumber( Random::nextInt( LUA::getNumber<int>(2) ) );

    return LUA::returnNumber( Random::nextInt( LUA::getRange(2) ) );
}

int LRandom::nextBool ( lua_State* ) {
    return LUA::returnBoolean( Random::nextBool() );
}

int LRandom::nextInt64 ( lua_State* ) {
    return LUA::returnNumber( Random::nextInt64() );
}

/////// setters
int LRandom::fillBitsRandomly ( lua_State* ) {
    // override
    // void* bufferToFill = LUA::from_luce<Lvoid>(2); // TODO;
    // size_t sizeInBytes = *LUA::from_luce<Lsize_t>(2); // TODO;
    // Random::fillBitsRandomly( bufferToFill, sizeInBytes );

    // override
    BigInteger arrayToChange = *LUA::from_luce<LBigInteger>(2);
    int startBit = LUA::getNumber<int>(2);
    int numBits = LUA::getNumber<int>(2);
    Random::fillBitsRandomly( arrayToChange, startBit, numBits );
    return 0;
}

int LRandom::setSeedRandomly ( lua_State* ) {
    Random::setSeedRandomly();
    return 0;
}

int LRandom::combineSeed ( lua_State* ) {
    Random::combineSeed(LUA::getNumber<int64>());
    return 0;
}
