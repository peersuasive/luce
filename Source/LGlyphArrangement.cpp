/************************************************************

 LGlyphArrangement.cpp

    @author Christophe Berbizier (cberbizier@peersuasive.com)
    @license GPLv3
    @copyright 


(c) 2014, Peersuasive Technologies

*************************************************************/

#include "LGlyphArrangement_inh.h"

////// static methods
const char LGlyphArrangement::className[] = "LGlyphArrangement";
const Luna<LGlyphArrangement>::PropertyType LGlyphArrangement::properties[] = {
    {0,0}
};
const Luna<LGlyphArrangement>::FunctionType LGlyphArrangement::methods[] = {
    method( LGlyphArrangement, findGlyphIndexAt ),
    method( LGlyphArrangement, getNumGlyphs ),
    method( LGlyphArrangement, getBoundingBox ),
    method( LGlyphArrangement, getGlyph ),
    method( LGlyphArrangement, removeRangeOfGlyphs ),
    method( LGlyphArrangement, addLineOfText ),
    method( LGlyphArrangement, addGlyph ),
    method( LGlyphArrangement, addCurtailedLineOfText ),
    method( LGlyphArrangement, justifyGlyphs ),
    method( LGlyphArrangement, stretchRangeOfGlyphs ),
    method( LGlyphArrangement, draw ),
    method( LGlyphArrangement, addGlyphArrangement ),
    method( LGlyphArrangement, addFittedText ),
    method( LGlyphArrangement, createPath ),
    method( LGlyphArrangement, moveRangeOfGlyphs ),
    method( LGlyphArrangement, clear ),
    method( LGlyphArrangement, addJustifiedText ),
    {0,0}
};

/////// ctor/dtor
LGlyphArrangement::LGlyphArrangement(lua_State *L)
    : LBase(L, "LGlyphArrangement", true),
      GlyphArrangement()
{
}

LGlyphArrangement::LGlyphArrangement(lua_State *L, const GlyphArrangement& class_)
    : LBase(L, "LGlyphArrangement", true),
      GlyphArrangement( class_ )
{
}

LGlyphArrangement::~LGlyphArrangement() {}

int LGlyphArrangement::findGlyphIndexAt ( lua_State* ) {
    float x = LUA::getNumber<float>(2);
    float y = LUA::getNumber<float>(2);
    return LUA::returnNumber( GlyphArrangement::findGlyphIndexAt( x, y ) );
}

int LGlyphArrangement::getNumGlyphs ( lua_State* ) {
    return LUA::returnNumber( GlyphArrangement::getNumGlyphs() );
}

int LGlyphArrangement::getBoundingBox ( lua_State* ) {
    int startIndex = LUA::getNumber<int>(2);
    int numGlyphs = LUA::getNumber<int>(2);
    bool includeWhitespace = LUA::getBoolean(2);
    return LUA::returnTable( GlyphArrangement::getBoundingBox( startIndex, numGlyphs, includeWhitespace ) );
}

int LGlyphArrangement::getGlyph ( lua_State *L ) {
    return LUA::storeAndReturnUserdata<LPositionedGlyph>( new LPositionedGlyph(L,
        GlyphArrangement::getGlyph( LUA::getNumber<int>(2) )
    ));
}

/////// setters
int LGlyphArrangement::removeRangeOfGlyphs ( lua_State* ) {
    int startIndex = LUA::getNumber<int>(2);
    int numGlyphs = LUA::getNumber<int>(2);
    GlyphArrangement::removeRangeOfGlyphs( startIndex, numGlyphs );
    return 0;
}

int LGlyphArrangement::addLineOfText ( lua_State* ) {
    Font font = *LUA::from_luce<LFont>(2);
    String text = LUA::getString(2);
    float x = LUA::getNumber<float>(2);
    float y = LUA::getNumber<float>(2);
    GlyphArrangement::addLineOfText( font, text, x, y );
    return 0;
}

int LGlyphArrangement::addGlyph ( lua_State* ) {
    GlyphArrangement::addGlyph( *LUA::from_luce<LPositionedGlyph>(2) );
    return 0;
}

int LGlyphArrangement::addCurtailedLineOfText ( lua_State* ) {
    Font font = *LUA::from_luce<LFont>(2);
    String text = LUA::getString(2);
    float x = LUA::getNumber<float>(2);
    float y = LUA::getNumber<float>(2);
    float maxWidthPixels = LUA::getNumber<float>(2);
    bool useEllipsis = LUA::getBoolean(2);
    GlyphArrangement::addCurtailedLineOfText( font, text, x, y, maxWidthPixels, useEllipsis );
    return 0;
}

int LGlyphArrangement::justifyGlyphs ( lua_State* ) {
    int startIndex = LUA::getNumber<int>(2);
    int numGlyphs = LUA::getNumber<int>(2);
    float x = LUA::getNumber<float>(2);
    float y = LUA::getNumber<float>(2);
    float width = LUA::getNumber<float>(2);
    float height = LUA::getNumber<float>(2);
    Justification justification = (Justification)LUA::getNumber<int>(2);
    GlyphArrangement::justifyGlyphs( startIndex, numGlyphs, x, y, width, height, justification );
    return 0;
}

int LGlyphArrangement::stretchRangeOfGlyphs ( lua_State* ) {
    int startIndex = LUA::getNumber<int>(2);
    int numGlyphs = LUA::getNumber<int>(2);
    float horizontalScaleFactor = LUA::getNumber<float>(2);
    GlyphArrangement::stretchRangeOfGlyphs( startIndex, numGlyphs, horizontalScaleFactor );
    return 0;
}

int LGlyphArrangement::draw ( lua_State *L ) {
    Graphics *g = (Graphics*)LUA::from_luce<LGraphics>(2);
    if(lua_isnoneornil(L,2))
        GlyphArrangement::draw(*g);
    GlyphArrangement::draw(*g, *LUA::from_luce<LAffineTransform>(2) );
    return 0;
}

int LGlyphArrangement::addGlyphArrangement ( lua_State* ) {
    GlyphArrangement::addGlyphArrangement( *LUA::from_luce<LGlyphArrangement>(2) );
    return 0;
}

int LGlyphArrangement::addFittedText ( lua_State* ) {
    Font font = *LUA::from_luce<LFont>(2);
    String text = LUA::getString(2);
    float x = LUA::getNumber<float>(2);
    float y = LUA::getNumber<float>(2);
    float width = LUA::getNumber<float>(2);
    float height = LUA::getNumber<float>(2);
    Justification layout = (Justification)LUA::getNumber<int>(2);
    int maximumLinesToUse = LUA::getNumber<int>(2);
    float minimumHorizontalScale = LUA::checkAndGetNumber<float>(2, 0.7f);
    GlyphArrangement::addFittedText( font, text, x, y, width, height, layout, maximumLinesToUse, minimumHorizontalScale );
    return 0;
}

int LGlyphArrangement::createPath ( lua_State* ) {
    GlyphArrangement::createPath( *LUA::from_luce<LPath>(2) );
    return 0;
}

int LGlyphArrangement::moveRangeOfGlyphs ( lua_State* ) {
    int startIndex = LUA::getNumber<int>(2);
    int numGlyphs = LUA::getNumber<int>(2);
    float deltaX = LUA::getNumber<float>(2);
    float deltaY = LUA::getNumber<float>(2);
    GlyphArrangement::moveRangeOfGlyphs( startIndex, numGlyphs, deltaX, deltaY );
    return 0;
}

int LGlyphArrangement::clear ( lua_State* ) {
    GlyphArrangement::clear();
    return 0;
}

int LGlyphArrangement::addJustifiedText ( lua_State* ) {
    Font font = *LUA::from_luce<LFont>(2);
    String text = LUA::getString(2);
    float x = LUA::getNumber<float>(2);
    float y = LUA::getNumber<float>(2);
    float maxLineWidth = LUA::getNumber<float>(2);
    Justification horizontalLayout = (Justification)LUA::getNumber<int>(2);
    GlyphArrangement::addJustifiedText( font, text, x, y, maxLineWidth, horizontalLayout );
    return 0;
}

