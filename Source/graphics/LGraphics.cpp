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
    method( LGraphics, setColour ),
    
    method( LGraphics, ScopedSaveState ),
    {0,0}
};

/////// ctor/dtor
const Luna<LGraphics>::StaticType LGraphics::statics[] = {
    {0,0}
};

LGraphics::LGraphics(lua_State *L)
    : LBase(L, "LGraphics", true),
      Graphics(Image::null)
{
    // invalid, just there for luna
}

LGraphics::LGraphics(lua_State *L, juce::Graphics& class_)
    : LBase(L, "LGraphics", true),
      Graphics(class_.getInternalContext())
{
}

LGraphics::LGraphics(lua_State *L, juce::Image& img)
    : LBase(L, "LGraphics", true),
      Graphics(img)
{
}

LGraphics::~LGraphics() {
}

int LGraphics::lnew(lua_State *L) {
    if(lua_isnoneornil(L,2))
        return LUA::storeAndReturnUserdata<LGraphics>( new LGraphics(L) );
    else if( LUCE::luce_isofclass(LImage, 2) )
        return LUA::storeAndReturnUserdata<LGraphics>( new LGraphics(L, *LUA::from_luce<LImage>(2)) );
    return 0;
}

Graphics* LGraphics::getGraphics() {
    return *this;
}
LGraphics::operator Graphics* () const {
    return *this;
}
//LGraphics::operator const Graphics& () const {
//    return *(*this);
//}

int LGraphics::ScopedSaveState(lua_State *L) {
    Graphics::ScopedSaveState state( *this );
    lua_pushlightuserdata(L, (void*)&state);
    return 1;
}

/////// getters
int LGraphics::isVectorDevice ( lua_State* ) {
    return LUA::returnBoolean(Graphics::isVectorDevice() );
}

int LGraphics::getCurrentFont ( lua_State *L ) {
    return LUA::storeAndReturnUserdata<LFont>( new LFont(L,
         Graphics::getCurrentFont()
    ));
}

int LGraphics::getClipBounds ( lua_State* ) {
    return LUCE::luce_pushtable(Graphics::getClipBounds() );
}

int LGraphics::reduceClipRegion ( lua_State* L ) {
    if(lua_isnumber(L, 2)) {
        int x = LUA::getNumber<int>(2);
        int y = LUA::getNumber<int>(2);
        int w = LUA::getNumber<int>(2);
        int h = LUA::getNumber<int>(2);
        return LUA::returnBoolean(Graphics::reduceClipRegion(x,y,w,h));
    }
    else if(LUCE::luce_isoftype(LRectangle, 2)) {
        return LUA::returnBoolean(Graphics::reduceClipRegion( LUCE::luce_torectangle<int>(2) ) );
    }
    else if(LUCE::luce_isoftype(LRectangleList, 2)) {
        return LUA::returnBoolean(Graphics::reduceClipRegion( LUCE::luce_torectanglelist<int>(2) ) );
    }
    else if(LUCE::luce_isofclass(LPath, 2)) {
        Path path = *LUA::from_luce<LPath>(2);
        AffineTransform aff = AffineTransform::identity;
        if(LUCE::luce_isofclass(LAffineTransform,2))
            aff = LUCE::luce_toaffinetransform(2);
        return LUA::returnBoolean(Graphics::reduceClipRegion( path, aff ));
    }
    else if(LUCE::luce_isofclass(LImage, 2)) {
        Image img = *LUA::from_luce<LImage>(2);
        AffineTransform aff = AffineTransform::identity;
        if(LUCE::luce_isofclass(LAffineTransform,2))
            aff = LUCE::luce_toaffinetransform(2);
        return LUA::returnBoolean(Graphics::reduceClipRegion( img, aff ));
    }
    else if(lua_istable(L,2)) {
        return LUA::returnBoolean(Graphics::reduceClipRegion( LUCE::luce_torectangle<int>(2) ) );
    }
    // error
    LUCE::luce_error(lua_pushfstring(L,
            "LGraphics: reduceClipRegion: wrong arguments.\nExpected:\n %s,\n %s,\n %s,\n %s",
            "(LRectangle)",
            "(LRectangleList)",
            "(LPath, [LAffineTransform])",
            "(LImage, [LAffineTransform])"));
}

int LGraphics::clipRegionIntersects ( lua_State* ) {
    return LUA::returnBoolean(Graphics::clipRegionIntersects( LUA::getRectangle(2) ) );
}

int LGraphics::isClipEmpty ( lua_State* ) {
    return LUA::returnBoolean(Graphics::isClipEmpty() );
}

/////// setters
int LGraphics::resetToDefaultState ( lua_State* ) {
    Graphics::resetToDefaultState();
    return 0;
}

int LGraphics::fillAll ( lua_State *L ) {
    if(lua_isnoneornil(L, 2))
        Graphics::fillAll();
    else if (lua_isstring(L, 2))
        Graphics::fillAll( Colours::findColourForName( LUA::getString(2), Colours::black ) );
    else
        Graphics::fillAll( *LUA::from_luce<LColour>(2) );
    return 0;
}

int LGraphics::fillEllipse ( lua_State* ) {
     Graphics::fillEllipse(LUA::getRectangle<float>(2));
    return 0;
}

int LGraphics::drawEllipse ( lua_State* L ) {
    Rectangle<float> area;
    if(lua_isnumber(L,2)) {
        float x = LUA::getNumber<float>(2);
        float y = LUA::getNumber<float>(2);
        float w = LUA::getNumber<float>(2);
        float h = LUA::getNumber<float>(2);
        area = {x,y,w,h};
    //} else if(LUCE::luce_isoftype(LRectangle,2)) {
    } else if(lua_istable(L,2)) { // LRectangle
        area = LUCE::luce_torectangle<float>(2);
    } else {
        // error
        LUCE::luce_error(lua_pushfstring(L,
                "LGraphics: drawEllipse: wrong arguments.\nExpected:\n %s,\n %s",
                "(x,y,w,h)",
                "(LRectangle)"));
    }
    float lineThickness = LUA::getNumber<float>(2);
    Graphics::drawEllipse( area, lineThickness );
    return 0;
}

int LGraphics::saveState ( lua_State* ) {
    Graphics::saveState();
    return 0;
}

int LGraphics::excludeClipRegion ( lua_State* ) {
    Graphics::excludeClipRegion(LUCE::luce_torectangle<int>(2));
    return 0;
}

int LGraphics::endTransparencyLayer ( lua_State* ) {
    Graphics::endTransparencyLayer();
    return 0;
}

int LGraphics::fillCheckerBoard ( lua_State *L ) {
    Rectangle<int> area = LUCE::luce_torectangle<int>(2);
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

    Graphics::fillCheckerBoard( area, checkWidth, checkHeight, colour1, colour2 );
    return 0;
}

int LGraphics::drawHorizontalLine ( lua_State* ) {
    int y = LUA::getNumber<int>(2);
    float left = LUA::getNumber<float>(2);
    float right = LUA::getNumber<float>(2);
    Graphics::drawHorizontalLine( y, left, right );
    return 0;
}

int LGraphics::setOrigin ( lua_State* ) {
    Graphics::setOrigin( LUA::getPoint(2) );
    return 0;
}

int LGraphics::beginTransparencyLayer ( lua_State* ) {
    Graphics::beginTransparencyLayer(LUA::getNumber<float>());
    return 0;
}

int LGraphics::restoreState ( lua_State* ) {
    Graphics::restoreState();
    return 0;
}

int LGraphics::drawText ( lua_State *L ) {
    String text = LUA::getString(2);
    Rectangle<float> area;
    if(lua_isnumber(L,2)) {
        float x = LUA::getNumber<float>(2); 
        float y = LUA::getNumber<float>(2);
        float w = LUA::getNumber<float>(2); 
        float h = LUA::getNumber<float>(2);
        area = { x, y, w, h };
    }
    //else if(LUCE::luce_isoftype(LRectangle,2)) {
    else if(lua_istable(L,2)) {
        area = LUCE::luce_torectangle<float>(2);
    }
    else {
        // error
        LUCE::luce_error(lua_pushfstring(L,
            "LGraphics: drawEllipse: wrong arguments.\nExpected:\n %s,\n %s",
            "(x,y,w,h)",
            "(LRectangle)"));
    }
    Justification justificationType = (Justification)LUA::getNumber<int>(2);
    bool useEllipsesIfTooBig = LUA::getBoolean(2);
    Graphics::drawText( text, area, justificationType, useEllipsesIfTooBig );
    return 0;
}

int LGraphics::drawFittedText ( lua_State *L ) {
    String text = LUA::getString(2);
    Rectangle<int> area;
    if(!lua_isnumber(L, 2)) {
        int x = LUA::getNumber<int>(2); 
        int y = LUA::getNumber<int>(2);
        int w = LUA::getNumber<int>(2); 
        int h = LUA::getNumber<int>(2);
        area = { x, y, w, h };
    }
    //else if(LUCE::luce_isoftype(LRectangle,2)) {
    else if(lua_istable(L,2)) {
        area = LUCE::luce_torectangle<int>(2);
    }
    else {
        // error
        LUCE::luce_error(lua_pushfstring(L,
            "LGraphics: drawEllipse: wrong arguments.\nExpected:\n %s,\n %s",
            "(x,y,w,h)",
            "(LRectangle)"));
    }
    Justification justificationFlags = LUA::getNumber<int>(2);
    int maximumNumberOfLines = LUA::getNumber<int>(2);
    float minimumHorizontalScale = LUA::checkAndGetNumber<float>(2, 0.7f);
    Graphics::drawFittedText( text, area, justificationFlags, maximumNumberOfLines, minimumHorizontalScale );
    return 0;
}

int LGraphics::fillRoundedRectangle ( lua_State *L ) {
    Rectangle<float> area;
    if(!lua_isnumber(L, 2)) {
        float x = LUA::getNumber<float>(2); 
        float y = LUA::getNumber<float>(2);
        float w = LUA::getNumber<float>(2); 
        float h = LUA::getNumber<float>(2);
        area = { x, y, w, h };
    }
    //else if(LUCE::luce_isoftype(LRectangle,2)) {
    else if(lua_istable(L,2)) {
        area = LUCE::luce_torectangle<float>(2);
    }
    else {
        // error
        LUCE::luce_error(lua_pushfstring(L,
            "LGraphics: drawEllipse: wrong arguments.\nExpected:\n %s,\n %s",
            "(x,y,w,h)",
            "(LRectangle)"));
    }
    float cornerSize = LUCE::luce_tonumber<float>(2);
    Graphics::fillRoundedRectangle( area, cornerSize );
    return 0;
}

int LGraphics::drawMultiLineText ( lua_State* ) {
    String text = LUA::getString(2);
    int startX = LUA::getNumber<int>(2);
    int baselineY = LUA::getNumber<int>(2);
    int maximumLineWidth = LUA::getNumber<int>(2);
    Graphics::drawMultiLineText( text, startX, baselineY, maximumLineWidth );
    return 0;
}

int LGraphics::setFont ( lua_State *L ) {
    if(lua_isnumber(L,2))
        Graphics::setFont(LUA::getNumber<float>(2));
    else if(LUCE::luce_isofclass(LFont, 2))
        Graphics::setFont( *LUA::from_luce<LFont>(2) );
    else
        LUCE::luce_error(lua_pushfstring(L,
            "LGraphics: setFont: wrong arguments.\nExpected:\n %s, %s\n got %s",
            "(font size)",
            "(LFong)",
            lua_typename(L, lua_type(L, 2))));
    return 0;
}

int LGraphics::fillRect ( lua_State *L ) {
    Rectangle<float> r;
    if(lua_isnumber(L,2) && lua_isnumber(L,3) && lua_isnumber(L,4) && lua_isnumber(L,5)) {
        float x = LUA::getNumber<float>(2);
        float y = LUA::getNumber<float>(2);
        float w = LUA::getNumber<float>(2);
        float h = LUA::getNumber<float>(2);
        r = {x,y,w,h};
    }
    else if( LUCE::luce_isoftype(LRectangle, 2) || lua_istable(L, 2) ) {
        r = LUCE::luce_torectangle<float>(2);
    }
    else {
        LUCE::luce_error(lua_pushfstring(L, 
            "LGraphics: fillRect: wrong arguments.\nExpected:\n %s, %s",
            "(x,y,w,h)",
            "(LRectangle)"));
    }
    Graphics::fillRect( r );
    return 0;
}

int LGraphics::setPixel ( lua_State* ) {
    int x = LUA::getNumber<int>(2);
    int y = LUA::getNumber<int>(2);
    Graphics::setPixel( x, y );
    return 0;
}

int LGraphics::drawSingleLineText ( lua_State* ) {
    String text = LUA::getString(2);
    int startX = LUA::getNumber<int>(2);
    int baselineY = LUA::getNumber<int>(2);
    Justification justification = LUA::getNumber<int>(2);
    Graphics::drawSingleLineText( text, startX, baselineY, justification );
    return 0;
}

int LGraphics::drawVerticalLine ( lua_State* ) {
    int x = LUA::getNumber<int>(2);
    float top = LUA::getNumber<float>(2);
    float bottom = LUA::getNumber<float>(2);
    Graphics::drawVerticalLine( x, top, bottom );
    return 0;
}

int LGraphics::drawRect( lua_State* L) {
    Rectangle<float> r;
    if(lua_isnumber(L,2)) {
        float x = LUA::getNumber<float>(2);
        float y = LUA::getNumber<float>(2);
        float w = LUA::getNumber<float>(2);
        float h = LUA::getNumber<float>(2);
        r = {x,y,w,h};
    } else if(lua_istable(L,2)) {
        r = LUCE::luce_torectangle<float>(2);
    }
    else {
        LUCE::luce_error(lua_pushfstring(L, 
            "LGraphics: drawRect: wrong arguments.\nExpected:\n %s, %s",
            "(x,y,w,h,[thickness])",
            "(LRectangle,[thickness])"));
    }
    int lineThickness = LUA::checkAndGetNumber<int>(2, 1);
    Graphics::drawRect( r, lineThickness );
    return 0;
}

int LGraphics::drawRoundedRectangle( lua_State* L ) {
    Rectangle<float> r;
    if(lua_isnumber(L,2)) {
        float x = LUA::getNumber<float>(2);
        float y = LUA::getNumber<float>(2);
        float w = LUA::getNumber<float>(2);
        float h = LUA::getNumber<float>(2);
        r = {x,y,w,h};
    } 
    else if(lua_istable(L,2)) {
        r = LUCE::luce_torectangle<float>(2);
    }
    else {
        LUCE::luce_error(lua_pushfstring(L,
            "LGraphics: drawRect: wrong arguments.\nExpected:\n %s, %s",
            "(x,y,w,h,cornerSize,thickness)",
            "(LRectangle,cornerSize,thickness)"));
    }
    if(!lua_isnumber(L,2) || !lua_isnumber(L,3))
        LUCE::luce_error(lua_pushfstring(L,
            "LGraphics: drawRect: wrong arguments.\nExpected:\n %s, %s",
            "(x,y,w,h,cornerSize,thickness)",
            "(LRectangle,cornerSize,thickness)"));

    float cornerSize = LUA::getNumber<float>(2);
    float lineThickness = LUA::getNumber<float>(2);
    Graphics::drawRoundedRectangle( r, cornerSize, lineThickness );
    return 0;
}

int LGraphics::drawLine( lua_State *L ) {
    Line<float> line;
    if(lua_istable(L,2))
        line = LUCE::luce_toline<float>(2);
    else if(lua_gettop(L)>4) {
        float x1,y1,x2,y2;
        x1 = LUA::getNumber<float>(2); y1 = LUA::getNumber<float>(2);
        x2 = LUA::getNumber<float>(2); y2 = LUA::getNumber<float>(2);
        line = Line<float>(x1,y1,x2,y2);
    }
    else
        LUCE::luce_error(lua_pushfstring(L,
            "LGraphics: drawLine: wrong arguments.\nExpected:\n %s,\n %s",
                "(LLine,[thickness])",
                "(x1,y1,x2,y2,[thickness])"));

    float thickness = LUA::checkAndGetNumber<float>(2, 1.0f);
    Graphics::drawLine(line, thickness);
    return 0;
}

int LGraphics::setOpacity ( lua_State* ) {
    Graphics::setOpacity(LUA::getNumber<float>());
    return 0;
}

int LGraphics::setColour ( lua_State *L ) {
    if(lua_istable(L,2))
        Graphics::setColour( *LUA::from_luce<LColour>(2) );
    else
        Graphics::setColour( Colours::findColourForName( LUA::getString(2), Colours::black ) );
    return 0;
}

int LGraphics::drawArrow ( lua_State* ) {
    Line<float> line = LUCE::luce_toline<float>(2);
    float lineThickness = LUA::getNumber<float>(2);
    float arrowheadWidth = LUA::getNumber<float>(2);
    float arrowheadLength = LUA::getNumber<float>(2);
    Graphics::drawArrow( line, lineThickness, arrowheadWidth, arrowheadLength );
    return 0;
}

int LGraphics::drawDashedLine(lua_State* L) {
    if(!lua_gettop(L)>3 
            || (!LUCE::luce_isoftype(LLine,2) &&!lua_istable(L,2)) 
            || !lua_istable(L,2))
    {
        LUCE::luce_error(lua_pushfstring(L,
            "LGraphics: drawDashedLine: wrong arguments.\nExpected:\n %s",
            "(LLine, {even list of numbers}, [thickness], [startIndex])"));
    }
    Line<float> line = LUCE::luce_toline<float>(2);
    size_t n = lua_objlen(L,2);
    if((n%2)!=0)
        LUCE::luce_error("LGraphics: drawDashedLine: list of numbers isn't even.");
    float dashLengths[n];
    for(int i=0; i<n; ++i) {
        lua_pushnumber(L,i+1);
        lua_gettable(L,2);
        dashLengths[i] = lua_tonumber(L,-1);
    }
    lua_pop(L,n);
    lua_remove(L,2);

    float lineThickness = LUA::checkAndGetNumber<float>(2, 1.0f);
    int dashIndexToStartFrom = LUA::checkAndGetNumber<int>(2, 0);
    Graphics::drawDashedLine( line, dashLengths, n, lineThickness, dashIndexToStartFrom );
    return 0;
}

int LGraphics::fillPath(lua_State* L) {
    Path path = *LUA::from_luce<LPath>(2);
    AffineTransform transform = AffineTransform::identity;
    if(LUCE::luce_isoftype(LAffineTransform,2) || lua_istable(L,2))
        transform = LUCE::luce_toaffinetransform(2);
    Graphics::fillPath( path, transform );
    return 0;
}

int LGraphics::addTransform(lua_State*) {
    Graphics::addTransform( LUCE::luce_toaffinetransform(2) );
    return 0;
}

int LGraphics::setImageResamplingQuality ( lua_State* ) {
    Graphics::setImageResamplingQuality ( (Graphics::ResamplingQuality)LUA::getNumber<int>(2) );
    return 0;
}

int LGraphics::drawImageAt ( lua_State* ) {
    Image imageToDraw = *LUA::from_luce<LImage>(2);
    int topLeftX = LUA::getNumber<int>(2);
    int topLeftY = LUA::getNumber<int>(2);
    bool fillAlphaChannelWithCurrentBrush = LUA::checkAndGetBoolean(2, false);
    Graphics::drawImageAt( imageToDraw, topLeftX, topLeftY, fillAlphaChannelWithCurrentBrush );
    return 0;
}

int LGraphics::drawImage ( lua_State* ) {
    Image imageToDraw = *LUA::from_luce<LImage>(2);
    int destX        = LUA::getNumber<int>(2);
    int destY        = LUA::getNumber<int>(2);
    int destWidth    = LUA::getNumber<int>(2);
    int destHeight   = LUA::getNumber<int>(2);
    int sourceX      = LUA::getNumber<int>(2);
    int sourceY      = LUA::getNumber<int>(2);
    int sourceWidth  = LUA::getNumber<int>(2);
    int sourceHeight = LUA::getNumber<int>(2);
    bool fillAlphaChannelWithCurrentBrush = LUA::checkAndGetBoolean(2, false);
    Graphics::drawImage( imageToDraw, destX, destY, destWidth, destHeight, sourceX, sourceY, sourceWidth, sourceHeight, fillAlphaChannelWithCurrentBrush );
    return 0;
}

int LGraphics::drawImageWithin(lua_State*) {
    Image imageToDraw = *LUA::from_luce<LImage>(2);
    int destX = LUA::getNumber<int>(2);
    int destY = LUA::getNumber<int>(2);
    int destWidth = LUA::getNumber<int>(2);
    int destHeight = LUA::getNumber<int>(2);
    RectanglePlacement placementWithinTarget = LUCE::luce_torectangleplacement(2);
    bool fillAlphaChannelWithCurrentBrush = LUA::checkAndGetBoolean(2, false);
    Graphics::drawImageWithin( imageToDraw, destX, destY, destWidth, destHeight, 
                            placementWithinTarget, fillAlphaChannelWithCurrentBrush );
    return 0;
}

int LGraphics::drawImageTransformed(lua_State*) {
    Image imageToDraw = *LUA::from_luce<LImage>(2);
    AffineTransform transform = LUCE::luce_toaffinetransform(2);
    bool fillAlphaChannelWithCurrentBrush = LUA::checkAndGetBoolean(2, false);
    Graphics::drawImageTransformed( imageToDraw, transform, fillAlphaChannelWithCurrentBrush );
    return 0;
}

int LGraphics::setTiledImageFill(lua_State*) {
    Image imageToUse = *LUA::from_luce<LImage>(2);
    int anchorX = LUA::getNumber<int>(2);
    int anchorY = LUA::getNumber<int>(2);
    float opacity = LUA::getNumber<float>(2);
    Graphics::setTiledImageFill( imageToUse, anchorX, anchorY, opacity );
    return 0;
}

int LGraphics::strokePath(lua_State* L) {
    Path path = *LUA::from_luce<LPath>(2);
    PathStrokeType strokeType = *LUA::from_luce<LPathStrokeType>(2);
    AffineTransform transform = AffineTransform::identity;
    if(!lua_isnoneornil(L,2))
        transform = LUCE::luce_toaffinetransform(2);

    Graphics::strokePath( path, strokeType, transform );
    return 0;
}

// setters
int LGraphics::setFillType(lua_State* L) {
    Graphics::setFillType(*LUA::from_luce<LFillType>(2));
    return 0;
}

int LGraphics::fillRectList(lua_State* L) {
    if(LUCE::luce_isoftype(LRectangleList,2)) {
        Graphics::fillRectList( LUCE::luce_torectanglelist<float>(2) );
    }
    else {
        LUCE::luce_error(lua_pushfstring(L, 
            "LGraphics: fillRectList: wrong arguments.\nExpected:\n %s\n got %s",
            "(LRectangleList)",
            lua_typename(L,lua_type(L,2)) ));
    }
    return 0;
    /*
    LUCE::NumType t = LUCE::luce_numtype(2);
    if( LUCE::luce_isnumtype(int, t) ) {
        RectangleList<int> rl = LUCE::luce_torectanglelist(2);
        Graphics::fillRectList( rl );
    } else if(LUCE::luce_isnumtype(float, t)) {
        RectangleList<float> rl = LUCE::luce_torectanglelist<float>(2);
        Graphics::fillRectList( rl );
    } else {
        std::cout << "ERROR: unknown type for rl: " << t << std::endl;
    }
    return 0;
    */
}

int LGraphics::setGradientFill(lua_State* L) {
    Colour colour1, colour2;
    float x1, y1, x2, y2;
    bool isRadial;
    if(lua_isstring(L, 2)) {
        colour1 = Colours::findColourForName( LUA::getString(2), Colours::black );
    } else {
        colour1 = *LUA::from_luce<LColour>(2);
    }
    x1 = LUA::getNumber<float>(2);
    y1 = LUA::getNumber<float>(2);
    if(lua_isstring(L, 2)) {
        colour2 = Colours::findColourForName( LUA::getString(2), Colours::black );
    } else {
        colour1 = *LUA::from_luce<LColour>(2);
    }
    x2 = LUA::getNumber<float>(2);
    y2 = LUA::getNumber<float>(2);
    isRadial = LUA::getBoolean(2);

    ColourGradient cg(colour1, x1, y1, colour2, x2, y2, isRadial);
    Graphics::setGradientFill( cg );
    return 0;
}

// probably won't do
int LGraphics::getInternalContext ( lua_State* ) {
    // CHECK
    // return LUA::storeAndReturnUserdata<LLowLevelGraphicsContext>( new LLowLevelGraphicsContext(LUA::Get(),
    //     Graphics::getInternalContext()
    // ));
    lua_settop(LUA::Get(), 1); // added by TODO
    return LUA::TODO_OBJECT( "LowLevelGraphicsContext getInternalContext()" );
}
