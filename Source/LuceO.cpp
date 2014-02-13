/************************************************************

 Luce.cpp

handle objects to/from lua

    @author Christophe Berbizier (cberbizier@peersuasive.com)
    @license GPLv3
    @copyright 


(c) 2014, Peersuasive Technologies

*************************************************************/

#ifndef __LUCE_O_H
#define __LUCE_O_H

namespace LUCE {
namespace {
    lua_State *L = nullptr;
    void Set(lua_State *L_) {
        if ( !L || L == nullptr ) L = L_;
    }

    void throw_error(const char *msg) {
        //lua_pushstring(L, msg);
        lua_error(L);
    }

    const char* luce_typename(int i) {
        if (!lua_istable(L, i)) return NULL;
        lua_getfield(L, i, "__ltype");
        const char *res = lua_tostring(L,-1);
        lua_pop(L,1);
        return res;
    }
    const char* luce_numtype(int i) {
        if (!lua_istable(L, i)) return NULL;
        lua_getfield(L, i, "__type");
        const char *res = lua_tostring(L,-1);
        lua_pop(L,1);
        return res ? res : "int";
    }
    int luce_pushvalue(int i = -1) {
        i = (i<0) ? lua_gettop(L)-(i+1) : i;
        const char *ltype = luce_typename(i);
        if(! ltype)
            throw_error(lua_pushfstring(L, "Expected LObject, got %s", lua_typename(L,lua_type(L,-1))));
        
        const char *numtype = luce_numtype(i);
        lua_pushvalue(L,i);
        int top = lua_gettop(L);
        lua_getfield(L, -1, "dump");
        lua_pushvalue(L, i); // self
        if ( lua_pcall(L, 1, 1, 0) != 0 ) // push self as the only argument, expects one result
            lua_error(L);
        if(lua_isnoneornil(L,-1))
            throw_error(lua_pushfstring(L, "Dumped result error: expected something, got nil"));
        
        lua_pushstring(L, numtype);
        lua_pushstring(L, ltype);
        lua_pushvalue(L, -3); // result
        lua_remove(L, -4);    // original result
        lua_remove(L, top);   // copy of object -- CHECK: can't remember if getfield replaces the table
        lua_remove(L, i);     // original object
        return lua_objlen(L, -1);
    }

    int luce_pushnumber(int i = -1) {
        if(!lua_isnumber(L,i))
            return 0;
        lua_pushstring(L, "number");
        lua_pushstring(L, "int");
        lua_pushvalue(L, i);
        lua_remove(L, i);
        return 1;
    }
    template<class T>
    const T luce_tonumber(int i) {
        i = (i<0) ? lua_gettop(L)-(i+1) : i;
        int res;
        if(!luce_typename(i))
            res = luce_pushnumber(i);
        else
            res = luce_pushvalue(i);
        if(res) {
            int ind = lua_gettop(L);
            lua_rawgeti(L, ind, 1);
            T n = luaL_checknumber(L, -1);
            lua_pop(L, 3); // ltype + type + num*4
            return n;
        }
        else
            throw_error(lua_pushfstring(L, "Luce Error: expected Number, got %s with size %d", 
                        lua_typename(L,lua_type(L,-1)), lua_objlen(L, -1)));
    
        lua_pop(L,3);
        return 0;
    }
    const int luce_tonumber(int i) {
        return luce_tonumber<int>(i);
    }

    int luce_pushtable(int i = -1) {
        if(!lua_istable(L,i))
            return 0;
        int res = lua_objlen(L, i);
        lua_pushstring(L, "table");
        lua_pushstring(L, "int");
        lua_pushvalue(L, i);
        lua_remove(L, i);
        return res;
    }

    template<class T>
    const juce::Rectangle<T> luce_torectangle(int i) {
        int res;
        if(!luce_typename(i))
            res = luce_pushtable(i);
        else
            res = luce_pushvalue(i);

        if(res) {
            int ind = lua_gettop(L);
            lua_rawgeti(L, ind, 1);
            T x = luaL_checknumber(L, -1);
            lua_rawgeti(L, ind, 2);
            T y = luaL_checknumber(L, -1);
            lua_rawgeti(L, ind, 3);
            T w = luaL_checknumber(L, -1);
            lua_rawgeti(L, ind, 4);
            T h = luaL_checknumber(L, -1);
            lua_pop(L, 6); // ltype + type + num*4
            return { x, y, w, h };
        } else
            throw_error(lua_pushfstring(L, "Luce Error: expected Rectangle, got %s with size %d", 
                        lua_typename(L,lua_type(L,-1)), lua_objlen(L, -1)));
        lua_pop(L,3); // type, ltype, nil
        return {};
    }
    const juce::Rectangle<int> luce_torectangle(int i) {
        return luce_torectangle<int>(i);
    }

    template<class T>
    const juce::RectangleList<T> luce_torectanglelist(int i) {
        juce::RectangleList<T> rl;
        int res = luce_pushvalue(i);
        if ( res ) {
            lua_pushnil(L);
            while(lua_next(L, -2)) {
                //rl.addWithoutMerging( luce_torectangle<T>(-1) );
                rl.add( luce_torectangle<T>(-1) );
                lua_pop(L,1);
            }
            lua_pop(L, 1);
        }
        lua_pop(L, 1); // 3 ???
        return rl;
    }
    const juce::RectangleList<int> luce_torectanglelist(int i) {
        return luce_torectanglelist<int>(i);
    }

    const juce::AffineTransform luce_toaffinetransform(int i) {
        int res = luce_pushvalue(i);
        if ( res ) {
            int top = lua_gettop(L);
            float matrices[6];
            for(int i=0;i<6;++i) {
                lua_rawgeti(L, top, i+1);
                matrices[i] = (float)lua_tonumber(L, -1);
            }
            lua_pop(L, 6);
            lua_pop(L, 3);
            return { matrices[0], matrices[1], matrices[2], matrices[3], matrices[4], matrices[5] };
        }
        lua_pop(L, 3);
        return {};
    }
    
    template<class T>
    const juce::Point<T> luce_topoint(int i) {
        int res;
        if(!luce_typename(i))
            res = luce_pushtable(i);
        else
            res = luce_pushvalue(i);

        if(res) {
            int ind = lua_gettop(L);
            lua_rawgeti(L, ind, 1);
            T x = luaL_checknumber(L, -1);
            lua_rawgeti(L, ind, 2);
            T y = luaL_checknumber(L, -1);
            lua_pop(L, 4); // ltype + type + num*2
            return { x, y };
        } else
            throw_error(lua_pushfstring(L, "Luce Error: expected Point, got %s with size %d", 
                        lua_typename(L,lua_type(L,-1)), lua_objlen(L, -1)));
        lua_pop(L,3); // type, ltype, nil
        return {};
    }
    const juce::Point<int> luce_topoint(int i) {
        return luce_topoint<int>(i);
    }

    const juce::StringArray luce_tostringarray(int i) {
        int res;
        if(!luce_typename(i))
            res = luce_pushtable(i);
        else
            res = luce_pushvalue(i);
        if(res) {
            String array[res];
            int ind = lua_gettop(L);
            for ( int i = 1; i<= res; ++i ) {
                lua_rawgeti(L, ind, i);
                array[i-1] = luaL_checkstring(L, -1);
                lua_pop(L,1);
            }
            lua_pop(L, 3); // ltype, type, table
            return { array, res };
        }
        lua_pop(L, 3); // type, ltype, nil
        return {};
    }

    bool isofnumtype(const char *t, int i) {
        return luce_numtype(i) == t;
    }
    bool isoftype(const char *t, int i) {
        return luce_typename(i) == t;
    }

    bool isnumtype(const char* t1, const char *t2) {
        return strcmp(t1,t2) == 0;
    }
    #define luce_isoftype(t,i) isoftype(#t, i)
    #define luce_isofnumtype(t,i) isofnumtype(#t, i)

    #define luce_isnumtype(t1, t2) isnumtype(#t1, t2)
}
}
#endif // __LUCE_O_H
