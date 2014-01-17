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
    Component::setName(myName());
}

LMainComponent::~LMainComponent() {
    Component::deleteAllChildren();
}

void LMainComponent::paint(Graphics& g) {
    if ( hasCallback("paint") ) {
        LComponent::lpaint(g);
    } else {
        Component::paint(g);
    }
}

void LMainComponent::resized() {
    if ( hasCallback("resized") ) {
        LComponent::lresized();
    } else {
        Component::resized();
    }
}

void LMainComponent::mouseMove(const MouseEvent& e) {
    if ( hasCallback("mouseMove") ) {
        LComponent::lmouseMove(e);
    } else {
        Component::mouseMove(e);
    }
}

void LMainComponent::mouseEnter(const MouseEvent& e) {
    if ( hasCallback("mouseEnter") ) {
        LComponent::lmouseEnter(e);
    } else {
        Component::mouseEnter(e);
    }
}

void LMainComponent::mouseExit(const MouseEvent& e) {
    if ( hasCallback("mouseExit") ) {
        LComponent::lmouseExit(e);
    } else {
        Component::mouseExit(e);
    }
}

void LMainComponent::mouseDown(const MouseEvent& e) {
    if ( hasCallback("mouseDown") ) {
        LComponent::lmouseDown(e);
    } else {
        Component::mouseDown(e);
    }
}

void LMainComponent::mouseDrag(const MouseEvent& e) {
    if ( hasCallback("mouseDrag") ) {
        LComponent::lmouseDrag(e);
    } else {
        Component::mouseDrag(e);
    }
}

void LMainComponent::mouseUp(const MouseEvent& e) {
    if ( hasCallback("mouseUp") ) {
        LComponent::lmouseUp(e);
    } else {
        Component::mouseUp(e);
    }
}

void LMainComponent::mouseDoubleClick(const MouseEvent& e) {
    if ( hasCallback("mouseDoubleClick") ) {
        LComponent::lmouseDoubleClick(e);
    } else {
        Component::mouseDoubleClick(e);
    }
}

void LMainComponent::mouseWheelMove (const MouseEvent& e, const MouseWheelDetails& wheel) {
    if ( hasCallback("mouseWheelMove") ) {
        LComponent::lmouseWheelMove(e, wheel);
    } else {
        Component::mouseWheelMove(e, wheel);
    }
}

void LMainComponent::mouseMagnify (const MouseEvent& e, float scaleFactor) {
    if ( hasCallback("mouseMagnify") ) {
        LComponent::lmouseMagnify(e, scaleFactor);
    } else {
        Component::mouseMagnify(e, scaleFactor);
    }
}
