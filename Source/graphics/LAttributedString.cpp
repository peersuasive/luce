/************************************************************

 LAttributedString.cpp

    @author Christophe Berbizier (cberbizier@peersuasive.com)
    @license GPLv3
    @copyright 


(c) 2014, Peersuasive Technologies

*************************************************************/

#include "LAttributedString_inh.h"

const char LAttributedString::className[] = "LAttributedString";
const Luna<LAttributedString>::PropertyType LAttributedString::properties[] = {
    {"justification", &LAttributedString::getJustification, &LAttributedString::setJustification},
    {"lineSpacing", &LAttributedString::getLineSpacing, &LAttributedString::setLineSpacing},
    {"readingDirection", &LAttributedString::getReadingDirection, &LAttributedString::setReadingDirection},
    {"wordWrap", &LAttributedString::getWordWrap, &LAttributedString::setWordWrap},
    {"text", &LAttributedString::getText, &LAttributedString::setText},
    {0,0}
};
const Luna<LAttributedString>::FunctionType LAttributedString::methods[] = {
    method( LAttributedString, getNumAttributes ),
    method( LAttributedString, getJustification ),
    method( LAttributedString, setJustification ),
    method( LAttributedString, getAttribute ),
    method( LAttributedString, getLineSpacing ),
    method( LAttributedString, setLineSpacing ),
    method( LAttributedString, getReadingDirection ),
    method( LAttributedString, setReadingDirection ),
    method( LAttributedString, getWordWrap ),
    method( LAttributedString, setWordWrap ),
    method( LAttributedString, getText ),
    method( LAttributedString, setText ),
    method( LAttributedString, append ),
    method( LAttributedString, setColour ),
    method( LAttributedString, draw ),
    method( LAttributedString, setFont ),
    method( LAttributedString, clear ),
    {0,0}
};

const Luna<LAttributedString>::StaticType LAttributedString::statics[] = {
    {0,0}
};

LAttributedString::LAttributedString(lua_State *L)
    : LBase(L, "LAttributedString", true),
      AttributedString()
{
}

LAttributedString::LAttributedString(lua_State *L, const AttributedString& class_)
    : LBase(L, "LAttributedString", true),
      AttributedString( class_ )
{
}

LAttributedString::~LAttributedString() {}

/////// getters/setters
int LAttributedString::getJustification ( lua_State* ) {
    return LUA::returnNumber( AttributedString::getJustification().getFlags() );
}
int LAttributedString::setJustification ( lua_State* ) {
    AttributedString::setJustification((Justification)LUA::getNumber<int>(2));
    return 0;
}

int LAttributedString::getLineSpacing ( lua_State* ) {
    return LUA::returnNumber( AttributedString::getLineSpacing() );
}
int LAttributedString::setLineSpacing ( lua_State* ) {
    AttributedString::setLineSpacing(LUA::getNumber<float>(2));
    return 0;
}

int LAttributedString::getReadingDirection ( lua_State *L ) {
    return LUA::returnNumber( (int)AttributedString::getReadingDirection() );
}
int LAttributedString::setReadingDirection ( lua_State* ) {
    AttributedString::setReadingDirection( (ReadingDirection)LUA::getNumber<int>(2) );
    return 0;
}

int LAttributedString::getWordWrap ( lua_State *L ) {
    return LUA::returnNumber( (int)AttributedString::getWordWrap() );
}
int LAttributedString::setWordWrap ( lua_State* ) {
    AttributedString::setWordWrap( (WordWrap)LUA::getNumber<int>(2) );
    return 0;
}

int LAttributedString::getText ( lua_State* ) {
    return LUA::returnString( AttributedString::getText() );
}
int LAttributedString::setText ( lua_State* ) {
    AttributedString::setText(LUA::getString());
    return 0;
}

/////// getters
int LAttributedString::getNumAttributes ( lua_State* ) {
    return LUA::returnNumber( AttributedString::getNumAttributes() );
}

int LAttributedString::getAttribute ( lua_State *L ) {
    return LUA::returnUserdata<LAttribute, Attribute>( 
        AttributedString::getAttribute( LUA::getNumber<int>(2) ) 
    );
}

/////// setters
int LAttributedString::append ( lua_State *L ) {
    String text = LUA::getString(2);
    if(lua_isnoneornil(L,2))
        AttributedString::append(text);
    
    else if(lua_gettop(L) > 3)
        AttributedString::append( text, *LUA::from_luce<Font>(2), *LUA::from_luce<Colour>(3) );
    
    else if( LUCE::luce_isofclass(Font, 2) )
        AttributedString::append( text, Font(*LUA::from_luce<LFont>(2)) );
    
    else {
        Colour c;
        if(!lua_isnumber(L,2) && lua_isstring(L,2))
            c = Colours::findColourForName( LUA::getString(2), Colours::black );
        else
            c = Colour( *LUA::from_luce<LColour>(2) );
        AttributedString::append( text, c );
    }
    return 0;
}

int LAttributedString::setColour ( lua_State *L ) {
    Colour c;
    int i = lua_gettop(L) > 2 ? 3 : 2;
    if(!lua_isnumber(L,i) && lua_isstring(L,i))
        c = Colours::findColourForName( LUA::getString(i), Colours::black );
    else
        c = Colour( *LUA::from_luce<LColour>(i) );
    
    if(i>2)
        AttributedString::setColour( LUA::getRange(2), c );
    else
        AttributedString::setColour( c );
    return 0;
}

int LAttributedString::draw ( lua_State* ) {
    Graphics& g = (Graphics&)*LUA::from_luce<LGraphics>(2);
    AttributedString::draw( g, LUA::getRectangle<float>(2) );
    return 0;
}

int LAttributedString::setFont ( lua_State *L ) {
    int i = lua_gettop(L) > 2 ? 3 : 2;
    Font f( *LUA::from_luce<LFont>(i) );
    if(i>2)
        AttributedString::setFont( LUA::getRange<int>(2), f );
    else
        AttributedString::setFont( f );
    return 0;
}

int LAttributedString::clear ( lua_State* ) {
    AttributedString::clear();
    return 0;
}
