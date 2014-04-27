/************************************************************

 LDrawablePath.cpp

    @author Christophe Berbizier (cberbizier@peersuasive.com)
    @license GPLv3
    @copyright 


(c) 2014, Peersuasive Technologies

*************************************************************/

#include "LDrawablePath_inh.h"

const char LDrawablePath::className[] = "LDrawablePath";
const Luna<LDrawablePath>::PropertyType LDrawablePath::properties[] = {
    {"path", &LDrawablePath::getPath, &LDrawablePath::setPath},
    {0,0}
};
const Luna<LDrawablePath>::FunctionType LDrawablePath::methods[] = {
    method( LDrawablePath, getPath ),
    method( LDrawablePath, setPath ),
    method( LDrawablePath, createValueTree ),
    method( LDrawablePath, getStrokePath ),
    method( LDrawablePath, createCopy ),
    method( LDrawablePath, refreshFromValueTree ),

    method( LDrawablePath, pathChanged ),
    method( LDrawablePath, strokeChanged ),
    method( LDrawablePath, isStrokeVisible ),
    method( LDrawablePath, refreshFillTypes ),
    method( LDrawablePath, writeTo ),

    {0,0}
};

const Luna<LDrawablePath>::StaticType LDrawablePath::statics[] = {
    {0,0}
};

LDrawablePath::LDrawablePath(lua_State *L)
    : LDrawableShape(L, this),
      DrawablePath()
{
    REGISTER_CLASS(LDrawablePath);
}

LDrawablePath::LDrawablePath(lua_State *L, const DrawablePath& dp)
    : LDrawableShape(L, this),
      DrawablePath(dp)
{
    REGISTER_CLASS(LDrawablePath);
}

LDrawablePath::~LDrawablePath() {}

int LDrawablePath::getPath ( lua_State *L ) {
    return LUA::storeAndReturnUserdata<LPath>( new LPath(L,
        DrawablePath::getPath()
    ));
}
int LDrawablePath::setPath ( lua_State* ) {
    DrawablePath::setPath(*LUA::from_luce<LPath>(2));
    // TODO: RelativePointPath
    return 0;
}

int LDrawablePath::getStrokePath( lua_State *L ) {
    return LUA::storeAndReturnUserdata<LPath>( new LPath(L,
        DrawablePath::getStrokePath()
    ));
}

int LDrawablePath::createCopy( lua_State *L ) {
    return LUA::storeAndReturnUserdata<LDrawablePath>( new LDrawablePath(L,
        *(DrawablePath*)DrawablePath::createCopy()
    ));
}

int LDrawablePath::pathChanged(lua_State*) {
    DrawablePath::pathChanged();
    return 0;
}

int LDrawablePath::strokeChanged(lua_State*) {
    DrawablePath::strokeChanged();
    return 0;
}

int LDrawablePath::isStrokeVisible(lua_State*) {
    return LUA::returnBoolean(DrawablePath::isStrokeVisible());
    return 0;
}

int LDrawablePath::refreshFillTypes(lua_State*) {
    return LUA::TODO_OBJECT( "refreshFillTypes" );
    return 0;
}

int LDrawablePath::writeTo(lua_State*) {
    return LUA::TODO_OBJECT( "writeTo" );
    return 0;
}

// TODO
int LDrawablePath::createValueTree ( lua_State *L ) {
    // ComponentBuilder::ImageProvider* imageProvider = LUA::from_luce<LComponentBuilder::ImageProvider>(2); // TODO;
    // CHECK
    // return LUA::storeAndReturnUserdata<LValueTree>( new LValueTree(L,
    //     DrawablePath::createValueTree( imageProvider )
    // ));
    lua_settop(LUA::Get(), 1); // added by TODO
    return LUA::TODO_OBJECT( "ValueTree createValueTree( imageProvider )" );
}


int LDrawablePath::refreshFromValueTree ( lua_State* ) {
    // ValueTree tree = *LUA::from_luce<LValueTree>(2); // TODO;
    // ComponentBuilder builder = *LUA::from_luce<LComponentBuilder>(2); // TODO;
    // DrawablePath::refreshFromValueTree( tree, builder );
    LUA::TODO_OBJECT( "refreshFromValueTree,  tree, builder " );
    lua_settop(LUA::Get(), 1); // added by TODO
    return 0;
}



