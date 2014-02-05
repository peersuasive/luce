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

/// protected methods
void LBase::set( const String& r, int lua_type, int pos ) {
    if ( LUA::set(this, r.toRawUTF8(), pos) )
        this->registered.set(r, true);
}

int LBase::callback( const String& k, int nb_ret, const std::list<var>& args ) const {
    return LUA::call_cb(this, k.toRawUTF8(), nb_ret, args);
}

bool LBase::hasCallback( const String& k ) const {
    return this->registered[k];
}

int LBase::readOnly(lua_State*) {
    LUA::throwError("Attempted to set a read-only variable");
}

int LBase::writeOnly(lua_State*) {
    LUA::returnNil();
}

const String LBase::getBaseName() const {
    return myName();
}
