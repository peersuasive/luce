/************************************************************

 LPath.cpp

    @author Christophe Berbizier (cberbizier@peersuasive.com)
    @license GPLv3
    @copyright 


(c) 2014, Peersuasive Technologies

*************************************************************/

#include "LPath_inh.h"

////// static methods
const char LPath::className[] = "LPath";
const Luna<LPath>::PropertyType LPath::properties[] = {
    {"usingNonZeroWinding", &LPath::isUsingNonZeroWinding, &LPath::setUsingNonZeroWinding},
    {0,0}
};
const Luna<LPath>::FunctionType LPath::methods[] = {
    method( LPath, isEmpty ),
    method( LPath, createPathWithRoundedCorners ),
    method( LPath, getPointAlongPath ),
    method( LPath, getLength ),
    method( LPath, intersectsLine ),
    method( LPath, isUsingNonZeroWinding ),
    method( LPath, setUsingNonZeroWinding ),
    method( LPath, getBounds ),
    method( LPath, getBoundsTransformed ),
    method( LPath, getClippedLine ),
    method( LPath, getCurrentPosition ),
    method( LPath, getTransformToScaleToFit ),
    method( LPath, toString ),
    method( LPath, getNearestPoint ),
    method( LPath, startNewSubPath ),
    method( LPath, addArc ),
    method( LPath, addCentredArc ),
    method( LPath, addRectangle ),
    method( LPath, addTriangle ),
    method( LPath, restoreFromString ),
    method( LPath, addPieSegment ),
    method( LPath, lineTo ),
    method( LPath, closeSubPath ),
    method( LPath, addQuadrilateral ),
    method( LPath, addLineSegment ),
    method( LPath, writePathToStream ),
    method( LPath, loadPathFromStream ),
    method( LPath, loadPathFromData ),
    method( LPath, addStar ),
    method( LPath, scaleToFit ),
    method( LPath, addPath ),
    method( LPath, applyTransform ),
    method( LPath, quadraticTo ),
    method( LPath, swapWithPath ),
    method( LPath, addPolygon ),
    method( LPath, addBubble ),
    method( LPath, addRoundedRectangle ),
    method( LPath, addEllipse ),
    method( LPath, cubicTo ),
    method( LPath, clear ),
    method( LPath, addArrow ),
    {0,0}
};

/////// ctor/dtor
const Luna<LPath>::StaticType LPath::statics[] = {
    {0,0}
};

LPath::LPath(lua_State *L)
    : LBase(L, "LPath", true),
      Path()
{
}

LPath::LPath(lua_State *L, const Path& class_)
    : LBase(L, "LPath", true),
      Path( class_ )
{
}

LPath::~LPath() {}

/////// getters/setters
int LPath::isUsingNonZeroWinding ( lua_State* ) {
    return LUA::returnBoolean( Path::isUsingNonZeroWinding() );
}
int LPath::setUsingNonZeroWinding ( lua_State* ) {
    Path::setUsingNonZeroWinding(LUA::getBoolean());
    return 0;
}

/////// getters
int LPath::isEmpty ( lua_State* ) {
    return LUA::returnBoolean( Path::isEmpty() );
}

int LPath::createPathWithRoundedCorners ( lua_State* ) {
    return LUA::storeAndReturnUserdata<LPath>( new LPath(LUA::Get(),
        Path::createPathWithRoundedCorners( LUA::getNumber<float>(2) )
    ));
}

int LPath::getPointAlongPath ( lua_State* ) {
    float distanceFromStart = LUA::getNumber<float>(2);
    AffineTransform transform = LAffineTransform::fromLuce( LUA::getList<float>(2) );
    return LUCE::luce_pushtable( Path::getPointAlongPath( distanceFromStart, transform ) );
}

int LPath::getLength ( lua_State* ) {
    return LUA::returnNumber( Path::getLength( LAffineTransform::fromLuce( LUA::getList<float>(2) ) ) );
}

int LPath::intersectsLine ( lua_State* ) {
    Line<float> line = LUCE::luce_toline<float>(2);
    float tolerance = LUA::checkAndGetNumber<float>(2, 1.0f);
    return LUA::returnBoolean( Path::intersectsLine( line, tolerance ) );
}

int LPath::getBounds( lua_State* ) {
    return LUCE::luce_pushtable( Path::getBounds() );
}

int LPath::getBoundsTransformed ( lua_State* ) {
    return LUCE::luce_pushtable( Path::getBoundsTransformed( LAffineTransform::fromLuce( LUA::getList<float>(2) ) ) );
}

int LPath::getClippedLine ( lua_State* ) {
    Line<float> line = LUCE::luce_toline<float>(2);
    bool keepSectionOutsidePath = LUA::getBoolean(2);
    return LUCE::luce_pushtable( Path::getClippedLine( line, keepSectionOutsidePath ) );
}

int LPath::getCurrentPosition ( lua_State* ) {
    return LUCE::luce_pushtable( Path::getCurrentPosition() );
}

int LPath::getTransformToScaleToFit ( lua_State *L ) {
    Rectangle<float> area = LUCE::luce_torectangle<float>(2);
    bool preserveProportions = LUA::getBoolean(2);
    Justification justificationType = LUA::getNumber<int>(2);
    return LUCE::luce_pushtable(
         Path::getTransformToScaleToFit( area, preserveProportions, justificationType )
    );
    //return LUA::storeAndReturnUserdata<LAffineTransform>( new LAffineTransform(L,
    //     Path::getTransformToScaleToFit( area, preserveProportions, justificationType )
    //));
}

int LPath::toString ( lua_State* ) {
    return LUA::returnString( Path::toString() );
}

int LPath::getNearestPoint ( lua_State* ) {
    Point<float> targetPoint = LUCE::luce_topoint<float>(2);
    Point<float> pointOnPath = LUCE::luce_topoint<float>(2);
    AffineTransform transform = LUCE::luce_toaffinetransform(2);
    return LUA::returnNumber( Path::getNearestPoint( targetPoint, pointOnPath, transform ) );
}

/////// setters
int LPath::startNewSubPath(lua_State*) {
    Path::startNewSubPath(LUCE::luce_topoint<float>(2));
    return 0;
}

int LPath::addArc ( lua_State* ) {
    Rectangle<float> r = LUCE::luce_torectangle<float>(2);
    float fromRadians = LUA::getNumber<float>(2);
    float toRadians = LUA::getNumber<float>(2);
    bool startAsNewSubPath = LUA::checkAndGetBoolean(2, false);
    Path::addArc( r.getX(), r.getY(), r.getWidth(), r.getHeight(), fromRadians, toRadians, startAsNewSubPath );
    return 0;
}

int LPath::addCentredArc ( lua_State* ) {
    float centreX = LUA::getNumber<float>(2);
    float centreY = LUA::getNumber<float>(2);
    float radiusX = LUA::getNumber<float>(2);
    float radiusY = LUA::getNumber<float>(2);
    float rotationOfEllipse = LUA::getNumber<float>(2);
    float fromRadians = LUA::getNumber<float>(2);
    float toRadians = LUA::getNumber<float>(2);
    bool startAsNewSubPath = LUA::checkAndGetBoolean(2, false);
    Path::addCentredArc( centreX, centreY, radiusX, radiusY, rotationOfEllipse, fromRadians, toRadians, startAsNewSubPath );
    return 0;
}

int LPath::addRectangle ( lua_State* ) {
    Path::addRectangle(LUCE::luce_torectangle<float>(2));
    return 0;
}

int LPath::addTriangle ( lua_State* ) {
    float x1 = LUA::getNumber<float>(2);
    float y1 = LUA::getNumber<float>(2);
    float x2 = LUA::getNumber<float>(2);
    float y2 = LUA::getNumber<float>(2);
    float x3 = LUA::getNumber<float>(2);
    float y3 = LUA::getNumber<float>(2);
    Path::addTriangle( x1, y1, x2, y2, x3, y3 );
    return 0;
}

int LPath::restoreFromString ( lua_State* ) {
    Path::restoreFromString(LUA::getString(2));
    return 0;
}

int LPath::addPieSegment ( lua_State* ) {
    Rectangle<float> r = LUCE::luce_torectangle<float>(2);
    float fromRadians = LUA::getNumber<float>(2);
    float toRadians = LUA::getNumber<float>(2);
    float innerCircleProportionalSize = LUA::getNumber<float>(2);
    Path::addPieSegment( r.getX(), r.getY(), r.getWidth(), r.getHeight(), 
            fromRadians, toRadians, innerCircleProportionalSize );
    return 0;
}

int LPath::lineTo ( lua_State* ) {
    Path::lineTo(LUA::getPoint<float>(2));
    return 0;
}

int LPath::closeSubPath ( lua_State* ) {
    Path::closeSubPath();
    return 0;
}

int LPath::addQuadrilateral ( lua_State* ) {
    float x1 = LUA::getNumber<float>(2);
    float y1 = LUA::getNumber<float>(2);
    float x2 = LUA::getNumber<float>(2);
    float y2 = LUA::getNumber<float>(2);
    float x3 = LUA::getNumber<float>(2);
    float y3 = LUA::getNumber<float>(2);
    float x4 = LUA::getNumber<float>(2);
    float y4 = LUA::getNumber<float>(2);
    Path::addQuadrilateral( x1, y1, x2, y2, x3, y3, x4, y4 );
    return 0;
}

int LPath::addLineSegment ( lua_State* ) {
    Line<float> line = LUCE::luce_toline<float>(2);
    float lineThickness = LUA::getNumber<float>(2);
    Path::addLineSegment( line, lineThickness );
    return 0;
}

int LPath::addStar ( lua_State* ) {
    Point<float> centre = LUCE::luce_topoint<float>(2);
    int numberOfPoints = LUA::getNumber<int>(2);
    float innerRadius = LUA::getNumber<float>(2);
    float outerRadius = LUA::getNumber<float>(2);
    float startAngle = LUA::checkAndGetNumber<float>(2, 0.0f);
    Path::addStar( centre, numberOfPoints, innerRadius, outerRadius, startAngle );
    return 0;
}

int LPath::scaleToFit ( lua_State* ) {
    float x = LUA::getNumber<float>(2);
    float y = LUA::getNumber<float>(2);
    float width = LUA::getNumber<float>(2);
    float height = LUA::getNumber<float>(2);
    bool preserveProportions = LUA::getBoolean(2);
    Path::scaleToFit( x, y, width, height, preserveProportions );
    return 0;
}

int LPath::addPath ( lua_State *L ) {
    Path *pathToAppend = LUA::from_luce<LPath>(2);
    if ( lua_isnoneornil(L, 2) )
        Path::addPath( *pathToAppend );
    else { 
        AffineTransform transformToApply = LUCE::luce_toaffinetransform(2);
        Path::addPath( *pathToAppend, transformToApply );
    }
    // clear *pathToAppend ?
    return 0;
}

int LPath::applyTransform ( lua_State* ) {
    Path::applyTransform( LUCE::luce_toaffinetransform(2) );
    return 0;
}

int LPath::quadraticTo(lua_State* L) {
    Point<float> controlPoint, endPoint;
    if(lua_isnumber(L,2)) {
        float x1 = LUA::getNumber<float>(2);
        float y1 = LUA::getNumber<float>(2);
        float x2 = LUA::getNumber<float>(2);
        float y2 = LUA::getNumber<float>(2);
        controlPoint = {x1,y1};
        endPoint = {x2,y2};
    } else {
        controlPoint = LUCE::luce_topoint<float>(2);
        endPoint = LUCE::luce_topoint<float>(2);
    }
    Path::quadraticTo( controlPoint, endPoint );
    return 0;
}

int LPath::swapWithPath ( lua_State* ) {
    Path::swapWithPath(*LUA::from_luce<LPath>(2));
    return 0;
}

int LPath::addPolygon ( lua_State* ) {
    Point<float> centre = LUCE::luce_topoint<float>(2);
    int numberOfSides = LUA::getNumber<int>(2);
    float radius = LUA::getNumber<float>(2);
    float startAngle = LUA::checkAndGetNumber<float>(2, 0.0f);
    Path::addPolygon( centre, numberOfSides, radius, startAngle );
    return 0;
}

int LPath::addBubble ( lua_State* ) {
    Rectangle<float> bodyArea = LUCE::luce_torectangle<float>(2);
    Rectangle<float> maximumArea = LUCE::luce_torectangle<float>(2);
    Point<float> arrowTipPosition = LUCE::luce_topoint<float>(2);
    float cornerSize = LUA::getNumber<float>(2);
    float arrowBaseWidth = LUA::getNumber<float>(2);
    Path::addBubble( bodyArea, maximumArea, arrowTipPosition, cornerSize, arrowBaseWidth );
    return 0;
}

int LPath::addRoundedRectangle(lua_State* L) {
    float x,y,w,h;
    Rectangle<float> r;
    if(lua_isnumber(L,2)) {
        x = LUA::getNumber<float>(2);
        y = LUA::getNumber<float>(2);
        w = LUA::getNumber<float>(2);
        h = LUA::getNumber<float>(2);
    } else if(lua_istable(L,2)) {
        Rectangle<float> r = LUCE::luce_torectangle<float>(2);
        x = r.getX();
        y = r.getY();
        w = r.getWidth();
        h = r.getHeight();
    } else {
        LUCE::luce_error(lua_pushfstring(L, 
            "LPath: addRoundedRectangle: wrong arguments.\nExpected:\n %s, %s",
            "(x,y,w,h,cornerSize,[cornerSizeY])",
            "(LRectangle,cornerSize,[cornerSizeY])"));
    }
    if(!lua_isnumber(L,2))
        LUCE::luce_error(lua_pushfstring(L, 
            "LPath: addRoundedRectangle: wrong arguments.\nExpected:\n %s, %s",
            "(x,y,w,h,cornerSize,[cornerSizeY])",
            "(LRectangle,cornerSize,[cornerSizeY])"));

    float cornerSizeX     = LUA::getNumber<float>(2);
    float cornerSizeY     = LUA::checkAndGetNumber<float>(2, cornerSizeX);
    bool curveTopLeft     = LUA::checkAndGetBoolean(2, true);
    bool curveTopRight    = LUA::checkAndGetBoolean(2, true);
    bool curveBottomLeft  = LUA::checkAndGetBoolean(2, true);
    bool curveBottomRight = LUA::checkAndGetBoolean(2, true);

    Path::addRoundedRectangle( x, y, w, h,
                               cornerSizeX, cornerSizeY,
                               curveTopLeft, curveTopRight, curveBottomLeft, curveBottomRight );

    return 0;
}

int LPath::addEllipse(lua_State*) {
    float x = LUA::getNumber<float>(2);
    float y = LUA::getNumber<float>(2);
    float width = LUA::getNumber<float>(2);
    float height = LUA::getNumber<float>(2);
    Path::addEllipse( x, y, width, height );
    return 0;
}

int LPath::cubicTo(lua_State*) {
    Point<float> controlPoint1 = LUCE::luce_topoint<float>(2);
    Point<float> controlPoint2 = LUCE::luce_topoint<float>(2);
    Point<float> endPoint = LUCE::luce_topoint<float>(2);
    Path::cubicTo( controlPoint1, controlPoint2, endPoint );
    return 0;
}

int LPath::clear(lua_State*) {
    Path::clear();
    return 0;
}

int LPath::addArrow(lua_State*) {
    Line<float> line = LUCE::luce_toline<float>(2);
    float lineThickness = LUA::getNumber<float>(2);
    float arrowheadWidth = LUA::getNumber<float>(2);
    float arrowheadLength = LUA::getNumber<float>(2);
    Path::addArrow( line, lineThickness, arrowheadWidth, arrowheadLength );
    return 0;
}

// TODO
//getters
int LPath::writePathToStream ( lua_State* ) {
    // Path::writePathToStream(*LUA::from_luce<LOutputStream>(2); // TODO);
    LUA::TODO_OBJECT( "writePathToStream, *LUA::from_luce<LOutputStream>(2); // TODO" );
    lua_settop(LUA::Get(), 1); // added by TODO
    return 0;
}

int LPath::loadPathFromStream ( lua_State* ) {
    // Path::loadPathFromStream(*LUA::from_luce<LInputStream>(2); // TODO);
    LUA::TODO_OBJECT( "loadPathFromStream, *LUA::from_luce<LInputStream>(2); // TODO" );
    lua_settop(LUA::Get(), 1); // added by TODO
    return 0;
}

int LPath::loadPathFromData ( lua_State* ) {
    // void* data = LUA::from_luce<Lvoid>(2); // TODO;
    // size_t numberOfBytes = *LUA::from_luce<Lsize_t>(2); // TODO;
    // Path::loadPathFromData( data, numberOfBytes );
    LUA::TODO_OBJECT( "loadPathFromData,  data, numberOfBytes " );
    lua_settop(LUA::Get(), 1); // added by TODO
    return 0;
}
