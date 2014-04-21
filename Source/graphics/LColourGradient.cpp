/************************************************************

 LColourGradient.cpp

    @author Christophe Berbizier (cberbizier@peersuasive.com)
    @license GPLv3
    @copyright 


(c) 2014, Peersuasive Technologies

*************************************************************/

#include "LColourGradient_inh.h"

const char LColourGradient::className[] = "LColourGradient";
const Luna<LColourGradient>::PropertyType LColourGradient::properties[] = {
    {"colour", &LColourGradient::getColour, &LColourGradient::setColour},
    {"point1", &LColourGradient::getPoint1, &LBase::readOnly},
    {"point2", &LColourGradient::getPoint2, &LBase::readOnly},
    {0,0}
};
const Luna<LColourGradient>::FunctionType LColourGradient::methods[] = {
    method( LColourGradient, clearColours ),
    method( LColourGradient, addColour ),
    method( LColourGradient, removeColour ),
    method( LColourGradient, multiplyOpacity ),
    method( LColourGradient, getNumColours ),
    method( LColourGradient, getColourPosition ),
    method( LColourGradient, getColour ),
    method( LColourGradient, setColour ),
    method( LColourGradient, getColourAtPosition ),
    method( LColourGradient, createLookupTable ),
    method( LColourGradient, isOpaque ),
    method( LColourGradient, isInvisible ),
    
    method( LColourGradient, getPoint1 ),
    method( LColourGradient, getPoint2 ),
    method( LColourGradient, isRadial ),

    {0,0}
};

const Luna<LColourGradient>::StaticType LColourGradient::statics[] = {
    {0,0}
};

LColourGradient::LColourGradient(lua_State *L)
    : LBase(L, "LColourGradient", true),
      ColourGradient()
{
}

LColourGradient::LColourGradient(lua_State *L, const ColourGradient& class_)
    : LBase(L, "LColourGradient", true),
      ColourGradient( class_ )
{
}

LColourGradient::~LColourGradient() {}

int LColourGradient::lnew(lua_State* L) {
    if(lua_isnoneornil(L,2)) {
        return LUA::storeAndReturnUserdata<LColourGradient>( new LColourGradient(L,
            ColourGradient()
        ));
    }
    else {
        Colour c1, c2;
        float x1, y1, x2, y2;
        if(lua_isstring(L,2))
            c1 = Colours::findColourForName(LUA::getString(2), Colours::black);
        else
            c1 = Colour(*LUA::from_luce<LColour>(2));
        x1 = LUA::getNumber<float>(2);
        y1 = LUA::getNumber<float>(2);

        if(lua_isstring(L,2))
            c2 = Colours::findColourForName(LUA::getString(2), Colours::black);
        else
            c2 = Colour(*LUA::from_luce<LColour>(2));
        x2 = LUA::getNumber<float>(2);
        y2 = LUA::getNumber<float>(2);

        bool isRadial = LUA::getBoolean(2);

        return LUA::storeAndReturnUserdata<LColourGradient>( new LColourGradient(L,
            ColourGradient(c1,x1,y1, c2,x2,y2, isRadial)
        ));
    }
}

int LColourGradient::clearColours(lua_State*) {
    ColourGradient::clearColours();
    return 0;
}

int LColourGradient::addColour(lua_State* L) {
    double proportionAlongGradient = LUA::getNumber<double>(2);
    Colour c;
    if(lua_isstring(L,2))
        c = Colours::findColourForName(LUA::getString(2), Colours::black);
    else
        c = Colour(*LUA::from_luce<LColour>(2));
    return LUA::returnNumber( ColourGradient::addColour( proportionAlongGradient, c ) );
}

int LColourGradient::removeColour(lua_State*) {
    ColourGradient::removeColour(LUA::getNumber<int>());
    return 0;
}

int LColourGradient::multiplyOpacity(lua_State*) {
    ColourGradient::multiplyOpacity(LUA::getNumber<float>());
    return 0;
}

int LColourGradient::getNumColours(lua_State*) {
    return LUA::returnNumber( ColourGradient::getNumColours() );
}

int LColourGradient::getColourAtPosition(lua_State *L) {
    double position = LUA::getNumber<double>(2);
    return LUA::storeAndReturnUserdata<LColour>( new LColour(L,
        ColourGradient::getColourAtPosition( position )
    ));
}

int LColourGradient::getColourPosition(lua_State*) {
    int index = LUA::getNumber<int>(2);
    return LUA::returnNumber( ColourGradient::getColourPosition( index ) );
}

int LColourGradient::getColour(lua_State* L) {
    int index = LUA::getNumber<int>(2);
    return LUA::storeAndReturnUserdata<LColour>( new LColour(L,
        ColourGradient::getColour( index )
    ));
}
int LColourGradient::setColour(lua_State* L) {
    int index = LUA::getNumber<int>(2);
    Colour newColour;
    if(lua_isstring(L,2))
        newColour = Colours::findColourForName(LUA::getString(2), Colours::black);
    else
        newColour = Colour(*LUA::from_luce<LColour>(2));
    ColourGradient::setColour( index, newColour );
    return 0;
}

int LColourGradient::createLookupTable ( lua_State* ) {
    // TODO: aff, HeapBlock<PixelARGB>
    // PixelARGB* resultLookupTable = LUA::from_luce<LPixelARGB>(2); // TODO;
    int numEntries = LUA::getNumber<int>(2);
    // ColourGradient::createLookupTable( resultLookupTable, numEntries );
    LUA::TODO_OBJECT( "createLookupTable,  resultLookupTable, numEntries " );
    lua_settop(LUA::Get(), 1); // added by TODO
    return 0;
}

int LColourGradient::isOpaque(lua_State*) {
    return LUA::returnBoolean( ColourGradient::isOpaque() );
}

int LColourGradient::isInvisible(lua_State*) {
    return LUA::returnBoolean( ColourGradient::isInvisible() );
}


int LColourGradient::getPoint1(lua_State*) {
    return LUCE::luce_pushtable(this->point1);
}

int LColourGradient::getPoint2(lua_State*) {
    return LUCE::luce_pushtable(this->point2);
}

int LColourGradient::isRadial(lua_State*) {
    return LUA::returnBoolean(ColourGradient::isRadial);
}
