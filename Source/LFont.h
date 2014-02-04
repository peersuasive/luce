/************************************************************

 LFont.h

    @author Christophe Berbizier (cberbizier@peersuasive.com)
    @license GPLv3
    @copyright 


(c) 2013, Peersuasive Technologies

*************************************************************/

#ifndef __LUCE_LFONT_H
#define __LUCE_LFONT_H

class LFont
    : public LBase,
      public Font
{
public:
    LFont(lua_State*);
    LFont(lua_State*, const Font&);
    ~LFont();

    //==============================================================================
    int setTypefaceStyle(lua_State*);
    int getTypefaceStyle(lua_State*);
    int setHeight(lua_State*);
    int getHeight(lua_State*);
    int setItalic(lua_State*);
    int isItalic(lua_State*);
    int setExtraKerningFactor(lua_State*);
    int getExtraKerningFactor(lua_State*);
    int setHorizontalScale(lua_State*);
    int getHorizontalScale(lua_State*);
    int setFallbackFontStyle(lua_State*);
    int getFallbackFontStyle(lua_State*);
    int setStyleFlags(lua_State*);
    int getStyleFlags(lua_State*);
    int setTypefaceName(lua_State*);
    int getTypefaceName(lua_State*);
    int setBold(lua_State*);
    int isBold(lua_State*);
    int setFallbackFontName(lua_State*);
    int getFallbackFontName(lua_State*);

    //==============================================================================
    int setHeightWithoutChangingWidth(lua_State*);
    int getGlyphPositions(lua_State*);
    int findFonts(lua_State*);
    int setSizeAndStyle(lua_State*);
    int setUnderline(lua_State*);

    //==============================================================================
    int getAscent(lua_State*);
    int getStringWidth(lua_State*);
    int fromString(lua_State*);
    int boldened(lua_State*);
    int withHorizontalScale(lua_State*);
    int getAvailableStyles(lua_State*);
    int getDescent(lua_State*);
    int findAllTypefaceStyles(lua_State*);
    int withStyle(lua_State*);
    int getDefaultSansSerifFontName(lua_State*);
    int getDefaultMonospacedFontName(lua_State*);
    int getHeightInPoints(lua_State*);
    int withTypefaceStyle(lua_State*);
    int getDefaultStyle(lua_State*);
    int findAllTypefaceNames(lua_State*);
    int withHeight(lua_State*);
    int getDescentInPoints(lua_State*);
    int getDefaultSerifFontName(lua_State*);
    int toString(lua_State*);
    int getStringWidthFloat(lua_State*);
    int getDefaultTypefaceForFont(lua_State*);
    int withExtraKerningFactor(lua_State*);
    int withPointHeight(lua_State*);
    int getAscentInPoints(lua_State*);
    int isUnderlined(lua_State*);
    int italicised(lua_State*);
    int getTypeface(lua_State*);

    //==============================================================================

    static const char className[];
    static const Luna<LFont>::Inheritence inherits[];
    static const Luna<LFont>::InheritenceF inheritsF[];
    static const Luna<LFont>::PropertyType properties[];
    static const Luna<LFont>::FunctionType methods[];
    static const Luna<LFont>::StaticType statics[];
    static const Luna<LFont>::Enum enums[];

private:

    //==============================================================================
    // callbacks

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (LFont)
};

#endif // __LUCE_LFONT_H
