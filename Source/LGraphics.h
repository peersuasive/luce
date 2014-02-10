/************************************************************

 LGraphics.h

    @author Christophe Berbizier (cberbizier@peersuasive.com)
    @license GPLv3
    @copyright 


(c) 2013, Peersuasive Technologies

*************************************************************/

#ifndef __LUCE_LGRAPHICS_H
#define __LUCE_LGRAPHICS_H

class LGraphics
    : public LBase,
      public Graphics
{
public:
    LGraphics(lua_State*);
    LGraphics(lua_State*, juce::Graphics&);
    ~LGraphics();

    Graphics* getGraphics();
    operator Graphics* () const;
    //operator const Graphics& () const;

    //==============================================================================
    int resetToDefaultState(lua_State*);
    int drawImageAt(lua_State*);
    int fillAll(lua_State*);
    int fillEllipse(lua_State*);
    int setFillType(lua_State*);
    int drawImage(lua_State*);
    int drawEllipse(lua_State*);
    int saveState(lua_State*);
    int drawArrow(lua_State*);
    int addTransform(lua_State*);
    int drawImageWithin(lua_State*);
    int excludeClipRegion(lua_State*);
    int endTransparencyLayer(lua_State*);
    int fillCheckerBoard(lua_State*);
    int drawHorizontalLine(lua_State*);
    int setOrigin(lua_State*);
    int drawDashedLine(lua_State*);
    int drawImageTransformed(lua_State*);
    int beginTransparencyLayer(lua_State*);
    int fillPath(lua_State*);
    int restoreState(lua_State*);
    int drawText(lua_State*);
    int fillRectList(lua_State*);
    int drawFittedText(lua_State*);
    int strokePath(lua_State*);
    int fillRoundedRectangle(lua_State*);
    int drawMultiLineText(lua_State*);
    int setFont(lua_State*);
    int setTiledImageFill(lua_State*);
    int fillRect(lua_State*);
    int setGradientFill(lua_State*);
    int setImageResamplingQuality(lua_State*);
    int setPixel(lua_State*);
    int drawSingleLineText(lua_State*);
    int drawVerticalLine(lua_State*);
    int drawRect(lua_State*);
    int drawRoundedRectangle(lua_State*);
    int drawLine(lua_State*);
    int setOpacity(lua_State*);
    int setColour(lua_State*);

    //==============================================================================
    int isVectorDevice(lua_State*);
    int getInternalContext(lua_State*);
    int getCurrentFont(lua_State*);
    int getClipBounds(lua_State*);
    int reduceClipRegion(lua_State*);
    int clipRegionIntersects(lua_State*);
    int isClipEmpty(lua_State*);

    //==============================================================================
    int ScopedSaveState(lua_State*);

    //==============================================================================
    static const char className[];
    static const Luna<LGraphics>::Inheritence inherits[];
    static const Luna<LGraphics>::InheritenceF inheritsF[];
    static const Luna<LGraphics>::PropertyType properties[];
    static const Luna<LGraphics>::FunctionType methods[];
    static const Luna<LGraphics>::StaticType statics[];
    static const Luna<LGraphics>::Enum enums[];

private:
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (LGraphics)
};

#endif // __LUCE_LGRAPHICS_H
