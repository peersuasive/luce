/************************************************************

 LBase.cpp

    @author Christophe Berbizier (cberbizier@peersuasive.com)
    @license GPLv3
    @copyright 


(c) 2013-2014, Peersuasive Technologies

*************************************************************/

LBase::LBase(lua_State *Ls, const String& name, bool pure)
     : LSelfKill(name, pure)
{
    LUA::Set(Ls);
    LUCE::Set(Ls);
    L = Ls;
    LUA::reg(this);
}

LBase::~LBase() 
{
    LUA::unreg(this);
}

int LBase::lnew(lua_State *L) {
    return 0;
}

void LBase::selfKill() {
    delete this;
}


// return a light user data
int LBase::light(lua_State *L) {
    lua_pushlightuserdata(L, (void*)this);
    return 1;
}

int LBase::unlight(lua_State *L) {
    if(lua_gettop(L)>2 && lua_islightuserdata(L, 3)) {
        String n = LUA::getString(2);
        void *base = lua_touserdata(L,2);
        lua_remove(L,2);
        return LUA::casttype_unlight(n, base);
    }
    lua_pushnil(L);
    return 1;
}

/// protected methods
void LBase::set( const String& r, int lua_type, int pos ) {
    if ( LUA::set(this, r.toRawUTF8(), pos) )
        this->registered.set(r, true);
}
void LBase::unset( const String& r ) {
    LUA::unset(this, r.toRawUTF8());
    this->registered.set(r, false);
}

int LBase::callback( const String& k, int nb_ret, const std::list<var>& args ) const {
    return LUA::call_cb(this, k.toRawUTF8(), nb_ret, args);
}

bool LBase::hasCallback( const String& k ) const {
    return this->registered[k];
}

int LBase::readOnly(lua_State*) {
    LUCE::luce_error("Attempted to set a read-only variable");
    return 0;
}

int LBase::writeOnly(lua_State*) {
    return LUA::returnNil();
}

const String LBase::getBaseName() const {
    return myName();
}
