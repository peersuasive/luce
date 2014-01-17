/************************************************************

 LStretchableLayoutManager.cpp

    @author Christophe Berbizier (cberbizier@peersuasive.com)
    @license GPLv3
    @copyright 


(c) 2014, Peersuasive Technologies

*************************************************************/

#include "LStretchableLayoutManager_inh.h"

////// static methods
const char LStretchableLayoutManager::className[] = "LStretchableLayoutManager";
const Luna<LStretchableLayoutManager>::PropertyType LStretchableLayoutManager::properties[] = {
    {0,0}
};
const Luna<LStretchableLayoutManager>::FunctionType LStretchableLayoutManager::methods[] = {
    method( LStretchableLayoutManager, getItemCurrentPosition ),
    method( LStretchableLayoutManager, getItemCurrentRelativeSize ),
    method( LStretchableLayoutManager, getItemLayout ),
    method( LStretchableLayoutManager, setItemLayout ),
    method( LStretchableLayoutManager, getItemCurrentAbsoluteSize ),
    method( LStretchableLayoutManager, clearAllItems ),
    method( LStretchableLayoutManager, setItemPosition ),
    method( LStretchableLayoutManager, layOutComponents ),
    {0,0}
};

LStretchableLayoutManager::LStretchableLayoutManager(lua_State *L)
    : LBase(L),
      StretchableLayoutManager()
{
    myName( LUA::checkAndGetString(2, "LStretchableLayoutManager") );
}

LStretchableLayoutManager::~LStretchableLayoutManager() {}

int LStretchableLayoutManager::getItemLayout ( lua_State* ) {
    double minimumSize, maximumSize, preferedSize;
    bool hasBeenSet = StretchableLayoutManager::getItemLayout( LUA::getNumber(2), minimumSize, maximumSize, preferedSize );
    if ( hasBeenSet )
        return LUA::returnTable( {minimumSize, maximumSize, preferedSize} );
    else
        return LUA::returnNil();
}

int LStretchableLayoutManager::setItemLayout ( lua_State* ) {
    int itemIndex = LUA::getNumber(2);
    Array<var> values = LUA::getList();
    StretchableLayoutManager::setItemLayout( itemIndex, values[0], values[1], values[2] );
    return 0;
}

/////// getters
int LStretchableLayoutManager::getItemCurrentPosition ( lua_State* ) {
    return LUA::returnNumber( StretchableLayoutManager::getItemCurrentPosition( LUA::getNumber(2) ) );
}

int LStretchableLayoutManager::getItemCurrentRelativeSize ( lua_State* ) {
    return LUA::returnNumber( StretchableLayoutManager::getItemCurrentRelativeSize( LUA::getNumber(2) ) );
}

int LStretchableLayoutManager::getItemCurrentAbsoluteSize ( lua_State* ) {
    return LUA::returnNumber( StretchableLayoutManager::getItemCurrentAbsoluteSize( LUA::getNumber(2) ) );
}

/////// setters
int LStretchableLayoutManager::clearAllItems ( lua_State* ) {
    StretchableLayoutManager::clearAllItems();
    return 0;
}

int LStretchableLayoutManager::setItemPosition ( lua_State* ) {
    Array<var> values = LUA::getList();
    StretchableLayoutManager::setItemPosition( values[0], values[1] );
    return 0;
}

int LStretchableLayoutManager::layOutComponents ( lua_State* ) {
    int n = LUA::getNumber(2);
    Array<Component*> lcomps = LUA::getComponentList(n, 2);
    Component *comps[lcomps.size()];
    for (int i=0; i<lcomps.size(); ++i)
        comps[i] = lcomps[i];

    int numComponents = lcomps.size();
    Array<var> pos = LUA::getList(2);

    bool vertically = LUA::checkAndGetBoolean(2, true);
    bool resizeOtherDimension = LUA::checkAndGetBoolean(2, true);
    StretchableLayoutManager::layOutComponents( comps, numComponents, 
            pos[0], pos[1], pos[2], pos[3], vertically, resizeOtherDimension );
    return 0;
}
