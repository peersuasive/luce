/************************************************************

 LPath.h

    @author Christophe Berbizier (cberbizier@peersuasive.com)
    @license GPLv3
    @copyright 


(c) 2013, Peersuasive Technologies

*************************************************************/

#ifndef __LUCE_LPATH_H
#define __LUCE_LPATH_H

class LPath
    : public LBase,
      public Path
{
public:
    LPath(lua_State*);
    LPath(lua_State*, const Path&);
    ~LPath();

    //==============================================================================
    int setUsingNonZeroWinding(lua_State*);
    int isUsingNonZeroWinding(lua_State*);

    //==============================================================================
    int startNewSubPath(lua_State*);
    int addArc(lua_State*);
    int addCentredArc(lua_State*);
    int addRectangle(lua_State*);
    int addTriangle(lua_State*);
    int restoreFromString(lua_State*);
    int addPieSegment(lua_State*);
    int lineTo(lua_State*);
    int closeSubPath(lua_State*);
    int addQuadrilateral(lua_State*);
    int addLineSegment(lua_State*);
    int writePathToStream(lua_State*);
    int loadPathFromStream(lua_State*);
    int loadPathFromData(lua_State*);
    int addStar(lua_State*);
    int scaleToFit(lua_State*);
    int addPath(lua_State*);
    int applyTransform(lua_State*);
    int quadraticTo(lua_State*);
    int swapWithPath(lua_State*);
    int addPolygon(lua_State*);
    int addBubble(lua_State*);
    int addRoundedRectangle(lua_State*);
    int addEllipse(lua_State*);
    int cubicTo(lua_State*);
    int clear(lua_State*);
    int addArrow(lua_State*);

    //==============================================================================
    int isEmpty(lua_State*);
    int createPathWithRoundedCorners(lua_State*);
    int getPointAlongPath(lua_State*);
    int getLength(lua_State*);
    int intersectsLine(lua_State*);
    int getBoundsTransformed(lua_State*);
    int getClippedLine(lua_State*);
    int getCurrentPosition(lua_State*);
    int getTransformToScaleToFit(lua_State*);
    int toString(lua_State*);
    int getNearestPoint(lua_State*);

    //==============================================================================

    static const char className[];
    static const Luna<LPath>::Inheritence inherits[];
    static const Luna<LPath>::InheritenceF inheritsF[];
    static const Luna<LPath>::PropertyType properties[];
    static const Luna<LPath>::FunctionType methods[];
    static const Luna<LPath>::StaticType statics[];
    static const Luna<LPath>::Enum enums[];

private:

    //==============================================================================
    // callbacks


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (LPath)
};

#endif // __LUCE_LPATH_H
