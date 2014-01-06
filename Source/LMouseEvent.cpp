/************************************************************

 LMouseEvent.cpp

    @author Christophe Berbizier (cberbizier@peersuasive.com)
    @license GPLv3
    @copyright 


(c) 2014, Peersuasive Technologies

*************************************************************/

#include "LMouseEvent_inh.h"

////// static methods
const char LMouseEvent::className[] = "LMouseEvent";
const Luna<LMouseEvent>::PropertyType LMouseEvent::properties[] = {
    {"doubleClickTimeout", &LMouseEvent::getDoubleClickTimeout, &LMouseEvent::setDoubleClickTimeout},
    {0,0}
};
const Luna<LMouseEvent>::FunctionType LMouseEvent::methods[] = {
    method( LMouseEvent, getMouseDownY ),
    method( LMouseEvent, getMouseDownScreenX ),
    method( LMouseEvent, getNumberOfClicks ),
    method( LMouseEvent, mouseWasClicked ),
    method( LMouseEvent, getEventRelativeTo ),
    method( LMouseEvent, getDistanceFromDragStartX ),
    method( LMouseEvent, getScreenPosition ),
    method( LMouseEvent, getPosition ),
    method( LMouseEvent, getDoubleClickTimeout ),
    method( LMouseEvent, setDoubleClickTimeout ),
    method( LMouseEvent, withNewPosition ),
    method( LMouseEvent, getMouseDownX ),
    method( LMouseEvent, getDistanceFromDragStartY ),
    method( LMouseEvent, getMouseDownScreenY ),
    method( LMouseEvent, getScreenX ),
    method( LMouseEvent, getScreenY ),
    method( LMouseEvent, getDistanceFromDragStart ),
    method( LMouseEvent, getMouseDownScreenPosition ),
    method( LMouseEvent, getOffsetFromDragStart ),
    method( LMouseEvent, getLengthOfMousePress ),
    method( LMouseEvent, getMouseDownPosition ),
    {0,0}
};

/*
    MouseEvent (MouseInputSource source,
                Point<int> position,
                ModifierKeys modifiers,
                Component* eventComponent,
                Component* originator,
                Time eventTime,
                Point<int> mouseDownPos,
                Time mouseDownTime,
                int numberOfClicks,
                bool mouseWasDragged) noexcept;
*/

/////// ctor/dtor
LMouseEvent::LMouseEvent(lua_State *L)
    : LBase(L),
      MouseEvent( 
            *LUA::raw_cast<MouseInputSource>(2),
            LUA::getPoint(2),
            *LUA::raw_cast<ModifierKeys>(2),
            LUA::from_luce<Component>(2),
            LUA::from_luce<Component>(2),
            *LUA::raw_cast<Time>(2),
            LUA::getPoint(2),
            *LUA::raw_cast<Time>(2),
            LUA::getNumber(2),
            LUA::getBoolean()
      )
{}

LMouseEvent::LMouseEvent(lua_State *L, const MouseEvent& e) 
    : LBase(L),
      MouseEvent(e)
{}

LMouseEvent::~LMouseEvent(){}

/////// callbacks
/////// getters/setters
int LMouseEvent::getDoubleClickTimeout ( lua_State* ) {
    return LUA::returnNumber( MouseEvent::getDoubleClickTimeout() );
}
int LMouseEvent::setDoubleClickTimeout ( lua_State* ) {
    MouseEvent::setDoubleClickTimeout(LUA::getNumber());
    return 0;
}

/////// getters
int LMouseEvent::getMouseDownY ( lua_State* ) {
    return LUA::returnNumber( MouseEvent::getMouseDownY() );
}

int LMouseEvent::getMouseDownScreenX ( lua_State* ) {
    return LUA::returnNumber( MouseEvent::getMouseDownScreenX() );
}

int LMouseEvent::getNumberOfClicks ( lua_State* ) {
    return LUA::returnNumber( MouseEvent::getNumberOfClicks() );
}

int LMouseEvent::mouseWasClicked ( lua_State* ) {
    return LUA::returnBoolean( MouseEvent::mouseWasClicked() );
}

int LMouseEvent::getEventRelativeTo ( lua_State* ) {
    return LUA::returnUserdata<LMouseEvent, MouseEvent>( 
            new MouseEvent( MouseEvent::getEventRelativeTo( LUA::from_luce<Component>(2) ) ) );
}

int LMouseEvent::getDistanceFromDragStartX ( lua_State* ) {
    return LUA::returnNumber( MouseEvent::getDistanceFromDragStartX() );
}

int LMouseEvent::getScreenPosition ( lua_State* ) {
    // return LUA::TODO_RETURN_OBJECT_Point( MouseEvent::getScreenPosition() );
    lua_settop(LUA::Get(), 1); // added by TODO
    return LUA::TODO_OBJECT( "Point getScreenPosition()" );
}

int LMouseEvent::getPosition ( lua_State* ) {
    // return LUA::TODO_RETURN_OBJECT_Point( MouseEvent::getPosition() );
    lua_settop(LUA::Get(), 1); // added by TODO
    return LUA::TODO_OBJECT( "Point getPosition()" );
}

int LMouseEvent::withNewPosition ( lua_State* ) {
    // Point<int> newPosition = LUA::TODO_OBJECT_Point;
    // return LUA::TODO_RETURN_OBJECT_MouseEvent( MouseEvent::withNewPosition( newPosition ) );
    lua_settop(LUA::Get(), 1); // added by TODO
    return LUA::TODO_OBJECT( "MouseEvent withNewPosition( newPosition )" );
}

int LMouseEvent::getMouseDownX ( lua_State* ) {
    return LUA::returnNumber( MouseEvent::getMouseDownX() );
}

int LMouseEvent::getDistanceFromDragStartY ( lua_State* ) {
    return LUA::returnNumber( MouseEvent::getDistanceFromDragStartY() );
}

int LMouseEvent::getMouseDownScreenY ( lua_State* ) {
    return LUA::returnNumber( MouseEvent::getMouseDownScreenY() );
}

int LMouseEvent::getScreenX ( lua_State* ) {
    return LUA::returnNumber( MouseEvent::getScreenX() );
}

int LMouseEvent::getScreenY ( lua_State* ) {
    return LUA::returnNumber( MouseEvent::getScreenY() );
}

int LMouseEvent::getDistanceFromDragStart ( lua_State* ) {
    return LUA::returnNumber( MouseEvent::getDistanceFromDragStart() );
}

int LMouseEvent::getMouseDownScreenPosition ( lua_State* ) {
    // return LUA::TODO_RETURN_OBJECT_Point( MouseEvent::getMouseDownScreenPosition() );
    lua_settop(LUA::Get(), 1); // added by TODO
    return LUA::TODO_OBJECT( "Point getMouseDownScreenPosition()" );
}

int LMouseEvent::getOffsetFromDragStart ( lua_State* ) {
    // return LUA::TODO_RETURN_OBJECT_Point( MouseEvent::getOffsetFromDragStart() );
    lua_settop(LUA::Get(), 1); // added by TODO
    return LUA::TODO_OBJECT( "Point getOffsetFromDragStart()" );
}

int LMouseEvent::getLengthOfMousePress ( lua_State* ) {
    return LUA::returnNumber( MouseEvent::getLengthOfMousePress() );
}

int LMouseEvent::getMouseDownPosition ( lua_State* ) {
    // return LUA::TODO_RETURN_OBJECT_Point( MouseEvent::getMouseDownPosition() );
    lua_settop(LUA::Get(), 1); // added by TODO
    return LUA::TODO_OBJECT( "Point getMouseDownPosition()" );
}

/////// setters
