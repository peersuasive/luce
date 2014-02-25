/************************************************************

 MainThread.cpp

    @author Christophe Berbizier (cberbizier@peersuasive.com)
    @license GPLv3
    @copyright 


(c) 2013, Peersuasive Technologies

*************************************************************/

MainThread::MainThread( const String& name, lua_State *L, const int& ref) 
    : Thread(name),
      cb_ref(ref)
{
}

MainThread::~MainThread() {
    // unref cb
    luaL_unref(LUA::Get(), LUA_REGISTRYINDEX, cb_ref);
}

// returns 0 or 1
const int run_cb(lua_State *L, int ref) {
    int status = 0;
    lua_rawgeti(L, LUA_REGISTRYINDEX, ref);
    if ( lua_pcall(L, 0, 1, 0) )
        LUA::throwError( "Error while running start function");
    status = lua_toboolean(L,-1);
    lua_pop(L, 1);
    return status;
}

void MainThread::run() {
    lua_State *L = LUA::Get();
    while (! threadShouldExit()) {
        MessageManagerLock mml (Thread::getCurrentThread());
        if (!mml.lockWasGained())
            return;

        if (! MessageManager::getInstance()->runDispatchLoopUntil(0) )
            break;
        if ( run_cb(L, cb_ref) != 0 )
            break;

        /*
        if ( cb_ref != LUA_REFNIL ) {
            MessageManagerLock mml (Thread::getCurrentThread());
            if (mml.lockWasGained()) {
                int rc = LUA::call_cb(cb_ref, 1);
                if ( lua_type(LUA::Get(), -1) != LUA_TNIL ) {
                    keep_running = lua_toboolean(LUA::Get(), -1);
                    lua_pop(LUA::Get(), 1);
                }
            }
        }
        */
        
            /*
            int rc = LUA::call_cb(cb_ref, 1);
            if ( rc < 0 ) {
                const char *err = lua_tostring(L, -1);
                LUA::throwError(String("Error while executing the main loop: ") + err);
                std::cout << "error while executing the callback: " << err << std::endl;
                lua_pop(L, 1);
            }
            else if ( rc ) {
                if ( lua_type(L, -1) != LUA_TNIL ) {
                    bool res = lua_toboolean(L, -1);
                    if( ! res ) {
                        DBG("exit after cb break");
                        keep_running = false;
                    }
                }
                lua_pop(L, 1);
            }
            */
    }
}
