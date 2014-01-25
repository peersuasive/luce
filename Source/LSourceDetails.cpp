/************************************************************

 LSourceDetails.cpp

    @author Christophe Berbizier (cberbizier@peersuasive.com)
    @license GPLv3
    @copyright 


(c) 2014, Peersuasive Technologies

*************************************************************/

#include "LSourceDetails_inh.h"

////// static methods
const char LSourceDetails::className[] = "LSourceDetails";
const Luna<LSourceDetails>::PropertyType LSourceDetails::properties[] = {
    {"description", &LSourceDetails::getDescription, &LSourceDetails::setDescription},
    {"sourceComponent", &LSourceDetails::getSourceComponent, &LSourceDetails::setSourceComponent},
    {"localPosition", &LSourceDetails::getLocalPosition, &LSourceDetails::setLocalPosition},
    {0,0}
};
const Luna<LSourceDetails>::FunctionType LSourceDetails::methods[] = {
    method( LSourceDetails, getDescription),
    method( LSourceDetails, setDescription),
    method( LSourceDetails, getSourceComponent),
    method( LSourceDetails, setSourceComponent),
    method( LSourceDetails, getLocalPosition),
    method( LSourceDetails, setLocalPosition),
    {0,0}
};

/////// ctor/dtor
LSourceDetails::LSourceDetails(lua_State *L)
    : LBase(L, "LSourceDetails", true)
{
    description = LUA::getString();
    sourceComponent = LUA::from_luce<LComponent, Component>();
    localPosition = LUA::getPoint();
}

LSourceDetails::LSourceDetails(lua_State*L, const juce::DragAndDropTarget::SourceDetails& sd)
    : LBase(L, "LSourceDetails (dynamic)")
{
    description = sd.description;
    sourceComponent = sd.sourceComponent;
    localPosition = sd.localPosition;
}

LSourceDetails::~LSourceDetails() {
    if(sourceComponent)
        sourceComponent = nullptr;
}

LSourceDetails::operator juce::DragAndDropTarget::SourceDetails () const {
    return { description , sourceComponent, localPosition };
}

int LSourceDetails::getDescription(lua_State*) {
    return LUA::returnString(description);
}
int LSourceDetails::setDescription(lua_State*) {
    description = LUA::getString();
}

int LSourceDetails::getSourceComponent(lua_State*) {
    return LUA::returnUserdata<LJComponent, Component>( sourceComponent );
}
int LSourceDetails::setSourceComponent(lua_State*) {
    sourceComponent = LUA::from_luce<LComponent, Component>(2);
}

int LSourceDetails::getLocalPosition(lua_State*) {
    return LUA::returnTable( localPosition );
}
int LSourceDetails::setLocalPosition(lua_State*) {
    localPosition = LUA::getPoint(2);
}
