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
    {0,0}
};
const Luna<LTextButton>::FunctionType LTextButton::methods[] = {
    method( LTextButton, getFont ),
    method( LTextButton, changeWidthToFitText ),

    method( LTextButton, addListener ),
    method( LTextButton, removeListener ),
    {0,0}
};

const Luna<LTextButton>::StaticType LTextButton::statics[] = {
    {0,0}
};

LTextButton::LTextButton(lua_State *L)
    : LButton(L, this),
      TextButton()
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

void LTextButton::paintButton(Graphics& g, bool isMouseOver, bool isButtonDown) {
    if(hasCallback("paintButton"))
        LButton::lpaintButton(g, isMouseOver, isButtonDown);
    else
        TextButton::paintButton(g, isMouseOver, isButtonDown);
}

void LTextButton::colourChanged () {
    if(hasCallback("colourChanged"))
        LComponent::lcolourChanged();
    else
        TextButton::colourChanged();
}

void LTextButton::mouseMove(const MouseEvent& e) {
    if(hasCallback("mouseMove"))
        LComponent::lmouseMove(e);
    else
        TextButton::mouseMove(e);
}

void LTextButton::mouseEnter(const MouseEvent& e) {
    if(hasCallback("mouseEnter"))
        LComponent::lmouseEnter(e);
    else
        TextButton::mouseEnter(e);
}

void LTextButton::mouseExit(const MouseEvent& e) {
    if(hasCallback("mouseExit"))
        LComponent::lmouseExit(e);
    else
        TextButton::mouseExit(e);
}

void LTextButton::mouseDown(const MouseEvent& e) {
    if(hasCallback("mouseDown"))
        LComponent::lmouseDown(e);
    else
        TextButton::mouseDown(e);
}

void LTextButton::mouseDrag(const MouseEvent& e) {
    if(hasCallback("mouseDrag"))
        LComponent::lmouseDrag(e);
    else
        TextButton::mouseDrag(e);
}

void LTextButton::mouseUp(const MouseEvent& e) {
    if(hasCallback("mouseUp"))
        LComponent::lmouseUp(e);
    else
        TextButton::mouseUp(e);
}

void LTextButton::mouseDoubleClick(const MouseEvent& e) {
    if(hasCallback("mouseDoubleClick"))
        LComponent::lmouseDoubleClick(e);
    else
        TextButton::mouseDoubleClick(e);
}

void LTextButton::mouseWheelMove (const MouseEvent& e, const MouseWheelDetails& wheel) {
    if(hasCallback("mouseWheelMove "))
        LComponent::lmouseWheelMove(e, wheel);
    else
        TextButton::mouseWheelMove (e, wheel);
}

void LTextButton::mouseMagnify (const MouseEvent& e, float scaleFactor) {
    if(hasCallback("mouseMagnify "))
        LComponent::lmouseMagnify(e, scaleFactor);
    else
        TextButton::mouseMagnify (e, scaleFactor);
}

bool LTextButton::keyPressed(const KeyPress& k) {
    if(hasCallback("keyPressed"))
        return LComponent::lkeyPressed(k);
    else
        return TextButton::keyPressed(k);
}

/////// getters
int LTextButton::getFont ( lua_State *L ) {
    LFont *f = new LFont( L, TextButton::getFont() );
    return LUA::storeAndReturnUserdata<LFont>( f );
}

/////// setters
int LTextButton::changeWidthToFitText ( lua_State* ) {
    TextButton::changeWidthToFitText(LUA::checkAndGetNumber(2, -1));
    return 0;
}
