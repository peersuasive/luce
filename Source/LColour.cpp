/************************************************************

 LColour.cpp

    @author Christophe Berbizier (cberbizier@peersuasive.com)
    @license GPLv3
    @copyright 


(c) 2014, Peersuasive Technologies

*************************************************************/

#include "LColour_inh.h"

////// static methods
const char LColour::className[] = "LColour";
const Luna<LColour>::PropertyType LColour::properties[] = {
    {0,0}
};
const Luna<LColour>::FunctionType LColour::methods[] = {
    method( LColour, fromFloatRGBA ),
    method( LColour, fromString ),
    method( LColour, fromRGB ),
    method( LColour, brighter ),
    method( LColour, getFloatRed ),
    method( LColour, interpolatedWith ),
    method( LColour, getRed ),
    method( LColour, getSaturation ),
    method( LColour, getFloatAlpha ),
    method( LColour, overlaidWith ),
    method( LColour, fromRGBA ),
    method( LColour, getPixelARGB ),
    method( LColour, toString ),
    method( LColour, withMultipliedBrightness ),
    method( LColour, withMultipliedAlpha ),
    method( LColour, toDisplayString ),
    method( LColour, contrasting ),
    method( LColour, getHue ),
    method( LColour, fromHSV ),
    method( LColour, greyLevel ),
    method( LColour, isTransparent ),
    method( LColour, withAlpha ),
    method( LColour, getARGB ),
    method( LColour, darker ),
    method( LColour, getFloatGreen ),
    method( LColour, getBlue ),
    method( LColour, getGreen ),
    method( LColour, getFloatBlue ),
    method( LColour, withSaturation ),
    method( LColour, getBrightness ),
    method( LColour, withRotatedHue ),
    method( LColour, withBrightness ),
    method( LColour, withHue ),
    method( LColour, withMultipliedSaturation ),
    method( LColour, getHSB ),
    {0,0}
};

LColour::LColour(lua_State *L)
    : LBase(L, "LColour", true),
      Colour( /* TODO: add args */ )
{
    if ( lua_isstring(L, 2) )
        myName( lua_tostring(L, 2) );
}

LColour::LColour(lua_State *L, const Colour& class_)
    : LBase(L, "LColour", true),
      Colour( class_ )
{
    if ( lua_isstring(L, 2) )
        myName( lua_tostring(L, 2) );
}

LColour::~LColour() {}

int LColour::fromRGB ( lua_State *L ) {
    uint8 red   = LUA::getNumber<uint8>(2);
    uint8 green = LUA::getNumber<uint8>(2);
    uint8 blue  = LUA::getNumber<uint8>(2);
    return LUA::storeAndReturnUserdata<LColour>( new LColour(L,
        Colour::fromRGB( red, green, blue )
    ));
}

int LColour::fromRGBA ( lua_State *L ) {
    uint8 red   = LUA::getNumber<uint8>(2);
    uint8 green = LUA::getNumber<uint8>(2);
    uint8 blue  = LUA::getNumber<uint8>(2);
    uint8 alpha = LUA::getNumber<uint8>(2);
    return LUA::storeAndReturnUserdata<LColour>( new LColour(L,
        Colour::fromRGBA( red, green, blue, alpha )
    ));
}

int LColour::fromHSV ( lua_State *L ) {
    float hue        = LUA::getNumber<float>(2);
    float saturation = LUA::getNumber<float>(2);
    float brightness = LUA::getNumber<float>(2);
    float alpha      = LUA::getNumber<float>(2);
    return LUA::storeAndReturnUserdata<LColour>( new LColour(L,
        Colour::fromHSV( hue, saturation, brightness, alpha )
    ));
}

int LColour::fromFloatRGBA ( lua_State *L ) {
    float red   = LUA::getNumber<float>(2);
    float green = LUA::getNumber<float>(2);
    float blue  = LUA::getNumber<float>(2);
    float alpha = LUA::getNumber<float>(2);
    return LUA::storeAndReturnUserdata<LColour>( new LColour(L,
        Colour::fromFloatRGBA( red, green, blue, alpha )
    ));
}

int LColour::contrasting ( lua_State *L ) {
    if (lua_isnoneornil(L,2) or lua_isnumber(L,2)) {
        float amount = LUA::checkAndGetNumber(1, 1.0f);
        return LUA::storeAndReturnUserdata<LColour>( new LColour(L, 
            Colour::contrasting( amount ) 
        ));
    }
    else if ( lua_isnumber(L, 3) ) {
        Colour targetColour = *LUA::from_luce<LColour>(2);
        float minLuminosityDiff = LUA::getNumber<float>(2);
        return LUA::storeAndReturnUserdata<LColour>( new LColour(L, 
            Colour::contrasting( targetColour, minLuminosityDiff ) 
        ));
    }
    else {
        Colour colour1 = *LUA::from_luce<LColour>(2);
        Colour colour2 = *LUA::from_luce<LColour>(2);
        return LUA::storeAndReturnUserdata<LColour>( new LColour(L, 
            Colour::contrasting( colour1, colour2 )
        ));
    }
}

int LColour::greyLevel ( lua_State *L ) {
    return LUA::storeAndReturnUserdata<LColour>( new LColour(L,
        Colour::greyLevel( LUA::getNumber<float>(2) )
    ));
}

int LColour::fromString ( lua_State *L ) {
    return LUA::storeAndReturnUserdata<LColour>( new LColour(L,
        Colour::fromString( StringRef(LUA::getString(2)) )
    ));
}

int LColour::brighter ( lua_State *L ) {
    return LUA::storeAndReturnUserdata<LColour>( new LColour(L,
        Colour::brighter( LUA::checkAndGetNumber<float>(2, 0.4f) )
    ));
}

int LColour::darker ( lua_State *L ) {
    return LUA::storeAndReturnUserdata<LColour>( new LColour(L,
        Colour::darker( LUA::checkAndGetNumber<float>(2, 0.4f) )
    ));
}

int LColour::interpolatedWith ( lua_State *L ) {
    Colour other = *LUA::from_luce<LColour>(2);
    float proportionOfOther = LUA::getNumber<float>(2);
    return LUA::storeAndReturnUserdata<LColour>( new LColour(L,
        Colour::interpolatedWith( other, proportionOfOther )
    ));
}

int LColour::overlaidWith ( lua_State *L ) {
    return LUA::storeAndReturnUserdata<LColour>( new LColour(L,
        Colour::overlaidWith( *LUA::from_luce<LColour>(2) )
    ));
}

int LColour::withMultipliedBrightness ( lua_State *L ) {
    return LUA::storeAndReturnUserdata<LColour>( new LColour(L,
        Colour::withMultipliedBrightness( LUA::getNumber<float>(2) )
    ));
}

int LColour::withMultipliedAlpha ( lua_State *L ) {
    return LUA::storeAndReturnUserdata<LColour>( new LColour(L,
        Colour::withMultipliedAlpha( LUA::getNumber<float>(2) )
    ));
}

int LColour::withSaturation ( lua_State *L ) {
    return LUA::storeAndReturnUserdata<LColour>( new LColour(L,
        Colour::withSaturation( LUA::getNumber<float>(2) )
    ));
}

int LColour::withRotatedHue ( lua_State *L ) {
    return LUA::storeAndReturnUserdata<LColour>( new LColour(L,
        Colour::withRotatedHue( LUA::getNumber<float>(2) )
    ));
}

int LColour::withBrightness ( lua_State *L ) {
    return LUA::storeAndReturnUserdata<LColour>( new LColour(L,
        Colour::withBrightness( LUA::getNumber<float>(2) )
    ));
}

int LColour::withHue ( lua_State *L ) {
    return LUA::storeAndReturnUserdata<LColour>( new LColour(L,
        Colour::withHue( LUA::getNumber<float>(2) )
    ));
}

int LColour::withMultipliedSaturation ( lua_State *L ) {
    return LUA::storeAndReturnUserdata<LColour>( new LColour(L,
        Colour::withMultipliedSaturation( LUA::getNumber<float>(2) )
    ));
}

int LColour::withAlpha ( lua_State* ) {
    return LUA::storeAndReturnUserdata<LColour>( new LColour(LUA::Get(),
        Colour::withAlpha( LUA::getNumber<float>(2) )
    ));
}

int LColour::getFloatRed ( lua_State* ) {
    return LUA::returnNumber( Colour::getFloatRed() );
}

int LColour::getRed ( lua_State* ) {
    return LUA::returnNumber( Colour::getRed() );
}

int LColour::getSaturation ( lua_State* ) {
    return LUA::returnNumber( Colour::getSaturation() );
}

int LColour::getFloatAlpha ( lua_State* ) {
    return LUA::returnNumber( Colour::getFloatAlpha() );
}

int LColour::toString ( lua_State* ) {
    return LUA::returnString( Colour::toString() );
}

int LColour::toDisplayString ( lua_State* ) {
    return LUA::returnString( Colour::toDisplayString( LUA::getBoolean(2) ) );
}

int LColour::getHue ( lua_State* ) {
    return LUA::returnNumber( Colour::getHue() );
}

int LColour::isTransparent ( lua_State* ) {
    return LUA::returnBoolean( Colour::isTransparent() );
}

int LColour::getARGB ( lua_State* ) {
    return LUA::returnNumber( Colour::getARGB() );
}

int LColour::getFloatGreen ( lua_State* ) {
    return LUA::returnNumber( Colour::getFloatGreen() );
}

int LColour::getBlue ( lua_State* ) {
    return LUA::returnNumber( Colour::getBlue() );
}

int LColour::getGreen ( lua_State* ) {
    return LUA::returnNumber( Colour::getGreen() );
}

int LColour::getFloatBlue ( lua_State* ) {
    return LUA::returnNumber( Colour::getFloatBlue() );
}

int LColour::getBrightness ( lua_State* ) {
    return LUA::returnNumber( Colour::getBrightness() );
}

int LColour::getHSB ( lua_State* ) {
    float hue, saturation, brightness;
    Colour::getHSB( hue, saturation, brightness );
    return LUA::returnTable( std::list<var>{ hue, saturation, brightness } );
}

// TODO
int LColour::getPixelARGB ( lua_State* ) {
    // return LUA::TODO_RETURN_OBJECT_PixelARGB( Colour::getPixelARGB() );
    lua_settop(LUA::Get(), 1); // added by TODO
    return LUA::TODO_OBJECT( "PixelARGB getPixelARGB()" );
}
