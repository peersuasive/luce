/************************************************************

 LImageButton.cpp

    @author Christophe Berbizier (cberbizier@peersuasive.com)
    @license GPLv3
    @copyright 


(c) 2013, Peersuasive Technologies

*************************************************************/

#include "LImageButton_inh.h"

const char LImageButton::className[] = "LImageButton";
const Luna<LImageButton>::PropertyType LImageButton::properties[] = {
    {0,0}
};
const Luna<LImageButton>::FunctionType LImageButton::methods[] = {
    method( LImageButton, setImages),
    method( LImageButton, getNormalImage ),
    method( LImageButton, getOverImage ),
    method( LImageButton, getDownImage ),

    method( LImageButton, addListener ),
    method( LImageButton, removeListener ),
    {0,0}
};

const Luna<LImageButton>::StaticType LImageButton::statics[] = {
    {0,0}
};

LImageButton::LImageButton(lua_State *L)
    : LButton(L, this),
      ImageButton()
{
    ImageButton::setName(myName());
    ImageButton::addListener(this);
    REGISTER_CLASS(LImageButton);
}

LImageButton::~LImageButton(){}

/////// callbacks
int LImageButton::removeListener ( lua_State* ) {
    ImageButton::removeListener(this);
    return 0;
}

int LImageButton::addListener ( lua_State* ) {
    ImageButton::addListener(this);
    return 0;
}

void LImageButton::buttonStateChanged() {
    LButton::lbuttonStateChanged();
}

void LImageButton::buttonClicked (Button* buttonThatWasClicked) {
    LButton::lbuttonClicked(buttonThatWasClicked);
}

void LImageButton::paintButton(Graphics& g, bool isMouseOver, bool isButtonDown) {
    if(hasCallback("paintButton"))
        LButton::lpaintButton(g, isMouseOver, isButtonDown);
    else
        ImageButton::paintButton(g, isMouseOver, isButtonDown);
}

void LImageButton::mouseMove(const MouseEvent& e) {
    if(hasCallback("mouseMove"))
        LComponent::lmouseMove(e);
    else
        ImageButton::mouseMove(e);
}

void LImageButton::mouseEnter(const MouseEvent& e) {
    if(hasCallback("mouseEnter"))
        LComponent::lmouseEnter(e);
    else
        ImageButton::mouseEnter(e);
}

void LImageButton::mouseExit(const MouseEvent& e) {
    if(hasCallback("mouseExit"))
        LComponent::lmouseExit(e);
    else
        ImageButton::mouseExit(e);
}

void LImageButton::mouseDown(const MouseEvent& e) {
    if(hasCallback("mouseDown"))
        LComponent::lmouseDown(e);
    else
        ImageButton::mouseDown(e);
}

void LImageButton::mouseDrag(const MouseEvent& e) {
    if(hasCallback("mouseDrag"))
        LComponent::lmouseDrag(e);
    else
        ImageButton::mouseDrag(e);
}

void LImageButton::mouseUp(const MouseEvent& e) {
    if(hasCallback("mouseUp"))
        LComponent::lmouseUp(e);
    else
        ImageButton::mouseUp(e);
}

void LImageButton::mouseDoubleClick(const MouseEvent& e) {
    if(hasCallback("mouseDoubleClick"))
        LComponent::lmouseDoubleClick(e);
    else
        ImageButton::mouseDoubleClick(e);
}

void LImageButton::mouseWheelMove (const MouseEvent& e, const MouseWheelDetails& wheel) {
    if(hasCallback("mouseWheelMove "))
        LComponent::lmouseWheelMove(e, wheel);
    else
        ImageButton::mouseWheelMove (e, wheel);
}

void LImageButton::mouseMagnify (const MouseEvent& e, float scaleFactor) {
    if(hasCallback("mouseMagnify "))
        LComponent::lmouseMagnify(e, scaleFactor);
    else
        ImageButton::mouseMagnify (e, scaleFactor);
}

bool LImageButton::keyPressed(const KeyPress& k) {
    if(hasCallback("keyPressed"))
        return LComponent::lkeyPressed(k);
    else
        return ImageButton::keyPressed(k);
}

int LImageButton::setImages(lua_State *L) {
    bool resizeNow = LUA::getBoolean(2);
    bool rescale   = LUA::getBoolean(2);
    bool preserve  = LUA::getBoolean(2);

    const Image *normal = LUA::from_luce<LImage,Image>(2);
    float opacityNormal = LUA::getNumber<float>(2);
    Colour overlayNormal = LUCE::luce_tocolour(2);

    const Image *over = LUA::from_luce<LImage,Image>(2);
    float opacityOver = LUA::getNumber<float>(2);
    Colour overlayOver = LUCE::luce_tocolour(2);

    const Image *down = LUA::from_luce<LImage,Image>(2);
    float opacityDown = LUA::getNumber<float>(2);
    Colour overlayDown = LUCE::luce_tocolour(2);

    float hitAlpha = LUA::checkAndGetNumber<float>(2, 0.0f);

    ImageButton::setImages( resizeNow, rescale, preserve, 
            *normal, opacityNormal, overlayNormal,
            *over, opacityOver, overlayOver,
            *down, opacityDown, overlayDown,
            hitAlpha);

    return 0;
}

int LImageButton::getNormalImage(lua_State*) {

    return 0;
}

int LImageButton::getOverImage(lua_State*) {

    return 0;
}

int LImageButton::getDownImage(lua_State*) {

    return 0;
}
