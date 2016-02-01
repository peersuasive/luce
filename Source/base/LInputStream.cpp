/************************************************************

 LInputStream.cpp

    @author Christophe Berbizier (cberbizier@peersuasive.com)
    @license GPLv3
    @copyright 


(c) 2016, Peersuasive Technologies

*************************************************************/



/************************************************************

TODO: should render this class more lua's io

*************************************************************/


#include "LInputStream_inh.h"

const char LInputStream::className[] = "LInputStream";
const Luna<LInputStream>::PropertyType LInputStream::properties[] = {
    {0,0}
};
const Luna<LInputStream>::FunctionType LInputStream::methods[] = {
    method( LInputStream, getNumBytesRemaining ),
    method( LInputStream, readShort ),
    method( LInputStream, readInt64BigEndian ),
    method( LInputStream, readInt ),
    method( LInputStream, readCompressedInt ),
    method( LInputStream, readShortBigEndian ),
    method( LInputStream, getTotalLength ),
    method( LInputStream, readDoubleBigEndian ),
    method( LInputStream, setPosition ),
    method( LInputStream, readFloat ),
    method( LInputStream, readByte ),
    method( LInputStream, getPosition ),
    method( LInputStream, isExhausted ),
    method( LInputStream, readEntireStreamAsString ),
    method( LInputStream, readString ),
    method( LInputStream, readDouble ),
    method( LInputStream, readNextLine ),
    method( LInputStream, readIntBigEndian ),
    method( LInputStream, readBool ),
    method( LInputStream, readInt64 ),
    method( LInputStream, readFloatBigEndian ),
    //method( LInputStream, readIntoMemoryBlock ),
    method( LInputStream, skipNextBytes ),
    method( LInputStream, read ),
    {0,0}
};

const Luna<LInputStream>::StaticType LInputStream::statics[] = {
    {0,0}
};

LInputStream::LInputStream(lua_State *L)
    : LBase(L, "LInputStream", true),
      InputStream()
{
    child = this;
}

LInputStream::LInputStream(lua_State *L, InputStream *child_)
    : LBase(L, "LInputStream", true),
      InputStream(),
      child(child_)
{
}

LInputStream::~LInputStream() {
    if (child) {
        child.release();
        child = nullptr;
    }
}

/////// getters
int LInputStream::getNumBytesRemaining ( lua_State* ) {
    if(child)
        return LUA::returnNumber( child->getNumBytesRemaining() );
    else return 0;
}

int LInputStream::readShort ( lua_State *L ) {
    if(child)
        return LUA::returnNumber( child->readShort() );
    else return 0;
}

int LInputStream::readInt64BigEndian ( lua_State* ) {
    if(child)
        return LUA::returnNumber( child->readInt64BigEndian() );
    else return 0;
}

int LInputStream::readInt ( lua_State* ) {
    if(child)
        return LUA::returnNumber( child->readInt() );
    else return 0;
}

int LInputStream::readCompressedInt ( lua_State* ) {
    if(child)
       return LUA::returnNumber( child->readCompressedInt() );
    else return 0;
}

int LInputStream::readShortBigEndian ( lua_State *L ) {
    if(child)
       return LUA::returnNumber( child->readShortBigEndian() );
    else return 0;
}

int64 LInputStream::getTotalLength() {
    if(child) return child->getTotalLength();
    else return 0;
}
int LInputStream::getTotalLength ( lua_State* ) {
    return LUA::returnNumber( getTotalLength() );
}

int LInputStream::readDoubleBigEndian ( lua_State* ) {
    if(child)
       return LUA::returnNumber( child->readDoubleBigEndian() );
    else return 0;
}

int LInputStream::readFloat ( lua_State* ) {
    if(child)
       return LUA::returnNumber( child->readFloat() );
    else return 0;
}

int LInputStream::readByte ( lua_State* ) {
    if(child)
       return LUA::returnNumber( child->readByte() );
    else return 0;
}

int64 LInputStream::getPosition() {
    if(child)return child->getPosition();
    else return 0;
}
int LInputStream::getPosition ( lua_State* ) {
    if(child)
        return LUA::returnNumber( getPosition() );
    else return 0;
}

bool LInputStream::setPosition (int64 newPosition) {
    if(child)return child->setPosition(newPosition);
    else return false;
}
int LInputStream::setPosition ( lua_State* ) {
    if(child) {
        int64 newPosition = LUA::getNumber<int64>(2);
        return LUA::returnBoolean( setPosition( newPosition ) );
    } else return 0;
}

bool LInputStream::isExhausted() {
    if(child)return child->isExhausted();
    else return true;
}
int LInputStream::isExhausted ( lua_State* ) {
    if(child)
        return LUA::returnBoolean( child->isExhausted() );
    else return 0;
}

int LInputStream::readEntireStreamAsString ( lua_State* ) {
    if(child)
       return LUA::returnString( child->readEntireStreamAsString() );
    else return 0;
}

int LInputStream::readString ( lua_State* ) {
    if(child)
       return LUA::returnString( child->readString() );
    else return 0;
}

int LInputStream::readDouble ( lua_State* ) {
    if(child)
       return LUA::returnNumber( child->readDouble() );
    else return 0;
}

int LInputStream::readNextLine ( lua_State* ) {
    if(child)
       return LUA::returnString( child->readNextLine() );
    else return 0;
}

int LInputStream::readIntBigEndian ( lua_State* ) {
    if(child)
       return LUA::returnNumber( child->readIntBigEndian() );
    else return 0;
}

int LInputStream::readBool ( lua_State* ) {
    if(child)
       return LUA::returnBoolean( child->readBool() );
    else return 0;
}

int LInputStream::readInt64 ( lua_State* ) {
    if(child)
       return LUA::returnNumber( child->readInt64() );
    else return 0;
}

int LInputStream::readFloatBigEndian ( lua_State* ) {
    if(child)
       return LUA::returnNumber( child->readFloatBigEndian() );
    else return 0;
}

int LInputStream::skipNextBytes(lua_State*) {
    if(child) {
        int64 numBytesToSkip = LUA::getNumber<int64>();
        child->skipNextBytes(numBytesToSkip);
    }
    return 0;
}

int LInputStream::read (void* destBuffer, int maxBytesToRead) {
    if(child)
        return child->read(destBuffer, maxBytesToRead);
    else return 0;
}
int LInputStream::read ( lua_State *L ) {
    if(child) {
        int maxBytesToRead = LUA::checkAndGetNumber<int>(2,0);
        MemoryOutputStream mo;
        mo << *child;
        size_t size = maxBytesToRead || mo.getDataSize();
        lua_pushlstring(L, (const char*)mo.getData(), size);
    } else lua_pushnil(L);
    return 1;
}

/* 
int LInputStream::readIntoMemoryBlock ( lua_State *L ) {
    // MemoryBlock destBlock = *LUA::from_luce<LMemoryBlock>(2); // TODO;
    // ssize_t maxNumBytesToRead = *LUA::from_luce<Lssize_t>(2); // TODO;
    // CHECK
    // return LUA::storeAndReturnUserdata<Lsize_t>( new Lsize_t(L,
    //     InputStream::readIntoMemoryBlock( destBlock, maxNumBytesToRead )
    // ));
    lua_settop(LUA::Get(), 1); // added by TODO
    return LUA::TODO_OBJECT( "size_t readIntoMemoryBlock( destBlock, maxNumBytesToRead )" );
}
*/
