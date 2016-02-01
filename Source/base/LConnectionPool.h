/************************************************************

 LConnectionPool.h

    @author Christophe Berbizier (cberbizier@peersuasive.com)
    @license GPLv3
    @copyright 


(c) 2016, Peersuasive Technologies

*************************************************************/

/****

Usage:
local pool = luce:ConnectionPool()

pool:reset{ luce:URL('https://beta.liego.fr'), luce:URL('https://ewdth.com') }
- or -
pool:reset{ {id="ID1", luce:URL('https://beta.liego.fr')}, {id="ID2",luce:URL('https://ewdth.com')} }

pool:start(function(data)
    --[[
        data are returned either with IDs or incremental index
        to keep data ordered when using indexes
        it is possible to provide a nil in stead of a URL
        in the list
    ]]--
    --[[...]]--
end)

pool:isRunning() -- check current status
pool:stop() -- try to stop pool
pool:kill() -- force pool to stop immediately

****/

#ifndef __LUCE_LCONNECTION_POOL_H
#define __LUCE_LCONNECTION_POOL_H

struct Results{
    StringPairArray headers;
    int responseCode = 0;
    MemoryBlock destData;
};

struct LURLThread;
class LConnectionPool
    : public LBase,
      public Thread
{
public:
    LConnectionPool(lua_State*);
    ~LConnectionPool();
    
    //==============================================================================
    static int s_createPool(lua_State*);

    //==============================================================================
    void abort();

    //==============================================================================
    void addURL(void *empty, int index, String id = String());
    void addURL(const URL *url, int index, String id = String());

    //==============================================================================
    void run() override;

    //==============================================================================
    int isRunning(lua_State*);
    int start(lua_State*);
    int stop(lua_State*);
    int kill(lua_State*);
    int destroy(lua_State*);
    int reset(lua_State*);

    //==============================================================================
    int receive(lua_State*);

    //==============================================================================
    static const char className[];
    static const Luna<LConnectionPool>::Inheritence inherits[];
    static const Luna<LConnectionPool>::InheritenceF inheritsF[];
    static const Luna<LConnectionPool>::PropertyType properties[];
    static const Luna<LConnectionPool>::FunctionType methods[];
    static const Luna<LConnectionPool>::StaticType statics[];
    static const Luna<LConnectionPool>::Enum enums[];

private:
    //==============================================================================
    lua_State *L;

    //==============================================================================
    void clear();

    //==============================================================================
    StringPairArray ids;
    OwnedArray<Results> results;
    OwnedArray<LURLThread> threads;

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (LConnectionPool)
};

#endif // __LUCE_LCONNECTION_POOL_H
