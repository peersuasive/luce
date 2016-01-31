/************************************************************

 LStretchableLayoutResizerBar.cpp

    @author Christophe Berbizier (cberbizier@peersuasive.com)
    @license GPLv3
    @copyright 


NOTE: should better be implemented in pure lua

(c) 2014, Peersuasive Technologies

*************************************************************/

#include "LStretchableLayoutResizerBar_inh.h"

////// static methods
const char LStretchableLayoutResizerBar::className[] = "LStretchableLayoutResizerBar";
const Luna<LStretchableLayoutResizerBar>::PropertyType LStretchableLayoutResizerBar::properties[] = {
    {0,0}
};
const Luna<LStretchableLayoutResizerBar>::FunctionType LStretchableLayoutResizerBar::methods[] = {
    method( LStretchableLayoutResizerBar, mouseDrag ),
    //method( LStretchableLayoutResizerBar, mouseDown ),
    method( LStretchableLayoutResizerBar, hasBeenMoved ),
    {0,0}
};

/////// ctor/dtor
const Luna<LStretchableLayoutResizerBar>::StaticType LStretchableLayoutResizerBar::statics[] = {
    {0,0}
};

LStretchableLayoutResizerBar::LStretchableLayoutResizerBar(lua_State *L)
    : LComponent(L, this),
      StretchableLayoutResizerBar(nullptr,0,0)
{
    StretchableLayoutResizerBar::setName(myName());
    REGISTER_CLASS(LStretchableLayoutResizerBar);
}


LStretchableLayoutResizerBar::LStretchableLayoutResizerBar(lua_State *L, StretchableLayoutManager *layout, int idx, bool vertical)
    : LComponent(L, this),
      StretchableLayoutResizerBar(layout, idx, vertical)
{
    StretchableLayoutResizerBar::setName(myName());
    REGISTER_CLASS(LStretchableLayoutResizerBar);
}
LStretchableLayoutResizerBar::~LStretchableLayoutResizerBar(){}

int LStretchableLayoutResizerBar::lnew(lua_State *L) {
    if(lua_gettop(L)>3) {
        int idx = lua_gettop(L)>4 && lua_type(L,2)==LUA_TSTRING ? 3 : 2; // named component ?
        ScopedPointer<StretchableLayoutManager> layout( LUA::from_luce<LStretchableLayoutManager>(idx) );
        int index = LUA::getNumber(idx);
        bool vertical = LUA::getBoolean(idx);
        return LUA::storeAndReturnUserdata<LStretchableLayoutResizerBar>(
                new LStretchableLayoutResizerBar(L, layout.release(), index, vertical));
    } else {
        LUCE::luce_error("LStretchableLayoutResizerBar: invalid constructor.");
    }
    return 0;
}


/////// callbacks
void LStretchableLayoutResizerBar::hasBeenMoved() {
    if (hasCallback("hasBeenMoved"))
        callback("hasBeenMoved");
    else
        StretchableLayoutResizerBar::hasBeenMoved();
}
int LStretchableLayoutResizerBar::hasBeenMoved(lua_State*){
    set("hasBeenMoved");
    return 0;
}

void LStretchableLayoutResizerBar::mouseDoubleClick(const MouseEvent& e) {
    if(hasCallback("mouseDoubleClick"))
        LComponent::lmouseDoubleClick(e);
    else
        StretchableLayoutResizerBar::mouseDoubleClick(e);
}

int LStretchableLayoutResizerBar::mouseDrag(lua_State*L) {
    StretchableLayoutResizerBar::mouseDrag( *LUA::toUserdata<LMouseEvent>(2) );
    return 0;
}

//int LStretchableLayoutResizerBar::mouseDrag ( lua_State* ) {
//    // StretchableLayoutResizerBar::mouseDrag(LUA::TODO_OBJECT_MouseEvent);
//    LUA::TODO_OBJECT( "mouseDrag, LUA::TODO_OBJECT_MouseEvent" );
//    lua_settop(LUA::Get(), 1); // added by TODO
//    return 0;
//}
//
//int LStretchableLayoutResizerBar::paint ( lua_State* ) {
//    // StretchableLayoutResizerBar::paint(LUA::TODO_OBJECT_Graphics);
//    LUA::TODO_OBJECT( "paint, LUA::TODO_OBJECT_Graphics" );
//    lua_settop(LUA::Get(), 1); // added by TODO
//    return 0;
//}
//
//int LStretchableLayoutResizerBar::mouseDown ( lua_State* ) {
//    // StretchableLayoutResizerBar::mouseDown(LUA::TODO_OBJECT_MouseEvent);
//    LUA::TODO_OBJECT( "mouseDown, LUA::TODO_OBJECT_MouseEvent" );
//    lua_settop(LUA::Get(), 1); // added by TODO
//    return 0;
//}
