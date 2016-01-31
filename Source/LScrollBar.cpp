/************************************************************

 LScrollBar.cpp

    @author Christophe Berbizier (cberbizier@peersuasive.com)
    @license GPLv3
    @copyright 


(c) 2014, Peersuasive Technologies

*************************************************************/

#include "LScrollBar_inh.h"

const char LScrollBar::className[] = "LScrollBar";
const Luna<LScrollBar>::PropertyType LScrollBar::properties[] = {
    //{"currentRange", &LScrollBar::getCurrentRange, &LScrollBar::setCurrentRange},
    //{"currentRangeStart", &LScrollBar::getCurrentRangeStart, &LScrollBar::setCurrentRangeStart},
    {0,0}
};
const Luna<LScrollBar>::FunctionType LScrollBar::methods[] = {
    method( LScrollBar, autoHides ),
    method( LScrollBar, getMaximumRangeLimit ),
    method( LScrollBar, moveScrollbarInPages ),
    method( LScrollBar, isVertical ),
    method( LScrollBar, getRangeLimit ),
    method( LScrollBar, getCurrentRange ),
    method( LScrollBar, setCurrentRange ),
    method( LScrollBar, scrollToBottom ),
    method( LScrollBar, moveScrollbarInSteps ),
    method( LScrollBar, getCurrentRangeSize ),
    method( LScrollBar, getMinimumRangeLimit ),
    method( LScrollBar, getCurrentRangeStart ),
    method( LScrollBar, setCurrentRangeStart ),
    method( LScrollBar, scrollToTop ),
    method( LScrollBar, addListener ),
    method( LScrollBar, setOrientation ),
    method( LScrollBar, removeListener ),
    method( LScrollBar, setSingleStepSize ),
    method( LScrollBar, setAutoHide ),
    method( LScrollBar, setButtonRepeatSpeed ),
    method( LScrollBar, setRangeLimits ),
    {0,0}
};

const Luna<LScrollBar>::StaticType LScrollBar::statics[] = {
    {0,0}
};

LScrollBar::LScrollBar(lua_State *L)
    : LComponent(L, this),
      ScrollBar(false)
{
    ScrollBar::setName(myName());
    //ScrollBar::addListener(this);

    REGISTER_CLASS(LScrollBar);
}

LScrollBar::LScrollBar(lua_State *L, bool isVertical)
    : LComponent(L, this),
      ScrollBar(isVertical)
{
    ScrollBar::setName(myName());
    //ScrollBar::addListener(this);

    REGISTER_CLASS(LScrollBar);
}


LScrollBar::~LScrollBar() {}

int LScrollBar::lnew(lua_State* L) {
    int idx = lua_gettop(L)>2 && lua_type(L,2)==LUA_TSTRING ? 3 : 2; // named component ?
    return LUA::storeAndReturnUserdata<LScrollBar>( new LScrollBar(L, LUA::getBoolean(idx)));
}

void LScrollBar::mouseMove(const MouseEvent& e) {
    if(hasCallback("mouseMove"))
        LComponent::lmouseMove(e);
    else
        ScrollBar::mouseMove(e);
}

void LScrollBar::mouseEnter(const MouseEvent& e) {
    if(hasCallback("mouseEnter"))
        LComponent::lmouseEnter(e);
    else
        ScrollBar::mouseEnter(e);
}

void LScrollBar::mouseExit(const MouseEvent& e) {
    if(hasCallback("mouseExit"))
        LComponent::lmouseExit(e);
    else
        ScrollBar::mouseExit(e);
}

void LScrollBar::mouseDown(const MouseEvent& e) {
    if(hasCallback("mouseDown"))
        LComponent::lmouseDown(e);
    else
        ScrollBar::mouseDown(e);
}

void LScrollBar::mouseDrag(const MouseEvent& e) {
    if(hasCallback("mouseDrag"))
        LComponent::lmouseDrag(e);
    else
        ScrollBar::mouseDrag(e);
}

void LScrollBar::mouseUp(const MouseEvent& e) {
    if(hasCallback("mouseUp"))
        LComponent::lmouseUp(e);
    else
        ScrollBar::mouseUp(e);
}

void LScrollBar::mouseDoubleClick(const MouseEvent& e) {
    if(hasCallback("mouseDoubleClick"))
        LComponent::lmouseDoubleClick(e);
    else
        ScrollBar::mouseDoubleClick(e);
}

void LScrollBar::mouseWheelMove(const MouseEvent& e, const MouseWheelDetails& wheel) {
    if(hasCallback("mouseWheelMove"))
        LComponent::lmouseWheelMove(e, wheel);
    else
        ScrollBar::mouseWheelMove(e, wheel);
}

bool LScrollBar::keyPressed(const KeyPress& k) {
    if(hasCallback("keyPressed"))
        return LComponent::lkeyPressed(k);
    else
        return ScrollBar::keyPressed(k);
}

int LScrollBar::getCurrentRange ( lua_State* ) {
    return LUCE::luce_pushtable( ScrollBar::getCurrentRange() );
}
int LScrollBar::setCurrentRange ( lua_State* L ) {
    Range<double> range;
    double newStart, newSize;
    if(lua_isnumber(L,2)) {
        double newStart = LUA::getNumber<double>(2);
        double newSize = LUA::getNumber<double>(2);
        range = Range<double>(newStart, newSize);
    } else {
        range = LUCE::luce_torange<double>(2);
    }
    NotificationType notification = 
            (NotificationType)LUA::checkAndGetNumber<int>(2, NotificationType::sendNotificationAsync);
    return LUA::returnBoolean( ScrollBar::setCurrentRange( range, notification ) );
}

int LScrollBar::getCurrentRangeStart ( lua_State* ) {
    return LUA::returnNumber( ScrollBar::getCurrentRangeStart() );
}
int LScrollBar::setCurrentRangeStart ( lua_State* ) {
    double newStart = LUA::getNumber<double>(2);
    NotificationType notification = 
            (NotificationType)LUA::checkAndGetNumber<int>(2, NotificationType::sendNotificationAsync);
    ScrollBar::setCurrentRangeStart( newStart, notification );
    return 0;
}

int LScrollBar::autoHides ( lua_State* ) {
    return LUA::returnBoolean( ScrollBar::autoHides() );
}

int LScrollBar::getMaximumRangeLimit ( lua_State* ) {
    return LUA::returnNumber( ScrollBar::getMaximumRangeLimit() );
}

int LScrollBar::moveScrollbarInSteps ( lua_State* ) {
    int howManySteps = LUA::getNumber<int>(2);
    NotificationType notification = 
            (NotificationType)LUA::checkAndGetNumber<int>(2, NotificationType::sendNotificationAsync);
    return LUA::returnBoolean( ScrollBar::moveScrollbarInSteps( howManySteps, notification ) );
}


int LScrollBar::moveScrollbarInPages ( lua_State* ) {
    int howManyPages = LUA::getNumber<int>(2);
    NotificationType notification = 
            (NotificationType)LUA::checkAndGetNumber<int>(2, NotificationType::sendNotificationAsync);
    return LUA::returnBoolean( ScrollBar::moveScrollbarInPages( howManyPages, notification ) );
}

int LScrollBar::isVertical ( lua_State* ) {
    return LUA::returnBoolean( ScrollBar::isVertical() );
}

int LScrollBar::getRangeLimit ( lua_State* ) {
    return LUCE::luce_pushtable( ScrollBar::getRangeLimit() );
}

int LScrollBar::scrollToBottom ( lua_State* ) {
    NotificationType notification = 
            (NotificationType)LUA::checkAndGetNumber<int>(2, NotificationType::sendNotificationAsync);
    return LUA::returnBoolean( ScrollBar::scrollToBottom( notification ) );
}

int LScrollBar::getCurrentRangeSize ( lua_State* ) {
    return LUA::returnNumber( ScrollBar::getCurrentRangeSize() );
}

int LScrollBar::getMinimumRangeLimit ( lua_State* ) {
    return LUA::returnNumber( ScrollBar::getMinimumRangeLimit() );
}

int LScrollBar::scrollToTop ( lua_State* ) {
    NotificationType notification = 
            (NotificationType)LUA::checkAndGetNumber<int>(2, NotificationType::sendNotificationAsync);
    return LUA::returnBoolean( ScrollBar::scrollToTop( notification ) );
}

int LScrollBar::addListener ( lua_State* ) {
    // ScrollBar::addListener(LUA::from_luce<LListener>(2); // TODO);
    LUA::TODO_OBJECT( "addListener, LUA::from_luce<LListener>(2); // TODO" );
    lua_settop(LUA::Get(), 1); // added by TODO
    return 0;
}

int LScrollBar::removeListener ( lua_State* ) {
    // ScrollBar::removeListener(LUA::from_luce<LListener>(2); // TODO);
    LUA::TODO_OBJECT( "removeListener, LUA::from_luce<LListener>(2); // TODO" );
    lua_settop(LUA::Get(), 1); // added by TODO
    return 0;
}

int LScrollBar::setOrientation ( lua_State* ) {
    ScrollBar::setOrientation(LUA::getBoolean());
    return 0;
}

int LScrollBar::setSingleStepSize ( lua_State* ) {
    ScrollBar::setSingleStepSize(LUA::getNumber<double>());
    return 0;
}

int LScrollBar::setAutoHide ( lua_State* ) {
    ScrollBar::setAutoHide(LUA::getBoolean());
    return 0;
}

int LScrollBar::setButtonRepeatSpeed ( lua_State* ) {
    int initialDelayInMillisecs = LUA::getNumber<int>(2);
    int repeatDelayInMillisecs = LUA::getNumber<int>(2);
    int minimumDelayInMillisecs = LUA::checkAndGetNumber<int>(2, -1);
    ScrollBar::setButtonRepeatSpeed( initialDelayInMillisecs, repeatDelayInMillisecs, minimumDelayInMillisecs );
    return 0;
}

int LScrollBar::setRangeLimits ( lua_State* L) {
    Range<double> newRangeLimit;
    if(lua_isnumber(L,2)) {
        double min = LUA::getNumber<double>(2);
        double max = LUA::getNumber<double>(2);
        newRangeLimit = Range<double>(min, max);
    }
    else {
        newRangeLimit = LUCE::luce_torange<double>(2);
    }
    NotificationType notification = 
            (NotificationType)LUA::checkAndGetNumber<int>(2, NotificationType::sendNotificationAsync);

    ScrollBar::setRangeLimits(newRangeLimit, notification);
    return 0;
}
