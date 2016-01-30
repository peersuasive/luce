#ifndef __LUA_O_H
#define __LUA_O_H

#if defined LUA52 || defined LUA53
//#define LUA_COMPAT_MODULE
#ifndef lua_objlen
#define lua_objlen(L,i)           lua_rawlen(L, (i))
#endif
//#define lua_strlen(L,i)           lua_rawlen(L, (i))
//#define lua_equal(L,idx1,idx2)    lua_compare(L,(idx1),(idx2),LUA_OPEQ)
//#define lua_lessthan(L,idx1,idx2) lua_compare(L,(idx1),(idx2),LUA_OPLT)
//#define luaL_getn(L,i)            luaL_len(L,(i))
#endif

namespace LUA {
    extern lua_State LUCE_API *L;
    namespace {
        const char *SELF = "self";
        juce::Array<int> locked;

        void Set(lua_State *L_) {
            if ( !L || L == nullptr ) L = L_;
        }
        lua_State *Get() {
            return L;
        }

        void throwError(const char *msg) {
            if(LUA_COMMON::liveCoding())
                std::cout << "ERROR: " << msg << std::endl;
            else {
                if(!lua_isstring(L,-1))
                    lua_pushstring(L, msg);
                lua_error(L);
            }
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

        bool set(const LBase* key, const char* name, int n_ = -1) {
            bool res = false;
            if ( ! lua_isfunction(L, n_) )
                throwError(lua_pushfstring(L,
                            "LUCE ERROR: from %s: callback: %s is not a valid function.",
                                key->getBaseName().toRawUTF8(), name));
        
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
        bool put(const LBase* key, const char* name) {
            bool res = false;
            lua_pushlightuserdata(L, (void*)key);
            lua_gettable(L, LUA_REGISTRYINDEX);
            if ( lua_istable(L, -1) ) {
                lua_pushstring(L, name);
                lua_newtable(L);
                lua_settable(L, -3);
                lua_pop(L,2);
                res = true;
            } else {
                lua_pop(L,1); // nil
                // could create table here, instead... but I want to get sure this
                // is stored at the correct place, just to avoid having ghost tables
                std::cout << "Can't get registry for " << key << std::endl;
                throwError("LUCE ERROR: can't get registry to store register");
            }
            return res;
        }

        bool get(const LBase *key, const char *name) {
            bool res = false;
            lua_pushlightuserdata(L, (void*)key);
            lua_gettable(L, LUA_REGISTRYINDEX);
            int i = lua_gettop(L);
            if ( lua_istable(L, -1) ) {
                lua_getfield(L, -1, name);
                res = true;
            }
            lua_remove(L, i);
            // leaves callback on top
            return res;
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

        bool isEmpty(int i = -1) {
            return lua_isnoneornil(L,i);
        }

        // get results from stack
        const var getNumber(int i = -1) {
            var res( luaL_checknumber(L, i) );
            lua_remove(L, i);
            return res;
        }
        const var checkAndGetNumber(int i = 2, var def = 0) {
            if (lua_type(L, i) == LUA_TNUMBER)
                return getNumber(i);
            if(lua_type(L,i) == LUA_TNIL)
                lua_remove(L, i);
            return def;
        }
        template<class T>
        const T getNumber(int i = -1) {
            T n = luaL_checknumber(L, i);
            lua_remove(L, i);
            return n;
        }
        template<class T>
        const T checkAndGetNumber(int i = 2, T def = 0) {
            if (lua_type(L, i) == LUA_TNUMBER)
                return getNumber<T>(i);
            if(lua_type(L,i) == LUA_TNIL)
                lua_remove(L, i);
            return def;
        }

        const bool getBoolean(int i = -1) {
            luaL_checktype(L, i, LUA_TBOOLEAN);
            bool res = lua_toboolean(L, i);
            lua_remove(L, i);
            return res;
        }
        const bool checkAndGetBoolean(int i = 2, int def = false) {
            if ((lua_type(L, i) == LUA_TBOOLEAN))
                return getBoolean(i);
            if(lua_type(L,i) == LUA_TNIL)
                lua_remove(L, i);
            return def;
        }

        const String getString(int i = -1) {
            size_t len;
            const char *s = luaL_checklstring(L, i, &len);
            CharPointer_UTF8 cp(s);
            String str(cp, len);
            lua_remove(L,i);
            return str;
            //return String(s, len);
        }
        const String checkAndGetString(int i = 2, String def = String::empty) {
            if (lua_type(L, i) == LUA_TSTRING)
                return getString(i);
            if(lua_type(L,i) == LUA_TNIL)
                lua_remove(L, i);
            return def;
        }

        const Array<var> getList(int i = -1) {
            luaL_checktype(L, i, LUA_TTABLE);
            lua_pushvalue(L, i);
            Array<var> res;
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
        const Array<T> getList(int i = -1) {
            luaL_checktype(L, i, LUA_TTABLE);
            lua_pushvalue(L, i);
            Array<T> res;
            lua_pushnil(L);
            while( lua_next(L, -2) != 0 ) {
                res.add( luaL_checknumber(L, -1) );
                lua_pop(L, 1);
            }
            lua_pop(L, 1);
            lua_remove(L,i);
            return res;
        }

        template<class T>
        const juce::Rectangle<T> getRectangle(int i = -1) {
            luaL_checktype(L, i, LUA_TTABLE);
            i = (i<0) ? lua_gettop(L)-(i+1) : i;
            if ( lua_getmetatable(L, i) > 0 ) {
                lua_getfield(L, -1, "__self");
                if ( ! lua_isnil(L, -1) ) { // LRectangle object
                    if ( std::string( lua_tostring(L, -1) ) == "LRectangle" ) {
                        lua_pop(L,1); // __self
                        lua_getfield(L, i, "dump"); // provided by LRectangle
                        lua_pushvalue(L, i); // push self
                        if ( lua_pcall(L, 1, 1, 0) != 0 ) {// get self as argument
                            throwError(lua_pushfstring(L, "LRectangle parsing error: %s", lua_tostring(L,-1)) );
                            return {};
                        }
                    } else {
                        throwError("Wrong object given as a LRectangle");
                        return {};
                    }
                }
            }
            else { // a table
                lua_pushnil(L);
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
        const juce::Rectangle<int> getRectangle(int i = -1) {
            return getRectangle<int>(i);
        }

        template<class T>
        const juce::Line<T> getLine(int i = -1) {
            luaL_checktype(L, i, LUA_TTABLE);
            i = (i<0) ? lua_gettop(L)-(i+1) : i;
            lua_getmetatable(L, i);
            lua_getfield(L, -1, "__self");
            if ( ! lua_isnil(L, -1) ) { // LRectangle object
                if ( std::string( lua_tostring(L, -1) ) == "LLine" ) {
                    lua_pop(L,1); // __self
                    lua_getfield(L, i, "dump"); // provided by LRectangle
                    lua_pushvalue(L, i); // push self
                    if ( lua_pcall(L, 1, 1, 0) != 0 ) {// get self as argument
                        throwError(lua_pushfstring(L, "LLine parsing error: %s", lua_tostring(L,-1)));
                        return {};
                    }
                } else {
                    throwError("Wrong object given as a LLine");
                    return {};
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
            T x1 = luaL_checknumber(L, -1);
            lua_rawgeti(L, ind, 4);
            T y1 = luaL_checknumber(L, -1);

            lua_pop(L, 5); // table + x, y, w, h
            lua_pop(L,1); // mt or nil
            lua_remove(L,i); // original argument

            return { x, y, x1, y1 };
        }
        const juce::Line<int> getLine(int i = -1) {
            return getLine<int>(i);
        }


        template<class T>
        const juce::Point<T> getPoint(int i = -1) {
            luaL_checktype(L, i, LUA_TTABLE);
            lua_pushvalue(L, i);
            lua_rawgeti(L, -1, 1);
            T x = luaL_checknumber(L, -1);
            lua_rawgeti(L, -2, 2);
            T y = luaL_checknumber(L, -1);
            lua_pop(L, 3);
            lua_remove(L,i);
            return { x, y };
        }
        const juce::Point<int> getPoint(int i = -1) {
            return getPoint<int>(i);
        }

        template<class T>
        const juce::Range<T> getRange(int i = -1) {
            luaL_checktype(L, i, LUA_TTABLE);
            lua_pushvalue(L, i);
            lua_rawgeti(L, -1, 1);
            T x = luaL_checknumber(L, -1);
            lua_rawgeti(L, -2, 2);
            T y = luaL_checknumber(L, -1);
            lua_pop(L, 3);
            lua_remove(L,i);
            return { x, y };
        }
        const juce::Range<int> getRange(int i = -1) {
            return getRange<int>(i);
        }

        const juce::SparseSet<int> getSparseSet(int i = -1) {
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

        const std::list<var> getStdList(int i = -1) {
            luaL_checktype(L, i, LUA_TTABLE);
            lua_pushvalue(L,i);
            std::list<var> res;
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
        T* toUserdata(int i = -1) {
            T* res = Luna<T>::check(L,i);
            lua_remove(L,1);
            return res;
        }

        template<class T>
        T* to_juce(int i = -1) {
            T* res = Luna<T>::to_juce(L, i);
            lua_remove(L,i);
            return res;
        }

        template<class T>
        T* raw_cast(int i = -1) {
            luaL_checktype(L, i, LUA_TUSERDATA);
            T* res = static_cast<T*>(lua_touserdata(L, i));
            lua_remove(L,i);
            return res;
        }

        template<class T, class U=T>
        U* from_luce(int i = -1) {
            // TODO: use check, meaning -- refactor luna5 first
            //T* res = Luna<T>::check(L,i);
            //lua_remove(L,i);
            //return dynamic_cast<U*>(res);
            //luaL_checktype(L, i, LUA_TTABLE);
            if ( lua_type(L,i) != LUA_TTABLE )
                //LUCE::luce_error("from_luce: given object is not a valid Luce object.");
                throwError("from_luce: given object is not a valid Luce object.");

            lua_getfield(L, i, "__self");
            if ( lua_isnil(L, -1) ) {
                //LUCE::luce_error("from_luce: given object is not a valid Luce object: can't find __self.");
                throwError("from_luce: given object is not a valid Luce object: can't find __self.");
                return nullptr;
            }
            // ???? et si l'objet était détruit par C++ ? il faudrait peut-être incrémenter les références
            // mais si l'objet n'est pas détruit par C++, il ne le sera jamais !...
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
                    if ( lua_isnil(L, -1) ) {
                        lua_pushstring(L, "Internal Error: Can't register class -- please, send a bug report");
                        lua_error(L);
                    }
                    
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
                    for ( auto& it : T::enums[i].values ) {
                        lua_pushstring(L, it.first.c_str());
                        lua_pushnumber(L, it.second);
                        lua_settable(L, nt);
                    }
                    lua_settable(L, t);
                }

                lua_pushcfunction(L, &Luna < T >::__eq);
                lua_setfield(L, t, "LEquals");

                luaL_getmetatable(L, T::className);
                if ( ! lua_isnil(L, -1) ) {
                    lua_setmetatable(L, -2);
                } else lua_pop(L,1);

                return 1;

            } else {
                lua_pushnil(L);
                return 1;
            }
        }
        template<class T, class U = T>
        int storeAndReturnUserdata(U* udata) {
            WeakReference<LSelfKill> ref = dynamic_cast<LSelfKill*>(udata);
            LUA_COMMON::store( (intptr_t)udata, ref );
            return returnUserdata<T, U>(udata);
        }

        // as for Component
        typedef int(*constructor_t)(Component* udata);
        typedef std::map<String, constructor_t> types_t;
        types_t types, testtypes;

        template<class T>
        int luacast(Component* udata) { return returnUserdata<T,Component>(udata); }

        template<class T>
        int testcast(Component* udata) {
            return( dynamic_cast<T*>(udata) != nullptr );
        }

        template<class T>
        void register_class(String const& n) {
            types.insert( std::make_pair(n, &luacast<T>));
            testtypes.insert( std::make_pair(n, &testcast<T>));
        }
        
        int casttype(String const& n, Component* udata) {
            types_t::iterator i = types.find(n);
            if( i==types.end() ) return 0;
            return i->second(udata);
        }

        int testtype(String const& n, Component* udata) {
            types_t::iterator i = testtypes.find(n);
            if( i==testtypes.end() ) return 0;
            return i->second(udata);
        }

        template<class T>
        T luaL_getnum(const char *t, int i = -1);

        // from LBase light user data
        typedef int(*constructor_unlight_t)(void* udata);
        typedef std::map<String, constructor_unlight_t> types_unlight_t;
        types_unlight_t types_unlight;

        template<class T, class U = T>
        int luacast_unlight(void* udata) {
            return returnUserdata<T,U>(static_cast<U*>(udata));
        }

        template<class T, class U = T>
        void register_class_unlight(String const& n) {
            types_unlight.insert( std::make_pair("L"+n, &luacast_unlight<T,U>) );
        }
        
        int casttype_unlight(String const& n, void* udata) {
            types_unlight_t::iterator i = types_unlight.find(n);
            if( i==types_unlight.end() ) return 0;
            return i->second(udata);
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
            std::string str = val.toStdString();
            lua_pushlstring(L, str.c_str(), str.length());
            //lua_pushlstring(L, val.toRawUTF8(), val.length());
            return 1;
        }
        int returnString(const std::string& val) {
            lua_pushlstring(L, val.c_str(), val.size());
            return 1;
        }

        int TODO_OBJECT(const String& tmpl, const String& msg = "Not yet implemented: ") {
            throwError((msg + tmpl).toRawUTF8());
            return 0;
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

        const int call_cb( const LBase* key, const char *name, int nb_ret = 0,
                                                                const std::list<var>& args = std::list<var>() ) {
            jassert( L != nullptr );
            if ( L == nullptr ) {
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
                    if( type == "index" ) {
                        int idx = lr->getIndex();
                        lua_pushvalue(L, idx);
                        lua_remove(L, idx);
                        --func_index;
                    } else if ( type == "MouseEvent" || type == "LMouseEvent" ) {
                        //returnUserdata<LMouseEvent, MouseEvent>( (MouseEvent*)lr->getMe() );
                        returnUserdata<LMouseEvent, MouseEvent>( static_cast<const MouseEvent*>(lr->getMe()) );

                    } else if ( type == "KeyPress" ) {
                        returnUserdata<LKeyPress, KeyPress>( static_cast<const KeyPress*>(lr->getMe()) );

                    } else if ( type == "Graphics" ) {
                        returnUserdata<LGraphics>( (LGraphics*)lr->getMe() );

                    } else if ( type == "TreeViewItem" ) {
                        //returnUserdata<LTreeViewItem, TreeViewItem>( (TreeViewItem*)lr->getMe() );
                        returnUserdata<LTreeViewItem, TreeViewItem>( static_cast<const TreeViewItem*>(lr->getMe()) );

                    } else if ( type == "SourceDetails" ) {
                        returnUserdata<LSourceDetails>( static_cast<const LSourceDetails*>(lr->getMe()) );

                    } else if ( type == "Component" ) {
                        returnUserdata<LJComponent, Component>( (Component*)lr->getMe() );

                    } else if ( type == "PopupMenu" ) {
                        returnUserdata<LPopupMenu>( (LPopupMenu*)lr->getMe() );

                    } else if ( type == "Colour" ) {
                        returnUserdata<LColour, Colour>( static_cast<const LColour*>(lr->getMe()) );

                    #if LUCE_AUDIO
                    } else if ( type == "AudioSampleBuffer" ) {
                        returnUserdata<LAudioSampleBuffer>( (LAudioSampleBuffer*)lr->getMe() );
                    #endif

                    } else if ( type == SELF ) {
                        // UNTESTED
                        lua_pushvalue(L, 1);
                        luaL_getmetatable(L, LPopupMenu::className);
                        lua_setmetatable(L, -2);
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
                const char *msg = lua_tostring(L,-1);
                DBG(String("failed to execute callback: ") + name);
                DBG(String("Error was: ") + msg);
                lua_pop(L,1);
                lua_pushfstring(L, "Failed to execute callback '%s': %s", name, msg);
                // Get out, a failure's a failure
                throwError(lua_pushfstring(L, "failed to execute callback: %s", lua_tostring(L,-1)));
                return 0;
            }
            //lua_remove(L, errfunc);
            lua_remove(L, func_index);

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

        const char* lua_getnumtype(int i = -1) {
            if (lua_isnumber(L, i)) return "int";
            else if (!lua_istable(L, i)) return NULL;
            lua_getfield(L, i, "__type");
            const char *res = lua_tostring(L,-1);
            lua_pop(L,1);
            return res;
        }
        template<class T>
        T luaL_getlnumber(const char *t, int i = -1) {
            if(lua_istable(L,i))
                lua_rawgeti(L, i, 1);
            else lua_pushvalue(L,i);
            if(!lua_isnumber(L, -1)) {
                throwError(lua_pushfstring(L, "Expected LNumber, got %s", lua_typename(L,lua_type(L,-1))));
            }
            T n = lua_tonumber(L,-1);
            lua_pop(L,1);
            lua_remove(L, i);
            return n;
        }

        template<class T, class U = T>
        const Array<U*> getObjectList(int i = -1) {
            i = (i<0) ? lua_gettop(L) - (i+1) : i;
            luaL_checktype(L, i, LUA_TTABLE);
            int n = lua_objlen(L, i);
            Array<U*> res;

            for (int ind=1;ind<=n;++ind) {
                U *comp;
                lua_rawgeti(L, i, ind);
                // to emulate nil object, use a string
                if ( lua_type(L, -1) == LUA_TSTRING ) { // any string will do
                    comp = nullptr;
                    lua_pop(L,1);
                }
                else
                    comp = LUA::from_luce<T,U>();
                res.add( comp );
            }
            lua_remove(L,i);
            return res;
        }
        const Array<Component*> getComponentList(int i = -1) {
            return getObjectList<LComponent, Component>(i);
        }

        //bool isoftype(const char *t, int i) {
        //    return lua_getnumtype(i) == t;
        //}
        //#define lua_isoftype(t,i) isoftype(#t, i)
        //#define cn_1(p)   luaL_getlnumber<p>( #p )
        //#define cn_2(p,i) luaL_getlnumber<p>( #p, i )
        //#define cn_sel(x,p,i,FUNC, ...) FUNC
        //#define luaL_checknum(...) cn_sel(,##__VA_ARGS__, cn_2(__VA_ARGS__), cn_1(__VA_ARGS__),)

    }
}
#define REGISTER_CLASS(T) LUA::register_class<T>(#T)
#define REGISTER_LIGHT_CLASS(T) LUA::register_class_unlight<L##T, T>(#T)

#endif // __LUA_O_H
