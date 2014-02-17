/************************************************************

 LLine.cpp

    @author Christophe Berbizier (cberbizier@peersuasive.com)
    @license GPLv3
    @copyright 


(c) 2014, Peersuasive Technologies

*************************************************************/

#include "LLine_inh.h"

const char LLine::className[] = "LLine";
const Luna<LLine>::PropertyType LLine::properties[] = {
    { "runs"        , &LLine::getRuns       , &LLine::setRuns },
    { "stringRange" , &LLine::getStringRange, &LLine::setStringRange },
    { "lineOrigin"  , &LLine::getLineOrigin , &LLine::setLineOrigin },
    { "ascent"      , &LLine::getAscent     , &LLine::setAscent },
    { "descent"     , &LLine::getDescent    , &LLine::setDescent },
    { "leading"     , &LLine::getLeading    , &LLine::setLeading },

    {0,0}
};
const Luna<LLine>::FunctionType LLine::methods[] = {
    method( LLine, getLineBoundsX ),
    method( LLine, getRuns ),
    method( LLine, setRuns ),
    method( LLine, getStringRange ),
    method( LLine, setStringRange ),
    method( LLine, getLineOrigin ),
    method( LLine, setLineOrigin ),
    method( LLine, getAscent ),
    method( LLine, setAscent ),
    method( LLine, getDescent ),
    method( LLine, setDescent ),
    method( LLine, getLeading ),
    method( LLine, setLeading ),
    {0,0}
};

const Luna<LLine>::StaticType LLine::statics[] = {
    {0,0}
};

LLine::LLine(lua_State *L)
    : LBase(L, "LLine", true),
      Line( /* TODO: add args */ )
{
}

LLine::LLine(lua_State *L, const TextLayout::Line& class_)
    : LBase(L, "LLine", true),
      Line( class_ )
{
}

LLine::~LLine() {}

int LLine::getLineBoundsX ( lua_State* ) {
    return LUCE::luce_pushtable( Line::getLineBoundsX() );
}

int LLine::getRuns(lua_State*) {
    return LUCE::luce_pushtable<LRun, TextLayout::Run>( TextLayout::Line::runs );
}
int LLine::setRuns(lua_State*) {
    Array<TextLayout::Run*> lcomps = LUA::getObjectList<LRun,TextLayout::Run>(2);
    this->runs.clear();
    for (int i=0; i<lcomps.size(); ++i)
        this->runs.add( lcomps[i] );
    return 0;
}

int LLine::getStringRange(lua_State*) {
    return LUCE::luce_pushtable( TextLayout::Line::stringRange );
}
int LLine::setStringRange(lua_State*) {
    TextLayout::Line::stringRange = LUA::getRange<int>(2);
    return 0;
}

int LLine::getLineOrigin(lua_State*) {
    return LUCE::luce_pushtable( TextLayout::Line::lineOrigin );
}
int LLine::setLineOrigin(lua_State*) {
    TextLayout::Line::lineOrigin = LUA::getPoint<float>(2);
    return 0;
}

int LLine::getAscent(lua_State*) {
    return LUA::returnNumber( TextLayout::Line::ascent );
}
int LLine::setAscent(lua_State*) {
    TextLayout::Line::ascent = LUA::getNumber<float>(2);
    return 0;
}

int LLine::getDescent(lua_State*) {
    return LUA::returnNumber( TextLayout::Line::descent );
}
int LLine::setDescent(lua_State*) {
    TextLayout::Line::descent = LUA::getNumber<float>(2);
    return 0;
}

int LLine::getLeading(lua_State*) {
    return LUA::returnNumber( TextLayout::Line::leading );
}
int LLine::setLeading(lua_State*) {
    TextLayout::Line::leading = LUA::getNumber<float>(2);
    return 0;
}
