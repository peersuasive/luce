/************************************************************

 LBase.h

    @author Christophe Berbizier (cberbizier@peersuasive.com)
    @license GPLv3
    @copyright 


(c) 2013-2014, Peersuasive Technologies

*************************************************************/

#ifndef __LUCE_LBASE_H
#define __LUCE_LBASE_H

class LBase
{
public:    
    LBase(lua_State*);
    ~LBase();
    
    //==============================================================================
    static const char className[];
    static const Luna<LBase>::Inheritence inherits[];
    static const Luna<LBase>::InheritenceF inheritsF[];
    static const Luna<LBase>::PropertyType properties[];
    static const Luna<LBase>::FunctionType methods[];

    static const Luna<LBase>::Enum enums[];
protected:    
    //==============================================================================
    void reg( const String& );
    void set( const String& r, int lua_type = LUA_TFUNCTION, int pos = -1);
    int callback(const String&, int nb_res = 0, const std::list<var>& args = {}) const;
    bool hasCallback(const String&);

private:    
    //==============================================================================
    lua_State *L;
    
    //==============================================================================
    HashMap<String,int> cb;

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (LBase)
};

#endif // __LUCE_LBASE_H
