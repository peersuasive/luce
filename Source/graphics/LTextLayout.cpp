/************************************************************

 LTextLayout.cpp

    @author Christophe Berbizier (cberbizier@peersuasive.com)
    @license GPLv3
    @copyright 


(c) 2014, Peersuasive Technologies

*************************************************************/

#include "LTextLayout_inh.h"

const char LTextLayout::className[] = "LTextLayout";
const Luna<LTextLayout>::PropertyType LTextLayout::properties[] = {
    { "numLines", &LTextLayout::getNumLines, &LBase::readOnly },
    { "width", &LTextLayout::getWidth, &LBase::readOnly },
    { "height", &LTextLayout::getHeight, &LBase::readOnly },

    {0,0}
};
const Luna<LTextLayout>::FunctionType LTextLayout::methods[] = {
    method( LTextLayout, getNumLines ),
    method( LTextLayout, getLine ),
    method( LTextLayout, getWidth ),
    method( LTextLayout, getHeight ),
    method( LTextLayout, addLine ),
    method( LTextLayout, createLayoutWithBalancedLineLengths ),
    method( LTextLayout, ensureStorageAllocated ),
    method( LTextLayout, createLayout ),
    method( LTextLayout, draw ),
    {0,0}
};

const Luna<LTextLayout>::StaticType LTextLayout::statics[] = {
    {0,0}
};

LTextLayout::LTextLayout(lua_State *L)
    : LBase(L, "LTextLayout", true),
      TextLayout()
{
}

LTextLayout::LTextLayout(lua_State *L, const TextLayout& class_)
    : LBase(L, "LTextLayout", true),
      TextLayout( class_ )
{
}

LTextLayout::~LTextLayout() {}

/////// getters
int LTextLayout::getNumLines ( lua_State* ) {
    return LUA::returnNumber( TextLayout::getNumLines() );
}

int LTextLayout::getLine ( lua_State *L ) {
    return LUA::returnUserdata<LLine>( &TextLayout::getLine( LUA::getNumber<int>(2) ) );
}

int LTextLayout::getWidth ( lua_State* ) {
    return LUA::returnNumber( TextLayout::getWidth() );
}

int LTextLayout::getHeight ( lua_State* ) {
    return LUA::returnNumber( TextLayout::getHeight() );
}

/////// setters
int LTextLayout::addLine ( lua_State* ) {
    TextLayout::addLine( LUA::from_luce<LLine>(2) );
    return 0;
}

int LTextLayout::createLayoutWithBalancedLineLengths ( lua_State* ) {
    AttributedString text( *LUA::from_luce<LAttributedString>(2) );
    float maxWidth = LUA::getNumber<float>(2);
    TextLayout::createLayoutWithBalancedLineLengths( text, maxWidth );
    return 0;
}

int LTextLayout::ensureStorageAllocated ( lua_State* ) {
    TextLayout::ensureStorageAllocated(LUA::getNumber<int>());
    return 0;
}

int LTextLayout::createLayout ( lua_State* ) {
    AttributedString text( *LUA::from_luce<LAttributedString>(2) );
    float maxWidth = LUA::getNumber<float>(2);
    TextLayout::createLayout( text, maxWidth );
    return 0;
}

int LTextLayout::draw ( lua_State* ) {
    Graphics& g = (Graphics&)*LUA::from_luce<LGraphics>(2);
    Rectangle<float> area ( LUA::getRectangle<float>(2) );
    TextLayout::draw( g, area );
    return 0;
}
