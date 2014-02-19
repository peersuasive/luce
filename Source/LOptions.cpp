/************************************************************

 LOptions.cpp

    @author Christophe Berbizier (cberbizier@peersuasive.com)
    @license GPLv3
    @copyright 


(c) 2014, Peersuasive Technologies

*************************************************************/

#include "LOptions_inh.h"

const char LOptions::className[] = "LOptions";
const Luna<LOptions>::PropertyType LOptions::properties[] = {
    {0,0}
};
const Luna<LOptions>::FunctionType LOptions::methods[] = {
    method( LOptions, withTargetScreenArea ),
    method( LOptions, withMaximumNumColumns ),
    method( LOptions, withStandardItemHeight ),
    method( LOptions, withMinimumWidth ),
    method( LOptions, withTargetComponent ),
    method( LOptions, withItemThatMustBeVisible ),
    {0,0}
};

const Luna<LOptions>::StaticType LOptions::statics[] = {
    {0,0}
};

LOptions::LOptions(lua_State *L)
    : LBase(L, "LOptions", true),
      PopupMenu::Options()
{
}

LOptions::~LOptions() {}

int LOptions::withTargetComponent ( lua_State *L ) {
    Options::withTargetComponent( LUA::from_luce<LJComponent>(2) );
    return 1; // return self
}

int LOptions::withTargetScreenArea ( lua_State *L ) {
    Options::withTargetScreenArea( LUCE::luce_torectangle<int>(2) );
    return 1; // return self
}

int LOptions::withMaximumNumColumns ( lua_State *L ) {
    Options::withMaximumNumColumns( LUA::getNumber<int>(2) );
    return 1; // return self
}

int LOptions::withStandardItemHeight ( lua_State *L ) {
    Options::withStandardItemHeight( LUA::getNumber<int>(2) );
    return 1; // return self
}

int LOptions::withMinimumWidth ( lua_State *L ) {
    Options::withMinimumWidth( LUA::getNumber<int>(2) );
    return 1; // return self
}

int LOptions::withItemThatMustBeVisible ( lua_State *L ) {
    Options::withItemThatMustBeVisible( LUA::getNumber<int>(2) );
    return 1; // return self
}
