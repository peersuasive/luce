/************************************************************

 LSlider.cpp

    @author Christophe Berbizier (cberbizier@peersuasive.com)
    @license GPLv3
    @copyright 


(c) 2014, Peersuasive Technologies

*************************************************************/

#include "LSlider_inh.h"

const char LSlider::className[] = "LSlider";
const Luna<LSlider>::PropertyType LSlider::properties[] = {
    {"textValueSuffix", &LSlider::getTextValueSuffix, &LSlider::setTextValueSuffix},
    {"sliderSnapsToMousePosition", &LSlider::getSliderSnapsToMousePosition, &LSlider::setSliderSnapsToMousePosition},
    {"velocityBasedMode", &LSlider::getVelocityBasedMode, &LSlider::setVelocityBasedMode},
    {"doubleClickReturnValue", &LSlider::getDoubleClickReturnValue, &LSlider::setDoubleClickReturnValue},
    {"maxValue", &LSlider::getMaxValue, &LSlider::setMaxValue},
    {"sliderStyle", &LSlider::getSliderStyle, &LSlider::setSliderStyle},
    {"value", &LSlider::getValue, &LSlider::setValue},
    {"minValue", &LSlider::getMinValue, &LSlider::setMinValue},
    {"mouseDragSensitivity", &LSlider::getMouseDragSensitivity, &LSlider::setMouseDragSensitivity},
    {"skewFactor", &LSlider::getSkewFactor, &LSlider::setSkewFactor},
    {0,0}
};
const Luna<LSlider>::FunctionType LSlider::methods[] = {
    method( LSlider, isHorizontal ),
    method( LSlider, getVelocityOffset ),
    method( LSlider, snapValue ),
    method( LSlider, getMinimum ),
    method( LSlider, isTextBoxEditable ),
    method( LSlider, getValueFromText ),
    method( LSlider, getTextBoxWidth ),
    method( LSlider, getNumDecimalPlacesToDisplay ),
    method( LSlider, getThumbBeingDragged ),
    method( LSlider, getPositionOfValue ),
    method( LSlider, getInterval ),
    method( LSlider, getTextValueSuffix ),
    method( LSlider, setTextValueSuffix ),
    method( LSlider, getTextBoxPosition ),
    method( LSlider, setTextBoxStyle ),

    method( LSlider, getMaximum ),
    method( LSlider, getSliderSnapsToMousePosition ),
    method( LSlider, setSliderSnapsToMousePosition ),
    method( LSlider, getVelocityBasedMode ),
    method( LSlider, setVelocityBasedMode ),
    method( LSlider, getDoubleClickReturnValue ),
    method( LSlider, setDoubleClickReturnValue ),
    method( LSlider, getMaxValueObject ),
    method( LSlider, getMaxValue ),
    method( LSlider, setMaxValue ),
    method( LSlider, getMinValueObject ),
    method( LSlider, proportionOfLengthToValue ),
    method( LSlider, valueToProportionOfLength ),
    method( LSlider, getTextFromValue ),
    method( LSlider, isVertical ),
    method( LSlider, getSliderStyle ),
    method( LSlider, setSliderStyle ),
    method( LSlider, getValueObject ),
    method( LSlider, getCurrentPopupDisplay ),
    method( LSlider, getVelocityThreshold ),
    method( LSlider, getValue ),
    method( LSlider, setValue ),
    method( LSlider, getTextBoxHeight ),
    method( LSlider, getVelocitySensitivity ),
    method( LSlider, getVelocityModeIsSwappable ),
    method( LSlider, getMinValue ),
    method( LSlider, setMinValue ),
    method( LSlider, getMouseDragSensitivity ),
    method( LSlider, setMouseDragSensitivity ),
    method( LSlider, getSkewFactor ),
    method( LSlider, setSkewFactor ),
    method( LSlider, setSkewFactorFromMidPoint ),
    method( LSlider, setScrollWheelEnabled ),
    method( LSlider, setChangeNotificationOnlyOnRelease ),
    method( LSlider, setTextBoxIsEditable ),
    method( LSlider, showTextBox ),
    method( LSlider, setVelocityModeParameters ),
    method( LSlider, setPopupDisplayEnabled ),
    method( LSlider, removeListener ),
    method( LSlider, addListener ),
    method( LSlider, setMinAndMaxValues ),
    method( LSlider, updateText ),
    method( LSlider, setPopupMenuEnabled ),
    method( LSlider, setRotaryParameters ),
    method( LSlider, setIncDecButtonsMode ),
    method( LSlider, hideTextBox ),
    method( LSlider, setRange ),
    method( LSlider, startedDragging ),
    method( LSlider, stoppedDragging ),
    method( LSlider, valueChanged ),
    {0,0}
};

const Luna<LSlider>::StaticType LSlider::statics[] = {
    {0,0}
};

LSlider::LSlider(lua_State *L)
    : LComponent(L, this),
      Slider()
{
    Slider::setName(myName());
    Slider::addListener(this);

    REGISTER_CLASS(LSlider);
}

LSlider::~LSlider() {}


int LSlider::addListener ( lua_State* ) {
    Slider::addListener(this);
    return 0;
}

int LSlider::removeListener ( lua_State* ) {
    Slider::removeListener(this);
    return 0;
}

/////// callbacks
void LSlider::stoppedDragging() {
    if(hasCallback("stoppedDragging"))
        callback("stoppedDragging");
}
int LSlider::stoppedDragging(lua_State*) {
    set("stoppedDragging");
    return 0;
}

void LSlider::startedDragging() {
    if(hasCallback("startedDragging"))
        callback("startedDragging");
}
int LSlider::startedDragging(lua_State*) {
    set("startedDragging");
    return 0;
}

void LSlider::valueChanged() {
    if(hasCallback("valueChanged"))
        callback("valueChanged");
}
int LSlider::valueChanged(lua_State*){
    set("valueChanged");
    return 0;
}

void LSlider::sliderValueChanged(Slider*) {
    if(hasCallback("sliderValueChanged"))
        callback("sliderValueChanged");
}
int LSlider::sliderValueChanged(lua_State*){
    set("sliderValueChanged");
    return 0;
}

void LSlider::sliderDragStarted(Slider*) {
    if(hasCallback("sliderDragStarted"))
        callback("sliderDragStarted");
}
int LSlider::sliderDragStarted(lua_State*){
    set("sliderDragStarted");
    return 0;
}

void LSlider::sliderDragEnded(Slider*) {
    if(hasCallback("sliderDragEnded"))
        callback("sliderDragEnded");
}
int LSlider::sliderDragEnded(lua_State*){
    set("sliderDragEnded");
    return 0;
}

void LSlider::mouseMove(const MouseEvent& e) {
    if(hasCallback("mouseMove"))
        LComponent::lmouseMove(e);
    else
        Slider::mouseMove(e);
}

void LSlider::mouseEnter(const MouseEvent& e) {
    if(hasCallback("mouseEnter"))
        LComponent::lmouseEnter(e);
    else
        Slider::mouseEnter(e);
}

void LSlider::mouseExit(const MouseEvent& e) {
    if(hasCallback("mouseExit"))
        LComponent::lmouseExit(e);
    else
        Slider::mouseExit(e);
}

void LSlider::mouseDown(const MouseEvent& e) {
    if(hasCallback("mouseDown"))
        LComponent::lmouseDown(e);
    else
        Slider::mouseDown(e);
}

void LSlider::mouseDrag(const MouseEvent& e) {
    if(hasCallback("mouseDrag"))
        LComponent::lmouseDrag(e);
    else
        Slider::mouseDrag(e);
}

void LSlider::mouseUp(const MouseEvent& e) {
    if(hasCallback("mouseUp"))
        LComponent::lmouseUp(e);
    else
        Slider::mouseUp(e);
}

void LSlider::mouseDoubleClick(const MouseEvent& e) {
    if(hasCallback("mouseDoubleClick"))
        LComponent::lmouseDoubleClick(e);
    else
        Slider::mouseDoubleClick(e);
}

void LSlider::mouseWheelMove(const MouseEvent& e, const MouseWheelDetails& wheel) {
    if(hasCallback("mouseWheelMove"))
        LComponent::lmouseWheelMove(e, wheel);
    else
        Slider::mouseWheelMove(e, wheel);
}

//void LSlider::mouseMagnify(const MouseEvent& e, float scaleFactor) {
//    if(hasCallback("mouseMagnify"))
//        LComponent::lmouseMagnify(e, scaleFactor);
//    else
//        Slider::mouseMagnify(e, scaleFactor);
//}

bool LSlider::keyPressed(const KeyPress& k) {
    if(hasCallback("keyPressed"))
        return LComponent::lkeyPressed(k);
    else
        return Slider::keyPressed(k);
}

/////// getters/setters
int LSlider::getTextValueSuffix ( lua_State* ) {
    return LUA::returnString( Slider::getTextValueSuffix() );
}
int LSlider::setTextValueSuffix ( lua_State* ) {
    Slider::setTextValueSuffix(LUA::getString());
    return 0;
}

int LSlider::getSliderSnapsToMousePosition ( lua_State* ) {
    return LUA::returnBoolean( Slider::getSliderSnapsToMousePosition() );
}
int LSlider::setSliderSnapsToMousePosition ( lua_State* ) {
    Slider::setSliderSnapsToMousePosition(LUA::getBoolean());
    return 0;
}

int LSlider::getVelocityBasedMode ( lua_State* ) {
    return LUA::returnBoolean( Slider::getVelocityBasedMode() );
}
int LSlider::setVelocityBasedMode ( lua_State* ) {
    Slider::setVelocityBasedMode(LUA::getBoolean());
    return 0;
}

int LSlider::getDoubleClickReturnValue ( lua_State* ) {
    bool isEnabled = LUA::getBoolean(2);
    return LUA::returnNumber( Slider::getDoubleClickReturnValue( isEnabled ) );
}
int LSlider::setDoubleClickReturnValue ( lua_State* ) {
    bool isDoubleClickEnabled = LUA::getBoolean(2);
    double valueToSetOnDoubleClick = LUA::getNumber<double>(2);
    Slider::setDoubleClickReturnValue( isDoubleClickEnabled, valueToSetOnDoubleClick );
    return 0;
}

int LSlider::getMaxValue ( lua_State* ) {
    return LUA::returnNumber( Slider::getMaxValue() );
}
int LSlider::setMaxValue ( lua_State* ) {
    double newValue = LUA::getNumber<double>(2);
    NotificationType notification = (NotificationType)LUA::getNumber<int>(2);
    bool allowNudgingOfOtherValues = LUA::checkAndGetBoolean(2, false);
    Slider::setMaxValue( newValue, notification, allowNudgingOfOtherValues );
    return 0;
}

int LSlider::getSliderStyle ( lua_State *L ) {
    return LUA::returnNumber<int>( (int)Slider::getSliderStyle() );
}
int LSlider::setSliderStyle ( lua_State* ) {
    Slider::setSliderStyle( (SliderStyle)LUA::getNumber<int>(2) );
    return 0;
}

int LSlider::getValue ( lua_State* ) {
    return LUA::returnNumber( Slider::getValue() );
}
int LSlider::setValue ( lua_State* ) {
    double newValue = LUA::getNumber<double>(2);
    NotificationType notification = (NotificationType)LUA::getNumber<int>(2);
    Slider::setValue( newValue, notification );
    return 0;
}

int LSlider::getMinValue ( lua_State* ) {
    return LUA::returnNumber( Slider::getMinValue() );
}
int LSlider::setMinValue ( lua_State* ) {
    double newValue = LUA::getNumber<double>(2);
    NotificationType notification = (NotificationType)LUA::getNumber<int>(2);
    bool allowNudgingOfOtherValues = LUA::checkAndGetBoolean(2, false);
    Slider::setMinValue( newValue, notification, allowNudgingOfOtherValues );
    return 0;
}

int LSlider::getMouseDragSensitivity ( lua_State* ) {
    return LUA::returnNumber( Slider::getMouseDragSensitivity() );
}
int LSlider::setMouseDragSensitivity ( lua_State* ) {
    Slider::setMouseDragSensitivity(LUA::getNumber<int>());
    return 0;
}

int LSlider::getSkewFactor ( lua_State* ) {
    return LUA::returnNumber( Slider::getSkewFactor() );
}
int LSlider::setSkewFactor ( lua_State* ) {
    Slider::setSkewFactor(LUA::getNumber<double>());
    return 0;
}

/////// getters
int LSlider::isHorizontal ( lua_State* ) {
    return LUA::returnBoolean( Slider::isHorizontal() );
}

int LSlider::getVelocityOffset ( lua_State* ) {
    return LUA::returnNumber( Slider::getVelocityOffset() );
}

int LSlider::snapValue ( lua_State* ) {
    double attemptedValue = LUA::getNumber<double>(2);
    Slider::DragMode dragMode = (Slider::DragMode)LUA::getNumber<int>(2);
    return LUA::returnNumber( Slider::snapValue( attemptedValue, dragMode ) );
}

int LSlider::getMinimum ( lua_State* ) {
    return LUA::returnNumber( Slider::getMinimum() );
}

int LSlider::isTextBoxEditable ( lua_State* ) {
    return LUA::returnBoolean( Slider::isTextBoxEditable() );
}

int LSlider::getValueFromText ( lua_State* ) {
    String text = LUA::getString(2);
    return LUA::returnNumber( Slider::getValueFromText( text ) );
}

int LSlider::getTextBoxWidth ( lua_State* ) {
    return LUA::returnNumber( Slider::getTextBoxWidth() );
}

int LSlider::getNumDecimalPlacesToDisplay ( lua_State* ) {
    return LUA::returnNumber( Slider::getNumDecimalPlacesToDisplay() );
}

int LSlider::getThumbBeingDragged ( lua_State* ) {
    return LUA::returnNumber( Slider::getThumbBeingDragged() );
}

int LSlider::getPositionOfValue ( lua_State* ) {
    double value = LUA::getNumber<double>(2);
    return LUA::returnNumber( Slider::getPositionOfValue( value ) );
}

int LSlider::getInterval ( lua_State* ) {
    return LUA::returnNumber( Slider::getInterval() );
}

int LSlider::getTextBoxPosition ( lua_State *L ) {
    return LUA::returnNumber( (int)Slider::getTextBoxPosition() );
}

int LSlider::getMaximum ( lua_State* ) {
    return LUA::returnNumber( Slider::getMaximum() );
}

int LSlider::getMaxValueObject ( lua_State *L ) {
    return LUA::returnString( Slider::getMaxValueObject().toString() );
}

int LSlider::getMinValueObject ( lua_State *L ) {
    return LUA::returnString( Slider::getMinValueObject().toString() );
}

int LSlider::proportionOfLengthToValue ( lua_State* ) {
    double proportion = LUA::getNumber<double>(2);
    return LUA::returnNumber( Slider::proportionOfLengthToValue( proportion ) );
}

int LSlider::valueToProportionOfLength ( lua_State* ) {
    double value = LUA::getNumber<double>(2);
    return LUA::returnNumber( Slider::valueToProportionOfLength( value ) );
}

int LSlider::getTextFromValue ( lua_State* ) {
    double value = LUA::getNumber<double>(2);
    return LUA::returnString( Slider::getTextFromValue( value ) );
}

int LSlider::isVertical ( lua_State* ) {
    return LUA::returnBoolean( Slider::isVertical() );
}

int LSlider::getValueObject ( lua_State *L ) {
    return LUA::returnString( Slider::getValueObject().toString() );
}

int LSlider::getCurrentPopupDisplay ( lua_State *L ) {
    return LUA::returnUserdata<LJComponent, Component>( Slider::getCurrentPopupDisplay() );
}

int LSlider::getVelocityThreshold ( lua_State* ) {
    return LUA::returnNumber( Slider::getVelocityThreshold() );
}

int LSlider::getTextBoxHeight ( lua_State* ) {
    return LUA::returnNumber( Slider::getTextBoxHeight() );
}

int LSlider::getVelocitySensitivity ( lua_State* ) {
    return LUA::returnNumber( Slider::getVelocitySensitivity() );
}

int LSlider::getVelocityModeIsSwappable ( lua_State* ) {
    return LUA::returnBoolean( Slider::getVelocityModeIsSwappable() );
}

/////// setters
int LSlider::setSkewFactorFromMidPoint ( lua_State* ) {
    Slider::setSkewFactorFromMidPoint(LUA::getNumber<double>());
    return 0;
}

int LSlider::setScrollWheelEnabled ( lua_State* ) {
    Slider::setScrollWheelEnabled(LUA::getBoolean());
    return 0;
}

int LSlider::setTextBoxStyle ( lua_State* ) {
    TextEntryBoxPosition newPosition = (TextEntryBoxPosition)LUA::getNumber<int>(2);
    bool isReadOnly = LUA::getBoolean(2);
    int textEntryBoxWidth = LUA::getNumber<int>(2);
    int textEntryBoxHeight = LUA::getNumber<int>(2);
    Slider::setTextBoxStyle( newPosition, isReadOnly, textEntryBoxWidth, textEntryBoxHeight );
    return 0;
}

int LSlider::setChangeNotificationOnlyOnRelease ( lua_State* ) {
    Slider::setChangeNotificationOnlyOnRelease(LUA::getBoolean());
    return 0;
}

int LSlider::setTextBoxIsEditable ( lua_State* ) {
    Slider::setTextBoxIsEditable(LUA::getBoolean());
    return 0;
}

int LSlider::showTextBox ( lua_State* ) {
    Slider::showTextBox();
    return 0;
}

int LSlider::setVelocityModeParameters ( lua_State* ) {
    double sensitivity = LUA::checkAndGetNumber<double>(2, 1.0);
    int threshold = LUA::checkAndGetNumber<int>(2, 1);
    double offset = LUA::checkAndGetNumber<double>(2, 0.0);
    bool userCanPressKeyToSwapMode = LUA::checkAndGetBoolean(2, true);
    Slider::setVelocityModeParameters( sensitivity, threshold, offset, userCanPressKeyToSwapMode );
    return 0;
}

int LSlider::setPopupDisplayEnabled ( lua_State* ) {
    bool isEnabled = LUA::getBoolean(2);
    Component *parentComponentToUse = LUA::from_luce<LComponent, Component>(2);
    Slider::setPopupDisplayEnabled( isEnabled, parentComponentToUse );
    return 0;
}

int LSlider::setMinAndMaxValues ( lua_State* ) {
    double newMinValue = LUA::getNumber<double>(2);
    double newMaxValue = LUA::getNumber<double>(2);
    NotificationType notification = (NotificationType)LUA::getNumber<int>(2);
    Slider::setMinAndMaxValues( newMinValue, newMaxValue, notification );
    return 0;
}

int LSlider::updateText ( lua_State* ) {
    Slider::updateText();
    return 0;
}

int LSlider::setPopupMenuEnabled ( lua_State* ) {
    Slider::setPopupMenuEnabled(LUA::getBoolean());
    return 0;
}

int LSlider::setRotaryParameters ( lua_State* ) {
    float startAngleRadians = LUA::getNumber<float>(2);
    float endAngleRadians = LUA::getNumber<float>(2);
    bool stopAtEnd = LUA::getBoolean(2);
    Slider::setRotaryParameters( startAngleRadians, endAngleRadians, stopAtEnd );
    return 0;
}

int LSlider::setIncDecButtonsMode ( lua_State* ) {
    Slider::setIncDecButtonsMode( (IncDecButtonMode)LUA::getNumber<int>(2) );
    return 0;
}

int LSlider::hideTextBox ( lua_State* ) {
    Slider::hideTextBox(LUA::getBoolean());
    return 0;
}

int LSlider::setRange ( lua_State* ) {
    double newMinimum = LUA::getNumber<double>(2);
    double newMaximum = LUA::getNumber<double>(2);
    double newInterval = LUA::checkAndGetNumber<double>(2, 0);
    Slider::setRange( newMinimum, newMaximum, newInterval );
    return 0;
}
