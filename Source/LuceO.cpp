/************************************************************

 Luce.cpp

handle objects to/from lua

    @author Christophe Berbizier (cberbizier@peersuasive.com)
    @license GPLv3
    @copyright 


(c) 2014-2016, Peersuasive Technologies

*************************************************************/

#ifndef __LUCE_O_H
#define __LUCE_O_H

namespace LUCE {
namespace {
    //
    // internal
    //

    lua_State *L = nullptr;
    void Set(lua_State *L_) {
        if ( !L || L == nullptr ) L = L_;
    }

    std::string what;
    void luce_error(const char *msg) {
        if(LUA::liveCoding())
            std::cout << "ERROR: " << msg << std::endl;
        else {
            if(!lua_isstring(L,-1))
                lua_pushstring(L, msg);
            else if(msg) {
                const char* err = lua_tostring(L,-1);
                lua_pushfstring(L, "%s: %s\n", msg, err);
            }
            if(!what.empty())
                lua_pushfstring(L, "%s: %s", what.c_str(), lua_tostring(L,-1));
        
            what = "";
            int top = lua_gettop(L);

            lua_pushglobaltable(L);
            lua_getfield(L, -1, "debug");
            if(lua_istable(L,-1)) {
                lua_getfield(L,-1,"traceback");
                if(lua_isfunction(L,-1)) {
                    lua_pushvalue(L,top);
                    lua_pushinteger(L, 2);
                    lua_call(L, 2, 1);
                    lua_error(L);
                }
                else
                    lua_pop(L,2);
            }
            else
                lua_pop(L,1);

            lua_error(L);
        }
    }

    //
    // some lua/luce classes to C++ facilities
    //
    const char* luce_typename(int i) {
        i = (i<0) ? lua_gettop(L)-(i+1) : i;
        if (!lua_istable(L, i)) return NULL;
        lua_pushstring(L, "__ltype");
        lua_rawget(L, i);
        const char *res_c = lua_tostring(L, -1);
        lua_pop(L,1);
        if(!res_c)
            return NULL;
        std::string res(res_c);
        if(res.compare(0, 5, "light")==0)
            return res.substr(5).c_str();
        else
            return res.c_str();
    }
    const char* luce_numtype(int i) {
        i = (i<0) ? lua_gettop(L)-(i+1) : i;
        if (!lua_istable(L, i)) return NULL;
        lua_getfield(L, i, "__type");
        const char *res = lua_tostring(L,-1);
        lua_pop(L,1);
        return res ? res : "int";
    }

    //
    // macros and facilities
    //
    bool isofnumtype(const char *t, int i) {
        const char *res = luce_numtype(i);
        return res && strcmp(res, t) == 0;
    }
    bool isoftype(const char *t, int i) {
        const char *res = luce_typename(i);
        return res && strcmp(res, t) == 0;
    }

    bool isnumtype(const char* t1, const char *t2) {
        return strcmp(t1,t2) == 0;
    }
    //#define luce_isoftype(t,i) isoftype(#t, i)
    //#define luce_isofnumtype(t,i) isofnumtype(#t, i)

    //#define luce_isnumtype(t1, t2) isnumtype(#t1, t2)

    template<class T>
    bool isofclass(const char* t, int i) {
        i = (i<0) ? lua_gettop(L)-(i+1) : i;
        if(!lua_istable(L,i))
            return false;

        lua_getfield(L, i, "__self"); // may be nil
        if(!lua_isnoneornil(L, -1)) {
            const char* tname = std::string( std::string(t) +"_" ).c_str();
            void *p = lua_touserdata(L, -1);
            if (p != NULL) {
                if (lua_getmetatable(L, -1)) {
                    luaL_getmetatable(L, tname);
                    if (!lua_rawequal(L, -1, -2))
                        p = NULL;
                    lua_pop(L, 3); // field + mt*2
                    return p ? true : false;
                }
            }
        }

        lua_pop(L,1); // nil or userdata
        return false;
    }
    //#define ct_1(T)   isofclass<T>( #T )
    //#define ct_2(T,i) isofclass<T>( #T, i )
    //#define ct_sel(x,T,i,FUNC, ...) FUNC
    //#define luce_isofclass(...) ct_sel(,##__VA_ARGS__, ct_2(__VA_ARGS__), ct_1(__VA_ARGS__),)


    int luceI_pushvalue(int i = -1, const char* ltype_ = NULL) {
        i = (i<0) ? lua_gettop(L)-(i+1) : i;
        const char *ltype = ltype_ ? ltype_ : luce_typename(i);
        if(! ltype)
            luce_error(lua_pushfstring(L, "Expected LObject, got %s", lua_typename(L,lua_type(L,-1))));
        
        const char *numtype = luce_numtype(i);
        lua_pushvalue(L,i);
        int top = lua_gettop(L);
        lua_getfield(L, -1, "dump");
        lua_pushvalue(L, i); // self
        if ( lua_pcall(L, 1, 1, 0) != 0 ) // push self as the only argument, expects one result
            lua_error(L);
        if(lua_isnoneornil(L,-1))
            luce_error(lua_pushfstring(L, "Dumped result error: expected something, got nil"));
        
        lua_pushstring(L, numtype);
        lua_pushstring(L, ltype);
        lua_pushvalue(L, -3); // result
        lua_remove(L, -4);    // original result
        lua_remove(L, top);   // copy of object -- CHECK: can't remember if getfield replaces the table
        lua_remove(L, i);     // original object
        return lua_objlen(L, -1);
    }

    int luceI_pushnumber(int i = -1) {
        i = (i<0) ? lua_gettop(L)-(i+1) : i;
        if(!lua_isnumber(L,i))
            return 0;
        lua_pushstring(L, "number");
        lua_pushstring(L, "int");
        lua_newtable(L);
        lua_pushvalue(L, i);
        lua_rawseti(L, -2, 1);
        lua_remove(L, i);
        return 1;
    }

    template<class T>
    const T luce_tonumber(int i) {
        i = (i<0) ? lua_gettop(L)-(i+1) : i;
        int res;
        const char *tn = luce_typename(i);
        if(!tn)
            res = luceI_pushnumber(i);
        else
            res = luceI_pushvalue(i, tn);
        if(res) {
            int ind = lua_gettop(L);
            lua_rawgeti(L, ind, 1);
            T n = luaL_checknumber(L, -1);
            lua_pop(L, 3); // ltype + type + num*4
            return n;
        }
        else
            luce_error(lua_pushfstring(L, "Luce Error: expected Number, got %s with size %d", 
                        lua_typename(L,lua_type(L,-1)), lua_objlen(L, -1)));
    
        lua_pop(L,3);
        return 0;
    }
    const int luce_tonumber(int i) {
        return luce_tonumber<int>(i);
    }

    //
    // internaly used methods
    //

    int luceI_pushtable(int i = -1) {
        i = (i<0) ? lua_gettop(L)-(i+1) : i;
        if(!lua_istable(L,i)) {
            //luce_error(lua_pushfstring(L, "Luce Error: expected LObject or table, got %s", 
            //            lua_typename(L,lua_type(L,-1))));
            return 0;
        }
        int res = lua_objlen(L, i);
        lua_pushstring(L, "table");
        lua_pushstring(L, "int");
        lua_pushvalue(L, i);
        lua_remove(L, i);
        return res;
    }

    // array of numbers
    template<class T>
    const ArrayType<T> luceI_tonumberarray(int i = -1) {
        luaL_checktype(L, i, LUA_TTABLE);
        i = (i<0) ? lua_gettop(L)-(i+1) : i;
        ArrayType<T> v;
        for(int j=1;j<=lua_objlen(L,i);++j) {
            lua_rawgeti(L, i, j);
            v.push_back((T)luaL_checknumber(L, -1));
            lua_pop(L,1);
        }
        return v;
    }
    template<class T>
    const ArrayType<T> luce_tonumberarray(int i) {
        ArrayType<T> v;
        int res;
        const char* tn = luce_typename(i);
        if(!tn) {
            res = luceI_pushtable(i);
        }
        else
            res = luceI_pushvalue(i, tn);

        if(res)
            v = luceI_tonumberarray<T>();
        else
            luce_error("type not matching");

        lua_pop(L,3); // type, ltype, nil or table
        return v;
    }

    // size 2 class
    template<class C, class T>
    const C luceI_to2SClass(int i = -1) {
        ArrayType<T> a = luce_tonumberarray<T>(i);
        return { a[0], a[1] };
    }
    
    // size 4 class
    template<class C, class T>
    const C luceI_to4SClass(int i = -1) {
        ArrayType<T> a = luce_tonumberarray<T>(i);
        return { a[0], a[1], a[2], a[3] };
    }

    // size 6 class
    template<class C, class T>
    const C luceI_to6SClass(int i = -1) {
        ArrayType<T> a = luce_tonumberarray<T>(i);
        return { a[0], a[1], a[2], a[3], a[4], a[5] };
    }

    // size 9 class
    template<class C, class T>
    const C luceI_to9SClass(int i = -1) {
        ArrayType<T> a = luce_tonumberarray<T>(i);
        return { a[0], a[1], a[2], a[3], a[4], a[5], a[6], a[7], a[8] };
    }


    //
    // from C++ to lua
    //

    //
    // TODO: implement push of full lua classes
    //       meaning having access to the lua scope 
    //       to call the call the class constructor...
    //
    int dump_lightclass(lua_State* L) {
        int n = lua_tointeger(L, lua_upvalueindex(1));
        lua_newtable(L);
        for(int i=1;i<=n;++i) {
            lua_pushnumber(L,i);
            lua_pushnumber(L,i);
            lua_gettable(L,1);
            lua_settable(L,2);
        }
        return 1;
    }
    template<class T>
    int luceI_pushlightclass(std::vector<T> a, const char *name, lua_CFunction dump = &dump_lightclass) {
        lua_newtable(L);
        int i = lua_gettop(L);
        for(int j=0;j<a.size();++j) {
            lua_pushnumber(L, a[j]);
            lua_rawseti(L, i, j+1);
        }
        lua_pushstring(L, name);
        lua_setfield(L, i, "__ltype");
        if(dump) {
            lua_pushnumber(L, a.size());
            lua_pushcclosure(L, dump, 1);
            lua_setfield(L, i, "dump");
        }
        return 1;
    }

    //
    // public facilities from/to luce/juce classes
    //
    
    // Point
    template<class T>
    const juce::Point<T> luce_topoint(int i) {
        what = "Point";
        return luceI_to2SClass<Point<T>, T>(i);
    }
    template<class T>
    int luce_pushlightpoint(const juce::Point<T>& p) {
        return luceI_pushlightclass<T>({p.getX(), p.getY()}, "lightLPoint");
    }
    template<class T>
    int luce_pushtable(const juce::Point<T>& p) {
        return luce_pushlightpoint<T>(p);
    }

    // Range
    template<class T>
    const juce::Range<T> luce_torange(int i) {
        what = "Range";
        return luceI_to2SClass<Range<T>, T>(i);
    }
    template<class T>
    int luce_pushlightrange(const juce::Range<T>& r) {
        return luceI_pushlightclass<T>({r.getStart(), r.getEnd()}, "lightLRange");
    }
    template<class T>
    int luce_pushtable(const juce::Range<T>& r) {
        return luce_pushlightrange<T>(r);
    }

    // Rectangle
    template<class T>
    const juce::Rectangle<T> luce_torectangle(int i) {
        what = "Rectangle";
        return luceI_to4SClass<Rectangle<T>, T>(i);
    }
    const juce::Rectangle<int> luce_torectangle(int i) {
        return luce_torectangle<int>(i);
    }
    template<class T>
    int luce_pushlightrectangle(const juce::Rectangle<T>& r) {
        return luceI_pushlightclass<T>({r.getX(), r.getY(), r.getWidth(), r.getHeight()}, 
                "lightLRectangle");
    }
    template<class T>
    int luce_pushtable(const juce::Rectangle<T>& r) {
        return luce_pushlightrectangle<T>(r);
    }

    // Line
    template<class T>
    const juce::Line<T> luce_toline(int i) {
        what = "Line";
        return luceI_to4SClass<Line<T>, T>(i);
    }
    const juce::Line<int> luce_toline(int i) {
        return luce_toline<int>(i);
    }
    template<class T>
    int luce_pushlightline(const juce::Line<T>& r) {
        return luceI_pushlightclass<T>({r.getStartX(), r.getStartY(), 
                    r.getEndX(), r.getEndY()}, "lightLLine");
    }
    template<class T>
    int luce_pushtable(const juce::Line<T>& r) {
        return luce_pushlightline<T>(r);
    }
 
    // AffineTransform
    const juce::AffineTransform luce_toaffinetransform(int i) {
        what = "AffineTransform";
        return luceI_to6SClass<juce::AffineTransform, float>(i);
    }
    int luce_pushlightaffinetransform(const juce::AffineTransform& aff) {
        return luceI_pushlightclass<float>({ aff.mat00, aff.mat01, aff.mat02,
                                    aff.mat10, aff.mat11, aff.mat12, }, "lightLAffineTransform");
    }
    int luce_pushtable(const juce::AffineTransform& aff) {
        return luce_pushlightaffinetransform(aff);
    }

    // RectanglePlacement
    const juce::RectanglePlacement luce_torectangleplacement(int i = -1) {
        what = "RectanglePlacement";
        int val = luce_tonumber<int>(i);
        return { val };
    }
    int luce_pushlightrectangleplacement(const juce::RectanglePlacement& r) {
        lua_newtable(L);
        int i = lua_gettop(L);
        lua_pushnumber(L, r.getFlags());
        lua_setfield(L, i, "flags");
        lua_pushstring(L, "lightLRectanglePlacement");
        lua_setfield(L, i, "__ltype");
        return 1;
    }
    int luce_pushtable(const juce::RectanglePlacement& r) {
        return luce_pushlightrectangleplacement(r);
    }

    // BorderSize
    template<class T>
    const juce::BorderSize<T> luce_tobordersize(int i) {
        what = "BorderSize";
        return luceI_to4SClass<BorderSize<T>, T>(i);
    }
    const juce::BorderSize<int> luce_tobordersize(int i) {
        return luce_tobordersize<int>(i);
    }
    template<class T>
    int luce_pushlightbordersize(const juce::BorderSize<T>& r) {
        return luceI_pushlightclass<T>({r.getTop(), r.getLeft(), r.getBottom(), r.getRight()}, 
                "lightLBorderSize");
    }
    template<class T>
    int luce_pushtable(const juce::BorderSize<T>& r) {
        return luce_pushlightbordersize<T>(r);
    }

    // ComponentBoundsConstrainer
    /*
    minW (0)
    maxW (0x3fffffff)
    minH (0)
    maxH (0x3fffffff)
    minOffTop (0)
    minOffLeft (0)
    minOffBottom (0)
    minOffRight (0)
    aspectRatio (0.0)
    */
    juce::ComponentBoundsConstrainer *luce_tocomponentboundsconstrainer(int i) {
        luaL_checktype(L, i, LUA_TTABLE);
        i = (i<0) ? lua_gettop(L)-(i+1) : i;
        lua_rawgeti(L, i, 1);
        int minW = luaL_checknumber(L, -1);
        lua_rawgeti(L, i, 2);
        int maxW = luaL_checknumber(L, -1);
        lua_rawgeti(L, i, 3);
        int minH = luaL_checknumber(L, -1);
        lua_rawgeti(L, i, 4);
        int maxH = luaL_checknumber(L, -1);
        lua_rawgeti(L, i, 5);
        int minOffTop = luaL_checknumber(L, -1);
        lua_rawgeti(L, i, 6);
        int minOffLeft = luaL_checknumber(L, -1);
        lua_rawgeti(L, i, 7);
        int minOffBottom = luaL_checknumber(L, -1);
        lua_rawgeti(L, i, 8);
        int minOffRight = luaL_checknumber(L, -1);
        lua_rawgeti(L, i, 9);
        double aspectRatio = luaL_checknumber(L, -1);
        lua_pop(L, 9);
        lua_remove(L,i);
        ComponentBoundsConstrainer *c = new ComponentBoundsConstrainer();
        c->setMinimumWidth( minW );
        c->setMaximumWidth( maxW );
        c->setMinimumHeight( minH );
        c->setMaximumHeight( maxH );
        c->setMinimumOnscreenAmounts( minOffTop, minOffLeft, minOffBottom, minOffRight );
        c->setFixedAspectRatio( aspectRatio );
        return c;
    }
    int luce_pushlightcomponentboundscontainer(const juce::ComponentBoundsConstrainer& c) {
        return luceI_pushlightclass<var>({
                    c.getMinimumWidth(),
                    c.getMaximumWidth(),
                    c.getMaximumHeight(),
                    c.getMaximumHeight(),
                    c.getMinimumWhenOffTheTop(),
                    c.getMinimumWhenOffTheLeft(),
                    c.getMinimumWhenOffTheBottom(),
                    c.getMinimumWhenOffTheRight(),
                    c.getFixedAspectRatio()
                }, 
                "lightLComponentBoundsConstrainer");
    }
    int luce_pushtable(const juce::ComponentBoundsConstrainer& c) {
        return luce_pushlightcomponentboundscontainer(c);
    }

    // Colour
    const juce::Colour luce_tocolour(int i) {
        what = "Colour";
        i = (i<0) ? lua_gettop(L)-(i+1) : i;
        if(isofclass<LColour>("LColour", i))
            return {*LUA::from_luce<LColour>(i)};
        
        int ltype = lua_type(L,i);
        switch(ltype) {
            case LUA_TTABLE: {
                lua_pushnumber(L,1);
                lua_rawget(L,i);
                uint8 red = LUA::getNumber<uint8>();
                lua_pushnumber(L,2);
                lua_rawget(L,i);
                uint8 green = LUA::getNumber<uint8>();
                lua_pushnumber(L,3);
                lua_rawget(L,i);
                uint8 blue = LUA::getNumber<uint8>();
                lua_pushnumber(L,4);
                lua_rawget(L,i);
                uint8 alpha = LUA::checkAndGetNumber<uint8>(-1, 255);
                lua_remove(L,i);
               
                return {red, green, blue, alpha};
            }
                break;
            case LUA_TNUMBER: {
                uint8 red = LUA::getNumber<uint8>(i);
                uint8 green = LUA::getNumber<uint8>(i);
                uint8 blue = LUA::getNumber<uint8>(i);
                uint8 alpha = LUA::checkAndGetNumber<uint8>(i, 255);
                return {red, green, blue, alpha};
            }
                break;
            case LUA_TSTRING: {
                std::string type = lua_tostring(L,i);
                lua_remove(L,i);
                if (type == "HSBA") {
                    int l_i = i+1;
                    uint8 hue = LUA::getNumber<float>(i);
                    uint8 sat = LUA::getNumber<float>(i);
                    uint8 bri = LUA::getNumber<float>(i);
                    uint8 alpha = LUA::getNumber<uint8>(i);
                    return {hue, sat, bri, alpha};
                }
                else
                    return { Colours::findColourForName(type, Colours::transparentWhite) };
            }
                break;
            default:
                luce_error(lua_pushfstring(L, 
                    "LColour: invalid class.\nExpected:\n %s,\n %s,\n %s,\n %s,\n %s\ngot: %s\n",
                    "()",
                    "(LColour)",
                    "({r,g,b,[a]})",
                    "(HSBA, 'HSBA')",
                    "('colour_name')",
                    lua_typename(L, lua_type(L,i))
                ));
            }
        return {};
    }

    //
    // generic lists
    //
    
    enum LVarType {
        LNUMBER     = 1,
        LBOOL       = 2,
        LSTRING     = 3,
        LTABLE      = 4,
        LFUNCTION   = 5,
        LOBJECT     = 6,
        LDATA       = 7,
        LNIL        = 8
    };
    const LVarType varType(const var& v) {
        if(v.isInt() || v.isInt64() || v.isDouble())
            return LNUMBER;
        else if(v.isBool())
            return LBOOL;
        else if(v.isString())
            return LSTRING;
        else if(v.isArray())
            return LTABLE;
        else if(v.isMethod())
            return LFUNCTION;
        else if(v.isObject())
            return LOBJECT;
        else if(v.isBinaryData())
            return LDATA;
        else if(v.isVoid() || v.isUndefined())
            return LNIL;
        else
            return LNIL;
    }
    int luce_pushtable(const std::list<var> l) {
        lua_newtable(L);
        int i = lua_gettop(L);
        int j = 0;
        for ( auto &it : l ) {
            switch(varType(it)) {
                case LNUMBER:
                    lua_pushnumber(L, it);
                    break;
                case LBOOL:
                    lua_pushboolean(L, (bool)it);
                    break;
                case LSTRING:
                    lua_pushlstring(L, it.toString().toRawUTF8(), it.toString().length() );
                    break;
                case LTABLE:
                case LFUNCTION:
                case LOBJECT:
                case LDATA:
                case LNIL:
                default:
                    lua_pushnil(L);
                    std::cout << "LUCE WARNING: type not yet implemented" << std::endl;
                    break;
            }
            lua_rawseti(L, i, ++j);
        }
        return 1;
    }

    template<class T>
    int luce_pushtable(const Array<T>& val) {
        std::list<var> r;
        for (int i=0;i<val.size();++i)
            r.push_back( val[i] );
        return luce_pushtable(r);
    }
    int luce_pushtable(const Array<var>& val) {
        return luce_pushtable<int>(val);
    }

    template<class T>
    int luce_pushtable( const juce::SparseSet<T>& r ) {
        std::list<var> l;
        for (int i=0; i<r.size(); ++i)
            l.push_back(r[i]);
        return luce_pushtable(l);
    }

    // fully specified call
    template<class T, class U>
    int luce_pushtable( const U& u ) {
        return luce_pushtable<T>(u);
    }


    //
    // specific lists
    //

    const juce::StringArray luce_tostringarray(int i) {
        StringArray array;
        int res;
        const char* tn = luce_typename(i);
        if(!tn)
            res = luceI_pushtable(i);
        else
            res = luceI_pushvalue(i, tn);
        if(res) {
            int ind = lua_gettop(L);
            for ( int i = 1; i<= res; ++i ) {
                lua_rawgeti(L, ind, i);
                array.add( luaL_checkstring(L, -1) );
                lua_pop(L,1);
            }
        }
        else
            luce_error( lua_pushfstring(L, "Luce Error: expected StringArray, got %s", lua_typename(L,lua_type(L,-1))) );

        lua_pop(L, 3); // type, ltype, nil or table
        return array;
    }
    int luce_pushtable(const StringArray& sa) {
        std::list<var> r;
        for(int i=0;i<sa.size();++i)
            r.push_back(sa[i]);
        return luce_pushtable(r);
    }

    const juce::StringPairArray luce_tostringpairarray(int i) {
        if(!lua_istable(L,i))
            luce_error(lua_pushfstring(L, "Luce Error: expected StringPairArray, got %s", lua_typename(L,lua_type(L,-1))) );
        StringPairArray array;
        int top = i;
        lua_pushnil(L);
        while(lua_next(L, top)) {
            array.set(lua_tostring(L,-2), lua_tostring(L,-1));
            lua_pop(L,1);
        }
        lua_remove(L,i);
        return array;
    }
    int luce_pushtable(const StringPairArray& spa) {
        int size = spa.size();
        lua_createtable(L, 0, size);
        StringArray keys = spa.getAllKeys();
        for(int i=0;i<keys.size();++i) {
            String k = keys[i];
            lua_pushstring(L, k.toRawUTF8());
            lua_pushstring(L, spa.getValue(StringRef(k), String::empty).toRawUTF8() );
            lua_settable(L,-3);
        }
        return 1;
    }

    template<class T>
    const juce::RectangleList<T> luce_torectanglelist(int i) {
        juce::RectangleList<T> rl;
        int res;
        const char* tn = luce_typename(i);
        if(!tn)
            res = luceI_pushtable(i);
        else
            res = luceI_pushvalue(i, tn);

        if ( res ) {
            lua_pushnil(L);
            while(lua_next(L, -2)) {
                lua_pushvalue(L,-1); // luce_torectangle will eat it
                rl.addWithoutMerging( luce_torectangle<T>() );
                lua_pop(L,1);
            }
        } else
            luce_error( lua_pushfstring(L, "Luce Error: expected RectangleList, got %s", lua_typename(L,lua_type(L,-1))) );

        lua_pop(L, 3); // type, ltype, nil or table
        return rl;
    }
    const juce::RectangleList<int> luce_torectanglelist(int i) {
        return luce_torectanglelist<int>(i);
    }

    // TODO: move to std::list<var> once Objects are implemented
    template<class T, class U>
    int luce_pushtable( const OwnedArray<U>& a) {
        lua_newtable(L);
        int t = lua_gettop(L);
        for(int i=0; i<a.size(); ++i) {
            LUA::returnUserdata<T, U>( a[i] );
            lua_rawseti(L, t, i+1);
        }
        return 1;
    }


    //
    // specific implementations
    //

    const juce::TextLayout::Glyph luce_toglyph(int i) {
        int res;
        const char* tn = luce_typename(i);
        if(!tn)
            res = luceI_pushtable(i);
        else
            res = luceI_pushvalue(i, tn);

        if(res) {
            int ind = lua_gettop(L);
            lua_getfield(L, ind, "glyphCode");
            int glyphCode = lua_tonumber(L, -1);
            lua_getfield(L, ind, "width");
            float width = (float)lua_tonumber(L, -1);
            lua_getfield(L, ind, "anchor");
            Point<float> anchor = luce_topoint<float>(-1);

            lua_pop(L, 3); // ltype + type + value
            return { glyphCode, anchor, width };
        } else
            luce_error(lua_pushfstring(L, "Luce Error: expected Glyph, got %s with size %d", 
                        lua_typename(L,lua_type(L,-1)), lua_objlen(L, -1)));
        lua_pop(L,3); // type, ltype, nil
        return { 0, Point<float>(), 0 };
    }
    int luce_pushlightglyph(const TextLayout::Glyph& glyph) {
        lua_newtable(L);
        int i = lua_gettop(L);

        lua_pushnumber(L, glyph.glyphCode);
        lua_setfield(L, i, "glyphCode");
        
        lua_pushnumber(L, glyph.width);
        lua_setfield(L, i, "width");

        luce_pushlightpoint<float>( glyph.anchor );
        lua_setfield(L, i, "anchor");
        
        lua_pushliteral(L, "lightLGlyph");
        lua_setfield(L, i, "__ltype");
        return 1;
    }

}
}
#endif // __LUCE_O_H
