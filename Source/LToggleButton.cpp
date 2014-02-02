/************************************************************

 LToggleButton.cpp

    @author Christophe Berbizier (cberbizier@peersuasive.com)
    @license GPLv3
    @copyright 


(c) 2014, Peersuasive Technologies

*************************************************************/

#include "LToggleButton_inh.h"

////// static methods
const char LToggleButton::className[] = "LToggleButton";
const Luna<LToggleButton>::PropertyType LToggleButton::properties[] = {
    {0,0}
};
const Luna<LToggleButton>::FunctionType LToggleButton::methods[] = {
    method( LToggleButton, changeWidthToFitText ),
    method( LToggleButton, paintButton ),

    method( LToggleButton, addListener ),
    method( LToggleButton, removeListener ),
    {0,0}
};

/////// ctor/dtor
LToggleButton::LToggleButton(lua_State *L)
    : LButton(L, this),
      ToggleButton()
{
    ToggleButton::setName(myName());
    ToggleButton::addListener(this);
    REGISTER_CLASS(LToggleButton);
}

LToggleButton::~LToggleButton() {}

int LToggleButton::removeListener ( lua_State* ) {
    ToggleButton::removeListener(this);
    return 0;
}

int LToggleButton::addListener ( lua_State* ) {
    ToggleButton::addListener(this);
    return 0;
}

/////// callbacks
void LToggleButton::buttonStateChanged() {
    LButton::lbuttonStateChanged();
}

void LToggleButton::buttonClicked (Button* buttonThatWasClicked) {
    LButton::lbuttonClicked(buttonThatWasClicked);
}

int LToggleButton::paintButton ( lua_State* ) {
    if(hasCallback("paintButton"))
        callback("paintButton");
    return 0;
}

/////// setters
int LToggleButton::changeWidthToFitText ( lua_State* ) {
    ToggleButton::changeWidthToFitText();
    return 0;
}
