/************************************************************

 LBase.cpp

    @author Christophe Berbizier (cberbizier@peersuasive.com)
    @license GPLv3
    @copyright 


(c) 2013-2014, Peersuasive Technologies

*************************************************************/

LBase::LBase(lua_State *Ls, const String& name)
     : LSelfKill(name)
{
    LUA::Set(Ls);
    L = Ls;
    LUA::reg(this);
}

LBase::~LBase() 
{
    DBG(String("DELETE LBase: ")+ myName());
    LUA::unreg(this);
}

void LBase::selfKill() {
    delete this;
}

/// protected methods
void LBase::set( const String& r, int lua_type, int pos ) {
    if ( LUA::set(this, r.toRawUTF8(), pos) )
        this->registered.set(r, true);
}

int LBase::callback( const String& k, int nb_ret, const std::list<var>& args ) const {
    return LUA::call_cb(this, k.toRawUTF8(), nb_ret, args);
}

bool LBase::hasCallback( const String& k ) {
    return this->registered[k];
}

int LBase::readOnly(lua_State*) {
    LUA::throwError("Attempted to set a read-only variable");
}
