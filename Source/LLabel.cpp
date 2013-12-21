/************************************************************

 LLabel.cpp

    @author Christophe Berbizier (cberbizier@peersuasive.com)
    @license GPLv3
    @copyright 


(c) 2013, Peersuasive Technologies

*************************************************************/


#include "LLabel_inh.h"
const char LLabel::className[] = "LLabel";

const Luna<LLabel>::PropertyType LLabel::properties[] = {
    {"text", &LLabel::getText, &LLabel::setText},
    {"editable", &LLabel::isEditable, &LLabel::setEditable},
    {0,0}
};

const Luna<LLabel>::FunctionType LLabel::methods[] = {
    method( LLabel, setText ),
    method( LLabel, getText ),

    method( LLabel, attachToComponent ),
    method( LLabel, isAttachedOnLeft ),
    method( LLabel, setEditable ),
    method( LLabel, isEditable ),

    method( LLabel, labelTextChanged ),

    method( LLabel, removeListener ),

    {0,0}
};

LLabel::LLabel(lua_State *L)
    : LComponent(L, this),
      Label()
{
    Label::setName(myName);
    Label::addListener(this);

    reg("labelTextHasChanged");
}

LLabel::~LLabel() {
}

///

int LLabel::setText(lua_State *L) {
    String text = LUA::getString(2);
    //if( lua_isstring(L, 2)  ) {
        //Label::setText( text, LNotificationType::get( LUA::getString(2) ) );

    // I'm not sure this is really collected, so better use strings until checked
    //if( lua_isuserdata(L, 2)  ) {
    //    Label::setText( text, *(NotificationType*)(lua_touserdata(L, 2) ) );
    if( lua_isstring(L, 2)  ) {
        Label::setText( text, LNotificationType::get( LUA::getString(2) ) );
    } else {
        Label::setText( text, NotificationType::dontSendNotification );
    }

    return 0;
}

int LLabel::getText(lua_State *L) {
    return LUA::returnString( Label::getText() );
}

int LLabel::attachToComponent(lua_State *L) {
    Component *comp = LUA::to_juce<Component>(2);
    bool onLeft = ( LUA::checkAndGetBoolean(-1, true) );
    Label::attachToComponent(comp, onLeft);
    return 0;
}

int LLabel::isAttachedOnLeft(lua_State *L) {
    return ( LUA::returnBoolean(Label::isAttachedOnLeft()) );
}

int LLabel::setEditable(lua_State *L) { // bool sc, bool dc, bool lostOfFocusDiscardChanges
    bool editOnSingleClick = LUA::getBoolean(2);
    bool editOnDoubleClick = LUA::checkAndGetBoolean(2, false);
    bool lossOfFocusDiscardChanged = LUA::checkAndGetBoolean(2, false);
    Label::setEditable(editOnSingleClick, editOnDoubleClick, lossOfFocusDiscardChanged);
    return 0;
}

int LLabel::isEditable(lua_State *L) {
    return LUA::returnBoolean(Label::isEditable());
}

void LLabel::labelTextChanged(Label *label) {
    callback("labelTextHasChanged");
}
int LLabel::labelTextChanged(lua_State *L) {
    set("labelTextHasChanged");

    return 0;
}

int LLabel::addListener(lua_State *L) {
    // may want to get a listener, but let's keep it simple
    // for the time being
    Label::addListener(this);
    return 0;
}

int LLabel::removeListener(lua_State *L) {
    Label::removeListener(this);
    return 0;
}
