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

    {"x", &LMouseEvent::getX, &LBase::readOnly},
    {"y", &LMouseEvent::getY, &LBase::readOnly},
    {"mods", &LMouseEvent::getMods, &LBase::readOnly},
    {"originalComponent", &LMouseEvent::getOriginalComponent, &LBase::readOnly},
    {"eventComponent", &LMouseEvent::getEventComponent, &LBase::readOnly},
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
const Luna<LMouseEvent>::StaticType LMouseEvent::statics[] = {
    {0,0}
};

LMouseEvent::LMouseEvent(lua_State *L)
    : LBase(L, "LMouseEvent", true),
      MouseEvent( *LUA::from_luce<LMouseEvent,MouseEvent>(2) )
{
}

LMouseEvent::LMouseEvent(lua_State *L, const MouseEvent *e)
    : LBase(L, "LMouseEvent (dynamic)", true),
      MouseEvent(*e) 
{
}

LMouseEvent::LMouseEvent(lua_State *L, const MouseEvent& e) 
    : LBase(L),
      MouseEvent(e)
{
    myName("LMouseEvent (dynamic)");
}

LMouseEvent::~LMouseEvent() {}

// custom methods
int LMouseEvent::getX(lua_State*) {
    return LUA::returnNumber( MouseEvent::x );
}
int LMouseEvent::getY(lua_State*) {
    return LUA::returnNumber( MouseEvent::y );
}

int LMouseEvent::getOriginalComponent(lua_State*) {
    return LUA::returnUserdata<LJComponent, Component>(MouseEvent::originalComponent);
}

int LMouseEvent::getEventComponent(lua_State*) {
    return LUA::returnUserdata<LJComponent, Component>(MouseEvent::eventComponent);
}

int LMouseEvent::getMods(lua_State* L) {
    return LUA::returnUserdata<LModifierKeys, ModifierKeys>( &this->mods );
}

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

int LMouseEvent::getEventRelativeTo ( lua_State* L) {
    LMouseEvent *lme = 
        new LMouseEvent( L, MouseEvent::getEventRelativeTo( LUA::from_luce<LComponent,Component>(2) ) );
    return LUA::storeAndReturnUserdata<LMouseEvent>( lme );
    //ScopedPointer<LMouseEvent> se (
    //    new LMouseEvent( L, MouseEvent::getEventRelativeTo( LUA::from_luce<LComponent,Component>(2) ) ) 
    //);
    //return LUA::storeAndReturnUserdata<LMouseEvent>( se.get() );
}

int LMouseEvent::getDistanceFromDragStartX ( lua_State* ) {
    return LUA::returnNumber( MouseEvent::getDistanceFromDragStartX() );
}

int LMouseEvent::getScreenPosition ( lua_State* ) {
    return LUCE::luce_pushtable( MouseEvent::getScreenPosition() );
}

int LMouseEvent::getPosition ( lua_State* ) {
    return LUCE::luce_pushtable( MouseEvent::getPosition() );
}

int LMouseEvent::withNewPosition ( lua_State* L ) {
    LMouseEvent *lme =
        new LMouseEvent( L, MouseEvent::withNewPosition( LUCE::luce_topoint<int>() ) );
    return LUA::storeAndReturnUserdata<LMouseEvent>( lme );
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
    return LUCE::luce_pushtable( MouseEvent::getMouseDownScreenPosition() );
}

int LMouseEvent::getOffsetFromDragStart ( lua_State* ) {
    return LUCE::luce_pushtable( MouseEvent::getOffsetFromDragStart() );
}

int LMouseEvent::getLengthOfMousePress ( lua_State* ) {
    return LUA::returnNumber( MouseEvent::getLengthOfMousePress() );
}

int LMouseEvent::getMouseDownPosition ( lua_State* ) {
    return LUCE::luce_pushtable( MouseEvent::getMouseDownPosition() );
}
