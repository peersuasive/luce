/************************************************************

 LTextButton.cpp

    @author Christophe Berbizier (cberbizier@peersuasive.com)
    @license GPLv3
    @copyright 


(c) 2013, Peersuasive Technologies

*************************************************************/

#include "LTextButton_inh.h"

////// static methods
const char LTextButton::className[] = "LTextButton";
const Luna<LTextButton>::PropertyType LTextButton::properties[] = {
    {0,0}
};
const Luna<LTextButton>::FunctionType LTextButton::methods[] = {
    method( LTextButton, getFont ),
    method( LTextButton, changeWidthToFitText ),
    method( LTextButton, paintButton ),
    method( LTextButton, colourChanged ),

    method( LTextButton, addListener ),
    method( LTextButton, removeListener ),
    {0,0}
};

/////// ctor/dtor
const Luna<LTextButton>::StaticType LTextButton::statics[] = {
    {0,0}
};

LTextButton::LTextButton(lua_State *L)
    : LButton(L, this),
      TextButton( /* TODO: add args */ )
{
    TextButton::setName(myName());
    TextButton::addListener(this);
    REGISTER_CLASS(LTextButton);
}

LTextButton::~LTextButton(){}

/////// callbacks
int LTextButton::removeListener ( lua_State* ) {
    TextButton::removeListener(this);
    return 0;
}

int LTextButton::addListener ( lua_State* ) {
    TextButton::addListener(this);
    return 0;
}

void LTextButton::buttonStateChanged() {
    LButton::lbuttonStateChanged();
}

void LTextButton::buttonClicked (Button* buttonThatWasClicked) {
    LButton::lbuttonClicked(buttonThatWasClicked);
}

/////// getters
int LTextButton::getFont ( lua_State* ) {
    // return LUA::TODO_RETURN_OBJECT_Font( TextButton::getFont() );
    lua_settop(LUA::Get(), 1); // added by TODO
    return LUA::TODO_OBJECT( "Font getFont()" );
}

/////// setters
int LTextButton::changeWidthToFitText ( lua_State* ) {
    TextButton::changeWidthToFitText(LUA::checkAndGetNumber(2, -1));
    return 0;
}

int LTextButton::paintButton ( lua_State* ) {
    // Graphics graphics_ = LUA::TODO_OBJECT_Graphics;
    //bool isMouseOverButton = LUA::getBoolean();
    //bool isButtonDown = LUA::getBoolean();
    // TextButton::paintButton( graphics_, isMouseOverButton, isButtonDown );
    LUA::TODO_OBJECT( "paintButton,  graphics_, isMouseOverButton, isButtonDown " );
    lua_settop(LUA::Get(), 1); // added by TODO
    return 0;
}

int LTextButton::colourChanged ( lua_State* ) {
    TextButton::colourChanged();
    return 0;
}
