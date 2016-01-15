/************************************************************

 LSystemTrayIconComponent.cpp

    @author Christophe Berbizier (cberbizier@peersuasive.com)
    @license GPLv3
    @copyright 


(c) 2016, Peersuasive Technologies

*************************************************************/

#include "LSystemTrayIconComponent_inh.h"

const char LSystemTrayIconComponent::className[] = "LSystemTrayIconComponent";
const Luna<LSystemTrayIconComponent>::PropertyType LSystemTrayIconComponent::properties[] = {
    {0,0}
};
const Luna<LSystemTrayIconComponent>::FunctionType LSystemTrayIconComponent::methods[] = {
    method(LSystemTrayIconComponent, setIconImage),
    method(LSystemTrayIconComponent, setIconTooltip),
    method(LSystemTrayIconComponent, setHighlighted),
    method(LSystemTrayIconComponent, showInfoBubble),
    method(LSystemTrayIconComponent, hideInfoBubble),
    {0,0}
};

const Luna<LSystemTrayIconComponent>::StaticType LSystemTrayIconComponent::statics[] = {
    {0,0}
};

LSystemTrayIconComponent::LSystemTrayIconComponent(lua_State *L)
    : LComponent(L, this),
      SystemTrayIconComponent()
{
    SystemTrayIconComponent::setName(myName());
    REGISTER_CLASS(LSystemTrayIconComponent);
}
LSystemTrayIconComponent::~LSystemTrayIconComponent() {}


int LSystemTrayIconComponent::showInfoBubble(lua_State *L) {
    String title = LUA::getString();
    String content = LUA::getString();
    SystemTrayIconComponent::showInfoBubble(title, content);
    return 0;
}
int LSystemTrayIconComponent::hideInfoBubble(lua_State*) {
    SystemTrayIconComponent::hideInfoBubble();
    return 0;
}

int LSystemTrayIconComponent::setIconImage(lua_State *L) {
    if(LUCE::luce_isofclass(LImage, 2)) {
        SystemTrayIconComponent::setIconImage ( *LUA::from_luce<LImage>(2) );
    } else LUCE::luce_error(lua_pushfstring(L,
            "LSystemTrayIconComponent: setIconImage: wrong arguments.\nExpected:\n %s", "(LImage)"));
    return 0;
}

int LSystemTrayIconComponent::setIconTooltip(lua_State*) {
    SystemTrayIconComponent::setIconTooltip( LUA::getString() );
    return 0;
}
int LSystemTrayIconComponent::setHighlighted(lua_State*) {
    SystemTrayIconComponent::setHighlighted(LUA::checkAndGetBoolean(2,true));
    return 0;
}

////
// mouse
void LSystemTrayIconComponent::mouseEnter(const MouseEvent& e) {
    if(hasCallback("mouseEnter"))
        LComponent::lmouseEnter(e);
    else
        SystemTrayIconComponent::mouseEnter(e);
}

void LSystemTrayIconComponent::mouseExit(const MouseEvent& e) {
    if(hasCallback("mouseExit"))
        LComponent::lmouseExit(e);
    else
        SystemTrayIconComponent::mouseExit(e);
}

void LSystemTrayIconComponent::mouseDown(const MouseEvent& e) {
    if(hasCallback("mouseDown")) {
        LComponent::lmouseDown(e);
        bool b = LUA::checkAndGetBoolean(-1, false);
        if(!b) SystemTrayIconComponent::mouseDown(e);
    } else {
        SystemTrayIconComponent::mouseDown(e);
    }
}

void LSystemTrayIconComponent::mouseUp(const MouseEvent& e) {
    if(hasCallback("mouseUp"))
        LComponent::lmouseUp(e);
    else
        SystemTrayIconComponent::mouseUp(e);
}

void LSystemTrayIconComponent::mouseDoubleClick(const MouseEvent& e) {
    if(hasCallback("mouseDoubleClick"))
        LComponent::lmouseDoubleClick(e);
    else
        SystemTrayIconComponent::mouseDoubleClick(e);
}
