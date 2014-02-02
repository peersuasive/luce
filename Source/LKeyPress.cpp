/************************************************************

 LKeyPress.cpp

    @author Christophe Berbizier (cberbizier@peersuasive.com)
    @license GPLv3
    @copyright 


(c) 2014, Peersuasive Technologies

*************************************************************/

#include "LKeyPress_inh.h"

////// static methods
const char LKeyPress::className[] = "LKeyPress";
const Luna<LKeyPress>::PropertyType LKeyPress::properties[] = {
    { "textCharacter", &LKeyPress::getTextCharacter, &LBase::readOnly },
    { "textDescriptionWithIcons", &LKeyPress::getTextDescriptionWithIcons, &LBase::readOnly },
    { "textDescription", &LKeyPress::getTextDescription, &LBase::readOnly },
    { "currentlyDown", &LKeyPress::isCurrentlyDown, &LBase::readOnly },
    { "keyCode", &LKeyPress::getKeyCode, &LBase::readOnly },
    { "currentlyDown", &LKeyPress::isCurrentlyDown, &LBase::readOnly },
    { "valid", &LKeyPress::isValid, &LBase::readOnly },
    { "modifiers", &LKeyPress::getModifiers, &LBase::readOnly },
    {0,0}
};
const Luna<LKeyPress>::FunctionType LKeyPress::methods[] = {
    method( LKeyPress, getTextCharacter ),
    method( LKeyPress, getTextDescriptionWithIcons ),
    method( LKeyPress, getTextDescription ),
    method( LKeyPress, isCurrentlyDown ),
    method( LKeyPress, getKeyCode ),
    method( LKeyPress, isKeyCode ),
    method( LKeyPress, isKeyCurrentlyDown ),
    method( LKeyPress, createFromDescription ),
    method( LKeyPress, isValid ),
    method( LKeyPress, getModifiers ),
    {0,0}
};

LKeyPress::LKeyPress(lua_State *L)
    : LBase(L, "LKeyPress", true),
      KeyPress()
{
    if ( lua_isstring(L, 2) )
        myName( lua_tostring(L, 2) );
}

LKeyPress::LKeyPress(lua_State *L, const KeyPress& class_)
    : LBase(L, "LKeyPress", true),
      KeyPress( class_ )
{
    if ( lua_isstring(L, 2) )
        myName( lua_tostring(L, 2) );
}

LKeyPress::~LKeyPress() {}

int LKeyPress::getTextCharacter ( lua_State* ) {
    return LUA::returnString( String(KeyPress::getTextCharacter()) );
}

int LKeyPress::getTextDescriptionWithIcons ( lua_State* ) {
    return LUA::returnString( KeyPress::getTextDescriptionWithIcons() );
}

int LKeyPress::getTextDescription ( lua_State* ) {
    return LUA::returnString( KeyPress::getTextDescription() );
}

int LKeyPress::isCurrentlyDown ( lua_State* ) {
    return LUA::returnBoolean( KeyPress::isCurrentlyDown() );
}

int LKeyPress::getKeyCode ( lua_State* ) {
    return LUA::returnNumber( KeyPress::getKeyCode() );
}

int LKeyPress::isKeyCode ( lua_State* ) {
    return LUA::returnBoolean( KeyPress::isKeyCode( LUA::getNumber<int>(2) ) );
}

int LKeyPress::isKeyCurrentlyDown ( lua_State* ) {
    int keyCode = LUA::getNumber<int>(2);
    return LUA::returnBoolean( KeyPress::isKeyCurrentlyDown( keyCode ) );
}

int LKeyPress::isValid ( lua_State* ) {
    return LUA::returnBoolean( KeyPress::isValid() );
}

int LKeyPress::getModifiers ( lua_State *L ) {
    return LUA::storeAndReturnUserdata<LModifierKeys>( new LModifierKeys(L,
        KeyPress::getModifiers()
    ));
}

int LKeyPress::createFromDescription ( lua_State* ) {
    return LUA::storeAndReturnUserdata<LKeyPress>( new LKeyPress(LUA::Get(),
        KeyPress::createFromDescription( LUA::getString(2) )
    ));
}
