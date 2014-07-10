/************************************************************

 LCallOutBox.cpp

    @author Christophe Berbizier (cberbizier@peersuasive.com)
    @license GPLv3
    @copyright 


(c) 2014, Peersuasive Technologies

*************************************************************/

#include "LCallOutBox_inh.h"

const char LCallOutBox::className[] = "LCallOutBox";
const Luna<LCallOutBox>::PropertyType LCallOutBox::properties[] = {
    {0,0}
};
const Luna<LCallOutBox>::FunctionType LCallOutBox::methods[] = {
    method( LCallOutBox, keyPressed ),
    method( LCallOutBox, hitTest ),
    method( LCallOutBox, dismiss ),
    method( LCallOutBox, handleCommandMessage ),
    method( LCallOutBox, resized ),
    method( LCallOutBox, inputAttemptWhenModal ),
    method( LCallOutBox, setArrowSize ),
    method( LCallOutBox, moved ),
    method( LCallOutBox, childBoundsChanged ),
    method( LCallOutBox, paint ),
    method( LCallOutBox, updatePosition ),
    {0,0}
};

const Luna<LCallOutBox>::StaticType LCallOutBox::statics[] = {
    smethod( LCallOutBox, launchAsynchronously ),
    {0,0}
};

LCallOutBox::LCallOutBox(lua_State *L)
    : LComponent(L, this),
      CallOutBox( *new Component(), Rectangle<int>(), NULL )
{
    // INVALID
    REGISTER_CLASS(LCallOutBox);
}

LCallOutBox::LCallOutBox(lua_State* L, Component& content, const Rectangle<int>& area, Component* parent )
    : LComponent(L, this),
      CallOutBox(content, area, parent)
{
    REGISTER_CLASS(LCallOutBox);
}

LCallOutBox::~LCallOutBox() {}

int LCallOutBox::lnew(lua_State* L) {
    Component* content = LUA::from_luce<LComponent,Component>(2);
    Rectangle<int> area = LUCE::luce_torectangle<int>(2);
    Component* parent = nullptr;
    if(!lua_isnoneornil(L,2))
        parent = LUA::from_luce<LComponent,Component>(2);
    return LUA::storeAndReturnUserdata<LCallOutBox>( new LCallOutBox(L,
        *content, area, parent
    ));
}

int LCallOutBox::s_launchAsynchronously ( lua_State *L ) {
    Component* content = LUA::from_luce<LComponent,Component>(1);
    Rectangle<int> area = LUCE::luce_torectangle<int>(1);
    Component* parent = nullptr;
    if(!lua_isnoneornil(L,1))
        parent = LUA::from_luce<LComponent,Component>(1);
    CallOutBox::launchAsynchronously(content, area, parent);
    return 0;
}

int LCallOutBox::keyPressed ( lua_State* ) {
    KeyPress keypress = *LUA::from_luce<LKeyPress>(2);
    return LUA::returnBoolean( CallOutBox::keyPressed( keypress ) );
}

int LCallOutBox::hitTest ( lua_State* ) {
    int x = LUA::getNumber<int>(2);
    int y = LUA::getNumber<int>(2);
    return LUA::returnBoolean( CallOutBox::hitTest( x, y ) );
}

int LCallOutBox::dismiss(lua_State*) {
    CallOutBox::dismiss();
    return 0;
}

int LCallOutBox::handleCommandMessage ( lua_State* ) {
    CallOutBox::handleCommandMessage(LUA::getNumber<int>());
    return 0;
}

int LCallOutBox::resized ( lua_State* ) {
    CallOutBox::resized();
    return 0;
}

int LCallOutBox::inputAttemptWhenModal ( lua_State* ) {
    CallOutBox::inputAttemptWhenModal();
    return 0;
}

int LCallOutBox::setArrowSize ( lua_State* ) {
    CallOutBox::setArrowSize(LUA::getNumber<float>());
    return 0;
}

int LCallOutBox::moved ( lua_State* ) {
    CallOutBox::moved();
    return 0;
}

int LCallOutBox::childBoundsChanged ( lua_State* ) {
    CallOutBox::childBoundsChanged(LUA::from_luce<LComponent, Component>(2));
    return 0;
}

int LCallOutBox::paint(lua_State*) {
    Graphics& g = (Graphics&)*LUA::from_luce<LGraphics>(2);
    CallOutBox::paint(g);
    return 0;
}

int LCallOutBox::updatePosition ( lua_State* ) {
    Rectangle<int> newAreaToPointTo ( LUCE::luce_torectangle<int>(2) );
    Rectangle<int> newAreaToFitIn ( LUCE::luce_torectangle<int>(2) );
    CallOutBox::updatePosition( newAreaToPointTo, newAreaToFitIn );
    return 0;
}
