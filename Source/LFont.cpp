/************************************************************

 LFont.cpp

    @author Christophe Berbizier (cberbizier@peersuasive.com)
    @license GPLv3
    @copyright 


(c) 2014, Peersuasive Technologies

*************************************************************/

#include "LFont_inh.h"

////// static methods
const char LFont::className[] = "LFont";
const Luna<LFont>::PropertyType LFont::properties[] = {
    {"height", &LFont::getHeight, &LFont::setHeight},
    {"italic", &LFont::isItalic, &LFont::setItalic},
    {"bold", &LFont::isBold, &LFont::setBold},
    {"underlined", &LFont::isUnderlined, &LFont::setUnderline},
    {"typefaceStyle", &LFont::getTypefaceStyle, &LFont::setTypefaceStyle},
    {"extraKerningFactor", &LFont::getExtraKerningFactor, &LFont::setExtraKerningFactor},
    {"horizontalScale", &LFont::getHorizontalScale, &LFont::setHorizontalScale},
    {"styleFlags", &LFont::getStyleFlags, &LFont::setStyleFlags},
    {"typefaceName", &LFont::getTypefaceName, &LFont::setTypefaceName},
    {0,0}
};
const Luna<LFont>::FunctionType LFont::methods[] = {
    method( LFont, setHeight ),
    method( LFont, getHeight ),
    method( LFont, isItalic ),
    method( LFont, setItalic ),
    method( LFont, isBold ),
    method( LFont, setBold ),
    method( LFont, isUnderlined ),
    method( LFont, setUnderline ),
    method( LFont, getTypefaceStyle ),
    method( LFont, setTypefaceStyle ),
    method( LFont, getExtraKerningFactor ),
    method( LFont, setExtraKerningFactor ),
    method( LFont, getHorizontalScale ),
    method( LFont, setHorizontalScale ),
    method( LFont, getStyleFlags ),
    method( LFont, setStyleFlags ),
    method( LFont, getTypefaceName ),
    method( LFont, setTypefaceName ),

    method( LFont, setSizeAndStyle ),
    method( LFont, setHeightWithoutChangingWidth ),
    method( LFont, getHeightInPoints ),

    method( LFont, getStringWidth ),

    method( LFont, italicised ),
    method( LFont, boldened ),
    method( LFont, withStyle ),
    method( LFont, withTypefaceStyle ),
    method( LFont, withHeight ),
    method( LFont, withExtraKerningFactor ),
    method( LFont, withPointHeight ),
    method( LFont, withHorizontalScale ),

    method( LFont, getAvailableStyles ),
    method( LFont, getDescent ),
    method( LFont, getDescentInPoints ),

    method( LFont, toString ),

    method( LFont, getStringWidthFloat ),
    method( LFont, getAscentInPoints ),
    method( LFont, getAscent ),
    method( LFont, getTypeface ),
    method( LFont, getGlyphPositions ),
    {0,0}
};

/////// ctor/dtor
const Luna<LFont>::StaticType LFont::statics[] = {
    smethod( LFont, getDefaultSansSerifFontName ),
    smethod( LFont, getDefaultMonospacedFontName ),
    smethod( LFont, getDefaultStyle ),
    smethod( LFont, getDefaultSerifFontName ),
    smethod( LFont, getDefaultTypefaceForFont ),
    smethod( LFont, findFonts ),
    smethod( LFont, findAllTypefaceStyles ),
    smethod( LFont, findAllTypefaceNames ),
    smethod( LFont, getFallbackFontName ),
    smethod( LFont, setFallbackFontName ),
    smethod( LFont, getFallbackFontStyle ),
    smethod( LFont, setFallbackFontStyle ),
    smethod( LFont, fromString ),

    {0,0}
};


LFont::LFont(lua_State *L)
    : LBase(L, "LFont", true),
      Font()
{
}

LFont::LFont(lua_State*L, const Font& f)
    : LBase(L, "LFont (dynamic)", true),
      Font(f)
{
}

int LFont::lnew(lua_State *L) {
    if (lua_isnoneornil(L,2))
        return LUA::storeAndReturnUserdata<LFont>( new LFont(L, Font()) );
    
    if (lua_isnumber(L, 2)) {
        float fontHeight = LUA::getNumber<float>(2);
        int styleFlag = LUA::checkAndGetNumber<int>(2, Font::FontStyleFlags::plain);
        return LUA::storeAndReturnUserdata<LFont>( new LFont(L, 
            Font( fontHeight, styleFlag )
        ));
    }

    if (lua_isstring(L, 2)) {
        String typefaceName = LUA::getString(2);
        if(lua_isnumber(L,2)) {
            float fontHeight = LUA::getNumber<float>(2);
            int styleFlag = LUA::getNumber<int>(2);
            return LUA::storeAndReturnUserdata<LFont>( new LFont(L, 
                Font( typefaceName, fontHeight, styleFlag )
            ));
        }
        String typefaceStyle = LUA::getString(2);
        float fontHeight = LUA::getNumber<float>(2);
        return LUA::storeAndReturnUserdata<LFont>( new LFont(L, 
            Font( typefaceName, typefaceStyle, fontHeight )
        ));
    }

    // TODO: copy constructor, Typeface...
    LUA::TODO_OBJECT( "Font(&Font), Font(Typeface::Ptr)" );
    lua_settop(LUA::Get(), 1);
}

LFont::~LFont() {}


///// statics
int LFont::s_getDefaultSansSerifFontName ( lua_State* ) {
    return LUA::returnString( Font::getDefaultSansSerifFontName() );
}

int LFont::s_getDefaultMonospacedFontName ( lua_State* ) {
    return LUA::returnString( Font::getDefaultMonospacedFontName() );
}

int LFont::s_getDefaultStyle ( lua_State* ) {
    return LUA::returnString( Font::getDefaultStyle() );
}

int LFont::s_getDefaultSerifFontName ( lua_State* ) {
    return LUA::returnString( Font::getDefaultSerifFontName() );
}

/**
    returns a table of strings
*/
int LFont::s_findFonts ( lua_State* ) {
    //Font::findFonts(LUA::getList());
    StringArray s;
    Array<Font> list;
    Font::findFonts(list);
    for(int i=0;i<list.size();++i)
        s.add( list[i].toString() );
    return LUA::returnTable(s);
}

int LFont::s_findAllTypefaceStyles ( lua_State* ) {
    return LUA::returnTable( Font::findAllTypefaceStyles(LUA::getString(2)) );
}

int LFont::s_findAllTypefaceNames ( lua_State* ) {
    return LUA::returnTable( Font::findAllTypefaceNames() );
}

int LFont::s_getFallbackFontName ( lua_State* ) {
    return LUA::returnString( Font::getFallbackFontName() );
}
int LFont::s_setFallbackFontName ( lua_State* ) {
    Font::setFallbackFontName(LUA::getString());
    return 0;
}

int LFont::s_getFallbackFontStyle ( lua_State* ) {
    return LUA::returnString( Font::getFallbackFontStyle() );
}
int LFont::s_setFallbackFontStyle ( lua_State* ) {
    Font::setFallbackFontStyle(LUA::getString());
    return 0;
}

int LFont::s_fromString ( lua_State *L ) {
    LFont *f = new LFont( L, Font::fromString(LUA::getString(2)) );
    return LUA::storeAndReturnUserdata<LFont>( f );
}

/////// getters/setters
int LFont::getTypefaceStyle ( lua_State* ) {
    return LUA::returnString( Font::getTypefaceStyle() );
}
int LFont::setTypefaceStyle ( lua_State* ) {
    Font::setTypefaceStyle(LUA::getString());
    return 0;
}

int LFont::getHeight ( lua_State* ) {
    return LUA::returnNumber( Font::getHeight() );
}
int LFont::setHeight ( lua_State* ) {
    Font::setHeight(LUA::getNumber());
    return 0;
}

int LFont::isItalic ( lua_State* ) {
    return LUA::returnBoolean( Font::isItalic() );
}
int LFont::setItalic ( lua_State* ) {
    Font::setItalic(LUA::getBoolean());
    return 0;
}

int LFont::getExtraKerningFactor ( lua_State* ) {
    return LUA::returnNumber( Font::getExtraKerningFactor() );
}
int LFont::setExtraKerningFactor ( lua_State* ) {
    Font::setExtraKerningFactor(LUA::getNumber());
    return 0;
}

int LFont::getHorizontalScale ( lua_State* ) {
    return LUA::returnNumber( Font::getHorizontalScale() );
}
int LFont::setHorizontalScale ( lua_State* ) {
    Font::setHorizontalScale(LUA::getNumber());
    return 0;
}

int LFont::getStyleFlags ( lua_State* ) {
    return LUA::returnNumber( Font::getStyleFlags() );
}
int LFont::setStyleFlags ( lua_State* ) {
    Font::setStyleFlags(LUA::getNumber());
    return 0;
}

int LFont::getTypefaceName ( lua_State* ) {
    return LUA::returnString( Font::getTypefaceName() );
}
int LFont::setTypefaceName ( lua_State* ) {
    Font::setTypefaceName(LUA::getString());
    return 0;
}

int LFont::isBold ( lua_State* ) {
    return LUA::returnBoolean( Font::isBold() );
}
int LFont::setBold ( lua_State* ) {
    Font::setBold(LUA::getBoolean());
    return 0;
}

/////// getters
int LFont::getAscent ( lua_State* ) {
    return LUA::returnNumber( Font::getAscent() );
}

int LFont::getStringWidth ( lua_State* ) {
    return LUA::returnNumber( Font::getStringWidth( LUA::getString(2) ) );
}

int LFont::boldened ( lua_State *L ) {
    LFont *f = new LFont( L, Font::boldened() );
    return LUA::storeAndReturnUserdata<LFont>( f );
}

int LFont::withHorizontalScale ( lua_State *L ) {
    LFont *f = new LFont( L, Font::withHorizontalScale((float)LUA::getNumber(2)) );
    return LUA::storeAndReturnUserdata<LFont>( f );
}

int LFont::getAvailableStyles ( lua_State *L ) {
    return LUA::returnTable( Font::getAvailableStyles() );
}

int LFont::getDescent ( lua_State* ) {
    return LUA::returnNumber( Font::getDescent() );
}

int LFont::withStyle ( lua_State *L ) {
    LFont *f = new LFont( L, Font::withStyle((int)LUA::getNumber(2)) );
    return LUA::storeAndReturnUserdata<LFont>( f );
}

int LFont::getHeightInPoints ( lua_State* ) {
    return LUA::returnNumber( Font::getHeightInPoints() );
}

int LFont::withTypefaceStyle ( lua_State *L ) {
    LFont *f = new LFont( L, Font::withTypefaceStyle(LUA::getString(2)) );
    return LUA::storeAndReturnUserdata<LFont>( f );
}

int LFont::withHeight ( lua_State *L ) {
    LFont *f = new LFont( L, Font::withHeight((float)LUA::getNumber(2)) );
    return LUA::storeAndReturnUserdata<LFont>( f );
}

int LFont::getDescentInPoints ( lua_State* ) {
    return LUA::returnNumber( Font::getDescentInPoints() );
}

int LFont::toString ( lua_State* ) {
    return LUA::returnString( Font::toString() );
}

int LFont::getStringWidthFloat ( lua_State* ) {
    return LUA::returnNumber( Font::getStringWidthFloat( LUA::getString(2) ) );
}

int LFont::withExtraKerningFactor ( lua_State *L ) {
    LFont *f = new LFont( L, Font::withExtraKerningFactor((float)LUA::getNumber(2)) );
    return LUA::storeAndReturnUserdata<LFont>( f );
}

int LFont::withPointHeight ( lua_State *L ) {
    LFont *f = new LFont( L, Font::withPointHeight((float)LUA::getNumber(2)) );
    return LUA::storeAndReturnUserdata<LFont>( f );
}

int LFont::getAscentInPoints ( lua_State* ) {
    return LUA::returnNumber( Font::getAscentInPoints() );
}

int LFont::isUnderlined ( lua_State* ) {
    return LUA::returnBoolean( Font::isUnderlined() );
}

int LFont::italicised ( lua_State *L ) {
    LFont *f = new LFont( L, Font::italicised() );
    return LUA::storeAndReturnUserdata<LFont>( f );
}

/////// setters
int LFont::setHeightWithoutChangingWidth ( lua_State* ) {
    Font::setHeightWithoutChangingWidth(LUA::getNumber(2));
    return 0;
}

int LFont::getGlyphPositions ( lua_State* ) {
    String text = LUA::getString(2);
    Array<int> glyphs = LUA::getList<int>(2);
    Array<float> xOffsets = LUA::getList<float>(2);
    Font::getGlyphPositions( text, glyphs, xOffsets );
    return 0;
}

int LFont::setSizeAndStyle ( lua_State *L ) {
    float newHeight = LUA::getNumber(2);
    float newHorizontalScale = LUA::getNumber(3);
    float newKerningAmount = LUA::getNumber(3);
    if(lua_isstring(L, 2)) {
        String newStyleFlags = LUA::getString(2);
        Font::setSizeAndStyle( newHeight, newStyleFlags, newHorizontalScale, newKerningAmount );
    }
    else {
        int newStyle = LUA::getNumber(2);
        Font::setSizeAndStyle( newHeight, newStyle, newHorizontalScale, newKerningAmount );
    }
    return 0;
}

int LFont::setUnderline ( lua_State* ) {
    Font::setUnderline(LUA::getBoolean());
    return 0;
}

// TODO
// getters
int LFont::s_getDefaultTypefaceForFont ( lua_State* ) {
    // Font font = LUA::TODO_OBJECT_Font;
    // return LUA::TODO_RETURN_OBJECT_Typeface::Ptr( Font::getDefaultTypefaceForFont( font ) );
    lua_settop(LUA::Get(), 1); // added by TODO
    return LUA::TODO_OBJECT( "Typeface::Ptr getDefaultTypefaceForFont( font )" );
}

int LFont::getTypeface ( lua_State* ) {
    // return LUA::TODO_RETURN_OBJECT_Typeface( Font::getTypeface() );
    lua_settop(LUA::Get(), 1); // added by TODO
    return LUA::TODO_OBJECT( "Typeface getTypeface()" );
}
