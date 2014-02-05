/************************************************************

 LPositionedGlyph.cpp

    @author Christophe Berbizier (cberbizier@peersuasive.com)
    @license GPLv3
    @copyright 


(c) 2014, Peersuasive Technologies

*************************************************************/

#include "LPositionedGlyph_inh.h"

const char LPositionedGlyph::className[] = "LPositionedGlyph";
const Luna<LPositionedGlyph>::PropertyType LPositionedGlyph::properties[] = {
    {0,0}
};
const Luna<LPositionedGlyph>::FunctionType LPositionedGlyph::methods[] = {
    method( LPositionedGlyph, getLeft ),
    method( LPositionedGlyph, getTop ),
    method( LPositionedGlyph, getBaselineY ),
    method( LPositionedGlyph, getRight ),
    method( LPositionedGlyph, getBounds ),
    method( LPositionedGlyph, isWhitespace ),
    method( LPositionedGlyph, getCharacter ),
    method( LPositionedGlyph, getBottom ),
    method( LPositionedGlyph, hitTest ),
    method( LPositionedGlyph, createPath ),
    method( LPositionedGlyph, draw ),
    method( LPositionedGlyph, moveBy ),
    {0,0}
};

const Luna<LPositionedGlyph>::StaticType LPositionedGlyph::statics[] = {
    {0,0}
};

LPositionedGlyph::LPositionedGlyph(lua_State *L)
    : LBase(L, "LPositionedGlyph", true),
      PositionedGlyph()
{
}

LPositionedGlyph::LPositionedGlyph(lua_State *L, const PositionedGlyph& class_)
    : LBase(L, "LPositionedGlyph", true),
      PositionedGlyph( class_ )
{
}

LPositionedGlyph::~LPositionedGlyph() {}

int LPositionedGlyph::getLeft ( lua_State* ) {
    return LUA::returnNumber( PositionedGlyph::getLeft() );
}

int LPositionedGlyph::getTop ( lua_State* ) {
    return LUA::returnNumber( PositionedGlyph::getTop() );
}

int LPositionedGlyph::getBaselineY ( lua_State* ) {
    return LUA::returnNumber( PositionedGlyph::getBaselineY() );
}

int LPositionedGlyph::getRight ( lua_State* ) {
    return LUA::returnNumber( PositionedGlyph::getRight() );
}

int LPositionedGlyph::getBounds ( lua_State* ) {
    return LUA::returnTable( PositionedGlyph::getBounds() );
}

int LPositionedGlyph::isWhitespace ( lua_State* ) {
    return LUA::returnBoolean( PositionedGlyph::isWhitespace() );
}

int LPositionedGlyph::getCharacter ( lua_State* ) {
    return LUA::returnString( String(PositionedGlyph::getCharacter()) );
}

int LPositionedGlyph::getBottom ( lua_State* ) {
    return LUA::returnNumber( PositionedGlyph::getBottom() );
}

int LPositionedGlyph::hitTest ( lua_State* ) {
    float x = LUA::getNumber<float>(2);
    float y = LUA::getNumber<float>(2);
    return LUA::returnBoolean( PositionedGlyph::hitTest( x, y ) );
}

/////// setters
int LPositionedGlyph::createPath ( lua_State* ) {
    PositionedGlyph::createPath( *LUA::from_luce<LPath>(2) );
    return 0;
}

int LPositionedGlyph::draw ( lua_State *L ) {
    const Graphics &g = (const Graphics&)*LUA::from_luce<LGraphics>(2);
    if(lua_isnoneornil(L,2))
        PositionedGlyph::draw(g);
    AffineTransform aff = LUCE::luce_toaffinetransform(2);
    PositionedGlyph::draw(g, aff);
    return 0;
}

int LPositionedGlyph::moveBy ( lua_State* ) {
    float deltaX = LUA::getNumber<float>(2);
    float deltaY = LUA::getNumber<float>(2);
    PositionedGlyph::moveBy( deltaX, deltaY );
    return 0;
}
