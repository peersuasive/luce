/************************************************************

 LHyperlinkButton.cpp

    @author Christophe Berbizier (cberbizier@peersuasive.com)
    @license GPLv3
    @copyright 


(c) 2014, Peersuasive Technologies

*************************************************************/

#include "LHyperlinkButton_inh.h"

const char LHyperlinkButton::className[] = "LHyperlinkButton";
const Luna<LHyperlinkButton>::PropertyType LHyperlinkButton::properties[] = {
    {"url", &LHyperlinkButton::getURL, &LHyperlinkButton::setURL},
    {"font", &LBase::writeOnly, &LHyperlinkButton::setFont},

    {0,0}
};
const Luna<LHyperlinkButton>::FunctionType LHyperlinkButton::methods[] = {
    method( LHyperlinkButton, getURL ),
    method( LHyperlinkButton, setURL ),
    method( LHyperlinkButton, setFont ),
    method( LHyperlinkButton, changeWidthToFitText ),
    {0,0}
};

const Luna<LHyperlinkButton>::StaticType LHyperlinkButton::statics[] = {
    {0,0}
};

LHyperlinkButton::LHyperlinkButton(lua_State *L)
    : LButton(L, this),
      HyperlinkButton()
{
    HyperlinkButton::setName(myName());
    HyperlinkButton::addListener(this);

    REGISTER_CLASS(LHyperlinkButton);
}

LHyperlinkButton::~LHyperlinkButton() {}

// callbacks
int LHyperlinkButton::addListener(lua_State*) {
    HyperlinkButton::addListener(this);
    return 0;
}

int LHyperlinkButton::removeListener(lua_State*) {
    HyperlinkButton::removeListener(this);
    return 0;
}

void LHyperlinkButton::paintButton(Graphics& g, bool isMouseOver, bool isButtonDown) {
    if(hasCallback("paintButton"))
        LButton::lpaintButton(g, isMouseOver, isButtonDown);
    else
        HyperlinkButton::paintButton(g, isMouseOver, isButtonDown);
}

void LHyperlinkButton::buttonStateChanged() {
    LButton::lbuttonStateChanged();
}

void LHyperlinkButton::buttonClicked (Button* buttonThatWasClicked) {
    LButton::lbuttonClicked(buttonThatWasClicked);
}

/////// getters/setters
int LHyperlinkButton::getURL ( lua_State *L ) {
    return LUA::returnString( HyperlinkButton::getURL().toString(true) );
}
int LHyperlinkButton::setURL ( lua_State* ) {
    HyperlinkButton::setURL( URL( LUA::getString() ) );
    return 0;
}

/////// setters
int LHyperlinkButton::setFont ( lua_State* ) {
    Font newFont = *LUA::from_luce<LFont>(2);
    bool resizeToMatchComponentHeight = LUA::checkAndGetBoolean(2, false);
    Justification justificationType ( 
            (Justification)LUA::checkAndGetNumber<int>(2, Justification::horizontallyCentred ) );
    HyperlinkButton::setFont( newFont, resizeToMatchComponentHeight, justificationType );
    return 0;
}

int LHyperlinkButton::changeWidthToFitText ( lua_State* ) {
    HyperlinkButton::changeWidthToFitText();
    return 0;
}
