/************************************************************

 LTextButton.cpp

    @author Christophe Berbizier (cberbizier@peersuasive.com)
    @license GPLv3
    @copyright 


(c) 2013, Peersuasive Technologies

*************************************************************/

#include "LTextButton_inh.h"
const char LTextButton::className[] = "LTextButton";

const Luna<LTextButton>::PropertyType LTextButton::properties[] = {
    {"text", &LTextButton::getButtonText, &LTextButton::setButtonText},
    {0,0}
};

const Luna<LTextButton>::FunctionType LTextButton::methods[] = {
    method( LTextButton, setButtonText ),
    method( LTextButton, getButtonText ),
    method( LTextButton, buttonClicked ),
    {0,0}
};

LTextButton::LTextButton(lua_State *L) 
    : LComponent(L, this),
      TextButton()
{
    TextButton::setName(myName);
    reg("buttonClicked");
    TextButton::addListener(this);
}

LTextButton::~LTextButton() {}

int LTextButton::setButtonText(lua_State *L) {
    TextButton::setButtonText( LUA::getString(2) );
    return 0;
}

int LTextButton::getButtonText(lua_State *L) {
    return LUA::returnString( TextButton::getButtonText() );
}

void LTextButton::buttonClicked (Button* buttonThatWasClicked) {
    callback("buttonClicked");
}

int LTextButton::buttonClicked(lua_State *L) {
    set("buttonClicked");
    return 0;
}

void LTextButton::resized() {
    lresized();
}
