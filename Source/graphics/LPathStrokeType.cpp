/************************************************************

 LPathStrokeType.cpp

    @author Christophe Berbizier (cberbizier@peersuasive.com)
    @license GPLv3
    @copyright 


(c) 2014, Peersuasive Technologies

*************************************************************/

// TODO: reimplement as a lua class
//       difficulties: enums... 

#include "LPathStrokeType_inh.h"

const char LPathStrokeType::className[] = "LPathStrokeType";
const Luna<LPathStrokeType>::PropertyType LPathStrokeType::properties[] = {
    {"jointStyle", &LPathStrokeType::getJointStyle, &LPathStrokeType::setJointStyle},
    {"strokeThickness", &LPathStrokeType::getStrokeThickness, &LPathStrokeType::setStrokeThickness},
    {"endStyle", &LPathStrokeType::getEndStyle, &LPathStrokeType::setEndStyle},
    {0,0}
};
const Luna<LPathStrokeType>::FunctionType LPathStrokeType::methods[] = {
    method( LPathStrokeType, getJointStyle ),
    method( LPathStrokeType, setJointStyle ),
    method( LPathStrokeType, getStrokeThickness ),
    method( LPathStrokeType, setStrokeThickness ),
    method( LPathStrokeType, getEndStyle ),
    method( LPathStrokeType, setEndStyle ),
    method( LPathStrokeType, createDashedStroke ),
    method( LPathStrokeType, createStrokeWithArrowheads ),
    method( LPathStrokeType, createStrokedPath ),
    {0,0}
};

const Luna<LPathStrokeType>::StaticType LPathStrokeType::statics[] = {
    {0,0}
};

LPathStrokeType::LPathStrokeType(lua_State *L)
    : LBase(L, "LPathStrokeType", true),
      PathStrokeType( 0.1f )
{
    // INVALID
}

LPathStrokeType::LPathStrokeType(lua_State *L, const PathStrokeType& class_)
    : LBase(L, "LPathStrokeType", true),
      PathStrokeType( class_ )
{
}

LPathStrokeType::~LPathStrokeType() {}

int LPathStrokeType::lnew(lua_State *L) {
    float thickness = LUA::getNumber<float>(2);
    JointStyle style = PathStrokeType::mitered;
    EndCapStyle endStyle = PathStrokeType::butt;
    if(lua_gettop(L)==2) {
        style = (JointStyle)LUA::getNumber<int>(2);
        endStyle = (EndCapStyle)LUA::checkAndGetNumber(2, (int)PathStrokeType::butt);
    }
    return LUA::storeAndReturnUserdata<LPathStrokeType>( new LPathStrokeType(L, 
        PathStrokeType(thickness, style, endStyle)
    ));
}

/////// getters/setters
int LPathStrokeType::getJointStyle ( lua_State *L ) {
    return LUA::returnNumber( PathStrokeType::getJointStyle() );
}
int LPathStrokeType::setJointStyle ( lua_State* ) {
    PathStrokeType::setJointStyle( (JointStyle)LUA::getNumber<int>(2) );
    return 0;
}

int LPathStrokeType::getStrokeThickness ( lua_State* ) {
    return LUA::returnNumber( PathStrokeType::getStrokeThickness() );
}
int LPathStrokeType::setStrokeThickness ( lua_State* ) {
    PathStrokeType::setStrokeThickness(LUA::getNumber<float>());
    return 0;
}

int LPathStrokeType::getEndStyle ( lua_State *L ) {
    return LUA::returnNumber( PathStrokeType::getEndStyle() );
}
int LPathStrokeType::setEndStyle ( lua_State* ) {
    PathStrokeType::setEndStyle( (EndCapStyle)LUA::getNumber<int>(2) );
    return 0;
}

/////// setters
int LPathStrokeType::createDashedStroke ( lua_State *L ) {
    Path destPath = *LUA::from_luce<LPath>(2);
    Path sourcePath = *LUA::from_luce<LPath>(2);
    const float* dashLengths = LUCE::luce_getnumarray<float>(2);
    int numDashLengths = LUA::getNumber<int>(2);
    AffineTransform transform = AffineTransform::identity;
    float extraAccuracy = 1.0f;
    if(! lua_isnoneornil(L, 2) ) {
        transform = LUCE::luce_toaffinetransform(2);
        extraAccuracy = LUA::checkAndGetNumber<float>(2, 1.0f);
    }
    PathStrokeType::createDashedStroke( destPath, sourcePath, 
                dashLengths, numDashLengths, transform, extraAccuracy );
    return 0;
}

int LPathStrokeType::createStrokeWithArrowheads ( lua_State *L ) {
    Path destPath = *LUA::from_luce<LPath>(2);
    Path sourcePath = *LUA::from_luce<LPath>(2);
    float arrowheadStartWidth = LUA::getNumber<float>(2);
    float arrowheadStartLength = LUA::getNumber<float>(2);
    float arrowheadEndWidth = LUA::getNumber<float>(2);
    float arrowheadEndLength = LUA::getNumber<float>(2);
    
    AffineTransform transform = AffineTransform::identity;
    float extraAccuracy = 1.0f;
    if(!lua_isnoneornil(L,2)) {
        transform = LUCE::luce_toaffinetransform(2);
        extraAccuracy = LUA::checkAndGetNumber<float>(2, 1.0f);
    }

    PathStrokeType::createStrokeWithArrowheads( destPath, sourcePath, arrowheadStartWidth, 
            arrowheadStartLength, arrowheadEndWidth, arrowheadEndLength, transform, extraAccuracy );
    return 0;
}

int LPathStrokeType::createStrokedPath ( lua_State *L ) {
    Path destPath = *LUA::from_luce<LPath>(2);
    Path sourcePath = *LUA::from_luce<LPath>(2);
    AffineTransform transform = AffineTransform::identity;
    float extraAccuracy = 1.0f;
    if(!lua_isnoneornil(L,2)) {
        transform = LUCE::luce_toaffinetransform(2);
        extraAccuracy = LUA::checkAndGetNumber<float>(2, 1.0f);
    }
    PathStrokeType::createStrokedPath( destPath, sourcePath, transform, extraAccuracy );
    return 0;
}

