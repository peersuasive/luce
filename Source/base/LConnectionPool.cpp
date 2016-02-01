/************************************************************

 LConnectionPool.cpp

    @author Christophe Berbizier (cberbizier@peersuasive.com)
    @license GPLv3
    @copyright 


(c) 2016, Peersuasive Technologies

*************************************************************/

#include "LConnectionPool_inh.h"

const char LConnectionPool::className[] = "LConnectionPool";
const Luna<LConnectionPool>::PropertyType LConnectionPool::properties[] = {
    {0,0}
};
const Luna<LConnectionPool>::FunctionType LConnectionPool::methods[] = {
    method( LConnectionPool, isRunning ),
    method( LConnectionPool, start ),
    method( LConnectionPool, stop ),
    method( LConnectionPool, kill ),
    method( LConnectionPool, destroy ),
    method( LConnectionPool, reset ),

    method( LConnectionPool, receive ),
    {0,0}
};

const Luna<LConnectionPool>::StaticType LConnectionPool::statics[] = {
    smethod( LConnectionPool, createPool ),
    {0,0}
};

LConnectionPool::LConnectionPool(lua_State * L_)
    : LBase(L_, "LConnectionPool", true),
      Thread("LConnectionPool")
{
    L=L_;
}

LConnectionPool::~LConnectionPool() {
}

struct LURLThread : public Thread {
    LURLThread(Results *_results, const URL *_url, int ms = 60000, String name = String("LURLThread")):
        Thread(name),
        url(_url),
        results(_results),
        timeout(ms)
    {
    }
    ~LURLThread() {
        if(isThreadRunning()) {
            stopThread(-1);
        }
    }
    void abort() {
        this->stopThread(-1);
        if(is)delete is;
    }
    void run() override {
        if(!threadShouldExit()) {
            StringPairArray resp;
            int status;
            this->is = url->createInputStream(false,nullptr,nullptr,String(),
                    timeout,
                    &resp,&status);
            is->readIntoMemoryBlock(results->destData);
            results->responseCode = status;
            results->headers = resp;
            delete is;
        }
    }

private:
    InputStream *is;
    int timeout;
    Results *results;
    const URL *url;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (LURLThread)
};

int LConnectionPool::reset(lua_State *L) {
    if(!lua_istable(L,2)) {
        lua_pushfstring(L, "LURL::ConnectionPool: expected table, found %s", lua_typename(L,lua_type(L,2)));
        lua_error(L);
    }
    abort();
    int total = lua_objlen(L,2);
    // FIXME: there's a bug with index in case of mixed IDs/indexes
    // FIXME: lua_isofclass doesn't return a nil,
    //        so nils won't be treated correctly
    //        we need to add a third condition with nils
    for(int i=0;i<total;++i) {
        lua_rawgeti(L, 2, i+1);
        if(lua_isnoneornil(L,-1)) {
            addURL( (void*)nullptr, i );
            lua_pop(L,1);
        } else if(LUCE::luce_isofclass(LURL,-1)) {
            URL *url = LUA::from_luce<LURL>(-1);
            addURL( url, i );
        }else{
            lua_getfield(L, -1, "id");
            String id = lua_tostring(L, -1);
            lua_pop(L,1);
            lua_rawgeti(L, -1, 1);
            if(lua_isnoneornil(L,-1))
                addURL((void*)nullptr, i, id);
            else {
                URL *url = LUA::from_luce<LURL>(-1);
                addURL(url, i, id);
            }
            lua_pop(L,1);
        }
    }
    return 0;
}

int LConnectionPool::s_createPool(lua_State *L) {
    LConnectionPool *pool = new LConnectionPool(L);
    pool->reset(L);
    return LUA::storeAndReturnUserdata<LConnectionPool>( pool );
}

void LConnectionPool::addURL(void *empty, int index, String id) {
    results.insert(index,nullptr);
    threads.insert(index,nullptr);
}

void LConnectionPool::addURL(const URL* url, int index, String id) {
    if(!id.isEmpty())
        ids.set(String(index), id);
    Results *r = new Results();
    results.insert(index,r);
    LURLThread *t = new LURLThread(r, url);
    threads.insert(index, t);
    notify();
}

void LConnectionPool::run() {
    int len = threads.size();
    DBG("THREAD SIZE: "+String(len));
    if(!len)return;
    for (int i=0;i<len;++i) {
        if(threadShouldExit())break;
        LURLThread *t = threads.getUnchecked(i);
        if(t!=nullptr) t->startThread();
    }
    while(!threadShouldExit()) {
        bool running = false;
        for (int i=0;i<len;++i) {
            LURLThread *t = threads.getUnchecked(i);
            if(t!=nullptr && t->isThreadRunning()) {
                running = true;
                break;
            }
        }
        if(!running) break;
    }
    if(threadShouldExit()) {
        for (int i=0;i<len;++i) {
            LURLThread *t = threads.getUnchecked(i);
            if(t!=nullptr && t->isThreadRunning())
                t->stopThread(10);
        }
    }
    if(!threadShouldExit()) {
        if(hasCallback("receive")) {
            const MessageManagerLock mmLock;

            int len = results.size();
            push_callback("receive");
            if(lua_isnoneornil(L,-1)) {
                std::cout << "An error occured when calling callback: callback not found" << std::endl;
                LUCE::luce_error("LConnectionPool: an error occured when calling callback: callback not found");
            } else {
                lua_pushvalue(L,-1);
                lua_newtable(L);
                for(int i=0;i<len;++i) {
                    Results &r = *results[i];
                    String id = ids[String(i)];
                    if(!id.isEmpty())
                        lua_pushstring(L,id.toRawUTF8());
                    else
                        lua_pushnumber(L,i+1);
                    lua_newtable(L);
                    lua_pushliteral(L, "status");
                    lua_pushnumber(L, r.responseCode);
                    lua_settable(L,-3);
                    int size = r.destData.getSize();
                    if(size) {
                        lua_pushliteral(L, "data");
                        lua_pushlstring(L, (const char*)r.destData.getData(), size);
                        lua_settable(L, -3);
                    }
                    lua_settable(L, -3);
                }
                if ( lua_pcall(L, 1, 0, 0) ) {
                    std::cout << "An error occured when calling callback!..."
                        << lua_tostring(L,-1)
                        << std::endl;
                    LUCE::luce_error("LConnectionPool");
                }
                lua_pop(L,1);
            }
        }
    }
    results.clear(true);
    threads.clear(true);
}

void LConnectionPool::clear() {
    int len = threads.size();
    for (int i=0;i<len;++i) {
        LURLThread *t = threads.getUnchecked(i);
        if(t!=nullptr && t->isThreadRunning()) {
            t->stopThread(-1);
            t->abort();
        }
    }
    results.clear(true);
    threads.clear(true);
}
void LConnectionPool::abort() {
    unset("receive");
    stopThread(-1);
    clear();
}

int LConnectionPool::receive(lua_State*) {
    set("receive");
    return 0;
}

int LConnectionPool::start(lua_State *L) {
    if(lua_isfunction(L,-1))
        set("receive");
    startThread();
    return 0;
}

int LConnectionPool::isRunning(lua_State *L) {
    lua_pushboolean(L, Thread::isThreadRunning());
    return 1;
}

int LConnectionPool::stop(lua_State*) {
    int ms = LUA::checkAndGetNumber(2, 200);
    stopThread(ms);
    clear();
    return 0;
}
int LConnectionPool::kill(lua_State*) {
    stopThread(-1);
    clear();
    return 0;
}

int LConnectionPool::destroy(lua_State *L) {
    abort();
    delete this;
    lua_settop(L,0);
    return 0;
}
