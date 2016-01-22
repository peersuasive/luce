#pragma once
/***************************************************
Luna Five

This version has been modified

@see http://lua-users.org/wiki/LunaFive

There's no mentioned license on the original code
all modifications are (c) 2013 Peersuasive Technologies

****************************************************/

#include <iostream>

#define method(class, name) {#name, &class::name}
#define smethod(class, name) {#name, &class::s_##name}

template < class T > 
class Luna {

private:
    static void *luaL_xtestudata (lua_State *L, int ud, const char *tname) {
        void *p = lua_touserdata(L, ud);
        if (p != NULL) {  /* value is a userdata? */
            if (lua_getmetatable(L, ud)) {  /* does it have a metatable? */
                luaL_getmetatable(L, tname);  /* get correct metatable */
                if (!lua_rawequal(L, -1, -2))  /* not the same? */
                    p = NULL;  /* value is a userdata with wrong metatable */
                lua_pop(L, 2);  /* remove both metatables */
                return p;
            }
        }
        return NULL;  /* value is not a userdata with a metatable */
    }

public:

    struct Inheritence {
        const char *name;
        int (T::*getter) (lua_State *);
        int (T::*setter) (lua_State *);
    };

    struct InheritenceF {
        const char* name;
        int (T::*func) (lua_State *);
    };

    struct PropertyType {
        const char *name;
        int (T::*getter) (lua_State *);
        int (T::*setter) (lua_State *);
    };

    struct FunctionType {
        const char* name;
        int (T::*func) (lua_State *);
    };

    struct StaticType {
        const char* name;
        int (*func) (lua_State*);
    };

    struct Enum {
        const char *name;
        std::map<std::string, int> values;
    };

    /**
      Retrieves a wrapped class from the arguments passed to the function, specified by narg (position).
      This function will raise an exception if the argument is not of the correct type.
      @param L Lua State
      @param narg Position to check
      @return 
      @exception std::exception
      */

    static T* check(lua_State * L, int narg) {
        luaL_checktype(L, narg, LUA_TTABLE);
        lua_getfield(L, narg, "__self");
        std::string cn = std::string(T::className)+"_";
        T** obj = static_cast <T **>(luaL_checkudata(L, -1, cn.c_str()));
        lua_pop(L,1);
        if ( !obj )
            return nullptr; // lightcheck returns nullptr if not found.

        return *obj;      // pointer to T object
    }

    static T* to_juce(lua_State * L, int narg) {
        luaL_checktype(L, narg, LUA_TTABLE);
        lua_getfield(L, narg, "__self");
        if ( lua_isnil(L, -1) ) {
            std::cout << "ERROR: not a valid object" << std::endl;
            lua_pop(L,1);
            return nullptr;
        }

        T **obj = static_cast<T**>(lua_touserdata(L, -1));
        if(!obj)
            return nullptr;

        lua_pop(L,1);
        return *obj;      // pointer to T object
    }

    /**
      Retrieves a wrapped class from the arguments passed to the func, specified by narg (position).
      This func will return nullptr if the argument is not of the correct type.  Useful for supporting
      multiple types of arguments passed to the func
      @param L Lua State
      @param narg Position to check
      */ 
    static T* lightcheck(lua_State * L, int narg) {
        T** obj = static_cast <T **>(luaL_testudata(L, narg, T::className));
        if ( !obj )
            return NULL; // lightcheck returns nullptr if not found.
        return *obj;      // pointer to T object
    }

    /*
       Registers your class with Lua.  Leave namespac "" if you want to load it into the global space.
       @param L Lua State
       @param namespac Namespace to load into, if black the global namespace is assumed
       */
    // TODO: check inherited classes and add inherited methods
    // TODO: add another array for static methods,
    //       like we'd need one for Time::getCurrentTime, for instance
    static void Register(lua_State * L, const char *namespac = NULL, bool is_inh = false ) {
        //DBG(String("**registering ") + T::className);
        lua_newtable(L);
        int nt = lua_gettop(L);
        lua_pushcfunction(L, &Luna < T >::lconstructor);
        lua_setfield(L, nt, "new");

        // static methods
        for (int i = 0; T::statics[i].name; ++i) {
            lua_pushcfunction(L, T::statics[i].func);
            lua_setfield(L, nt, T::statics[i].name);
        }

        // set static values, like enums...
        for ( int i = 0; T::enums[i].name; ++i ) {
            bool is_root = false;
            int subt;
            if(T::enums[i].name == "") { // is table name is empty, place directly in the main component table
                is_root=true;
                subt = nt;
            }
            else {
                lua_pushstring(L, T::enums[i].name);
                lua_newtable(L);
                subt = lua_gettop(L);
            }
            for ( auto& it : T::enums[i].values ) {
                lua_pushstring(L, it.first.c_str());
                lua_pushnumber(L, it.second);
                lua_settable(L, subt);
            }
            if(!is_root)
                lua_settable(L, nt);
        }

        luaL_newmetatable(L, T::className);
        int metatable = lua_gettop(L);

        // FIXME: instead of __exists, offer __index and __newindex
        //        @see http://stackoverflow.com/questions/3332448/treating-userdate-like-a-table-in-lua
        //        for an example, which would also take care of user defined variables
        lua_pushstring(L, "__exists");
        lua_pushcfunction(L, &Luna < T >::property_exists);
        lua_settable(L, metatable);

        lua_pushstring(L, "__call");
        lua_pushcfunction(L, &Luna < T >::constructor);
        lua_settable(L, metatable);

        lua_pushstring(L, "__gc");
        lua_pushcfunction(L, &Luna < T >::gc_obj);
        lua_settable(L, metatable);

        lua_pushstring(L, "__tostring");
        lua_pushcfunction(L, &Luna < T >::to_string);
        lua_settable(L, metatable);

        lua_pushstring(L, "__index");
        lua_pushcfunction(L, &Luna < T >::property_getter);
        lua_settable(L, metatable);

        lua_pushstring(L, "__newindex");
        lua_pushcfunction(L, &Luna < T >::property_setter);
        lua_settable(L, metatable);

        lua_pushstring(L, "__eq");
        lua_pushcfunction(L, &Luna < T >::___eq);
        lua_settable(L, metatable);

        int p_i = 0;
        for (int i = 0; T::properties[i].name; ++i, ++p_i) { // Register some properties in it
            lua_pushstring(L, T::properties[i].name);     // Having some string associated with them
            lua_pushnumber(L, i);                                         // And a number indexing which property it is
            lua_settable(L, metatable);
        }
        // inherited properties
        for ( int i = 0; T::inherits[i].name; ++i ) {
            lua_pushstring(L, T::inherits[i].name);
            lua_pushnumber(L, i+p_i);
            lua_settable(L, metatable);
        }
        lua_pushstring(L, "__pn");
        lua_pushnumber(L, p_i);
        lua_settable(L, metatable);
 
        int m_i = 0;
        for (int i = 0; T::methods[i].name; ++i, ++m_i) {
            lua_pushstring(L, T::methods[i].name);          // Register some functions in it
            lua_pushnumber(L, i | ( 1 << 8 ) );                   // Add a number indexing which func it is
            lua_settable(L, metatable);
        }
        // inherited methods
        for ( int i = 0; T::inheritsF[i].name; ++i ) {
            lua_pushstring(L, T::inheritsF[i].name);
            lua_pushnumber(L, i+m_i | (1 << 8));
            lua_settable(L, metatable);
        }
        lua_pushstring(L, "__mn");
        lua_pushnumber(L, m_i);
        lua_settable(L, metatable);

        lua_pop(L,1); // pop main mt

        std::string cn = std::string(T::className) + "_";
        luaL_newmetatable(L, cn.c_str());
        int metatable_ = lua_gettop(L);

        lua_pushstring(L, "__tostring");
        lua_pushcfunction(L, &Luna < T >::to_string_);
        lua_settable(L, metatable_);

        lua_pushstring(L, "__gc");
        lua_pushcfunction(L, &Luna < T >::gc_obj_);
        lua_settable(L, metatable);

        lua_pushstring(L, "__eq");
        lua_pushcfunction(L, &Luna < T >::__eq);
        lua_settable(L, metatable);

        lua_pop(L,1); // pop int. mt
        //DBG(String("*** registered ") + T::className);
    }

    /**
      Constuctor (used internally)
      @param L Lua State
      */
    static int constructor(lua_State * L) {
        T*  ap = new T(L);
        WeakReference<LSelfKill> ref = dynamic_cast<LSelfKill*>(ap);
        LUA::store( (intptr_t)ap, ref );

        lua_newtable(L);
        int t = lua_gettop(L);
        lua_pushstring(L, "__self");
        T** a = static_cast<T**>(lua_newuserdata(L, sizeof(T *))); // Push value = userdata
        *a = ap;

        //DBG(String("********** new for ") + T::className);
        std::string cn = std::string(T::className) + "_";
        luaL_getmetatable(L, cn.c_str());
        lua_setmetatable(L, -2); // udata metatable_

        lua_settable(L, t);

        lua_pushstring(L, "methods");
        lua_newtable(L);
        int nt = lua_gettop(L);
        int ind = 0;
        for ( int i = 0; T::methods[ind].name; ++i, ++ind) {
            lua_pushstring(L, T::methods[ind].name);
            lua_rawseti(L, nt, ind+1);
        }
        for ( int i = 0; T::inheritsF[i].name; ++i, ++ind ) {
            lua_pushstring(L, T::inheritsF[i].name);
            lua_rawseti(L, nt, ind);
        }
        lua_settable(L, t);

        // direct get/setters in a separate table
        lua_pushstring(L, "vars");
        lua_newtable(L);
        nt = lua_gettop(L);
        for ( int i = 0; T::inherits[i].name; ++i, ++ind ) {
            lua_pushstring(L, T::inherits[i].name);
            lua_rawseti(L, nt, ind);
        }
        lua_settable(L, t);

        /* gone at the class level... But repeat anyway for instance*/
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
        lua_setmetatable(L, -2);

        return 1;
    }

    static int lconstructor(lua_State * L) {
        int top = T::lnew(L);
        return (!top) ? constructor(L) : top;
    }

    /**
      Loads an instance of the class into the Lua stack, and provides you a pointer so you can modify it.
      @param L Lua State
      @param instance Instance to push
      */
    static void push(lua_State * L, T* instance ){
        T **a = (T **) lua_newuserdata(L, sizeof(T *)); // Create userdata
        *a = instance;

        luaL_getmetatable(L, T::className);

        lua_setmetatable(L, -2);
    }

    /**
      (Used Internally)
      @param L Lua State
      @return 
      */
    static int property_getter(lua_State * L) {
        luaL_checktype(L, -1, LUA_TSTRING);
        // TODO: checkudata on object at __self
        luaL_checktype(L, -2, LUA_TTABLE);

        lua_getmetatable(L, 1); // Look up the index of a name
        lua_pushvalue(L, 2);  // Push the name
        lua_rawget(L, -2);        // Get the index
        
        if (lua_isnumber(L, -1)) { // Check if we got a valid index
            int _index = lua_tonumber(L, -1);

            lua_pushstring(L, "__pn");
            lua_rawget(L, 3);
            int max_p = lua_tonumber(L, -1);
            lua_pop(L,1);

            lua_pushstring(L, "__mn");
            lua_rawget(L, 3);
            int max_m = lua_tonumber(L, -1);
            lua_pop(L,1);

            lua_getfield(L, 1, "__self");
            T** obj = static_cast<T**>(lua_touserdata(L, -1));

            lua_pushvalue(L, 3);

            if( _index & ( 1 << 8 ) ) // A func
            {
                lua_pushnumber(L, _index ^ ( 1 << 8 ) ); // Push the right func index
                lua_pushlightuserdata(L, obj);
                lua_pushnumber(L, max_m);
                lua_pushcclosure(L, &Luna < T >::function_dispatch, 3);
                return 1; // Return a func
            }
 
            lua_pop(L,2);    // Pop metatable and _index
            lua_remove(L,1); // Remove userdata
            lua_remove(L,1); // Remove [key]

            if ( _index < max_p )
                return ((*obj)->*(T::properties[_index].getter)) (L);
            else {
                //DBG("*** inheritence call");
                _index = _index - max_p;
                return ((*obj)->*(T::inherits[_index].getter)) (L);
            }
        }
        return 1;
    }

    /**
      (Used Internally)
      @param L Lua State
      @return 
      */
    static int property_exists(lua_State * L) {
        luaL_checktype(L, -1, LUA_TSTRING);
        // TODO: checkudata on object at __self
        luaL_checktype(L, -2, LUA_TTABLE);

        lua_getmetatable(L, 1); // Look up the index of a name
        lua_pushvalue(L, 2);  // Push the name
        lua_rawget(L, -2);        // Get the index
        
        if (lua_isnumber(L, -1)) { // Check if we got a valid index
            int _index = lua_tonumber(L, -1);

            lua_pushstring(L, "__pn");
            lua_rawget(L, 3);
            int max_p = lua_tonumber(L, -1);
            lua_pop(L,1);

            //lua_pushstring(L, "__mn");
            //lua_rawget(L, 3);
            //int max_m = lua_tonumber(L, -1);
            //lua_pop(L,1);

            if( _index & ( 1 << 8 ) ) // A func
                lua_pushboolean(L, true);
            else {
                if ( _index < max_p )
                    lua_pushboolean(L, true);
                else {
                    _index = _index - max_p;
                    if ( T::inherits[_index].getter )
                        lua_pushboolean(L, true);
                    else
                        lua_pushboolean(L, false);
                }
            }
        } else {
            lua_pop(L, 2); // metatable and index
            lua_pushboolean(L, false);
        }
        return 1;
    }

    /**
      (Used Internally)
      @param L Lua State
      @return 
      */
    static int property_setter(lua_State * L)
    {
        lua_getmetatable(L, 1); // Look up the index from name
        lua_pushvalue(L, 2);  //
        lua_rawget(L, -2);        //
        if ( lua_isnumber(L, -1) ) // Check if we got a valid index
        {
            int _index = lua_tonumber(L, -1);

            lua_pushstring(L, "__pn");
            lua_rawget(L, -3);
            int max_p = lua_tonumber(L, -1);
            lua_pop(L,1);

            //lua_pushstring(L, "__mn");
            //lua_rawget(L, -3);
            //int max_m = lua_tonumber(L, -1);
            //lua_pop(L,1);

            lua_getfield(L, 1, "__self");
            T** obj = static_cast<T**>(lua_touserdata(L, -1));
            lua_pop(L, 1);

            if( !obj || !*obj )
            {
                luaL_error( L , "Internal error, no object given!" );
                return 0;
            }

            if( _index >> 8 ) // Try to set a func
            {
                char c[128];
                sprintf( c , "Trying to set the method [%s] of class [%s]" , 
                        (*obj)->T::methods[_index ^ ( 1 << 8 ) ].name , T::className );
                luaL_error( L , c );
                return 0;
            }

            lua_pop(L,2);    // Pop metatable and _index
            lua_remove(L,2); // Remove [key], keep udata

            //return ((*obj)->*(T::properties[_index].setter)) (L);
            if ( _index < max_p )
                return ((*obj)->*(T::properties[_index].setter)) (L);
            else {
                _index = _index - max_p;
                return ((*obj)->*(T::inherits[_index].setter)) (L);
            }
        }
        return 0;
    }

    /**
      (Used Internally)
      @param L Lua State
      */
    static int function_dispatch(lua_State * L){
        int i = (int) lua_tonumber(L, lua_upvalueindex(1));
        T** obj = static_cast < T ** >(lua_touserdata(L, lua_upvalueindex(2)));
        int max_m = (int)lua_tonumber(L, lua_upvalueindex(3));

        //return ((*obj)->*(T::methods[i].func)) (L);
        if (i < max_m)
            return ((*obj)->*(T::methods[i].func)) (L);
        else {
            i = i - max_m;
            return ((*obj)->*(T::inheritsF[i].func)) (L);
        }
    }

    /**
      (Used Internally)
      @param L Lua State
      */
    static int gc_obj(lua_State * L) {
        // never used
        /*
        luaL_checktype(L, -1, LUA_TTABLE);
        lua_getfield(L, -1, "__self");

        T** obj = static_cast < T ** >(lua_touserdata(L, -1));

        if( obj && *obj && obj != nullptr )
            *obj = nullptr;

        return 0;
        */
        return 0;
    }

    static int gc_obj_(lua_State * L) {
        // delete only pure base objects, that is anything but Components
        T** obj = static_cast < T ** >(lua_touserdata(L, -1));
        if(obj and *obj) {
            int ptr = (intptr_t)(*obj);
            if( LUA::objects[ptr] && LUA::objects[ptr]->pureBase() ) {
                if( LUA::objects[ptr]->refCount() == 0) {
                    delete *obj;
                    LUA::objects.erase( ptr );
                }
                else
                    LUA::objects[ptr]->decRefCount();
            }
        }
        /*
        DBG(String(">>>>>>>>> collecting: ") + T::className);
        T** obj = static_cast < T ** >(lua_touserdata(L, -1));
        if ( LUA::objects[addr] ) {
            LBase *b = LUA::objects[addr];
            if ( b )
                delete *obj;
        } else {
            if( obj && *obj && obj != nullptr )
                *obj = nullptr;
        }
        LUA::objects.erase(addr);

        if ( LUA::objects.size() == 0 ) {
            if ( MessageManager::getInstanceWithoutCreating() != nullptr )
                MessageManager::deleteInstance();
            std::cout << ((MessageManager::getInstanceWithoutCreating() == nullptr) ? "CLEAN" : "NOT CLEAN") << std::endl;
        } else
            std::cout << "leaving " << LUA::objects.size() << " objects on stack" << std::endl;
        */
        return 0;
    }

    /**
      @param L Lua State
      */
    static int to_string(lua_State* L)
    {
        luaL_checktype( L, -1, LUA_TTABLE);
        lua_getfield(L, -1, "__self");

        T** obj = static_cast<T**>(lua_touserdata(L, -1));

        if( obj && obj != nullptr )
            lua_pushfstring(L, "%s", T::className);
        else
            lua_pushstring(L,"Empty object");

        return 1;
    }

    static int to_string_(lua_State* L)
    {
        T** obj = static_cast<T**>(lua_touserdata(L, -1));

        if( obj )
            lua_pushfstring(L, "%s (%p)", T::className, (void*)*obj);
        else
            lua_pushstring(L,"Empty object");

        return 1;
    }

    static int __eq(lua_State *L) {
        bool res = 0;
        if( lua_istable(L, -1) && lua_istable(L, -2) ) {
            lua_getfield(L, -1, "__self");
            int a = ! lua_isnoneornil(L, -1);
            lua_getfield(L, -3, "__self");
            int b = ! lua_isnoneornil(L, -1);
            if(a && b) {
                T** obj1 = static_cast<T**>(lua_touserdata(L, -1));
                T** obj2 = static_cast<T**>(lua_touserdata(L, -2));
                if( obj1 && obj2 && *obj1 == *obj2 )
                    res = true;
            }
        }
        lua_settop(L, 1);
        lua_pushboolean(L, res);
        return 1;
    }
    static int ___eq(lua_State *L) {
        //DBG("2 eq");
        return __eq(L);
    }


    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Luna<T>)
};
