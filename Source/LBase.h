/************************************************************

 LBase.h

    @author Christophe Berbizier (cberbizier@peersuasive.com)
    @license GPLv3
    @copyright 


(c) 2013-2014, Peersuasive Technologies

*************************************************************/

#ifndef __LUCE_LBASE_H
#define __LUCE_LBASE_H

class LBase : public LSelfKill
{
public:
    LBase(lua_State*, const String& name = "(unnamed)", bool pure = true);
    static int lnew(lua_State*);
    ~LBase();

    virtual void selfKill() override;

    //==============================================================================
    int readOnly(lua_State*);
    int writeOnly(lua_State*);
    
protected:    
    //==============================================================================
    HashMap<String, bool> registered;
    void set( const String& r, int lua_type = LUA_TFUNCTION, int pos = -1);
    int callback(const String& k, int nb_ret = 0, const std::list<var>& args = {}) const;
    bool hasCallback(const String&) const;

private:    
    //==============================================================================
    lua_State *L;

    //==============================================================================
    HashMap<String,int> cb;

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (LBase)
};

#endif // __LUCE_LBASE_H
