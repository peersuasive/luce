/************************************************************

 LImage.cpp

    @author Christophe Berbizier (cberbizier@peersuasive.com)
    @license GPLv3
    @copyright 


(c) 2014, Peersuasive Technologies

*************************************************************/

#include "LImage_inh.h"

////// static methods
const char LImage::className[] = "LImage";
const Luna<LImage>::PropertyType LImage::properties[] = {
    {"pixelAt", &LImage::getPixelAt, &LImage::setPixelAt},
    {"width", &LImage::getWidth, &LBase::readOnly},
    {"bounds", &LImage::getBounds, &LBase::readOnly},
    {0,0}
};
const Luna<LImage>::FunctionType LImage::methods[] = {
    method( LImage, getFormat ),
    method( LImage, isRGB ),
    method( LImage, createLowLevelContext ),
    method( LImage, convertedToFormat ),
    method( LImage, getReferenceCount ),
    method( LImage, getPixelAt ),
    method( LImage, setPixelAt ),
    method( LImage, getClippedImage ),
    method( LImage, isNull ),
    method( LImage, getPixelData ),
    method( LImage, createCopy ),
    method( LImage, isARGB ),
    method( LImage, isSingleChannel ),
    method( LImage, hasAlphaChannel ),
    method( LImage, isValid ),
    method( LImage, rescaled ),
    method( LImage, createSolidAreaMask ),
    method( LImage, multiplyAllAlphas ),
    method( LImage, moveImageSection ),
    method( LImage, desaturate ),
    method( LImage, multiplyAlphaAt ),
    method( LImage, clear ),
    method( LImage, duplicateIfShared ),
    {0,0}
};

/////// ctor/dtor
const Luna<LImage>::StaticType LImage::statics[] = {
    smethod( LImage, null ),
    {0,0}
};

LImage::LImage(lua_State *L)
    : LBase(L, "LImage", true),
      Image()
{
    if ( lua_isstring(L, 2) )
        myName( lua_tostring(L, 2) );
}

LImage::LImage(lua_State *L, const Image& class_)
    : LBase(L, "LImage", true),
      Image( class_ )
{
    if ( lua_isstring(L, 2) )
        myName( lua_tostring(L, 2) );
}

LImage::~LImage() {}

/////// statics

int LImage::s_null(lua_State *L) {
    return LUA::storeAndReturnUserdata<LImage>( new LImage(L,
         Image::null
    ));
}

/////// getters/setters
int LImage::getPixelAt ( lua_State *L ) {
    int x = LUA::getNumber<int>(2);
    int y = LUA::getNumber<int>(2);
    return LUA::storeAndReturnUserdata<LColour>( new LColour(L,
         Image::getPixelAt( x, y )
    ));
}
int LImage::setPixelAt ( lua_State* ) {
    int x = LUA::getNumber<int>(2);
    int y = LUA::getNumber<int>(2);
    Colour colour = *LUA::from_luce<LColour>(2);
    Image::setPixelAt( x, y, colour );
    return 0;
}
/////// getters
int LImage::getWidth(lua_State*) {
    return LUA::returnNumber(Image::getWidth());
}

int LImage::getBounds(lua_State*) {
    return LUCE::luce_pushtable( Image::getBounds() );
}

int LImage::getProperties(lua_State*) {
    // NameValueSet --> something we'd like to convert to a table, probably
    // but in this particular case, as we have a pointer, it might be interesting
    // to return a real object
    return 0;
}

int LImage::isRGB ( lua_State* ) {
    return LUA::returnBoolean( Image::isRGB() );
}

int LImage::getReferenceCount ( lua_State* ) {
    return LUA::returnNumber( Image::getReferenceCount() );
}

int LImage::getClippedImage ( lua_State *L ) {
    Rectangle<int> area ( LUA::getRectangle(2) );
    return LUA::storeAndReturnUserdata<LImage>( new LImage(L,
        Image::getClippedImage( area )
    ));
}

int LImage::isNull ( lua_State* ) {
    return LUA::returnBoolean( Image::isNull() );
}

int LImage::createCopy ( lua_State *L ) {
    return LUA::storeAndReturnUserdata<LImage>( new LImage(L,
        Image::createCopy()
    ));
}

int LImage::isARGB ( lua_State* ) {
    return LUA::returnBoolean( Image::isARGB() );
}

int LImage::isSingleChannel ( lua_State* ) {
    return LUA::returnBoolean( Image::isSingleChannel() );
}

int LImage::hasAlphaChannel ( lua_State* ) {
    return LUA::returnBoolean( Image::hasAlphaChannel() );
}

int LImage::isValid ( lua_State* ) {
    return LUA::returnBoolean( Image::isValid() );
}

int LImage::getFormat ( lua_State* ) {
    String format;
    switch( Image::getFormat() ) {
        case RGB:
            format = "RGB";
            break;
        case ARGB:
            format = "ARGB";
            break;
        case SingleChannel:
            format = "SingleChannel";
            break;
        default:
            format = "UnknownFormat";
    }
    return LUA::returnString( format );
}

int LImage::convertedToFormat ( lua_State *L ) {
    return LUA::storeAndReturnUserdata<LImage>( new LImage(L,
        Image::convertedToFormat( (PixelFormat)LUA::getNumber<int>(2) ) 
    ));
}

int LImage::rescaled ( lua_State* ) {
    int newWidth = LUA::getNumber<int>(2);
    int newHeight = LUA::getNumber<int>(2);
    Graphics::ResamplingQuality quality = 
        (Graphics::ResamplingQuality)LUA::checkAndGetNumber<int>(2, Graphics::mediumResamplingQuality);
    return LUA::storeAndReturnUserdata<LImage>( new LImage(LUA::Get(),
        Image::rescaled( newWidth, newHeight, quality )
    ));
}



/////// setters
int LImage::createSolidAreaMask ( lua_State* ) {
    // RectangleList<int> result = *LUA::from_luce<LRectangleList>(2); // TODO;
    float alphaThreshold = LUA::getNumber<float>(2);
    // Image::createSolidAreaMask( result, alphaThreshold );
    LUA::TODO_OBJECT( "createSolidAreaMask,  result, alphaThreshold " );
    lua_settop(LUA::Get(), 1); // added by TODO
    return 0;
}

int LImage::multiplyAllAlphas ( lua_State* ) {
    Image::multiplyAllAlphas(LUA::getNumber<float>());
    return 0;
}

int LImage::moveImageSection ( lua_State* ) {
    int destX = LUA::getNumber<int>(2);
    int destY = LUA::getNumber<int>(2);
    int sourceX = LUA::getNumber<int>(2);
    int sourceY = LUA::getNumber<int>(2);
    int width = LUA::getNumber<int>(2);
    int height = LUA::getNumber<int>(2);
    Image::moveImageSection( destX, destY, sourceX, sourceY, width, height );
    return 0;
}

int LImage::desaturate ( lua_State* ) {
    Image::desaturate();
    return 0;
}

int LImage::multiplyAlphaAt ( lua_State* ) {
    int x = LUA::getNumber<int>(2);
    int y = LUA::getNumber<int>(2);
    float multiplier = LUA::getNumber<float>(2);
    Image::multiplyAlphaAt( x, y, multiplier );
    return 0;
}

int LImage::clear ( lua_State *L ) {
    Rectangle<int> area ( LUA::getRectangle(2) );

    Colour colourToClearTo;
    if(lua_isnoneornil(L,2))
        colourToClearTo = Colour (0x00000000);
    else
        colourToClearTo = *LUA::from_luce<LColour>(2);
    Image::clear( area, colourToClearTo );
    return 0;
}

int LImage::duplicateIfShared ( lua_State* ) {
    Image::duplicateIfShared();
    return 0;
}

// TODO
// getters
int LImage::getPixelData ( lua_State* ) {
    // CHECK
    // return LUA::storeAndReturnUserdata<LImagePixelData>( new LImagePixelData(L,
    //     Image::getPixelData()
    // ));
    lua_settop(LUA::Get(), 1); // added by TODO
    return LUA::TODO_OBJECT( "ImagePixelData getPixelData()" );
}

int LImage::createLowLevelContext ( lua_State* ) {
    // CHECK
    // return LUA::storeAndReturnUserdata<LLowLevelGraphicsContext>( new LLowLevelGraphicsContext(L,
    //     Image::createLowLevelContext()
    // ));
    lua_settop(LUA::Get(), 1); // added by TODO
    return LUA::TODO_OBJECT( "LowLevelGraphicsContext createLowLevelContext()" );
}
