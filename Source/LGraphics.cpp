/************************************************************

 LGraphics.cpp

    @author Christophe Berbizier (cberbizier@peersuasive.com)
    @license GPLv3
    @copyright 


(c) 2014, Peersuasive Technologies

*************************************************************/

#include "LGraphics_inh.h"

////// static methods
const char LGraphics::className[] = "LGraphics";
const Luna<LGraphics>::PropertyType LGraphics::properties[] = {
    {0,0}
};
const Luna<LGraphics>::FunctionType LGraphics::methods[] = {
    method( LGraphics, isVectorDevice ),
    method( LGraphics, getInternalContext ),
    method( LGraphics, getCurrentFont ),
    method( LGraphics, getClipBounds ),
    method( LGraphics, reduceClipRegion ),
    method( LGraphics, clipRegionIntersects ),
    method( LGraphics, isClipEmpty ),
    method( LGraphics, resetToDefaultState ),
    method( LGraphics, drawImageAt ),
    method( LGraphics, fillAll ),
    method( LGraphics, fillEllipse ),
    method( LGraphics, setFillType ),
    method( LGraphics, drawImage ),
    method( LGraphics, drawEllipse ),
    method( LGraphics, saveState ),
    method( LGraphics, drawArrow ),
    method( LGraphics, addTransform ),
    method( LGraphics, drawImageWithin ),
    method( LGraphics, excludeClipRegion ),
    method( LGraphics, endTransparencyLayer ),
    method( LGraphics, fillCheckerBoard ),
    method( LGraphics, drawHorizontalLine ),
    method( LGraphics, setOrigin ),
    method( LGraphics, drawDashedLine ),
    method( LGraphics, drawImageTransformed ),
    method( LGraphics, beginTransparencyLayer ),
    method( LGraphics, fillPath ),
    method( LGraphics, restoreState ),
    method( LGraphics, drawText ),
    method( LGraphics, fillRectList ),
    method( LGraphics, drawFittedText ),
    method( LGraphics, strokePath ),
    method( LGraphics, fillRoundedRectangle ),
    method( LGraphics, drawMultiLineText ),
    method( LGraphics, setFont ),
    method( LGraphics, setTiledImageFill ),
    method( LGraphics, fillRect ),
    method( LGraphics, setGradientFill ),
    method( LGraphics, setImageResamplingQuality ),
    method( LGraphics, setPixel ),
    method( LGraphics, drawSingleLineText ),
    method( LGraphics, drawVerticalLine ),
    method( LGraphics, drawRect ),
    method( LGraphics, drawRoundedRectangle ),
    method( LGraphics, drawLine ),
    method( LGraphics, setOpacity ),
    {0,0}
};

/////// ctor/dtor
LGraphics::LGraphics(lua_State *L)
    : LBase(L, "LGraphics", true)
{
    if ( lua_isstring(L, 2) )
        myName( lua_tostring(L, 2) );

    // set g with Image
}

LGraphics::LGraphics(lua_State *L, juce::Graphics& class_)
    : LBase(L, "LGraphics", true)
{
    if ( lua_isstring(L, 2) )
        myName( lua_tostring(L, 2) );
    g = &class_;
}

LGraphics::~LGraphics() {}

/////// getters
int LGraphics::isVectorDevice ( lua_State* ) {
    return LUA::returnBoolean(g->isVectorDevice() );
}

int LGraphics::getCurrentFont ( lua_State *L ) {
    return LUA::storeAndReturnUserdata<LFont>( new LFont(L,
         g->getCurrentFont()
    ));
}

int LGraphics::getClipBounds ( lua_State* ) {
    return LUA::returnTable(g->getClipBounds() );
}

int LGraphics::reduceClipRegion ( lua_State* ) {
    Rectangle<int> area ( LUA::getRectangle(2) );
    return LUA::returnBoolean(g->reduceClipRegion( area ) );

    // override
    // RectangleList<int> clipRegion = *LUA::from_luce<LRectangleList>(2); // TODO;
    // return LUA::returnBoolean(g->reduceClipRegion( clipRegion ) );

    // override
    // Path path = *LUA::from_luce<LPath>(2); // TODO;
    // AffineTransform transform = *LUA::from_luce<LAffineTransform>(2); // TODO;
    // return LUA::returnBoolean(g->reduceClipRegion( path, transform ) );

    // override
    // Image image = *LUA::from_luce<LImage>(2); // TODO;
    // AffineTransform transform = *LUA::from_luce<LAffineTransform>(2); // TODO;
    // return LUA::returnBoolean(g->reduceClipRegion( image, transform ) );
}

int LGraphics::clipRegionIntersects ( lua_State* ) {
    return LUA::returnBoolean(g->clipRegionIntersects( LUA::getRectangle(2) ) );
}

int LGraphics::isClipEmpty ( lua_State* ) {
    return LUA::returnBoolean(g->isClipEmpty() );
}

/////// setters
int LGraphics::resetToDefaultState ( lua_State* ) {
    g->resetToDefaultState();
    return 0;
}

int LGraphics::fillAll ( lua_State *L ) {
    if(lua_isnoneornil(L, 2))
        g->fillAll();
    else if (lua_isstring(L, 2))
        g->fillAll( Colours::findColourForName( LUA::getString(2), Colours::black ) );
    else
        g->fillAll( *LUA::from_luce<LColour>(2) );
    return 0;
}

int LGraphics::fillEllipse ( lua_State* ) {
     g->fillEllipse(LUA::getRectangle<float>(2));
    return 0;
}

int LGraphics::drawEllipse ( lua_State* ) {
    Rectangle<float> area ( LUA::getRectangle<float>(2) );
    float lineThickness = LUA::getNumber<float>(2);
    g->drawEllipse( area, lineThickness );
    return 0;
}

int LGraphics::saveState ( lua_State* ) {
    g->saveState();
    return 0;
}

int LGraphics::excludeClipRegion ( lua_State* ) {
    g->excludeClipRegion(LUA::getRectangle(2));
    return 0;
}

int LGraphics::endTransparencyLayer ( lua_State* ) {
    g->endTransparencyLayer();
    return 0;
}

int LGraphics::fillCheckerBoard ( lua_State *L ) {
    Rectangle<int> area ( LUA::getRectangle<int>(2) );
    int checkWidth = LUA::getNumber<int>(2);
    int checkHeight = LUA::getNumber<int>(2);
    Colour colour1, colour2;
    if(lua_isstring(L,2))
        colour1 = Colours::findColourForName( LUA::getString(2), Colours::black );
    else
        Colour colour1 = *LUA::from_luce<LColour>(2);
    if(lua_isstring(L,2))
        colour2 = Colours::findColourForName( LUA::getString(2), Colours::black );
    else
        Colour colour2 = *LUA::from_luce<LColour>(2);

    g->fillCheckerBoard( area, checkWidth, checkHeight, colour1, colour2 );
    return 0;
}

int LGraphics::drawHorizontalLine ( lua_State* ) {
    int y = LUA::getNumber<int>(2);
    float left = LUA::getNumber<float>(2);
    float right = LUA::getNumber<float>(2);
    g->drawHorizontalLine( y, left, right );
    return 0;
}

int LGraphics::setOrigin ( lua_State* ) {
    g->setOrigin( LUA::getPoint(2) );
}

int LGraphics::beginTransparencyLayer ( lua_State* ) {
    g->beginTransparencyLayer(LUA::getNumber<float>());
    return 0;
}

int LGraphics::restoreState ( lua_State* ) {
    g->restoreState();
    return 0;
}

int LGraphics::drawText ( lua_State* ) {
    String text = LUA::getString(2);
    Rectangle<int> area ( LUA::getRectangle<int>(2) );
    Justification justificationType = LUA::getNumber<int>(2);
    bool useEllipsesIfTooBig = LUA::getBoolean(2);
    g->drawText( text, area, justificationType, useEllipsesIfTooBig );
    return 0;
}

int LGraphics::drawFittedText ( lua_State* ) {
    String text = LUA::getString(2);
    Rectangle<int> area ( LUA::getRectangle<int>(2) );
    Justification justificationFlags = LUA::getNumber<int>(2);
    int maximumNumberOfLines = LUA::getNumber<int>(2);
    float minimumHorizontalScale = LUA::checkAndGetNumber<float>(2, 0.7f);
    g->drawFittedText( text, area, justificationFlags, maximumNumberOfLines, minimumHorizontalScale );
    return 0;
}

int LGraphics::fillRoundedRectangle ( lua_State* ) {
    Rectangle<float> rectangle ( LUA::getRectangle<float>(2) );
    float cornerSize = LUA::getNumber<float>(2);
    g->fillRoundedRectangle( rectangle, cornerSize );
    return 0;
}

int LGraphics::drawMultiLineText ( lua_State* ) {
    String text = LUA::getString(2);
    int startX = LUA::getNumber<int>(2);
    int baselineY = LUA::getNumber<int>(2);
    int maximumLineWidth = LUA::getNumber<int>(2);
    g->drawMultiLineText( text, startX, baselineY, maximumLineWidth );
    return 0;
}

int LGraphics::setFont ( lua_State *L ) {
    if(lua_isnumber(L,2))
        g->setFont(LUA::getNumber<float>(2));
    else
        g->setFont( *LUA::from_luce<LFont>(2) );
    return 0;
}

int LGraphics::fillRect ( lua_State* ) {
    g->fillRect(LUA::getRectangle<float>(2));
    // TODO: fillRect( RectangleList<float> )
}

int LGraphics::setPixel ( lua_State* ) {
    int x = LUA::getNumber<int>(2);
    int y = LUA::getNumber<int>(2);
    g->setPixel( x, y );
    return 0;
}

int LGraphics::drawSingleLineText ( lua_State* ) {
    String text = LUA::getString(2);
    int startX = LUA::getNumber<int>(2);
    int baselineY = LUA::getNumber<int>(2);
    Justification justification = LUA::getNumber<int>(2);
    g->drawSingleLineText( text, startX, baselineY, justification );
    return 0;
}

int LGraphics::drawVerticalLine ( lua_State* ) {
    int x = LUA::getNumber<int>(2);
    float top = LUA::getNumber<float>(2);
    float bottom = LUA::getNumber<float>(2);
    g->drawVerticalLine( x, top, bottom );
    return 0;
}

int LGraphics::drawRect ( lua_State* ) {
    Rectangle<float> rectangle ( LUA::getRectangle<float>(2) );
    int lineThickness = LUA::checkAndGetNumber<int>(2, 1);
    g->drawRect( rectangle, lineThickness );
    return 0;
}

int LGraphics::drawRoundedRectangle ( lua_State* ) {
    Rectangle<float> rectangle ( LUA::getRectangle<float>(2) );
    float cornerSize = LUA::getNumber<float>(2);
    float lineThickness = LUA::getNumber<float>(2);
    g->drawRoundedRectangle( rectangle, cornerSize, lineThickness );
    return 0;
}

int LGraphics::drawLine ( lua_State *L ) {
    Line<float> line = LUA::getLine<float>(2);
    if(lua_isnumber(L,2)) 
        g->drawLine( line, LUA::getNumber<float>(2) );
    else
        g->drawLine( line );

    return 0;
}

int LGraphics::setOpacity ( lua_State* ) {
    g->setOpacity(LUA::getNumber<float>());
    return 0;
}

int LGraphics::drawArrow ( lua_State* ) {
    Line<float> line = LUA::getLine<float>(2);
    float lineThickness = LUA::getNumber<float>(2);
    float arrowheadWidth = LUA::getNumber<float>(2);
    float arrowheadLength = LUA::getNumber<float>(2);
    g->drawArrow( line, lineThickness, arrowheadWidth, arrowheadLength );
    return 0;
}

int LGraphics::drawDashedLine ( lua_State* ) {
    Line<float> line = LUA::getLine<float>(2);
    // TODO: 
    // a series of lengths to specify the on/off lengths 
    // - e.g. { 4, 5, 6, 7 } will draw a line of 4 pixels, skip 5 pixels, 
    // draw 6 pixels, skip 7 pixels, and then repeat
    //float* dashLengths = LUA::getNumber<float>(2);
    Array<float> dashes = LUA::getList<float>(2);

    float dashLengths[ dashes.size() ];
    for(int i=0; i<dashes.size(); ++i)
        dashLengths[i] = dashes[i];

    int numDashLengths = LUA::getNumber<int>(2);
    float lineThickness = LUA::checkAndGetNumber<float>(2, 1.0f);
    int dashIndexToStartFrom = LUA::checkAndGetNumber<int>(2, 0);
    g->drawDashedLine( line, dashLengths, numDashLengths, lineThickness, dashIndexToStartFrom );

    //LUA::TODO_OBJECT( "drawDashedLine,  line, dashLengths, numDashLengths, lineThickness, dashIndexToStartFrom " );
    //lua_settop(LUA::Get(), 1); // added by TODO
    return 0;
}

int LGraphics::fillPath ( lua_State *L ) {
    Path path = *LUA::from_luce<LPath>(2);
    AffineTransform transform = AffineTransform::identity;
    if(! lua_isnoneornil(L,2))
        transform = LAffineTransform::fromLuce( LUA::getList<float>(2) );
    g->fillPath( path, transform );
    return 0;
}

int LGraphics::addTransform ( lua_State* ) {
    g->addTransform( LAffineTransform::fromLuce( LUA::getList<float>(2) ) );
    return 0;
}


// TODO
// getters
int LGraphics::strokePath ( lua_State* ) {
    // Path path = *LUA::from_luce<LPath>(2); // TODO;
    // PathStrokeType strokeType = *LUA::from_luce<LPathStrokeType>(2); // TODO;
    // AffineTransform transform = *LUA::from_luce<LAffineTransform>(2); // TODO;
    //g->strokePath( path, strokeType, transform );
    LUA::TODO_OBJECT( "strokePath,  path, strokeType, transform " );
    lua_settop(LUA::Get(), 1); // added by TODO
    return 0;
}

int LGraphics::setFillType ( lua_State* ) {
    //g->setFillType(*LUA::from_luce<LFillType>(2); // TODO);
    LUA::TODO_OBJECT( "setFillType, *LUA::from_luce<LFillType>(2); // TODO" );
    lua_settop(LUA::Get(), 1); // added by TODO
    return 0;
}

int LGraphics::fillRectList ( lua_State* ) {
    // override
    //g->fillRectList(*LUA::from_luce<LRectangleList>(2); // TODO);
    LUA::TODO_OBJECT( "fillRectList, *LUA::from_luce<LRectangleList>(2); // TODO" );
    lua_settop(LUA::Get(), 1); // added by TODO
    return 0;
    // override
    //g->fillRectList(*LUA::from_luce<LRectangleList>(2); // TODO);
}

int LGraphics::setGradientFill ( lua_State* ) {
    //g->setGradientFill(*LUA::from_luce<LColourGradient>(2); // TODO);
    LUA::TODO_OBJECT( "setGradientFill, *LUA::from_luce<LColourGradient>(2); // TODO" );
    lua_settop(LUA::Get(), 1); // added by TODO
    return 0;
}

int LGraphics::setImageResamplingQuality ( lua_State* ) {
    //g->setImageResamplingQuality(*LUA::from_luce<LResamplingQuality>(2); // TODO);
    LUA::TODO_OBJECT( "setImageResamplingQuality, *LUA::from_luce<LResamplingQuality>(2); // TODO" );
    lua_settop(LUA::Get(), 1); // added by TODO
    return 0;
}

int LGraphics::drawImageAt ( lua_State* ) {
    // Image imageToDraw = *LUA::from_luce<LImage>(2); // TODO;
    int topLeftX = LUA::getNumber<int>(2);
    int topLeftY = LUA::getNumber<int>(2);
    bool fillAlphaChannelWithCurrentBrush = LUA::checkAndGetBoolean(2, false);
    //g->drawImageAt( imageToDraw, topLeftX, topLeftY, fillAlphaChannelWithCurrentBrush );
    LUA::TODO_OBJECT( "drawImageAt,  imageToDraw, topLeftX, topLeftY, fillAlphaChannelWithCurrentBrush " );
    lua_settop(LUA::Get(), 1); // added by TODO
    return 0;
}

int LGraphics::drawImage ( lua_State* ) {
    // Image imageToDraw = *LUA::from_luce<LImage>(2); // TODO;
    int destX        = LUA::getNumber<int>(2);
    int destY        = LUA::getNumber<int>(2);
    int destWidth    = LUA::getNumber<int>(2);
    int destHeight   = LUA::getNumber<int>(2);
    int sourceX      = LUA::getNumber<int>(2);
    int sourceY      = LUA::getNumber<int>(2);
    int sourceWidth  = LUA::getNumber<int>(2);
    int sourceHeight = LUA::getNumber<int>(2);
    bool fillAlphaChannelWithCurrentBrush = LUA::checkAndGetBoolean(2, false);
    //g->drawImage( imageToDraw, destX, destY, destWidth, destHeight, sourceX, sourceY, sourceWidth, sourceHeight, fillAlphaChannelWithCurrentBrush );
    LUA::TODO_OBJECT( "drawImage,  imageToDraw, destX, destY, destWidth, destHeight, sourceX, sourceY, sourceWidth, sourceHeight, fillAlphaChannelWithCurrentBrush " );
    lua_settop(LUA::Get(), 1); // added by TODO
    return 0;
}

int LGraphics::drawImageWithin ( lua_State* ) {
    // Image imageToDraw = *LUA::from_luce<LImage>(2); // TODO;
    int destX = LUA::getNumber<int>(2);
    int destY = LUA::getNumber<int>(2);
    int destWidth = LUA::getNumber<int>(2);
    int destHeight = LUA::getNumber<int>(2);
    // RectanglePlacement placementWithinTarget = *LUA::from_luce<LRectanglePlacement>(2); // TODO;
    bool fillAlphaChannelWithCurrentBrush = LUA::checkAndGetBoolean(2, false);
    //g->drawImageWithin( imageToDraw, destX, destY, destWidth, destHeight, placementWithinTarget, fillAlphaChannelWithCurrentBrush );
    LUA::TODO_OBJECT( "drawImageWithin,  imageToDraw, destX, destY, destWidth, destHeight, placementWithinTarget, fillAlphaChannelWithCurrentBrush " );
    lua_settop(LUA::Get(), 1); // added by TODO
    return 0;
}

int LGraphics::drawImageTransformed ( lua_State* ) {
    // Image imageToDraw = *LUA::from_luce<LImage>(2); // TODO;
    // AffineTransform transform = *LUA::from_luce<LAffineTransform>(2); // TODO;
    bool fillAlphaChannelWithCurrentBrush = LUA::checkAndGetBoolean(2, false);
    //g->drawImageTransformed( imageToDraw, transform, fillAlphaChannelWithCurrentBrush );
    LUA::TODO_OBJECT( "drawImageTransformed,  imageToDraw, transform, fillAlphaChannelWithCurrentBrush " );
    lua_settop(LUA::Get(), 1); // added by TODO
    return 0;
}

int LGraphics::setTiledImageFill ( lua_State* ) {
    // Image imageToUse = *LUA::from_luce<LImage>(2); // TODO;
    int anchorX = LUA::getNumber<int>(2);
    int anchorY = LUA::getNumber<int>(2);
    float opacity = LUA::getNumber<float>(2);
    //g->setTiledImageFill( imageToUse, anchorX, anchorY, opacity );
    LUA::TODO_OBJECT( "setTiledImageFill,  imageToUse, anchorX, anchorY, opacity " );
    lua_settop(LUA::Get(), 1); // added by TODO
    return 0;
}

int LGraphics::getInternalContext ( lua_State* ) {
    // CHECK
    // return LUA::storeAndReturnUserdata<LLowLevelGraphicsContext>( new LLowLevelGraphicsContext(LUA::Get(),
    //     g->getInternalContext()
    // ));
    lua_settop(LUA::Get(), 1); // added by TODO
    return LUA::TODO_OBJECT( "LowLevelGraphicsContext getInternalContext()" );
}
