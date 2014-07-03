/************************************************************

 LJComponent.cpp

    @author Christophe Berbizier (cberbizier@peersuasive.com)
    @license GPLv3
    @copyright 


(c) 2013, Peersuasive Technologies

*************************************************************/

//class LPositioner : public Component::Positioner {
//    virtual void applyNewBounds(const Rectangle<int> &newBounds) override {
//        if(hasCallback("applyNewBounds")) {
//            callback("applyNewBounds")
//        }
//    }
//}

#include "LJComponent_inh.h"
const char LJComponent::className[] = "LJComponent";

const Luna<LJComponent>::PropertyType LJComponent::properties[] = {
    {0,0}
};

const Luna<LJComponent>::FunctionType LJComponent::methods[] = {
    method( LJComponent, startDragging ),
    method( LJComponent, addToDesktop ),
    method( LJComponent, removeFromDesktop ),

    method( LJComponent, startDraggingComponent ),
    method( LJComponent, dragComponent ),
    {0,0}
};

const Luna<LJComponent>::StaticType LJComponent::statics[] = {
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

int LJComponent::addToDesktop(lua_State *L) {
    LComponent::addToDesktop(L);
    this->pureBase(true);
    return 0;
}

int LJComponent::removeFromDesktop(lua_State *L) {
    LComponent::removeFromDesktop(L);
    if(pureBase())
        delete this;
    return 0;
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

bool LJComponent::keyPressed(const KeyPress& k) {
    if(hasCallback("keyPressed"))
        return LComponent::lkeyPressed(k);
    else
        return Component::keyPressed(k);
}

void LJComponent::visibilityChanged() {
    if(hasCallback("visibilityChanged"))
        LComponent::lvisibilityChanged();
}

int LJComponent::startDraggingComponent(lua_State* L) {
    MouseEvent *me = LUA::from_luce<LMouseEvent>(2);
    ComponentDragger::startDraggingComponent(this, *me);
    return 0;
}

int LJComponent::dragComponent(lua_State *L) {
    MouseEvent *me = LUA::from_luce<LMouseEvent>(2);
    ComponentBoundsConstrainer *c = nullptr;
    if(! lua_isnoneornil(L, 2))
        c = LUCE::luce_tocomponentboundsconstrainer(2);
    ComponentDragger::dragComponent(this, *me, c);
    if(c)
        delete c;
    return 0;
}
