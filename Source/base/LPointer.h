#ifndef __LUCE_LPOINTER_H
#define __LUCE_LPOINTER_H

#define LNewPointer(T,...) LTPointer<T>(##__VA_ARGS__);

enum class LUCE_TYPE {
    number = 1,
    string = 2,
    pointer = 3,
    boolean = 4,
    nil = 5,
    undefined = 0
};

template<typename T, LUCE_TYPE Type = LUCE_TYPE::undefined>
class LTPointer {
public:
    LTPointer(lua_State *L, int size_ = 0, T *copy = nullptr, bool shouldBeDeleted_ = false, bool deleteData = false)
        :copied(false),
         size(size_),
         shouldBeDeleted(shouldBeDeleted_)
    {
        if(copy!=nullptr) {
            data = copy;
            if(!deleteData) copied = true;
        } else if(size) {
            data = (T*)calloc(size, sizeof(T));
        }
        /*
        else {
            if(lua_istable(L,2)) {
                int size = lua_objlen(L,2)+1;
                data = (T*)malloc(sizeof(T)*size-1);
                for(int i=1,j=0;i<size;++i,++j) {
                    lua_rawgeti(L,2,i);
                    T v = (T)lua_tonumber(L,-1);
                    lua_pop(L,1);
                    data[j] = v;
                }
                lua_pop(L,1);
            }
        }
        */
    }
    ~LTPointer() {
        if(!copied) free(data);
    }

    static int bulk_update(lua_State *L) {
        if(lua_istable(L,2)) {
            /*
            if(type==LUCE_TYPE::undefined) { // try to guess data type
                lua_getmetatable(L,-1);
                if(!lua_isnil(L,-1)) {
                    lua_getfield(L, -1, "__type");
                    if(!lua_isnil(L,-1)) {
                        type = (LUCE_TYPE)lua_tonumber(L,-1);
                    }
                    lua_pop(L,1);
                    if(type==LUCE_TYPE::undefined) {
                        lua_pushnil(L);
                        while(lua_next(L,-2)) {
                            if(!lua_isnoneornil(L,-1)) {
                                switch(lua_type(L,-1)) {
                                    case LUA_TNUMBER:
                                        type = LUCE_TYPE::number; break;
                                    case LUA_TBOOLEAN:
                                        type = LUCE_TYPE::boolean; break;
                                    case LUA_TSTRING:
                                        type = LUCE_TYPE::string; break;
                                    case LUA_TUSERDATA:
                                        type = LUCE_TYPE::pointer; break;
                                }
                                lua_pop(L,1);
                                break;
                            }
                            lua_pop(L,1);
                        }
                        lua_pop(L,1);
                    }
                }
                lua_pop(L,1);
            }
            */

            /*
            lua_pushnil(L);
            while(lua_next(L,2)) {
                T v;
                int i = lua_tonumber(L,-2)-1;
                switch(type) {
                    case LUCE_TYPE::number:
                        v = (T)lua_tonumber(L,-1);
                    case LUCE_TYPE::string:
                        v = (T)lua_tostring(L,-1);
                    case LUCE_TYPE::pointer:
                        v = (T)lua_touserdata(L,-1);
                }
                lua_pop(L,1);
                data[i] = v;
            }
            */
        }
        lua_settop(L,1);
    }

    //================================================================================

    /*
       self = {
           __sync = sync,
           __data = data
       }
       setmetatable(self, {
        __type = T,
        __index = function(self,k)
            return rawget(self,"__data")[k]
        end,
        __newindex = function(self, k, v)
            local t = rawget(self,"__data")
            local len = #t
            t[k] = v
            if(k>len)then
                rawget(self,"__update")(k)
            else
                rawget(self,"__sync")(k)
            end
        end,
       })
    */

    // BEWARE of double-free -- use shouldBeDeleted flag to enable or disable __gc
    static int __gc(lua_State *L) {
        T** udata = static_cast<T**>(lua_touserdata(L, -1));
        if(udata and *udata) {
            T* p = *udata;
            delete p;
        }
        return 0;
    }
    static int __tostring(lua_State *L) {
        lua_pushliteral(L, "LPointer");
        return 1;
    }

    //static int sync(lua_State *L, int k) {
    static int sync(lua_State *L) {
        T* _data = (T*)lua_touserdata(L, lua_upvalueindex(1));
        int k = lua_tonumber(L, 1);
        T v = (T)lua_tonumber(L, 2);
        _data[k] = v;
        return 0;
    }
    //static int update(lua_State *L, int k) {
    static int update(lua_State *L) {
        T* _data = (T*)lua_touserdata(L, lua_upvalueindex(1));
        int k = lua_tonumber(L, 1);
        T v = (T)lua_tonumber(L, 2);
        std::cout << "UPDATING array! " << k << std::endl;
        // TODO: extend array size
        return 0;
    }

    static int bulk_sync(lua_State *L) {
        T* _data = (T*)lua_touserdata(L, lua_upvalueindex(1));
        int size = (int)lua_tonumber(L, lua_upvalueindex(2));
        lua_pushliteral(L,"__data");
        lua_rawget(L,-2);
        for(int i=1,j=0;i<size;++i,++j) {
            lua_rawgeti(L, -1, i);
            _data[j] = (T)lua_tonumber(L,-1);
            lua_pop(L,1);
        }
        lua_pop(L,1);
        return 0;
    }

    static int __index(lua_State *L) { // self, k
        lua_pushliteral(L, "__data");
        lua_rawget(L, 1);
        lua_pushvalue(L, 2);
        lua_rawget(L, -2);
        lua_remove(L,-2);
        return 1;
    }
    static int __newindex(lua_State *L) { // self, k, v
        lua_pushliteral(L, "__data");
        lua_rawget(L,1);
        if(lua_isnoneornil(L,-1)) {
            std::cout << "NO TABLE FOUND!!!!!????" << std::endl;
            lua_pop(L,1);
            return 0;
        }
        int t = lua_type(L,2);
        if(t==LUA_TNUMBER) {
            int len = lua_objlen(L,-1);
            int k = lua_tonumber(L,2);
            lua_pushvalue(L, 3);
            lua_rawseti(L, -2, k);

            lua_pushliteral(L, "delayed");
            lua_rawget(L, -2);
            if(lua_toboolean(L,-1)) {
                lua_pop(L,2);
                return 0;
            }
            lua_pop(L,1);
            if(!lua_getmetatable(L,1)) {
                std::cout << "metatable not found !!!!" << std::endl;
                lua_error(L);
            }
            if(k>len) {
                std::cout << "ERROR: extending array is not (yet) allowed" << std::endl;
                /*
                lua_pushliteral(L, "update");
                lua_rawget(L,-2);
                if(!lua_isnoneornil(L,-1)) {
                    lua_pushvalue(L,2);
                    lua_pushvalue(L,3);
                    lua_pcall(L, 2, 0, 0);
                } else {
                    std::cout << "function UPDATE not found!" << std::endl;
                }
                */
                //update(L, k);
            }else{
                lua_pushliteral(L, "sync");
                lua_rawget(L,-2);
                if(!lua_isnoneornil(L,-1)) {
                    lua_pushvalue(L,2);
                    lua_pushvalue(L,3);
                    if(lua_pcall(L, 2, 0, 0)) {
                        std::cout << "LPointer: error while calling sync" << std::endl;
                        lua_error(L);
                    }
                } else {
                    std::cout << "function SYNC not found! " << lua_gettop(L) << std::endl;
                    //lua_error(L);
                }
                //sync(L, k);
            }
            lua_pop(L,1);

        }/* else if(t==LUA_TSTRING){
            const char *k = lua_tostring(L,2);
            if(k=="sync") {
                bulk_update(L);
            } else {
                lua_pushvalue(L,3);
                lua_setfield(L, -2, k);
            }
        }*/
        else{
            lua_pushvalue(L,2);
            lua_pushvalue(L,3);
            lua_rawset(L, -3);
        }
        lua_pop(L,1);
        return 0;
    }
    /*
    static int __len(lua_State *L) {
        int table_size = (int)lua_tonumber(L, lua_upvalueindex(1));
        lua_pushnumber(L, table_size);
        return 1;
    }
    */
    int __push_pointer(lua_State *L) {
        const char *name = String("LPointer"+String(typeid(T).name())).toRawUTF8();
        const char *name_p = String(name+String("Pointer")).toRawUTF8();

        lua_newtable(L);
        // copy existing values into a table
        lua_createtable(L, size, 0);
        for(int i=0;i<size;++i) {
            T v = data[i];
            lua_pushnumber(L,v);
            // FIXME: compiler won't let it work as expected, for types are set by type...
            //switch(type) {
            //    case LUCE_TYPE::number:
            //        lua_pushnumber(L,v);
            //    case LUCE_TYPE::string:
            //        lua_pushstring(L,v);
            //    case LUCE_TYPE::pointer:
            //        lua_pushlightuserdata(L,v);
            //}
            lua_rawseti(L, -2, i+1);
        }
        lua_pushliteral(L, "size");
        lua_pushnumber(L,size);
        lua_rawset(L, -3);

        lua_pushlightuserdata(L, data);
        lua_pushnumber(L,size);
        lua_pushcclosure(L, &bulk_sync, 2);
        lua_setfield(L,-2, "sync");

        lua_setfield(L, -2, "__data");

        // meta
        luaL_newmetatable(L, name);

        //void **udata = lua_newuserdata(L, sizeof(this));
        //*udata = this;
        T** udata = static_cast<T**>(lua_newuserdata(L, sizeof(T *)));
        *udata = (T*)this;
        
        luaL_newmetatable(L, name_p);
        lua_pushcclosure(L, &__tostring, 0);
        lua_setfield(L, -2, "__tostring");
        if(shouldBeDeleted) {
            lua_pushcclosure(L, &__gc, 0);
            lua_setfield(L, -2, "__gc");
        }
        lua_setmetatable(L,-2);
       
        lua_setfield(L, -2, "__self");

        lua_pushnumber(L, (int)type);
        lua_setfield(L, -2, "__type");

        lua_pushcclosure(L, &__index, 0);
        lua_setfield(L, -2, "__index");

        lua_pushcclosure(L, &__newindex, 0);
        lua_setfield(L, -2, "__newindex");

        lua_pushlightuserdata(L, data);
        lua_pushcclosure(L, &sync, 1);
        lua_setfield(L, -2, "sync");

        lua_pushlightuserdata(L, data);
        lua_pushcclosure(L, &update, 1);
        lua_setfield(L, -2, "update");

        /*
        lua_pushnumber(L,size);
        lua_pushcclosure(L, &__len, 1);
        lua_setfield(L, -2, "__len");
        */

        lua_setmetatable(L,-2);
        return 1;
    }

private:
    LUCE_TYPE type = Type;
    T *data;
    int size;
    bool copied;
    bool shouldBeDeleted;
};
typedef LTPointer<float, LUCE_TYPE::number> LPointerFloat;

#endif // __LUCE_LPOINTER_H
