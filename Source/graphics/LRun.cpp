/************************************************************

 LRun.cpp

    @author Christophe Berbizier (cberbizier@peersuasive.com)
    @license GPLv3
    @copyright 


(c) 2014, Peersuasive Technologies

*************************************************************/

#include "LRun_inh.h"

const char LRun::className[] = "LRun";
const Luna<LRun>::PropertyType LRun::properties[] = {
    { "font"        , &LRun::getFont        , &LRun::setFont },
    { "colour"      , &LRun::getColour      , &LRun::setColour },
    { "glyphs"      , &LRun::getGlyphs      , &LRun::setGlyphs },
    { "stringRange" , &LRun::getStringRange , &LRun::setStringRange },
    {0,0}
};
const Luna<LRun>::FunctionType LRun::methods[] = {
    method( LRun, getFont ),
    method( LRun, setFont ),
    method( LRun, getColour ),
    method( LRun, setColour ),
    method( LRun, getGlyphs ),
    method( LRun, setGlyphs ),
    method( LRun, getStringRange ),
    method( LRun, setStringRange ),
    {0,0}
};

const Luna<LRun>::StaticType LRun::statics[] = {
    {0,0}
};

LRun::LRun(lua_State *L)
    : LBase(L, "LRun", true),
      Run( /* TODO: add args */ )
{
}

LRun::LRun(lua_State *L, const TextLayout::Run& class_)
    : LBase(L, "LRun", true),
      Run( class_ )
{
}

LRun::~LRun() {}

int LRun::getFont(lua_State*) {
    return LUA::returnUserdata<LFont>( &this->font );
}
int LRun::setFont(lua_State*) {
    this->font = Font( *LUA::from_luce<LFont>(2) );
    return 0;
}

int LRun::getColour(lua_State*) {
    return LUA::returnUserdata<LColour>( &this->colour );
}
int LRun::setColour(lua_State*) {
    this->colour = Colour( *LUA::from_luce<LColour>(2) );
    return 0;
}

int LRun::getGlyphs(lua_State *L) {
    lua_newtable(L);
    int ind = lua_gettop(L);
    for (int i=0; i<glyphs.size();++i) {
        LUCE::luce_pushlightglyph( glyphs.getReference(i) );
        lua_rawseti(L, ind, i+1);
    }
    return 1;
}
int LRun::setGlyphs(lua_State *L) {
    luaL_checktype(L, 2, LUA_TTABLE);
    this->glyphs.clear();
    for(int i=1;i<=lua_objlen(L, 2); ++i) {
        lua_rawgeti(L, 2, i);
        TextLayout::Glyph glyph( LUCE::luce_toglyph(-1) );
        this->glyphs.add( glyph );
    }
    lua_remove(L, 2);
    return 0;
}

int LRun::getStringRange(lua_State*) {
    return LUCE::luce_pushtable( this->stringRange );
}
int LRun::setStringRange(lua_State*) {
    this->stringRange = LUA::getRange<int>(2);
    return 0;
}
