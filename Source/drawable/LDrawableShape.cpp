/************************************************************

 LDrawableShape.cpp

    @author Christophe Berbizier (cberbizier@peersuasive.com)
    @license GPLv3
    @copyright 


(c) 2014, Peersuasive Technologies

*************************************************************/

#include "LDrawableShape_inh.h"

const char LDrawableShape::className[] = "LDrawableShape";
const Luna<LDrawableShape>::PropertyType LDrawableShape::properties[] = {
    {"fill", &LDrawableShape::getFill, &LDrawableShape::setFill},
    {"strokeType", &LDrawableShape::getStrokeType, &LDrawableShape::setStrokeType},
    {"strokeFill", &LDrawableShape::getStrokeFill, &LDrawableShape::setStrokeFill},

    {0,0}
};
const Luna<LDrawableShape>::FunctionType LDrawableShape::methods[] = {
    method( LDrawableShape, getFill ),
    method( LDrawableShape, setFill ),
    method( LDrawableShape, getStrokeType ),
    method( LDrawableShape, setStrokeFill ),
    method( LDrawableShape, hitTest ),
    method( LDrawableShape, setStrokeThickness ),
    //method( LDrawableShape, paint ),
    
    {0,0}
};

const Luna<LDrawableShape>::StaticType LDrawableShape::statics[] = {
    {0,0}
};

LDrawableShape::LDrawableShape(lua_State *L, DrawableShape* child_, const String& name_)
    : LDrawable(L, child_, name_),
      child(child_)
{
}

LDrawableShape::~LDrawableShape() {}

int LDrawableShape::getFill ( lua_State *L ) {
    //return LUA::storeAndReturnUserdata<LRelativeFillType>( new LFillType(L,
    //    child->getFill()
    //));
    // TODO: RelativeFillType
    lua_settop(LUA::Get(), 1); // added by TODO
    return LUA::TODO_OBJECT( "RelativeFillType getFill()" );
    
}
int LDrawableShape::setFill ( lua_State* ) {
    child->setFill(*LUA::from_luce<LFillType>(2));
    // TODO: RelativeFillType
    return 0;
}

int LDrawableShape::getStrokeType ( lua_State *L ) {
    return LUA::storeAndReturnUserdata<LPathStrokeType>( new LPathStrokeType(L,
        child->getStrokeType()
    ));
}
int LDrawableShape::setStrokeType ( lua_State* ) {
    child->setStrokeType(*LUA::from_luce<LPathStrokeType>(2));
    return 0;
}

int LDrawableShape::getStrokeFill ( lua_State *L ) {
    // CHECK
    // return LUA::storeAndReturnUserdata<LRelativeFillType>( new LRelativeFillType(L,
    //     DrawableShape::getStrokeFill()
    // ));
    lua_settop(LUA::Get(), 1); // added by TODO
    return LUA::TODO_OBJECT( "RelativeFillType getStrokeFill()" );
}
int LDrawableShape::setStrokeFill ( lua_State* ) {
    child->setStrokeFill(*LUA::from_luce<LFillType>(2));
    // TODO: RelativeFillType
    return 0;
}

int LDrawableShape::hitTest ( lua_State* ) {
    int x = LUA::getNumber<int>(2);
    int y = LUA::getNumber<int>(2);
    return LUA::returnBoolean( child->hitTest( x, y ) );
}

int LDrawableShape::setStrokeThickness ( lua_State* ) {
    child->setStrokeThickness(LUA::getNumber<float>());
    return 0;
}

//int LDrawableShape::isStrokeVisible ( lua_State* ) {
//    return LUA::returnBoolean( child->isStrokeVisible() );
//}

//int LDrawableShape::refreshFillTypes ( lua_State* ) {
//    // FillAndStrokeState newState = *LUA::from_luce<LFillAndStrokeState>(2); // TODO;
//    // ComponentBuilder::ImageProvider* componentbuilder::imageprovider_ = LUA::from_luce<LComponentBuilder::ImageProvider>(2); // TODO;
//    // DrawableShape::refreshFillTypes( newState, componentbuilder::imageprovider_ );
//    LUA::TODO_OBJECT( "refreshFillTypes,  newState, componentbuilder::imageprovider_ " );
//    lua_settop(LUA::Get(), 1); // added by TODO
//    return 0;
//}

//int LDrawableShape::writeTo ( lua_State* ) {
//    // FillAndStrokeState state = *LUA::from_luce<LFillAndStrokeState>(2); // TODO;
//    // ComponentBuilder::ImageProvider* componentbuilder::imageprovider_ = LUA::from_luce<LComponentBuilder::ImageProvider>(2); // TODO;
//    // UndoManager* undomanager_ = LUA::from_luce<LUndoManager>(2); // TODO;
//    // DrawableShape::writeTo( state, componentbuilder::imageprovider_, undomanager_ );
//    LUA::TODO_OBJECT( "writeTo,  state, componentbuilder::imageprovider_, undomanager_ " );
//    lua_settop(LUA::Get(), 1); // added by TODO
//    return 0;
//}

//int LDrawableShape::pathChanged ( lua_State* ) {
//    DrawableShape::pathChanged();
//    return 0;
//}

//int LDrawableShape::paint ( lua_State* ) {
//    // DrawableShape::paint(*LUA::from_luce<LGraphics>(2); // TODO);
//    LUA::TODO_OBJECT( "paint, *LUA::from_luce<LGraphics>(2); // TODO" );
//    lua_settop(LUA::Get(), 1); // added by TODO
//    return 0;
//}

//int LDrawableShape::strokeChanged ( lua_State* ) {
//    DrawableShape::strokeChanged();
//    return 0;
//}
