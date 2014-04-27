/************************************************************

 LDrawableRectangle.cpp

    @author Christophe Berbizier (cberbizier@peersuasive.com)
    @license GPLv3
    @copyright 


(c) 2014, Peersuasive Technologies

*************************************************************/

#include "LDrawableRectangle_inh.h"

const char LDrawableRectangle::className[] = "LDrawableRectangle";
const Luna<LDrawableRectangle>::PropertyType LDrawableRectangle::properties[] = {
    {"path", &LDrawableRectangle::getPath, &LDrawableRectangle::setPath},
    {0,0}
};
const Luna<LDrawableRectangle>::FunctionType LDrawableRectangle::methods[] = {
    method( LDrawableRectangle, getRectangle ),
    method( LDrawableRectangle, setRectangle ),
    method( LDrawableRectangle, getCornerSize ),
    method( LDrawableRectangle, setCornerSize ),

    method( LDrawableRectangle, createValueTree ),
    method( LDrawableRectangle, getStrokePath ),
    method( LDrawableRectangle, setStrokePath ),
    method( LDrawableRectangle, createCopy ),
    method( LDrawableRectangle, refreshFromValueTree ),

    method( LDrawableRectangle, pathChanged ),
    method( LDrawableRectangle, strokeChanged ),
    method( LDrawableRectangle, isStrokeVisible ),
    method( LDrawableRectangle, refreshFillTypes ),
    method( LDrawableRectangle, writeTo ),

    {0,0}
};

const Luna<LDrawableRectangle>::StaticType LDrawableRectangle::statics[] = {
    {0,0}
};

LDrawableRectangle::LDrawableRectangle(lua_State *L)
    : LDrawableShape(L, this),
      DrawableRectangle()
{
    REGISTER_CLASS(LDrawableRectangle);
}

LDrawableRectangle::LDrawableRectangle(lua_State *L, const DrawableRectangle& dp)
    : LDrawableShape(L, this),
      DrawableRectangle(dp)
{
    REGISTER_CLASS(LDrawableRectangle);
}

LDrawableRectangle::~LDrawableRectangle() {}

int LDrawableRectangle::getRectangle(lua_State* L) {
    lua_settop(L, 1); // added by TODO
    return LUA::TODO_OBJECT( "getRectangle" );
}
int LDrawableRectangle::setRectangle(lua_State* L) {
    lua_settop(L, 1); // added by TODO
    return LUA::TODO_OBJECT( "setRectangle" );
}

int LDrawableRectangle::getCornerSize(lua_State* L) {
    lua_settop(L, 1); // added by TODO
    return LUA::TODO_OBJECT( "getCornerSize" );
}
int LDrawableRectangle::setCornerSize(lua_State* L) {
    lua_settop(L, 1); // added by TODO
    return LUA::TODO_OBJECT( "setCornerSize" );
}


int LDrawableRectangle::getPath(lua_State* L) {
    return LUA::storeAndReturnUserdata<LPath>( new LPath(L,
        this->path
    ));
}
int LDrawableRectangle::setPath(lua_State* L) {
    this->path = Path(*LUA::from_luce<LPath,Path>(2));
    DrawableRectangle::pathChanged();
    return 0;
}

int LDrawableRectangle::getStrokePath( lua_State *L ) {
    return LUA::storeAndReturnUserdata<LPath>( new LPath(L,
        this->strokePath
    ));
}
int LDrawableRectangle::setStrokePath( lua_State *L ) {
    this->strokePath = Path(*LUA::from_luce<LPath,Path>(2));
    DrawableRectangle::strokeChanged();
    return 0;
}

int LDrawableRectangle::createCopy( lua_State *L ) {
    return LUA::storeAndReturnUserdata<LDrawableRectangle>( new LDrawableRectangle(L,
        *(DrawableRectangle*)DrawableRectangle::createCopy()
    ));
}

int LDrawableRectangle::pathChanged(lua_State*) {
    DrawableRectangle::pathChanged();
    return 0;
}

int LDrawableRectangle::strokeChanged(lua_State*) {
    DrawableRectangle::strokeChanged();
    return 0;
}

int LDrawableRectangle::isStrokeVisible(lua_State*) {
    return LUA::returnBoolean(DrawableRectangle::isStrokeVisible());
    return 0;
}

int LDrawableRectangle::refreshFillTypes(lua_State*) {
    return LUA::TODO_OBJECT( "refreshFillTypes" );
    return 0;
}

int LDrawableRectangle::writeTo(lua_State*) {
    return LUA::TODO_OBJECT( "writeTo" );
    return 0;
}

// TODO
int LDrawableRectangle::refreshFromValueTree ( lua_State* ) {
    // ValueTree tree = *LUA::from_luce<LValueTree>(2); // TODO;
    // ComponentBuilder builder = *LUA::from_luce<LComponentBuilder>(2); // TODO;
    // DrawableRectangle::refreshFromValueTree( tree, builder );
    LUA::TODO_OBJECT( "refreshFromValueTree,  tree, builder " );
    lua_settop(LUA::Get(), 1); // added by TODO
    return 0;
}

int LDrawableRectangle::createValueTree ( lua_State *L ) {
    // ComponentBuilder::ImageProvider* imageProvider = LUA::from_luce<LComponentBuilder::ImageProvider>(2); // TODO;
    // CHECK
    // return LUA::storeAndReturnUserdata<LValueTree>( new LValueTree(L,
    //     DrawableRectangle::createValueTree( imageProvider )
    // ));
    lua_settop(LUA::Get(), 1); // added by TODO
    return LUA::TODO_OBJECT( "ValueTree createValueTree( imageProvider )" );
}


