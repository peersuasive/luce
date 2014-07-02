/************************************************************

 LFillType.cpp

    @author Christophe Berbizier (cberbizier@peersuasive.com)
    @license GPLv3
    @copyright 


(c) 2014, Peersuasive Technologies

*************************************************************/

#include "LFillType_inh.h"

const char LFillType::className[] = "LFillType";
const Luna<LFillType>::PropertyType LFillType::properties[] = {
    {"colour", &LFillType::getColour, &LFillType::setColour},
    {"gradient", &LFillType::getGradient, &LFillType::setGradient},
    {"image", &LFillType::getImage, &LBase::readOnly},
    {"transform", &LFillType::getTransform, &LBase::readOnly},
    {"opacity", &LFillType::getOpacity, &LFillType::setOpacity},
    {0,0}
};
const Luna<LFillType>::FunctionType LFillType::methods[] = {
    method( LFillType, isTiledImage ),
    method( LFillType, getImage ),
    method( LFillType, getTransform ),
    method( LFillType, setTiledImage ),
    method( LFillType, isInvisible ),
    method( LFillType, transformed ),
    method( LFillType, isGradient ),
    method( LFillType, getGradient ),
    method( LFillType, setGradient ),
    method( LFillType, isColour ),
    method( LFillType, getColour ),
    method( LFillType, setColour ),
    method( LFillType, getOpacity ),
    method( LFillType, setOpacity ),
    {0,0}
};

const Luna<LFillType>::StaticType LFillType::statics[] = {
    {0,0}
};

LFillType::LFillType(lua_State *L)
    : LBase(L, "LFillType", true),
      FillType()
{
}

LFillType::LFillType(lua_State *L, const FillType& class_)
    : LBase(L, "LFillType", true),
      FillType( class_ )
{
}

LFillType::~LFillType() {}

int LFillType::lnew(lua_State* L) {
    if(lua_isnoneornil(L,2)) {
        return LUA::storeAndReturnUserdata<LFillType>(new LFillType(L, 
            FillType()
        ));
    }
    else if(LUCE::luce_isofclass(LColour,2)) {
        return LUA::storeAndReturnUserdata<LFillType>(new LFillType(L, 
            FillType(*LUA::from_luce<LColour>(2))
        ));
    }
    else if(lua_isstring(L,2)) {
        Colour colour = Colours::findColourForName(LUA::getString(2), Colours::black);
        return LUA::storeAndReturnUserdata<LFillType>(new LFillType(L, 
            FillType(colour)
        ));
    }
    else if(LUCE::luce_isofclass(LColourGradient,2)) {
        return LUA::storeAndReturnUserdata<LFillType>(new LFillType(L, 
            FillType( *LUA::from_luce<LColourGradient>(2) )
        ));
    }
    else if(LUCE::luce_isofclass(LImage,2)) {
        Image *img = LUA::from_luce<LImage>(2);
        AffineTransform aff = LUCE::luce_toaffinetransform(2);
        return LUA::storeAndReturnUserdata<LFillType>(new LFillType(L, 
            FillType(*img, aff)
        ));
    }
    else if(LUCE::luce_isofclass(LFillType,2)) {
        return LUA::storeAndReturnUserdata<LFillType>(new LFillType(L,
            *LUA::from_luce<LFillType>(2)
        ));
    }
    else
        LUCE::luce_error(lua_pushfstring(L, 
            "LFillType: constructor not matched.\nExpected:\n %s,\n %s,\n %s,\n %s,\n %s,\n %s",
            "()",
            "(LColour)",
            "(string)",
            "(LColourGradient)",
            "(LImage)",
            "(LFillType)"
        ));

}

/////// getters/setters
int LFillType::isTiledImage ( lua_State* ) {
    return LUA::returnBoolean( FillType::isTiledImage() );
}
int LFillType::getImage ( lua_State* ) {
    return LUA::returnUserdata<LImage, Image>( &this->image );
}
int LFillType::getTransform ( lua_State* ) {
    return LUCE::luce_pushtable( FillType::transform );
}
int LFillType::setTiledImage ( lua_State* ) {
    Image image = *LUA::from_luce<LImage>(2);
    AffineTransform transform = LUCE::luce_toaffinetransform(2);
    FillType::setTiledImage( image, transform );
    return 0;
}

int LFillType::isGradient ( lua_State* ) {
    return LUA::returnBoolean( FillType::isGradient() );
}
int LFillType::getGradient ( lua_State* ) {
    return LUA::returnUserdata<LColourGradient,ColourGradient>( this->gradient );
}
int LFillType::setGradient ( lua_State* ) {
    FillType::setGradient(*LUA::from_luce<LColourGradient>(2));
    return 0;
}

int LFillType::isColour(lua_State*) {
    return LUA::returnBoolean( FillType::isColour() );
}
int LFillType::getColour(lua_State*) {
    return LUA::returnUserdata<LColour,Colour>( &this->colour );
}
int LFillType::setColour(lua_State* L) {
    if(lua_isstring(L,2)) {
        FillType::setColour( Colour(Colours::findColourForName(LUA::getString(2), Colours::black)) );
    }
    else
        FillType::setColour(*LUA::from_luce<LColour>(2));

    return 0;
}

int LFillType::getOpacity ( lua_State* ) {
    return LUA::returnNumber( FillType::getOpacity() );
}
int LFillType::setOpacity ( lua_State* ) {
    FillType::setOpacity(LUA::getNumber<float>(2));
    return 0;
}

/////// getters
int LFillType::isInvisible ( lua_State* ) {
    return LUA::returnBoolean( FillType::isInvisible() );
}

int LFillType::transformed ( lua_State *L ) {
    return LUA::storeAndReturnUserdata<LFillType>( new LFillType(L,
        FillType::transformed( LUCE::luce_toaffinetransform(2) )
    ));
}
