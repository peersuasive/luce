/************************************************************

 LMouseInputSource.cpp

    @author Christophe Berbizier (cberbizier@peersuasive.com)
    @license GPLv3
    @copyright 


(c) 2014, Peersuasive Technologies

*************************************************************/

#include "LMouseInputSource_inh.h"

const char LMouseInputSource::className[] = "LMouseInputSource";
const Luna<LMouseInputSource>::PropertyType LMouseInputSource::properties[] = {
    {"screenPosition", &LMouseInputSource::getScreenPosition, &LMouseInputSource::setScreenPosition},
    {"index", &LMouseInputSource::getIndex, &LBase::readOnly},
    {"touch", &LMouseInputSource::isTouch, &LBase::readOnly},
    {"mouse", &LMouseInputSource::isMouse, &LBase::readOnly},
    {"pressureValid", &LMouseInputSource::isPressureValid, &LBase::readOnly},
    {"pressure", &LMouseInputSource::getCurrentPressure, &LBase::readOnly},
    {0,0}
};
const Luna<LMouseInputSource>::FunctionType LMouseInputSource::methods[] = {
    method( LMouseInputSource, getIndex ),
    method( LMouseInputSource, getLastMouseDownPosition ),
    method( LMouseInputSource, getComponentUnderMouse ),
    method( LMouseInputSource, getCurrentPressure ),
    method( LMouseInputSource, hasMouseWheel ),
    method( LMouseInputSource, getCurrentModifiers ),
    method( LMouseInputSource, isPressureValid ),
    method( LMouseInputSource, getScreenPosition ),
    method( LMouseInputSource, setScreenPosition ),
    method( LMouseInputSource, hasMouseCursor ),
    method( LMouseInputSource, isUnboundedMouseMovementEnabled ),
    method( LMouseInputSource, getLastMouseDownTime ),
    method( LMouseInputSource, canDoUnboundedMovement ),
    method( LMouseInputSource, isTouch ),
    method( LMouseInputSource, isMouse ),
    method( LMouseInputSource, canHover ),
    method( LMouseInputSource, hasMouseMovedSignificantlySincePressed ),
    method( LMouseInputSource, getNumberOfMultipleClicks ),
    method( LMouseInputSource, isDragging ),
    method( LMouseInputSource, forceMouseCursorUpdate ),
    method( LMouseInputSource, hideCursor ),
    method( LMouseInputSource, showMouseCursor ),
    method( LMouseInputSource, triggerFakeMove ),
    method( LMouseInputSource, revealCursor ),
    method( LMouseInputSource, enableUnboundedMouseMovement ),
    {0,0}
};

const Luna<LMouseInputSource>::StaticType LMouseInputSource::statics[] = {
    {0,0}
};

LMouseInputSource::LMouseInputSource(lua_State *L)
    : LBase(L, "LMouseInputSource", true),
      MouseInputSource( *LUA::from_luce<LMouseInputSource,LMouseInputSource>(2) ) 
{
}

LMouseInputSource::LMouseInputSource(lua_State *L, const MouseInputSource *e)
    : LBase(L, "LMouseInputSource (dynamic)", true),
      MouseInputSource( *e )
{
}

LMouseInputSource::LMouseInputSource(lua_State *L, const MouseInputSource& e)
    : LBase(L),
      MouseInputSource( e )
{
    myName("LMouseInputSource (dynamic)");
}

LMouseInputSource::~LMouseInputSource() {}


/////// getters/setters
int LMouseInputSource::getScreenPosition ( lua_State* ) {
    return LUCE::luce_pushtable( MouseInputSource::getScreenPosition() );
}
int LMouseInputSource::setScreenPosition ( lua_State* ) {
    MouseInputSource::setScreenPosition(LUA::getPoint<float>(2));
    return 0;
}

/////// getters
int LMouseInputSource::getIndex ( lua_State* ) {
    return LUA::returnNumber( MouseInputSource::getIndex() );
}

int LMouseInputSource::getLastMouseDownPosition ( lua_State* ) {
    return LUCE::luce_pushtable( MouseInputSource::getLastMouseDownPosition() );
}

int LMouseInputSource::getComponentUnderMouse ( lua_State *L ) {
    return LUA::returnUserdata<LJComponent, Component>( MouseInputSource::getComponentUnderMouse() );
}

int LMouseInputSource::getCurrentPressure ( lua_State* ) {
    return LUA::returnNumber( MouseInputSource::getCurrentPressure() );
}

int LMouseInputSource::hasMouseWheel ( lua_State* ) {
    return LUA::returnBoolean( MouseInputSource::hasMouseWheel() );
}

int LMouseInputSource::getCurrentModifiers ( lua_State *L ) {
    //return LUA::returnUserdata<LModifierKeys, ModifierKeys>( MouseInputSource::getCurrentModifiers() );
    LModifierKeys *mods = 
        new LModifierKeys( L, MouseInputSource::getCurrentModifiers() );
    return LUA::storeAndReturnUserdata<LModifierKeys>( mods );
}

int LMouseInputSource::isPressureValid ( lua_State* ) {
    return LUA::returnBoolean( MouseInputSource::isPressureValid() );
}

int LMouseInputSource::hasMouseCursor ( lua_State* ) {
    return LUA::returnBoolean( MouseInputSource::hasMouseCursor() );
}

int LMouseInputSource::isUnboundedMouseMovementEnabled ( lua_State* ) {
    return LUA::returnBoolean( MouseInputSource::isUnboundedMouseMovementEnabled() );
}

int LMouseInputSource::getLastMouseDownTime ( lua_State *L ) {
    // CHECK
    // return LUA::storeAndReturnUserdata<LTime>( new LTime(L,
    //     MouseInputSource::getLastMouseDownTime()
    // ));
    lua_settop(LUA::Get(), 1); // added by TODO
    return LUA::TODO_OBJECT( "Time getLastMouseDownTime()" );
}

int LMouseInputSource::canDoUnboundedMovement ( lua_State* ) {
    return LUA::returnBoolean( MouseInputSource::canDoUnboundedMovement() );
}

int LMouseInputSource::isTouch ( lua_State* ) {
    return LUA::returnBoolean( MouseInputSource::isTouch() );
}

int LMouseInputSource::isMouse ( lua_State* ) {
    return LUA::returnBoolean( MouseInputSource::isMouse() );
}

int LMouseInputSource::canHover ( lua_State* ) {
    return LUA::returnBoolean( MouseInputSource::canHover() );
}

int LMouseInputSource::hasMouseMovedSignificantlySincePressed ( lua_State* ) {
    return LUA::returnBoolean( MouseInputSource::hasMouseMovedSignificantlySincePressed() );
}

int LMouseInputSource::getNumberOfMultipleClicks ( lua_State* ) {
    return LUA::returnNumber( MouseInputSource::getNumberOfMultipleClicks() );
}

int LMouseInputSource::isDragging ( lua_State* ) {
    return LUA::returnBoolean( MouseInputSource::isDragging() );
}

/////// setters
int LMouseInputSource::forceMouseCursorUpdate ( lua_State* ) {
    MouseInputSource::forceMouseCursorUpdate();
    return 0;
}

int LMouseInputSource::hideCursor ( lua_State* ) {
    MouseInputSource::hideCursor();
    return 0;
}

int LMouseInputSource::showMouseCursor ( lua_State* ) {
    // MouseInputSource::showMouseCursor(*LUA::from_luce<LMouseCursor>(2); // TODO);
    LUA::TODO_OBJECT( "showMouseCursor, *LUA::from_luce<LMouseCursor>(2); // TODO" );
    lua_settop(LUA::Get(), 1); // added by TODO
    return 0;
}

int LMouseInputSource::triggerFakeMove ( lua_State* ) {
    MouseInputSource::triggerFakeMove();
    return 0;
}

int LMouseInputSource::revealCursor ( lua_State* ) {
    MouseInputSource::revealCursor();
    return 0;
}

int LMouseInputSource::enableUnboundedMouseMovement ( lua_State* ) {
    bool isEnabled = LUA::getBoolean(2);
    bool keepCursorVisibleUntilOffscreen = LUA::checkAndGetBoolean(2, false);
    MouseInputSource::enableUnboundedMouseMovement( isEnabled, keepCursorVisibleUntilOffscreen );
    return 0;
}

