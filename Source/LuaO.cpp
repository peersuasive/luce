#ifndef __LUA_O_H
#define __LUA_O_H

#ifdef LUA52
int luaL_getn(lua_State *L, int idx) {
    return luaL_len(L, idx);
}
typedef luaL_Reg luaL_reg;
#endif

namespace LUA {
    namespace {
        juce::Array<int> locked;

        lua_State *L = nullptr;
        void Set(lua_State *L_) {
            if ( L == nullptr ) L = L_;
        }
        lua_State *Get() {
            return L;
        }
        void throwError(const String& err) {
            lua_pushstring(L, err.toRawUTF8());
            lua_error(L);
        }

        void reg(const LBase* key) {
            if ( ! key || key == nullptr )
                throwError("Trying to register a NULL pointer");

            lua_pushlightuserdata(L, (void*)key); // check if table exists
            lua_gettable(L, LUA_REGISTRYINDEX);    //
            if ( lua_isnil(L, -1) ) {
                lua_pop(L,1);
                lua_pushlightuserdata(L, (void*)key); // check if table exists
                lua_newtable(L);
                int i = lua_gettop(L);
                lua_settable(L, LUA_REGISTRYINDEX);
            }
            else
                lua_pop(L,1);
        }
        void unreg(const LBase* key) {
            lua_pushlightuserdata(L, (void*)key);
            lua_pushnil(L);
            lua_settable(L, LUA_REGISTRYINDEX);
        }

        bool set(const LBase* key, const char* name, int n_) {
            bool res = false;
            if ( ! lua_isfunction(L, n_) )
                throwError("LUCE ERROR: callback is not a function");
        
            int n = (n_<0) ? (lua_gettop(L)-(n_+1)) : n_;
            lua_pushlightuserdata(L, (void*)key);
            lua_gettable(L, LUA_REGISTRYINDEX);
            if ( lua_istable(L, -1) ) {
                int i = lua_gettop(L);
                lua_pushstring(L, name);
                lua_pushvalue(L, n);
                lua_settable(L, i);
                lua_pop(L,1);
                lua_remove(L, n);
                res = true;
            } else {
                lua_pop(L,1); // nil
                // could create table here, instead... but I want to get sure this
                // is stored at the correct place, just to avoid having ghost tables
                std::cout << "Can't get registry for " << key << std::endl;
                throwError("LUCE ERROR: can't get registry to store callbacks");
            }
            return res;
        }
        void unset(const LBase* key, const char* name) {
            lua_pushlightuserdata(L, (void*)key);
            lua_gettable(L, LUA_REGISTRYINDEX);
            if ( ! lua_istable(L, -1) ) {
                lua_pop(L,1);
                return;
            }
            int top = lua_gettop(L);
            lua_getfield(L, top, name);
            if ( lua_isnil(L,-1) ) {
                lua_pop(L,1);
                return;
            }
            lua_pushnil(L);
            lua_settable(L, top);
            lua_pop(L,1);
        }
        bool hasCallback(const LBase* key, const char* name) {
            bool res = false;
            lua_pushlightuserdata(L, (void*)key);
            lua_gettable(L, LUA_REGISTRYINDEX);
            if ( lua_istable(L, -1) ) {
                lua_getfield(L, -1, name);
                res = lua_isfunction(L, -1);
                lua_pop(L,1);
            }
            lua_pop(L,1);
            return res;
        }
        bool getCallback(const LBase* key, const char* name) {
            bool res = false;
            lua_pushlightuserdata(L, (void*)key);
            lua_gettable(L, LUA_REGISTRYINDEX);
            int i = lua_gettop(L);
            if ( lua_istable(L, -1) ) {
                lua_getfield(L, -1, name);
                if ( ! lua_isfunction(L, -1 ) )
                    lua_pop(L,1); // nil
                else 
                    res = true;
            }
            lua_remove(L, i);
            // leaves callback on top
            return res;
        }

        //void store(int addr, WeakReference<LBase> o) {
        void store(int addr, WeakReference<LSelfKill> o) {
            objects[addr] = o;
        }

        // get results from stack
        const var getNumber(int i) {
            var res( luaL_checknumber(L, i) );
            lua_remove(L, i);
            return res;
        }
        const var checkAndGetNumber(int i, var def) {
            if (lua_type(L, i) == LUA_TNUMBER)
                return getNumber(i);
            if(lua_type(L,i) == LUA_TNIL)
                lua_remove(L, i);
            return def;
        }
        template<class T>
        const T getNumber(int i) {
            return luaL_checknumber(L, i);
        }
        template<class T>
        const T checkAndGetNumber(int i, T def) {
            if (lua_type(L, i) == LUA_TNUMBER)
                return getNumber(i);
            if(lua_type(L,i) == LUA_TNIL)
                lua_remove(L, i);
            return def;
        }

        const bool getBoolean(int i) {
            luaL_checktype(L, i, LUA_TBOOLEAN);
            bool res = lua_toboolean(L, i);
            lua_remove(L, i);
            return res;
        }
        const bool checkAndGetBoolean(int i, int def) {
            if ((lua_type(L, i) == LUA_TBOOLEAN))
                return getBoolean(i);
            if(lua_type(L,i) == LUA_TNIL)
                lua_remove(L, i);
            return def;
        }

        const String getString(int i) {
            size_t len;
            const char *s = luaL_checklstring(L, i, &len);
            lua_remove(L,i);
            return String(s, len);
        }
        const String checkAndGetString(int i, String def) {
            if (lua_type(L, i) == LUA_TSTRING)
                return getString(i);
            if(lua_type(L,i) == LUA_TNIL)
                lua_remove(L, i);
            return def;
        }

        const Array<var> getList(int i) {
            luaL_checktype(L, i, LUA_TTABLE);
            lua_pushvalue(L, i);
            Array<var> res;
            int len = luaL_getn(L, -1);
            lua_pushnil(L);
            while( lua_next(L, -2) != 0 ) {
                switch( lua_type(L, -1) ) {
                    case LUA_TNIL:
                        break;
                    case LUA_TTABLE:
                        break;
                    case LUA_TNUMBER:
                        res.add(lua_tonumber(L, -1));
                        break;
                    case LUA_TSTRING:
                        {
                            size_t len;
                            const char *s = lua_tolstring(L, -1, &len);
                            res.add(String(s, len));
                        }
                        break;
                    case LUA_TBOOLEAN:
                        res.add(lua_toboolean(L, -1));
                        break;
                    default:
                        break;
                }
                lua_pop(L, 1);
            }
            lua_pop(L, 1);
            lua_remove(L,i);
            return res;
        }

        template<class T>
        const Array<T> getList(int i) {
            luaL_checktype(L, i, LUA_TTABLE);
            lua_pushvalue(L, i);
            Array<T> res;
            int len = luaL_getn(L, -1);
            lua_pushnil(L);
            while( lua_next(L, -2) != 0 ) {
                res.add( luaL_checknumber(L, -1) );
                lua_pop(L, 1);
            }
            lua_pop(L, 1);
            lua_remove(L,i);
            return res;
        }

        const Array<Component*> getComponentList(int n, int i) {
            luaL_checktype(L, i, LUA_TTABLE);
            lua_pushvalue(L, i);

            Array<Component*> res;

            for (int ind=1;ind<=n;++ind) {
                Component *comp;
                lua_rawgeti(L, i, ind);
                if ( lua_type(L, -1) == LUA_TSTRING ) { // any string will do
                    comp = nullptr;
                    lua_pop(L,1);
                }
                else
                    comp = from_luce<LComponent,Component>(lua_gettop(L));
                res.add( comp );
            }
            lua_pop(L,1);
            lua_remove(L,i);
            return res;
            /*
            lua_pushnil(L);
            while( lua_next(L, -2) != 0 ) {
                std::cout << " ** loop" << std::endl;
                Component *comp;
                if ( lua_type(L, -1) == LUA_TNIL ) {
                    std::cout << "******* NIL" << std::endl;
                    comp = nullptr;
                    lua_pop(L,1);
                }
                else
                    comp = from_luce<Component>(lua_gettop(L));
                res.add(comp);
            }
            lua_pop(L,1);
            lua_remove(L,i);
            return res;
            */
        }

        /*
        const juce::Rectangle<int> getRectangle(int i) {
            luaL_checktype(L, i, LUA_TTABLE);
            i = (i<0) ? lua_gettop(L)-(i+1) : i;
            //i = (i == -1) ? lua_gettop(L) : i; // ensure we have the real table index
            lua_getmetatable(L, i);
            lua_getfield(L, -1, "__self");
            if ( ! lua_isnil(L, -1) ) { // LRectangle object
                if ( std::string( lua_tostring(L, -1) ) == "LRectangle" ) {
                    lua_pop(L,1); // __self
                    lua_getfield(L, i, "dump"); // provided by LRectangle
                    lua_pushvalue(L, i); // push self
                    if ( lua_pcall(L, 1, 1, 0) != 0 ) // get self as argument
                        lua_error(L);
                } else {
                    throwError("Wrong object given as a LRectangle");
                }
            } else { // a table
                lua_pushvalue(L, i);
            }
            int ind = lua_gettop(L);
            lua_rawgeti(L, ind, 1);
            int x = luaL_checknumber(L, -1);
            lua_rawgeti(L, ind, 2);
            int y = luaL_checknumber(L, -1);
            lua_rawgeti(L, ind, 3);
            int w = luaL_checknumber(L, -1);
            lua_rawgeti(L, ind, 4);
            int h = luaL_checknumber(L, -1);

            lua_pop(L, 5); // table + x, y, w, h
            lua_pop(L,1); // mt or nil
            lua_remove(L,i); // original argument

            return { x, y, w, h };
        }
        */
        template<class T>
        const juce::Rectangle<T> getRectangle(int i) {
            luaL_checktype(L, i, LUA_TTABLE);
            i = (i<0) ? lua_gettop(L)-(i+1) : i;
            lua_getmetatable(L, i);
            lua_getfield(L, -1, "__self");
            if ( ! lua_isnil(L, -1) ) { // LRectangle object
                if ( std::string( lua_tostring(L, -1) ) == "LRectangle" ) {
                    lua_pop(L,1); // __self
                    lua_getfield(L, i, "dump"); // provided by LRectangle
                    lua_pushvalue(L, i); // push self
                    if ( lua_pcall(L, 1, 1, 0) != 0 ) // get self as argument
                        lua_error(L);
                } else {
                    throwError("Wrong object given as a LRectangle");
                }
            } else { // a table
                lua_pushvalue(L, i);
            }
            int ind = lua_gettop(L);
            lua_rawgeti(L, ind, 1);
            T x = luaL_checknumber(L, -1);
            lua_rawgeti(L, ind, 2);
            T y = luaL_checknumber(L, -1);
            lua_rawgeti(L, ind, 3);
            T w = luaL_checknumber(L, -1);
            lua_rawgeti(L, ind, 4);
            T h = luaL_checknumber(L, -1);

            lua_pop(L, 5); // table + x, y, w, h
            lua_pop(L,1); // mt or nil
            lua_remove(L,i); // original argument

            return { x, y, w, h };
        }
        const juce::Rectangle<int> getRectangle(int i) {
            return getRectangle<int>(i);
        }

        const juce::Point<int> getPoint(int i) {
            luaL_checktype(L, i, LUA_TTABLE);
            lua_pushvalue(L, i);
            lua_rawgeti(L, -1, 1);
            int x = luaL_checknumber(L, -1);
            lua_rawgeti(L, -2, 2);
            int y = luaL_checknumber(L, -1);
            lua_pop(L, 3);
            lua_remove(L,i);
            return { x, y };
        }

        const juce::Range<int> getRange(int i) {
            luaL_checktype(L, i, LUA_TTABLE);
            lua_pushvalue(L, i);
            lua_rawgeti(L, -1, 1);
            int x = luaL_checknumber(L, -1);
            lua_rawgeti(L, -2, 2);
            int y = luaL_checknumber(L, -1);
            lua_pop(L, 3);
            lua_remove(L,i);
            return { x, y };
        }

        const juce::SparseSet<int> getSparseSet(int i) {
            SparseSet<int> s;
            luaL_checktype(L, i, LUA_TTABLE);
            lua_pushvalue(L, i);
            lua_pushnil(L);
            while(lua_next(L, -2)) {
                luaL_checktype(L, -1, LUA_TTABLE);
                lua_rawgeti(L, -1, 1);
                int min = luaL_checknumber(L, -1);
                lua_rawgeti(L, -1, 1);
                int max = luaL_checknumber(L, -1);
                lua_pop(L,3); // or 2 ?
                s.addRange( { min, max } );
            }
            lua_pop(L,1);
            lua_remove(L,i);
            return s;
        }

        const std::list<var> getStdList(int i) {
            luaL_checktype(L, i, LUA_TTABLE);
            lua_pushvalue(L,i);
            std::list<var> res;
            int len = luaL_getn(L, -1);
            lua_pushnil(L);
            while( lua_next(L, -2) != 0 ) {
                switch( lua_type(L, -1) ) {
                    case LUA_TNIL:
                        break;
                    case LUA_TTABLE:
                        break;
                    case LUA_TNUMBER:
                        res.push_back(var(lua_tonumber(L, -1)));
                        break;
                    case LUA_TSTRING:
                        {
                            size_t len;
                            const char *s = lua_tolstring(L, -1, &len);
                            res.push_back(var(String(s, len)));
                        }
                        break;
                    case LUA_TBOOLEAN:
                        res.push_back(var(lua_toboolean(L, -1)));
                        break;
                    default:
                        break;
                }
                lua_pop(L,1);
            }
            lua_remove(L,i);

            return res;
        }

        template<class T>
        T* toUserdata(int i) {
            T* res = Luna<T>::check(L,i);
            lua_remove(L,1);
            return res;
        }

        template<class T>
        T* to_juce(int i) {
            T* res = Luna<T>::to_juce(L, i);
            lua_remove(L,i);
            return res;
        }

        template<class T>
        T* raw_cast(int i) {
            luaL_checktype(L, i, LUA_TUSERDATA);
            T* res = static_cast<T*>(lua_touserdata(L, i));
            lua_remove(L,i);
            return res;
        }

        template<class T, class U = T>
        U* from_luce(int i) {
            // TODO: use check, meaning -- refactor luna5 first
            /*
            T* res = Luna<T>::check(L,i);
            lua_remove(L,i);
            return dynamic_cast<U*>(res);
            */
            luaL_checktype(L, i, LUA_TTABLE);
            lua_getfield(L, i, "__self");
            if ( lua_isnil(L, -1) )
                throwError("given object is not a valid Luce object");
            T **obj = static_cast<T**>(lua_touserdata(L, -1));

            lua_remove(L, i); // object
            lua_pop(L,1); // pushed __self
            if(!obj)
                return nullptr;
            return dynamic_cast<U*>(*obj);
            //return *obj;
        }

        template<class T, class U = T>
        int returnUserdata(const U* udata) {
            if ( udata ) {
                const T *ldata = static_cast<const T*>( udata );
                lua_newtable(L);
                int t = lua_gettop(L);
                lua_pushstring(L, "__self");
                const T** r = static_cast<const T**>( lua_newuserdata(L, sizeof(const T*)) );
                *r = ldata;

                std::string cn = std::string(T::className) + "_";
                luaL_getmetatable(L, cn.c_str());
                if ( ! lua_isnil(L, -1) ) {
                    lua_setmetatable(L, -2); // index of udata
                } else {
                    lua_pop(L,1); // pop nil
                    Luna<T>::Register(L);
                    if ( lua_isnil(L, -1) )
                        throwError("Internal Error: Can't register class -- please, send a bug report");
                    lua_pop(L,1); // pop new()
                    luaL_getmetatable(L, cn.c_str());
                    lua_setmetatable(L, -2); // index of udata
                }

                lua_settable(L, t);

                lua_pushstring(L, "methods");
                lua_newtable(L);
                int nt = lua_gettop(L);
                for(int i= 0; T::methods[i].name; i++) {
                    lua_pushstring(L, T::methods[i].name);
                    lua_rawseti(L, nt, i+1);
                }
                lua_settable(L, t);

                // set static values, like enums...
                for ( int i = 0; T::enums[i].name; ++i ) {
                    lua_pushstring(L, T::enums[i].name);
                    lua_newtable(L);
                    int nt = lua_gettop(L);
                    int ii = 1;
                    for ( auto& it : T::enums[i].values ) {
                        lua_pushstring(L, it.first.c_str());
                        lua_pushnumber(L, it.second);
                        lua_settable(L, nt);
                    }
                    lua_settable(L, t);
                }

                luaL_getmetatable(L, T::className);
                if ( ! lua_isnil(L, -1) ) {
                    lua_setmetatable(L, -2);
                } else lua_pop(L,1);

                //DBG(String("size of L at the end: ") + String(lua_gettop(L)));
                return 1;

            } else {
                lua_pushnil(L);
                return 1;
            }
        }
        template<class T, class U = T>
        int storeAndReturnUserdata(U* udata) {
            WeakReference<LSelfKill> ref = dynamic_cast<LSelfKill*>(udata);
            LUA::store( (intptr_t)udata, ref );
            return returnUserdata<T, U>(udata);
        }

        int returnBoolean(bool val) {
            lua_pushboolean(L, val);
            return 1;
        }

        int returnNil() {
            lua_pushnil(L);
            return 1;
        }

        template<class T>
        int returnNumber(const T& val) {
            lua_pushnumber(L, val);
            return 1;
        }

        const int returnString(const String& val) {
            lua_pushlstring(L, val.toRawUTF8(), val.length());
            return 1;
        }
        int returnString(const std::string& val) {
            lua_pushlstring(L, val.c_str(), val.size());
            return 1;
        }

        // implement embedded tables
        int returnTable(const std::list<var>& val) {
            lua_newtable(L);
            int t = lua_gettop(L);
            int i = 0;
            for ( auto &it : val ) {
                if ( it.isInt() 
                        || it.isInt64() 
                        || it.isDouble()
                        ) {
                    lua_pushnumber(L, it);
                }
                else if ( it.isBool() ) {
                    lua_pushboolean(L, (bool)it);
                }
                else if ( it.isString() ) {
                    lua_pushlstring(L, it.toString().toRawUTF8(), it.toString().length() );
                }
                else if ( it.isArray() ) {
                    lua_pushnil(L);
                    std::cout << "type not yet implemented" << std::endl;
                    // TODO: test this
                    // returnTable( *it.getArray() );
                }
                else {
                    lua_pushnil(L);
                    std::cout << "type not yet implemented" << std::endl;
                }
                lua_rawseti(L, t, ++i);
            }
            return 1;
        }
        int returnTable(const Array<var>& val) {
            std::list<var> r;
            for (int i=0;i<val.size();++i)
                r.push_back( val[i] );
            return returnTable(r);
        }
        int returnTable(const StringArray& sa) {
            std::list<var> r;
            for(int i=0;i<sa.size();++i)
                r.push_back(sa[i]);
            return returnTable(r);
        }

        int TODO_OBJECT(const String& tmpl, const String& msg) {
            lua_pushstring(L, (msg + tmpl).toRawUTF8() );
            lua_error(L);
            return 0;
        }

        // we could set a table with x, y, width, height instead of an array
        // or we could also implement the rectangle class to get all the facilities
        // it offers ?
        int returnTable( const juce::Rectangle<int>& r ) {
            lua_newtable(L);
            int t = lua_gettop(L);
            lua_pushnumber(L, r.getX());
            lua_rawseti(L, t, 1);
            lua_pushnumber(L, r.getY());
            lua_rawseti(L, t, 2);
            lua_pushnumber(L, r.getWidth());
            lua_rawseti(L, t, 3);
            lua_pushnumber(L, r.getHeight());
            lua_rawseti(L, t, 4);
            return 1;
        }

        int returnTable( const juce::RectangleList<int>& r ) {
            // TODO
            //
            // for each rectangle, create a list of numbers
            return 0;
        }

        int returnTable( const juce::Point<int>& r ) {
            lua_newtable(L);
            int t = lua_gettop(L);
            lua_pushnumber(L, r.getX());
            lua_rawseti(L, t, 1);
            lua_pushnumber(L, r.getY());
            lua_rawseti(L, t, 2);
            return 1;
        }

        int returnTable( const juce::Range<int>& r ) {
            lua_newtable(L);
            int t = lua_gettop(L);
            lua_pushnumber(L, r.getStart());
            lua_rawseti(L, t, 1);
            lua_pushnumber(L, r.getEnd());
            lua_rawseti(L, t, 2);
            return 1;
        }

        int returnTable( const juce::SparseSet<int>& r ) {
            return returnTable( r.getTotalRange() );
        }

        int stacktrace(lua_State *L) {
            bool full_stack = false;
            lua_Debug info;
            int level = 0;
            // error
            lua_getstack(L, level++, &info),
            lua_getinfo(L, "nSl", &info);
            std::cerr << "Error while executing callback:" << std::endl;
            if ( info.name )
                std::cerr << "-> unknown method: " << info.name << "()" << std::endl;
            else {
                std::cerr << "-> attempt to call method from a nil table" << std::endl;
                std::cerr << "   (full stack)" << std::endl;
                full_stack = true;
            }
            
            // stack
            while (lua_getstack(L, level, &info)) {
                lua_getinfo(L, "nSl", &info);
                // dump only callback related stack
                if ( info.currentline == -1 && info.linedefined == -1 && String(info.what) == "C" ) break;

                if ( info.name )
                    std::cerr << "   -> from function " << info.name << "()";
                else
                    std::cerr << "   -> from <callback>";

                std::cerr << ":" << info.currentline
                          << " (defined at " << info.short_src <<":"<< info.linedefined << ")"
                          << std::endl;
                ++level;
            }
            // pop remaining traces
            while (lua_getstack(L, level, &info)) {
                lua_getinfo(L, "nSl", &info);
                if ( full_stack ) {
                    if ( info.name )
                        std::cerr << "   -> from function " << info.name << "()";
                    else
                        std::cerr << "   -> from <callback>";

                    std::cerr << ":" << info.currentline
                              << " (defined at " << info.short_src <<":"<< info.linedefined << ")"
                              << std::endl;

                }
                ++level;
            }

            return 0;
        }

        void unlock(int ref) {
            locked.removeFirstMatchingValue(ref);
        }
        const bool is_running(int ref) {
            return locked.contains(ref);
        }
        void lock_running(int ref) {
            locked.add(ref);
        }
        //const int call_cb(int ref, int nb_ret , const std::list<var>& args) {
        const int call_cb(int ref, int nb_ret) {
            if (is_running(ref)) {
                DBG("WARNING: callback already running !");
                return -3;
            }
            lock_running(ref);
            jassert( L != nullptr );
            if ( L == nullptr ) {
                unlock(ref);
                std::cout << "No lua state found !" << std::endl;
                return -2;
            }
            int status = 0;
            lua_rawgeti(L, LUA_REGISTRYINDEX, ref);
            int func_index = lua_gettop(L);
            if ( lua_type(L, -1) == LUA_TFUNCTION ) {
                lua_pushcclosure(L, stacktrace, 0);
                if ( lua_type(L, -1) == LUA_TNIL ) {
                    std::cout << "ERROR: callback is not a closure!" << std::endl;
                    throwError("INTERNAL ERROR: registered callback is not a closure!");
                }

                int errfunc = lua_gettop(L);
                lua_pushvalue(L, func_index);

                //if ( lua_pcall(L, nb_args, nb_ret, errfunc) != 0 ) {
                if ( lua_pcall(L, 0, nb_ret, 0) != 0 ) {
                    DBG("failed to execute callback.");
                    status = -1;
                    if ( lua_isstring(L, -1) ) {
                        const char *err = lua_tostring(L, -1);
                        lua_pop(L,1);

                        std::cout << "ERROR:" << err << std::endl;
                    }

                }
                else {
                    status = 1;
                }
                lua_remove(L, errfunc);
                lua_remove(L, func_index);
            } else {
                DBG("no cb found for ?");
                lua_remove(L, func_index);
            }
            unlock(ref);
            return status;
        }

        const int call_cb( const LBase* key, const char *name, int nb_ret, const std::list<var>& args ) {
            // lock running
            // ...
            
            jassert( L != nullptr );
            if ( L == nullptr ) {
                // unlock...
                std::cout << "No lua state found !" << std::endl;
                return -2;
            }
            if ( ! getCallback(key, name) ) {
                std::cout << "ERROR: no callback found for class: " << key->myName() << ", with name: " << name << std::endl;
                return 0; // not found
            }

            int status = 0;
            int func_index = lua_gettop(L);
            int nb_args = args.size();
            
            //lua_pushcclosure(L, stacktrace, 0);
            //int errfunc = lua_gettop(L);
            lua_pushvalue(L, func_index);

            // set arguments
            for ( auto &it : args ) {
                if ( it.isInt()
                        || it.isInt64() 
                        || it.isDouble()
                   ) {
                    lua_pushnumber(L, it);
                }
                else if ( it.isBool() ) {
                    lua_pushboolean(L, (bool)it);
                }
                else if ( it.isString() ) {
                    lua_pushlstring(L, it.toString().toRawUTF8(), it.toString().length() );
                }
                else if ( it.isObject() ) {
                    LRefBase* lr = ((LRefBase*)it.getObject());
                    String type = lr->getType();
                    if ( type == "MouseEvent" || type == "LMouseEvent" ) {
                        //returnUserdata<LMouseEvent, MouseEvent>( (MouseEvent*)lr->getMe() );
                        returnUserdata<LMouseEvent, MouseEvent>( static_cast<const MouseEvent*>(lr->getMe()) );

                    } else if ( type == "TreeViewItem" ) {
                        //returnUserdata<LTreeViewItem, TreeViewItem>( (TreeViewItem*)lr->getMe() );
                        returnUserdata<LTreeViewItem, TreeViewItem>( static_cast<const TreeViewItem*>(lr->getMe()) );

                    } else if ( type == "SourceDetails" ) {
                        returnUserdata<LSourceDetails>( static_cast<const LSourceDetails*>(lr->getMe()) );

                    } else if ( type == "Component" ) {
                        returnUserdata<LJComponent>( (LJComponent*)lr->getMe() );
                    }

                    else if ( type == "Properties" ) {
                        HashMap<String, var>& h = *lr->getHash();
                        lua_newtable(L);
                        int t = lua_gettop(L);
                        for (HashMap<String,var>::Iterator i(h); i.next();) {
                            lua_pushstring(L, i.getKey().toRawUTF8());
                            var val( i.getValue() );
                            if ( val.isString() )
                                lua_pushstring(L, val.toString().toRawUTF8());
                            else if ( val.isBool() )
                                lua_pushboolean(L, val);
                            else
                                lua_pushnumber(L, val);
                            lua_settable(L, t);
                        }
                    } else {
                        std::cout << "argument object type not yet implemented" << std::endl;
                        lua_pushnil(L);
                    }
                    lr = nullptr;
                }
                else {
                    lua_pushnil(L);
                    std::cout << "argument type not yet implemented" << std::endl;
                }
            }

            if ( ! (status = ! lua_pcall(L, nb_args, nb_ret, 0)) ) {
                DBG("failed to execute callback.");
                status = -1;
                if ( lua_isstring(L, -1) ) {
                    const char *err = lua_tostring(L, -1);
                    lua_pop(L,1);
                    std::cout << "ERROR:" << err << std::endl;
                }
            }
            //lua_remove(L, errfunc);
            lua_remove(L, func_index);

            // unlock
            // ...
            
            return status;
        }

        const String getError() {
            String err = String::empty;
            if ( lua_isstring(L, -1) ) {
                err = lua_tostring(L, -1);
                lua_pop(L,1);
            }
            return err;
        }
    }
}

#endif // __LUA_O_H
