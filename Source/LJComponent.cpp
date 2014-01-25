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
}

LJComponent::~LJComponent() {
    Component::deleteAllChildren();
}

int LJComponent::startDragging(lua_State*) {
    String desc = LUA::getString(2);
    Rectangle<int> pos = LUA::getRectangle(2);
    if ( ! desc.isEmpty() ) {
        if( DragAndDropContainer *const dragContainer = 
                DragAndDropContainer::findParentDragContainerFor( this ) ) {
            Image dragImage (Component::createComponentSnapshot (pos, true));
            //Point<int> imageOffset (pos.getPosition() - e.getPosition());
            dragContainer->startDragging (desc, this, dragImage, true);//, &imageOffset);
        }
    }
    return 0;
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
    if ( hasCallback("mouseMove") ) {
        LComponent::lmouseMove(e);
    } else {
        Component::mouseMove(e);
    }
}

void LJComponent::mouseEnter(const MouseEvent& e) {
    if ( hasCallback("mouseEnter") ) {
        LComponent::lmouseEnter(e);
    } else {
        Component::mouseEnter(e);
    }
}

void LJComponent::mouseExit(const MouseEvent& e) {
    if ( hasCallback("mouseExit") ) {
        LComponent::lmouseExit(e);
    } else {
        Component::mouseExit(e);
    }
}

void LJComponent::mouseDown(const MouseEvent& e) {
    if ( hasCallback("mouseDown") ) {
        LComponent::lmouseDown(e);
    } else {
        Component::mouseDown(e);
    }
}

void LJComponent::mouseDrag(const MouseEvent& e) {
    if ( hasCallback("mouseDrag") )
        LComponent::lmouseDrag(e);
}

void LJComponent::mouseUp(const MouseEvent& e) {
    if ( hasCallback("mouseUp") ) {
        LComponent::lmouseUp(e);
    } else {
        Component::mouseUp(e);
    }
}

void LJComponent::mouseDoubleClick(const MouseEvent& e) {
    if ( hasCallback("mouseDoubleClick") ) {
        LComponent::lmouseDoubleClick(e);
    } else {
        Component::mouseDoubleClick(e);
    }
}

void LJComponent::mouseWheelMove (const MouseEvent& e, const MouseWheelDetails& wheel) {
    if ( hasCallback("mouseWheelMove") ) {
        LComponent::lmouseWheelMove(e, wheel);
    } else {
        Component::mouseWheelMove(e, wheel);
    }
}

void LJComponent::mouseMagnify (const MouseEvent& e, float scaleFactor) {
    if ( hasCallback("mouseMagnify") ) {
        LComponent::lmouseMagnify(e, scaleFactor);
    } else {
        Component::mouseMagnify(e, scaleFactor);
    }
}
