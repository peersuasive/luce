/************************************************************

 LKeyPress.cpp

    @author Christophe Berbizier (cberbizier@peersuasive.com)
    @license GPLv3
    @copyright 


(c) 2014, Peersuasive Technologies

*************************************************************/

// TODO: make a lua class of this

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
    : LBase(L, "LKeyPress (invalid)",true),
      KeyPress()
{
}

LKeyPress::LKeyPress(lua_State *L, const KeyPress& class_)
    : LBase(L, "LKeyPress (dyn)", true),
      KeyPress(class_)
{
}

int LKeyPress::lnew(lua_State *L)
{
    if (lua_isnoneornil(L,2))
        return LUA::storeAndReturnUserdata<LKeyPress>( new LKeyPress(L, KeyPress()) );

    int keyCode = 0;
    if ( lua_isnumber(L,2) )
        keyCode = LUA::getNumber<int>(2);
    else {
        String kc = LUA::getString(2);
        keyCode = (int)kc[0];
    }
 
    //int keyCode = LUA::getNumber<int>(2);
    if(lua_isnoneornil(L,2))
        return LUA::storeAndReturnUserdata<LKeyPress>( new LKeyPress(L, KeyPress(keyCode)) );
    
    ModifierKeys mods;
    if(lua_isnumber(L,2))
        mods = (ModifierKeys)LUA::getNumber<int>(2);
    else
        mods = *LUA::from_luce<LModifierKeys>(2);
    juce_wchar text = LUA::checkAndGetString(2, String::empty)[0];
    return LUA::storeAndReturnUserdata<LKeyPress>( new LKeyPress(L, KeyPress(keyCode, mods, text)) );

    // TODO: copy constructor
}

LKeyPress::~LKeyPress() {
    std::cout << "DESTROYING KEY PRESS" << std::endl;
}

int LKeyPress::isValid ( lua_State* ) {
    return LUA::returnBoolean( KeyPress::isValid() );
}

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

int LKeyPress::getModifiers ( lua_State *L ) {
    return LUA::storeAndReturnUserdata<LModifierKeys>( new LModifierKeys(L,
        KeyPress::getModifiers()
    ));
}

int LKeyPress::createFromDescription ( lua_State *L ) {
    return LUA::storeAndReturnUserdata<LKeyPress>( new LKeyPress(L,
        KeyPress::createFromDescription( LUA::getString(2) )
    ));
}
