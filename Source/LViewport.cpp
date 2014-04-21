/************************************************************

 LViewport.cpp

    @author Christophe Berbizier (cberbizier@peersuasive.com)
    @license GPLv3
    @copyright 


(c) 2014, Peersuasive Technologies

*************************************************************/

#include "LViewport_inh.h"

const char LViewport::className[] = "LViewport";
const Luna<LViewport>::PropertyType LViewport::properties[] = {
    {"viewPosition", &LViewport::getViewPosition, &LViewport::setViewPosition},
    {"scrollBarThickness", &LViewport::getScrollBarThickness, &LViewport::setScrollBarThickness},
    {"viewedComponent", &LViewport::getViewedComponent, &LViewport::setViewedComponent},
    {0,0}
};
const Luna<LViewport>::FunctionType LViewport::methods[] = {
    method( LViewport, useMouseWheelMoveIfNeeded ),
    method( LViewport, getViewPosition ),
    method( LViewport, setViewPosition ),
    method( LViewport, getViewArea ),
    method( LViewport, getVerticalScrollBar ),
    method( LViewport, getHorizontalScrollBar ),
    method( LViewport, getViewWidth ),
    method( LViewport, getScrollBarThickness ),
    method( LViewport, setScrollBarThickness ),
    method( LViewport, getViewedComponent ),
    method( LViewport, setViewedComponent ),
    method( LViewport, getMaximumVisibleHeight ),
    method( LViewport, getViewHeight ),
    method( LViewport, autoScroll ),
    method( LViewport, isHorizontalScrollBarShown ),
    method( LViewport, isVerticalScrollBarShown ),
    method( LViewport, getMaximumVisibleWidth ),
    method( LViewport, getViewPositionY ),
    method( LViewport, getViewPositionX ),
    method( LViewport, setViewPositionProportionately ),
    method( LViewport, componentMovedOrResized ),
    method( LViewport, scrollBarMoved ),
    method( LViewport, setSingleStepSizes ),
    method( LViewport, setScrollBarsShown ),
    method( LViewport, visibleAreaChanged ),
    method( LViewport, viewedComponentChanged ),
    {0,0}
};

const Luna<LViewport>::StaticType LViewport::statics[] = {
    smethod( LViewport, respondsToKey ),
    {0,0}
};

LViewport::LViewport(lua_State *L)
    : LComponent(L, this),
      Viewport()
{
    Viewport::setName(myName());

    REGISTER_CLASS(LViewport);
}

LViewport::~LViewport() {}

/////// statics
int LViewport::s_respondsToKey ( lua_State* ) {
    return LUA::returnBoolean( Viewport::respondsToKey( *LUA::from_luce<LKeyPress>(2) ) );
}

/////// callbacks
void LViewport::visibleAreaChanged( const Rectangle<int>& newVisibleArea ) {
    if(hasCallback("visibleAreaChanged"))
        callback("visibleAreaChanged");
}
int LViewport::visibleAreaChanged(lua_State*){
    set("visibleAreaChanged");
    return 0;
}

void LViewport::viewedComponentChanged( Component* newComponent ) {
    if(hasCallback("viewedComponentChanged"))
        callback("viewedComponentChanged");
}
int LViewport::viewedComponentChanged(lua_State*){
    set("viewedComponentChanged");
    return 0;
}

void LViewport::mouseMove(const MouseEvent& e) {
    if(hasCallback("mouseMove"))
        LComponent::lmouseMove(e);
    else
        Viewport::mouseMove(e);
}

void LViewport::mouseEnter(const MouseEvent& e) {
    if(hasCallback("mouseEnter"))
        LComponent::lmouseEnter(e);
    else
        Viewport::mouseEnter(e);
}

void LViewport::mouseExit(const MouseEvent& e) {
    if(hasCallback("mouseExit"))
        LComponent::lmouseExit(e);
    else
        Viewport::mouseExit(e);
}

void LViewport::mouseDown(const MouseEvent& e) {
    if(hasCallback("mouseDown"))
        LComponent::lmouseDown(e);
    else
        Viewport::mouseDown(e);
}

void LViewport::mouseDrag(const MouseEvent& e) {
    if(hasCallback("mouseDrag"))
        LComponent::lmouseDrag(e);
    else
        Viewport::mouseDrag(e);
}

void LViewport::mouseUp(const MouseEvent& e) {
    if(hasCallback("mouseUp"))
        LComponent::lmouseUp(e);
    else
        Viewport::mouseUp(e);
}

void LViewport::mouseDoubleClick(const MouseEvent& e) {
    if(hasCallback("mouseDoubleClick"))
        LComponent::lmouseDoubleClick(e);
    else
        Viewport::mouseDoubleClick(e);
}

void LViewport::mouseWheelMove(const MouseEvent& e, const MouseWheelDetails& wheel) {
    if(hasCallback("mouseWheelMove"))
        if(LComponent::lmouseWheelMove(e, wheel))
            Viewport::mouseWheelMove(e,wheel);
    else
        Viewport::mouseWheelMove(e, wheel);
}

//void LViewport::mouseMagnify(const MouseEvent& e, float scaleFactor) {
//    if(hasCallback("mouseMagnify"))
//        LComponent::lmouseMagnify(e, scaleFactor);
//    else
//        Viewport::mouseMagnify(e, scaleFactor);
//}

bool LViewport::keyPressed(const KeyPress& k) {
    if(hasCallback("keyPressed"))
        return LComponent::lkeyPressed(k);
    else
        return Viewport::keyPressed(k);
}

/////// getters/setters
int LViewport::getViewPosition ( lua_State* ) {
    return LUCE::luce_pushtable( Viewport::getViewPosition() );
}
int LViewport::setViewPosition ( lua_State *L ) {
    Point<int> pos;
    if (lua_gettop(L) > 2) {
        int x = LUA::getNumber<int>(2); int y = LUA::getNumber<int>(2);
        pos = Point<int>(x,y);
    }
    Viewport::setViewPosition( pos );
    return 0;
}

int LViewport::getScrollBarThickness ( lua_State* ) {
    return LUA::returnNumber( Viewport::getScrollBarThickness() );
}
int LViewport::setScrollBarThickness ( lua_State* ) {
    Viewport::setScrollBarThickness(LUA::getNumber<int>());
    return 0;
}

int LViewport::getViewedComponent ( lua_State *L ) {
    return LUA::returnUserdata<LJComponent, Component>(Viewport::getViewedComponent());
}
int LViewport::setViewedComponent ( lua_State* ) {
    Component* newViewedComponent = LUA::from_luce<LComponent, Component>(2);
    bool deleteComponentWhenNoLongerNeeded = LUA::checkAndGetBoolean(2, true);
    Viewport::setViewedComponent( newViewedComponent, deleteComponentWhenNoLongerNeeded );
    return 0;
}

/////// getters
int LViewport::useMouseWheelMoveIfNeeded ( lua_State *L ) {
    MouseEvent m = *LUA::from_luce<LMouseEvent>(2);

    MouseWheelDetails md;
    lua_getfield(L, 2, "deltaX");
    md.deltaX = luaL_checknumber(L,-1);
    lua_getfield(L, 2, "deltaY");
    md.deltaY = luaL_checknumber(L,-1);
    lua_getfield(L, 2, "isReversed");
    md.deltaY = lua_toboolean(L,-1);
    lua_getfield(L, 2, "isSmooth");
    md.deltaY = lua_toboolean(L,-1);
    lua_remove(L,2);

    return LUA::returnBoolean( Viewport::useMouseWheelMoveIfNeeded( m, md ) );
}

int LViewport::getViewArea ( lua_State* ) {
    return LUCE::luce_pushtable( Viewport::getViewArea() );
}

int LViewport::getVerticalScrollBar ( lua_State *L ) {
    return LUA::returnUserdata<LScrollBar>( Viewport::getVerticalScrollBar() );
}

int LViewport::getHorizontalScrollBar ( lua_State *L ) {
    return LUA::returnUserdata<LScrollBar>( Viewport::getHorizontalScrollBar() );
}

int LViewport::getViewWidth ( lua_State* ) {
    return LUA::returnNumber( Viewport::getViewWidth() );
}

int LViewport::getMaximumVisibleHeight ( lua_State* ) {
    return LUA::returnNumber( Viewport::getMaximumVisibleHeight() );
}

int LViewport::getViewHeight ( lua_State* ) {
    return LUA::returnNumber( Viewport::getViewHeight() );
}

int LViewport::autoScroll ( lua_State* ) {
    int mouseX = LUA::getNumber<int>(2);
    int mouseY = LUA::getNumber<int>(2);
    int distanceFromEdge = LUA::getNumber<int>(2);
    int maximumSpeed = LUA::getNumber<int>(2);
    return LUA::returnBoolean( Viewport::autoScroll( mouseX, mouseY, distanceFromEdge, maximumSpeed ) );
}

int LViewport::isHorizontalScrollBarShown ( lua_State* ) {
    return LUA::returnBoolean( Viewport::isHorizontalScrollBarShown() );
}

int LViewport::isVerticalScrollBarShown ( lua_State* ) {
    return LUA::returnBoolean( Viewport::isVerticalScrollBarShown() );
}

int LViewport::getMaximumVisibleWidth ( lua_State* ) {
    return LUA::returnNumber( Viewport::getMaximumVisibleWidth() );
}

int LViewport::getViewPositionY ( lua_State* ) {
    return LUA::returnNumber( Viewport::getViewPositionY() );
}

int LViewport::getViewPositionX ( lua_State* ) {
    return LUA::returnNumber( Viewport::getViewPositionX() );
}

/////// setters
int LViewport::setViewPositionProportionately ( lua_State* ) {
    double proportionX = LUA::getNumber<double>(2);
    double proportionY = LUA::getNumber<double>(2);
    Viewport::setViewPositionProportionately( proportionX, proportionY );
    return 0;
}

int LViewport::componentMovedOrResized ( lua_State* ) {
    Component &comp = *LUA::from_luce<LComponent, Component>(2);
    bool wasMoved = LUA::getBoolean(2);
    bool wasResized = LUA::getBoolean(2);
    Viewport::componentMovedOrResized( comp, wasMoved, wasResized );
    return 0;
}

int LViewport::scrollBarMoved ( lua_State* ) {
    // ScrollBar* scrollbar_ = LUA::from_luce<LScrollBar>(2); // TODO;
    double newRangeStart = LUA::getNumber<double>(2);
    // Viewport::scrollBarMoved( scrollbar_, newRangeStart );
    LUA::TODO_OBJECT( "scrollBarMoved,  scrollbar_, newRangeStart " );
    lua_settop(LUA::Get(), 1); // added by TODO
    return 0;
}

int LViewport::setSingleStepSizes ( lua_State* ) {
    int stepX = LUA::getNumber<int>(2);
    int stepY = LUA::getNumber<int>(2);
    Viewport::setSingleStepSizes( stepX, stepY );
    return 0;
}

int LViewport::setScrollBarsShown ( lua_State* ) {
    bool showVerticalScrollbarIfNeeded = LUA::getBoolean(2);
    bool showHorizontalScrollbarIfNeeded = LUA::getBoolean(2);
    Viewport::setScrollBarsShown( showVerticalScrollbarIfNeeded, showHorizontalScrollbarIfNeeded );
    return 0;
}
