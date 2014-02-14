/************************************************************

 LGlyph.cpp

    @author Christophe Berbizier (cberbizier@peersuasive.com)
    @license GPLv3
    @copyright 


(c) 2014, Peersuasive Technologies

*************************************************************/

#include "LGlyph_inh.h"

const char LGlyph::className[] = "LGlyph";
const Luna<LGlyph>::PropertyType LGlyph::properties[] = {
    { "glyphCode", &LGlyph::getGlyphCode, &LGlyph::setGlyphCode },
    { "anchor", &LGlyph::getAnchor, &LGlyph::setAnchor },
    { "width", &LGlyph::getWidth, &LGlyph::setWidth },
    {0,0}
};
const Luna<LGlyph>::FunctionType LGlyph::methods[] = {
    method( LGlyph, getGlyphCode ),
    method( LGlyph, setGlyphCode ),
    method( LGlyph, getAnchor ),
    method( LGlyph, setAnchor ),
    method( LGlyph, getWidth ),
    method( LGlyph, setWidth ),
    {0,0}
};

const Luna<LGlyph>::StaticType LGlyph::statics[] = {
    {0,0}
};

LGlyph::LGlyph(lua_State *L)
    : LBase(L, "LGlyph", true),
      Glyph(0, Point<float>(), 0)
{
    // INVALID
}

LGlyph::LGlyph(lua_State *L, const TextLayout::Glyph& class_)
    : LBase(L, "LGlyph", true),
      Glyph( class_ )
{
}

LGlyph::~LGlyph() {}

int LGlyph::getGlyphCode(lua_State*) {
    return LUA::returnNumber( this->glyphCode );
}
int LGlyph::setGlyphCode(lua_State*) {
    this->glyphCode = LUA::getNumber<int>(2);
    return 0;
}

int LGlyph::getAnchor(lua_State*) {
    return LUA::returnTable( this->anchor );
}
int LGlyph::setAnchor(lua_State*) {
    this->anchor = LUA::getPoint<float>(2);
    return 0;
}

int LGlyph::getWidth(lua_State*) {
    return LUA::returnNumber( this->width );
}
int LGlyph::setWidth(lua_State*) {
    this->width = LUA::getNumber<float>(2);
    return 0;
}
