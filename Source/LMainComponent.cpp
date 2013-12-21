/************************************************************

 LMainComponent.cpp

    @author Christophe Berbizier (cberbizier@peersuasive.com)
    @license GPLv3
    @copyright 


(c) 2013, Peersuasive Technologies

*************************************************************/

#include "LMainComponent_inh.h"
const char LMainComponent::className[] = "LMainComponent";

const Luna<LMainComponent>::PropertyType LMainComponent::properties[] = {
    {0,0}
};

const Luna<LMainComponent>::FunctionType LMainComponent::methods[] = {
    {0,0}
};

LMainComponent::LMainComponent(lua_State *L) 
    : LComponent(L, this),
      Component()
{
    Component::setName(myName);
}

LMainComponent::~LMainComponent() {
    Component::deleteAllChildren();
}
