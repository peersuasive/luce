/************************************************************

 LColourSelector.cpp

    @author Christophe Berbizier (cberbizier@peersuasive.com)
    @license GPLv3
    @copyright 


(c) 2014, Peersuasive Technologies

*************************************************************/

#include "LColourSelector_inh.h"

const char LColourSelector::className[] = "LColourSelector";
const Luna<LColourSelector>::PropertyType LColourSelector::properties[] = {
    {"currentColour", &LColourSelector::getCurrentColour, &LColourSelector::setCurrentColour},
    {"swatchColour", &LColourSelector::getSwatchColour, &LColourSelector::setSwatchColour},
    {0,0}
};
const Luna<LColourSelector>::FunctionType LColourSelector::methods[] = {
    method( LColourSelector, getCurrentColour ),
    method( LColourSelector, setCurrentColour ),
    method( LColourSelector, getNumSwatches ),
    method( LColourSelector, getSwatchColour ),
    method( LColourSelector, setSwatchColour ),

    method( LColourSelector, addChangeListener ),
    method( LColourSelector, removeChangeListener ),
    {0,0}
};

const Luna<LColourSelector>::StaticType LColourSelector::statics[] = {
    {0,0}
};

LColourSelector::LColourSelector(lua_State *L)
    : LComponent(L, this),
      ColourSelector()
{
    //ColourSelector::addChangeListener(this);
    REGISTER_CLASS(LColourSelector);
}

LColourSelector::~LColourSelector() {}


int LColourSelector::addChangeListener(lua_State*) {
    ColourSelector::addChangeListener(this);
    return 0;
}
int LColourSelector::removeChangeListener(lua_State*) {
    ColourSelector::removeChangeListener(this);
    return 0;
}

void LColourSelector::changeListenerCallback(ChangeBroadcaster* br) {
    if(br == this) {
        if(hasCallback("colourChanged")) {
            //LComponent::callback("colourChanged", 1, {  ColourSelector::getCurrentColour().toString()  });
            //Colour c =ColourSelector::getCurrentColour();
            LColour *c = new LColour(LUA::Get(), ColourSelector::getCurrentColour());
            LComponent::callback("colourChanged", 1, { new LRefBase("Colour", c ) });
        }
    }
}
int LColourSelector::colourChanged(lua_State*) {
    set("colourChanged");
    return 0;
}

int LColourSelector::getCurrentColour ( lua_State *L ) {
    return LUA::storeAndReturnUserdata<LColour>( new LColour(L,
        ColourSelector::getCurrentColour()
    ));
}
int LColourSelector::setCurrentColour ( lua_State* ) {
    ColourSelector::setCurrentColour( LUCE::luce_tocolour(2) );
    return 0;
}

int LColourSelector::getSwatchColour ( lua_State *L ) {
    int index = LUA::getNumber<int>(2);
    return LUA::storeAndReturnUserdata<LColour>( new LColour(L,
        ColourSelector::getSwatchColour( index )
    ));
}
int LColourSelector::setSwatchColour ( lua_State* ) {
    int index = LUA::getNumber<int>(2);
    Colour newColour = LUCE::luce_tocolour(2);
    ColourSelector::setSwatchColour( index, newColour );
    return 0;
}

int LColourSelector::getNumSwatches ( lua_State* ) {
    return LUA::returnNumber( ColourSelector::getNumSwatches() );
}
