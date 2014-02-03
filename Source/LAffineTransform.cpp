/************************************************************

 LAffineTransform.cpp

    @author Christophe Berbizier (cberbizier@peersuasive.com)
    @license GPLv3
    @copyright 


(c) 2014, Peersuasive Technologies

*************************************************************/

// TODO: implement this in lua

#include "LAffineTransform_inh.h"

////// static methods
const char LAffineTransform::className[] = "LAffineTransform";
const Luna<LAffineTransform>::PropertyType LAffineTransform::properties[] = {
    { "identity", &LAffineTransform::getIdentity, &LBase::readOnly },
    {0,0}
};
const Luna<LAffineTransform>::FunctionType LAffineTransform::methods[] = {
    method( LAffineTransform, rotation ),
    method( LAffineTransform, translated ),
    method( LAffineTransform, getScaleFactor ),
    method( LAffineTransform, withAbsoluteTranslation ),
    method( LAffineTransform, isSingularity ),
    method( LAffineTransform, translation ),
    method( LAffineTransform, getTranslationX ),
    method( LAffineTransform, verticalFlip ),
    method( LAffineTransform, shear ),
    method( LAffineTransform, rotated ),
    method( LAffineTransform, scaled ),
    method( LAffineTransform, isOnlyTranslation ),
    method( LAffineTransform, followedBy ),
    method( LAffineTransform, getTranslationY ),
    method( LAffineTransform, fromTargetPoints ),
    method( LAffineTransform, sheared ),
    method( LAffineTransform, scale ),
    method( LAffineTransform, inverted ),
    method( LAffineTransform, isIdentity ),
    method( LAffineTransform, transformPoint ),
    method( LAffineTransform, transformPoints ),
    {0,0}
};

LAffineTransform::LAffineTransform(lua_State *L)
    : LBase(L, "LAffineTransform", true),
      AffineTransform()
{
    if ( lua_isstring(L, 2) )
        myName( lua_tostring(L, 2) );
}

LAffineTransform::LAffineTransform(lua_State *L, const AffineTransform& class_)
    : LBase(L, "LAffineTransform", true),
      AffineTransform( class_ )
{
    if ( lua_isstring(L, 2) )
        myName( lua_tostring(L, 2) );
}

LAffineTransform::~LAffineTransform() {}

int LAffineTransform::getIdentity(lua_State *L) {
    return LUA::storeAndReturnUserdata<LAffineTransform>( new LAffineTransform(L,
        AffineTransform::identity
    ));
}

AffineTransform LAffineTransform::fromLuce( float mat00, float mat01, float mat02, 
        float mat10, float mat11, float mat12) 
{
    return { mat00, mat01, mat02, mat10, mat11, mat12 };
}

AffineTransform LAffineTransform::fromLuce( const Array<float>& a )
{
    return { a[0], a[1], a[2], a[3], a[4], a[5] };
}

int LAffineTransform::dump(lua_State*) {
    return LUA::returnTable( std::list<var>{ mat00, mat01, mat02, mat10, mat11, mat12 } );
}

/////// getters
int LAffineTransform::rotation ( lua_State *L ) {
    float angleInRadians = LUA::getNumber<float>(2);
    if(lua_isnoneornil(L,2))
        return LUA::storeAndReturnUserdata<LAffineTransform>( new LAffineTransform(L,
            AffineTransform::rotation( angleInRadians )
        ));
        
    float pivotX = LUA::getNumber<float>(2);
    float pivotY = LUA::getNumber<float>(2);
    return LUA::storeAndReturnUserdata<LAffineTransform>( new LAffineTransform(LUA::Get(),
        AffineTransform::rotation( angleInRadians, pivotX, pivotY )
    ));
}

int LAffineTransform::translated ( lua_State *L ) {
    return LUA::storeAndReturnUserdata<LAffineTransform>( new LAffineTransform(L,
        AffineTransform::translated( LUA::getPoint<float>(2) )
    ));
}

int LAffineTransform::getScaleFactor ( lua_State* ) {
    return LUA::returnNumber( AffineTransform::getScaleFactor() );
}

int LAffineTransform::withAbsoluteTranslation ( lua_State* ) {
    float translationX = LUA::getNumber<float>(2);
    float translationY = LUA::getNumber<float>(2);
    return LUA::storeAndReturnUserdata<LAffineTransform>( new LAffineTransform(LUA::Get(),
        AffineTransform::withAbsoluteTranslation( translationX, translationY )
    ));
}

int LAffineTransform::isSingularity ( lua_State* ) {
    return LUA::returnBoolean( AffineTransform::isSingularity() );
}

int LAffineTransform::translation ( lua_State *L ) {
    return LUA::storeAndReturnUserdata<LAffineTransform>( new LAffineTransform(L,
        AffineTransform::translation( LUA::getPoint<float>(2) )
    ));
}

int LAffineTransform::getTranslationX ( lua_State* ) {
    return LUA::returnNumber( AffineTransform::getTranslationX() );
}

int LAffineTransform::verticalFlip ( lua_State *L ) {
    return LUA::storeAndReturnUserdata<LAffineTransform>( new LAffineTransform(L,
        AffineTransform::verticalFlip( LUA::getNumber<float>(2) )
    ));
}

int LAffineTransform::shear ( lua_State *L ) {
    float shearX = LUA::getNumber<float>(2);
    float shearY = LUA::getNumber<float>(2);
    return LUA::storeAndReturnUserdata<LAffineTransform>( new LAffineTransform(L,
        AffineTransform::shear( shearX, shearY )
    ));
}

int LAffineTransform::rotated ( lua_State *L ) {
    float angleInRadians = LUA::getNumber<float>(2);
    if(lua_isnoneornil(L,2))
        return LUA::storeAndReturnUserdata<LAffineTransform>( new LAffineTransform(L,
            AffineTransform::rotated( angleInRadians )
        ));

    float pivotX = LUA::getNumber<float>(2);
    float pivotY = LUA::getNumber<float>(2);
    return LUA::storeAndReturnUserdata<LAffineTransform>( new LAffineTransform(L,
        AffineTransform::rotated( angleInRadians, pivotX, pivotY )
    ));
}

int LAffineTransform::scaled ( lua_State *L ) {
    float factorX = LUA::getNumber<float>(2);
    if(lua_isnoneornil(L,2))
        return LUA::storeAndReturnUserdata<LAffineTransform>( new LAffineTransform(L,
            AffineTransform::scaled( factorX )
        ));

    float factorY = LUA::getNumber<float>(2);
    if(lua_isnoneornil(L, 2))
        return LUA::storeAndReturnUserdata<LAffineTransform>( new LAffineTransform(L,
            AffineTransform::scaled( factorX, factorY )
        ));

    float pivotX = LUA::getNumber<float>(2);
    float pivotY = LUA::getNumber<float>(2);
    return LUA::storeAndReturnUserdata<LAffineTransform>( new LAffineTransform(L,
        AffineTransform::scaled( factorX, factorY, pivotX, pivotY )
    ));
}

int LAffineTransform::isOnlyTranslation ( lua_State* ) {
    return LUA::returnBoolean( AffineTransform::isOnlyTranslation() );
}

int LAffineTransform::followedBy ( lua_State *L ) {
    return LUA::storeAndReturnUserdata<LAffineTransform>( new LAffineTransform(L,
        AffineTransform::followedBy( *LUA::from_luce<LAffineTransform>(2) )
    ));
}

int LAffineTransform::getTranslationY ( lua_State* ) {
    return LUA::returnNumber( AffineTransform::getTranslationY() );
}

int LAffineTransform::fromTargetPoints ( lua_State *L ) {
    float x00 = LUA::getNumber<float>(2);
    float y00 = LUA::getNumber<float>(2);
    float x10 = LUA::getNumber<float>(2);
    float y10 = LUA::getNumber<float>(2);
    float x01 = LUA::getNumber<float>(2);
    float y01 = LUA::getNumber<float>(2);
    if(lua_isnoneornil(L,2))
        return LUA::storeAndReturnUserdata<LAffineTransform>( new LAffineTransform(L,
            AffineTransform::fromTargetPoints( x00, y00, x10, y10, x01, y01 )
        ));

    float targetX2 = LUA::getNumber<float>(2);
    float targetY2 = LUA::getNumber<float>(2);
    float sourceX3 = LUA::getNumber<float>(2);
    float sourceY3 = LUA::getNumber<float>(2);
    float targetX3 = LUA::getNumber<float>(2);
    float targetY3 = LUA::getNumber<float>(2);
    return LUA::storeAndReturnUserdata<LAffineTransform>( new LAffineTransform(L,
        AffineTransform::fromTargetPoints( x00, y00, x10, y10, x01, y01, 
            targetX2, targetY2, sourceX3, sourceY3, targetX3, targetY3 )
    ));
}

int LAffineTransform::sheared ( lua_State *L ) {
    float shearX = LUA::getNumber<float>(2);
    float shearY = LUA::getNumber<float>(2);
    return LUA::storeAndReturnUserdata<LAffineTransform>( new LAffineTransform(L,
        AffineTransform::sheared( shearX, shearY )
    ));
}

int LAffineTransform::scale ( lua_State *L ) {
    float factorX = LUA::getNumber<float>(2);
    if(lua_isnoneornil(L,2))
        return LUA::storeAndReturnUserdata<LAffineTransform>( new LAffineTransform(L,
            AffineTransform::scale( factorX )
        ));

    float factorY = LUA::getNumber<float>(2);
    if(lua_isnoneornil(L,2))
        return LUA::storeAndReturnUserdata<LAffineTransform>( new LAffineTransform(L,
            AffineTransform::scale( factorX, factorY )
        ));

    float pivotX = LUA::getNumber<float>(2);
    float pivotY = LUA::getNumber<float>(2);
    return LUA::storeAndReturnUserdata<LAffineTransform>( new LAffineTransform(L,
        AffineTransform::scale( factorX, factorY, pivotX, pivotY )
    ));
}

int LAffineTransform::inverted ( lua_State *L ) {
    return LUA::storeAndReturnUserdata<LAffineTransform>( new LAffineTransform(L,
        AffineTransform::inverted()
    ));
}

int LAffineTransform::isIdentity ( lua_State* ) {
    return LUA::returnBoolean( AffineTransform::isIdentity() );
}

/////// setters
int LAffineTransform::transformPoint ( lua_State* ) {
    // ValueType x = *LUA::from_luce<LValueType>(2); // TODO;
    // ValueType y = *LUA::from_luce<LValueType>(2); // TODO;
    // AffineTransform::transformPoint( x, y );
    LUA::TODO_OBJECT( "transformPoint,  x, y " );
    lua_settop(LUA::Get(), 1); // added by TODO
    return 0;
}

int LAffineTransform::transformPoints ( lua_State* ) {
    // override
    // ValueType x1 = *LUA::from_luce<LValueType>(2); // TODO;
    // ValueType y1 = *LUA::from_luce<LValueType>(2); // TODO;
    // ValueType x2 = *LUA::from_luce<LValueType>(2); // TODO;
    // ValueType y2 = *LUA::from_luce<LValueType>(2); // TODO;
    // AffineTransform::transformPoints( x1, y1, x2, y2 );

    // override
    // ValueType x1 = *LUA::from_luce<LValueType>(2); // TODO;
    // ValueType y1 = *LUA::from_luce<LValueType>(2); // TODO;
    // ValueType x2 = *LUA::from_luce<LValueType>(2); // TODO;
    // ValueType y2 = *LUA::from_luce<LValueType>(2); // TODO;
    // ValueType x3 = *LUA::from_luce<LValueType>(2); // TODO;
    // ValueType y3 = *LUA::from_luce<LValueType>(2); // TODO;
    // AffineTransform::transformPoints( x1, y1, x2, y2, x3, y3 );
    LUA::TODO_OBJECT( "transformPoints,  x1, y1, x2, y2, x3, y3 " );
    lua_settop(LUA::Get(), 1); // added by TODO
    return 0;
}
