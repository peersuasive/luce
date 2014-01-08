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

        // get results from stack
        const var getNumber(int i= -1) {
            var res( luaL_checknumber(L, i) );
            lua_remove(L, i);
            return res;
        }
        const var checkAndGetNumber(int i=-1, var def = 0) {
            return lua_type(L, i) == LUA_TNUMBER ? getNumber(i) : def;
        }
        
        const bool getBoolean(int i) {
            luaL_checktype(L, i, LUA_TBOOLEAN);
            bool res = lua_toboolean(L, i);
            lua_remove(L, i);
            return res;
        }
        const bool checkAndGetBoolean(int i=-1, int def = false) {
            return lua_type(L, i) == LUA_TBOOLEAN ? getBoolean(i) : def;
        }

        const String getString(int i = -1) {
            size_t len;
            const char *s = luaL_checklstring(L, i, &len);
            lua_remove(L,i);
            return String(s, len);
        }

        const Array<var> getList(int i=-1) {
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
            lua_remove(L,i);
            return res;
        }

        const juce::Rectangle<int> getRectangle(int i=-1) {
            luaL_checktype(L, i, LUA_TTABLE);
            lua_pushvalue(L, i);
            int ind = lua_gettop(L);
            lua_rawgeti(L, ind, 1);
            int x = luaL_checknumber(L, -1);
            lua_rawgeti(L, ind, 2);
            int y = luaL_checknumber(L, -1);
            lua_rawgeti(L, ind, 3);
            int w = luaL_checknumber(L, -1);
            lua_rawgeti(L, ind, 4);
            int h = luaL_checknumber(L, -1);
            lua_pop(L, 5);
            lua_remove(L,i);
            return { x, y, w, h };
        }

        const juce::Point<int> getPoint(int i=-1) {
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

        const std::list<var> getStdList(int i=-1) {
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
        T* toUserdata(int i=-1) {
            T* res = Luna<T>::check(L,i);
            lua_remove(L,1);
            return res;
        }

        template<class T>
        T* to_juce(int i=-1) {
            T* res = Luna<T>::to_juce(L, i);
            lua_remove(L,i);
            return res;
        }

        template<class T>
        T* raw_cast(int i=-1) {
            luaL_checktype(L, i, LUA_TUSERDATA);
            T* res = static_cast<T*>(lua_touserdata(L, i));
            lua_remove(L,i);
            return res;
        }

        template<class T>
        T* from_luce(int i=-1) {
            luaL_checktype(L, i, LUA_TTABLE);
            lua_getfield(L, i, "__self");
            if ( lua_isnil(L, -1) )
                throwError("given object is not a valid Luce object");
            T **obj = static_cast<T**>(lua_touserdata(L, -1));
            lua_remove(L, i); // object
            lua_pop(L,1); // pushed __self
            if(!obj)
                return nullptr;
            return *obj;
        }

        template<class T, class U = T>
        int returnUserdata(U* udata) {
            if ( udata ) {
                DBG(String("size of L at the beginning: ") + String(lua_gettop(L)));

                T *ldata = static_cast<T*>( udata );
                lua_newtable(L);
                int t = lua_gettop(L);
                lua_pushstring(L, "__self");
                T** r = static_cast<T**>( lua_newuserdata(L, sizeof(T*)) );
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

                DBG(String("size of L at the end: ") + String(lua_gettop(L)));
                return 1;

            } else {
                lua_pushnil(L);
                return 1;
            }
        }

        int returnUserdata(MouseEvent* e) {
            return returnUserdata<LMouseEvent, MouseEvent>( (MouseEvent*)e );
        }

        int returnBoolean(bool val) {
            lua_pushboolean(L, val);
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
                else {
                    lua_pushnil(L);
                    std::cout << "type not yet implemented" << std::endl;
                }
                lua_rawseti(L, t, ++i);
            }
            return 1;
        }

        int TODO_OBJECT(const String& tmpl, const String& msg = "Not yet implemented: ") {
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
            int i = 0;
            lua_newtable(L);
            int t = lua_gettop(L);
            lua_pushnumber(L, r.getX());
            lua_rawseti(L, t, 1);
            lua_pushnumber(L, r.getY());
            lua_rawseti(L, t, 2);
            return 1;
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

        const int call_cb(int ref, int nb_ret , const std::list<var>& args  ) {
            int nb_args = args.size();
            jassert( L != nullptr );
            if ( L == nullptr ) {
                std::cout << "No lua state found !" << std::endl;
                return -2;
            }
            int status = 0;
            lua_rawgeti(L, LUA_REGISTRYINDEX, ref);
            int func_index = lua_gettop(L);
            if ( lua_type(L, -1) == LUA_TFUNCTION ) {
                lua_pushcclosure(L, stacktrace, 0);
                int errfunc = lua_gettop(L);
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
                            returnUserdata<LMouseEvent, MouseEvent>( (MouseEvent*)lr->getMe() );

                        } else if ( type == "Properties" ) {
                            --nb_args;
                            HashMap<String, var>& h = *lr->getHash();
                            lua_newtable(L);
                            int t = lua_gettop(L);
                            for (HashMap<String,var>::Iterator i(h); i.next();) {
                                ++nb_args;
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
                            std::cout << "type not yet implemented" << std::endl;
                            lua_pushnil(L);
                        }
                        lr = nullptr;
                    }
                    else {
                        // ça peut etre un tableau, donc _newtable, boucle, recusivité avec ici
                        // ou un hashmap, idem, mais on pushstring avand le newtable s'il y a lieu, etc.
                        // ou un objet -- comment je détècte ? le type Binary... du var ?
                        // en tout cas, probablement, lightuserdata, du moins s'il fait
                        // partie des types L-implémentés, sinon... ?
                        // un nouvel objet n'aurait le comportement attendu,
                        // mais peut-etre implémenter l'instanciation par copie de l'objet avec la L-classe correspondante ?
                        // et si elle n'existe pas, on se pose pas la question, c'est une erreur, mais il y a peu de chances
                        // pour que ça arrive puisqu'on est dans notre environnement
                        lua_pushnil(L);
                        std::cout << "type not yet implemented" << std::endl;
                    }
                }

                // call callback function
                if ( lua_pcall(L, args.size(), nb_ret, errfunc) != 0 ) {
                    DBG("failed to execute callback.");
                    status = -1;
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
            std::cout << "stack state (end): " << lua_gettop(L) << std::endl;
            return status;
        }

        const int call_cb( const HashMap<String,int>& cb, const String& key, int nb_ret, 
                                                                const std::list<var>& args) 
        {
            // quick return
            if ( ! cb.contains(key) || (cb[key] == LUA_REFNIL) )
                return -1;

            int status = call_cb(cb[key], nb_ret, args);
            if ( status < 0 ) {
                DBG("couldn't execute the " + key + " callback.");
            }
            else if ( ! status ) {
                DBG("no callback found for " + key);
            }
            return status;
        }

        void unreg( const HashMap<String, int>& cb, const String& key) {
            luaL_unref(LUA::Get(), LUA_REGISTRYINDEX, cb[key]);
        }

        void unregAll( const HashMap<String,int>& cb ) {
            HashMap<String, int>::Iterator i(cb);
            while(i.next()) {
                luaL_unref(LUA::Get(), LUA_REGISTRYINDEX, i.getValue());
            }
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
