/************************************************************

 LDrawableComposite.cpp

    @author Christophe Berbizier (cberbizier@peersuasive.com)
    @license GPLv3
    @copyright 


(c) 2014, Peersuasive Technologies

*************************************************************/

#include "LDrawableComposite_inh.h"

const char LDrawableComposite::className[] = "LDrawableComposite";
const Luna<LDrawableComposite>::PropertyType LDrawableComposite::properties[] = {
    {"boundingBox", &LDrawableComposite::getBoundingBox, &LDrawableComposite::setBoundingBox},
    {"contentArea", &LDrawableComposite::getContentArea, &LDrawableComposite::setContentArea},
    {0,0}
};
const Luna<LDrawableComposite>::FunctionType LDrawableComposite::methods[] = {
    method( LDrawableComposite, createCopy ),
    method( LDrawableComposite, getBoundingBox ),
    method( LDrawableComposite, setBoundingBox ),
    method( LDrawableComposite, createValueTree ),
    method( LDrawableComposite, getDrawableBounds ),
    method( LDrawableComposite, getContentArea ),
    method( LDrawableComposite, setContentArea ),
    method( LDrawableComposite, getMarkers ),
    method( LDrawableComposite, parentHierarchyChanged ),
    method( LDrawableComposite, childrenChanged ),
    method( LDrawableComposite, resetContentAreaAndBoundingBoxToFitChildren ),
    method( LDrawableComposite, childBoundsChanged ),
    method( LDrawableComposite, resetBoundingBoxToContentArea ),
    method( LDrawableComposite, refreshFromValueTree ),
    {0,0}
};

const Luna<LDrawableComposite>::StaticType LDrawableComposite::statics[] = {
    smethod( LDrawableComposite, contentLeftMarkerName ),
    smethod( LDrawableComposite, contentRightMarkerName ),
    smethod( LDrawableComposite, contentToptMarkerName ),
    smethod( LDrawableComposite, contentBottomMarkerName ),
    smethod( LDrawableComposite, valueTreeType ),

    {0,0}
};

LDrawableComposite::LDrawableComposite(lua_State *L)
    : LDrawable(L, this),
      DrawableComposite()
{
    REGISTER_CLASS(LDrawableComposite);
}

LDrawableComposite::LDrawableComposite(lua_State *L, const DrawableComposite& dc)
    : LDrawable(L, this),
      DrawableComposite(dc)
{
    REGISTER_CLASS(LDrawableComposite);
}

LDrawableComposite::~LDrawableComposite() {}


int LDrawableComposite::s_contentLeftMarkerName(lua_State* L) {
    lua_pushstring(L, DrawableComposite::contentLeftMarkerName );
    return 1;
}

int LDrawableComposite::s_contentRightMarkerName(lua_State* L) {
    lua_pushstring(L, DrawableComposite::contentRightMarkerName );
    return 0;
}

int LDrawableComposite::s_contentToptMarkerName(lua_State* L) {
    lua_pushstring(L, DrawableComposite::contentTopMarkerName );
    return 0;
}

int LDrawableComposite::s_contentBottomMarkerName(lua_State* L) {
    lua_pushstring(L, DrawableComposite::contentBottomMarkerName );
    return 0;
}

int LDrawableComposite::s_valueTreeType(lua_State*) {
    return LUA::returnString( DrawableComposite::valueTreeType.toString() );
}

int LDrawableComposite::createCopy(lua_State *L) {
    return LUA::storeAndReturnUserdata<LDrawableComposite>( new LDrawableComposite(L,
        *(DrawableComposite*)DrawableComposite::createCopy()
    ));
}

int LDrawableComposite::getDrawableBounds(lua_State*) {
    return LUCE::luce_pushtable( DrawableComposite::getDrawableBounds() );
}

int LDrawableComposite::parentHierarchyChanged(lua_State*) {
    DrawableComposite::parentHierarchyChanged();
    return 0;
}

int LDrawableComposite::childrenChanged(lua_State*) {
    DrawableComposite::childrenChanged();
    return 0;
}

int LDrawableComposite::resetContentAreaAndBoundingBoxToFitChildren(lua_State*) {
    DrawableComposite::resetContentAreaAndBoundingBoxToFitChildren();
    return 0;
}

int LDrawableComposite::childBoundsChanged(lua_State*) {
    DrawableComposite::childBoundsChanged( LUA::from_luce<LComponent, Component>(2) );
    return 0;
}

int LDrawableComposite::resetBoundingBoxToContentArea(lua_State*) {
    DrawableComposite::resetBoundingBoxToContentArea();
    return 0;
}

int LDrawableComposite::refreshFromValueTree ( lua_State* ) {
    // ValueTree tree = *LUA::from_luce<LValueTree>(2); // TODO;
    // ComponentBuilder builder = *LUA::from_luce<LComponentBuilder>(2); // TODO;
    // DrawableComposite::refreshFromValueTree( tree, builder );
    LUA::TODO_OBJECT( "refreshFromValueTree,  tree, builder " );
    lua_settop(LUA::Get(), 1); // added by TODO
    return 0;
}

// TODO
int LDrawableComposite::getBoundingBox ( lua_State *L ) {
    // CHECK
    // return LUA::storeAndReturnUserdata<LRelativeParallelogram>( new LRelativeParallelogram(L,
    //     DrawableComposite::getBoundingBox()
    // ));
    lua_settop(LUA::Get(), 1); // added by TODO
    return LUA::TODO_OBJECT( "RelativeParallelogram getBoundingBox()" );
}
int LDrawableComposite::setBoundingBox ( lua_State* ) {
    // DrawableComposite::setBoundingBox(*LUA::from_luce<LRelativeParallelogram>(2); // TODO);
    LUA::TODO_OBJECT( "setBoundingBox, *LUA::from_luce<LRelativeParallelogram>(2); // TODO" );
    lua_settop(LUA::Get(), 1); // added by TODO
    return 0;
}

int LDrawableComposite::getContentArea ( lua_State *L ) {
    // CHECK
    // return LUA::storeAndReturnUserdata<LRelativeRectangle>( new LRelativeRectangle(L,
    //     DrawableComposite::getContentArea()
    // ));
    lua_settop(LUA::Get(), 1); // added by TODO
    return LUA::TODO_OBJECT( "RelativeRectangle getContentArea()" );
}
int LDrawableComposite::setContentArea ( lua_State* ) {
    // DrawableComposite::setContentArea(*LUA::from_luce<LRelativeRectangle>(2); // TODO);
    LUA::TODO_OBJECT( "setContentArea, *LUA::from_luce<LRelativeRectangle>(2); // TODO" );
    lua_settop(LUA::Get(), 1); // added by TODO
    return 0;
}

int LDrawableComposite::getMarkers ( lua_State *L ) {
    bool xAxis = LUA::getBoolean(2);
    // CHECK
    // return LUA::storeAndReturnUserdata<LMarkerList>( new LMarkerList(L,
    //     DrawableComposite::getMarkers( xAxis )
    // ));
    lua_settop(LUA::Get(), 1); // added by TODO
    return LUA::TODO_OBJECT( "MarkerList getMarkers( xAxis )" );
}

int LDrawableComposite::createValueTree ( lua_State *L ) {
    // ComponentBuilder::ImageProvider* imageProvider = LUA::from_luce<LComponentBuilder::ImageProvider>(2); // TODO;
    // CHECK
    // return LUA::storeAndReturnUserdata<LValueTree>( new LValueTree(L,
    //     DrawableComposite::createValueTree( imageProvider )
    // ));
    lua_settop(LUA::Get(), 1); // added by TODO
    return LUA::TODO_OBJECT( "ValueTree createValueTree( imageProvider )" );
}


