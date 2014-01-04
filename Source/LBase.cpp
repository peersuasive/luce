/************************************************************

 LBase.cpp

    @author Christophe Berbizier (cberbizier@peersuasive.com)
    @license GPLv3
    @copyright 


(c) 2013-2014, Peersuasive Technologies

*************************************************************/

#include "LBase_inh.h"
const char LBase::className[] = "LBase";

const Luna<LBase>::PropertyType LBase::properties[] = {
    {0,0}
};

const Luna<LBase>::FunctionType LBase::methods[] = {
    {0,0}
};

LBase::LBase(lua_State *Ls)
{
    LUA::Set(Ls);
    L = Ls;
}

LBase::~LBase() 
{
    LUA::unregAll(cb);
}

/// protected methods
void LBase::reg( const String& r ) {
    cb.set( r, LUA_REFNIL);
}

void LBase::set( const String& r, int lua_type, int pos ) {
    luaL_checktype(L, pos, lua_type );
    cb.set(r, luaL_ref(L, LUA_REGISTRYINDEX));
    lua_pop(L,1);
}

int LBase::callback( const String& r, int nb_res, const std::list<var>& args ) const {
    return LUA::call_cb(cb, r, nb_res, args);
}
