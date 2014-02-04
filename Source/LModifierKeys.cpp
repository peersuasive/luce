/************************************************************

 LModifierKeys.cpp

    @author Christophe Berbizier (cberbizier@peersuasive.com)
    @license GPLv3
    @copyright 


(c) 2014, Peersuasive Technologies

*************************************************************/

#include "LModifierKeys_inh.h"

// TODO: implement this in lua

////// static methods
const char LModifierKeys::className[] = "LModifierKeys";
const Luna<LModifierKeys>::PropertyType LModifierKeys::properties[] = {
    {0,0}
};
const Luna<LModifierKeys>::FunctionType LModifierKeys::methods[] = {
    method( LModifierKeys, isLeftButtonDown),
    method( LModifierKeys, getNumMouseButtonsDown),
    method( LModifierKeys, isAnyMouseButtonDown),
    method( LModifierKeys, isRightButtonDown),
    method( LModifierKeys, isMiddleButtonDown),

    method( LModifierKeys, isAnyModifierKeyDown),
    method( LModifierKeys, isCtrlDown),
    method( LModifierKeys, isCommandDown),
    method( LModifierKeys, isShiftDown),
    method( LModifierKeys, isAltDown),

    method( LModifierKeys, isPopupMenu),

    method( LModifierKeys, testFlags),
    method( LModifierKeys, getRawFlags),

    method( LModifierKeys, withOnlyMouseButtons),
    method( LModifierKeys, withoutMouseButtons),
    method( LModifierKeys, withFlags),
    method( LModifierKeys, withoutFlags),

    method( LModifierKeys, getCurrentModifiers),
    method( LModifierKeys, getCurrentModifiersRealtime),

    {0,0}
};

/////// ctor/dtor
const Luna<LModifierKeys>::StaticType LModifierKeys::statics[] = {
    {0,0}
};

LModifierKeys::LModifierKeys(lua_State *L)
    : LBase(L),
      ModifierKeys( LUA::getNumber() )
{
}

LModifierKeys::LModifierKeys(lua_State* L, const ModifierKeys &m) 
    : LBase(L),
      ModifierKeys( m )
{
}

LModifierKeys::~LModifierKeys() {}

int LModifierKeys::isLeftButtonDown ( lua_State* ) {
    return LUA::returnBoolean( ModifierKeys::isLeftButtonDown() );
}

int LModifierKeys::getNumMouseButtonsDown ( lua_State* ) {
    return LUA::returnNumber( ModifierKeys::getNumMouseButtonsDown() );
}

int LModifierKeys::isAnyMouseButtonDown ( lua_State* ) {
    return LUA::returnBoolean( ModifierKeys::isAnyMouseButtonDown() );
}

int LModifierKeys::isRightButtonDown ( lua_State* ) {
    return LUA::returnBoolean( ModifierKeys::isRightButtonDown() );
}

int LModifierKeys::isMiddleButtonDown ( lua_State* ) {
    return LUA::returnBoolean( ModifierKeys::isMiddleButtonDown() );
}


int LModifierKeys::isAnyModifierKeyDown ( lua_State* ) {
    return LUA::returnBoolean( ModifierKeys::isAnyModifierKeyDown() );
}

int LModifierKeys::isCtrlDown ( lua_State* ) {
    return LUA::returnBoolean( ModifierKeys::isCtrlDown() );
}

int LModifierKeys::isCommandDown ( lua_State* ) {
    return LUA::returnBoolean( ModifierKeys::isCommandDown() );
}

int LModifierKeys::isShiftDown ( lua_State* ) {
    return LUA::returnBoolean( ModifierKeys::isShiftDown() );
}

int LModifierKeys::isAltDown ( lua_State* ) {
    return LUA::returnBoolean( ModifierKeys::isAltDown() );
}


int LModifierKeys::isPopupMenu ( lua_State* ) {
    return LUA::returnBoolean( ModifierKeys::isPopupMenu() );
}


int LModifierKeys::testFlags ( lua_State* ) {
    int flagsToTest = LUA::getNumber(1);
    return LUA::returnBoolean( ModifierKeys::testFlags( flagsToTest ) );
}

int LModifierKeys::getRawFlags ( lua_State* ) {
    return LUA::returnNumber( ModifierKeys::getRawFlags() );
}

int LModifierKeys::withOnlyMouseButtons ( lua_State* ) {
    ModifierKeys m( ModifierKeys::withOnlyMouseButtons() );
    return LUA::returnUserdata<LModifierKeys, ModifierKeys>( &m );
}

// TODO

int LModifierKeys::withoutMouseButtons ( lua_State* ) {
    // return LUA::TODO_RETURN_OBJECT_ModifierKeys( ModifierKeys::withoutMouseButtons() );
    lua_settop(LUA::Get(), 1); // added by TODO
    return LUA::TODO_OBJECT( "ModifierKeys withoutMouseButtons()" );
}

int LModifierKeys::withFlags ( lua_State* ) {
    // int rawFlagsToSet = LUA::getNumber();
    // return LUA::TODO_RETURN_OBJECT_ModifierKeys( ModifierKeys::withFlags( rawFlagsToSet ) );
    lua_settop(LUA::Get(), 1); // added by TODO
    return LUA::TODO_OBJECT( "ModifierKeys withFlags( rawFlagsToSet )" );
}

int LModifierKeys::withoutFlags ( lua_State* ) {
    // int rawFlagsToClear = LUA::getNumber();
    // return LUA::TODO_RETURN_OBJECT_ModifierKeys( ModifierKeys::withoutFlags( rawFlagsToClear ) );
    lua_settop(LUA::Get(), 1); // added by TODO
    return LUA::TODO_OBJECT( "ModifierKeys withoutFlags( rawFlagsToClear )" );
}

int LModifierKeys::getCurrentModifiers ( lua_State* ) {
    // return LUA::TODO_RETURN_OBJECT_ModifierKeys( ModifierKeys::getCurrentModifiers() );
    lua_settop(LUA::Get(), 1); // added by TODO
    return LUA::TODO_OBJECT( "ModifierKeys getCurrentModifiers()" );
}

int LModifierKeys::getCurrentModifiersRealtime ( lua_State* ) {
    // return LUA::TODO_RETURN_OBJECT_ModifierKeys( ModifierKeys::getCurrentModifiersRealtime() );
    lua_settop(LUA::Get(), 1); // added by TODO
    return LUA::TODO_OBJECT( "ModifierKeys getCurrentModifiersRealtime()" );
}
