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
      StretchableLayoutResizerBar( LUA::from_luce<LStretchableLayoutManager>(2), 
                                        (int)LUA::getNumber(3), LUA::getBoolean(4) )
{
    StretchableLayoutResizerBar::setName(myName());
    REGISTER_CLASS(LStretchableLayoutResizerBar);
}
LStretchableLayoutResizerBar::~LStretchableLayoutResizerBar(){}

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
