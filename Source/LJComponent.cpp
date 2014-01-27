/************************************************************

 LJComponent.cpp

    @author Christophe Berbizier (cberbizier@peersuasive.com)
    @license GPLv3
    @copyright 


(c) 2013, Peersuasive Technologies

*************************************************************/

#include "LJComponent_inh.h"
const char LJComponent::className[] = "LJComponent";

const Luna<LJComponent>::PropertyType LJComponent::properties[] = {
    {0,0}
};

const Luna<LJComponent>::FunctionType LJComponent::methods[] = {
    method( LJComponent, startDragging ),
    {0,0}
};

LJComponent::LJComponent(lua_State *L) 
    : LComponent(L, this)
{
    Component::setName( myName() );
    REGISTER_CLASS(LJComponent);
}

LJComponent::~LJComponent() {
    Component::deleteAllChildren();
}

void LJComponent::paint(Graphics& g) {
    if ( hasCallback("paint") ) {
        LComponent::lpaint(g);
    } else {
        Component::paint(g);
    }
}

void LJComponent::resized() {
    if ( hasCallback("resized") ) {
        LComponent::lresized();
    } else {
        Component::resized();
    }
}

void LJComponent::mouseMove(const MouseEvent& e) {
    LComponent::lmouseMove(e);
}

void LJComponent::mouseEnter(const MouseEvent& e) {
    LComponent::lmouseEnter(e);
}

void LJComponent::mouseExit(const MouseEvent& e) {
    LComponent::lmouseExit(e);
}

void LJComponent::mouseDown(const MouseEvent& e) {
    LComponent::lmouseDown(e);
}

void LJComponent::mouseDrag(const MouseEvent& e) {
    LComponent::lmouseDrag(e);
}

void LJComponent::mouseUp(const MouseEvent& e) {
    LComponent::lmouseUp(e);
}

void LJComponent::mouseDoubleClick(const MouseEvent& e) {
    LComponent::lmouseDoubleClick(e);
}

void LJComponent::mouseWheelMove (const MouseEvent& e, const MouseWheelDetails& wheel) {
    LComponent::lmouseWheelMove(e, wheel);
}

void LJComponent::mouseMagnify (const MouseEvent& e, float scaleFactor) {
    LComponent::lmouseMagnify(e, scaleFactor);
}
