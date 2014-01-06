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

void LMainComponent::paint(Graphics& g) {
    LComponent::lpaint(g);
}

void LMainComponent::resized() {
    LComponent::lresized();
}

void LMainComponent::mouseMove(const MouseEvent& e) {
    LComponent::lmouseMove(e);
}

void LMainComponent::mouseEnter(const MouseEvent& e) {
    LComponent::lmouseEnter(e);
}

void LMainComponent::mouseExit(const MouseEvent& e) {
    LComponent::lmouseExit(e);
}

void LMainComponent::mouseDown(const MouseEvent& e) {
    LComponent::lmouseDown(e);
}

void LMainComponent::mouseDrag(const MouseEvent& e) {
    LComponent::lmouseDrag(e);
}

void LMainComponent::mouseUp(const MouseEvent& e) {
    LComponent::lmouseUp(e);
}

void LMainComponent::mouseDoubleClick(const MouseEvent& e) {
    LComponent::lmouseDoubleClick(e);
}

void LMainComponent::mouseWheelMove (const MouseEvent& e, const MouseWheelDetails& wheel) {
    LComponent::lmouseWheelMove(e, wheel);
}

void LMainComponent::mouseMagnify (const MouseEvent& e, float scaleFactor) {
    LComponent::lmouseMagnify(e, scaleFactor);
}
