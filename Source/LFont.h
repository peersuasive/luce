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
    static int lnew(lua_State*);
    ~LFont();
    
    //==============================================================================
    static int s_getDefaultSansSerifFontName(lua_State*);
    static int s_getDefaultMonospacedFontName(lua_State*);
    static int s_getDefaultStyle(lua_State*);
    static int s_getDefaultSerifFontName(lua_State*);
    static int s_getDefaultTypefaceForFont(lua_State*);
    static int s_findFonts(lua_State*);
    static int s_findAllTypefaceStyles(lua_State*);
    static int s_findAllTypefaceNames(lua_State*);
    static int s_setFallbackFontName(lua_State*);
    static int s_getFallbackFontStyle(lua_State*);
    static int s_setFallbackFontStyle(lua_State*);
    static int s_getFallbackFontName(lua_State*);
    static int s_fromString(lua_State*);

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
    int setStyleFlags(lua_State*);
    int getStyleFlags(lua_State*);
    int setTypefaceName(lua_State*);
    int getTypefaceName(lua_State*);
    int setBold(lua_State*);
    int isBold(lua_State*);

    //==============================================================================
    int setHeightWithoutChangingWidth(lua_State*);
    int getGlyphPositions(lua_State*);
    int setSizeAndStyle(lua_State*);
    int setUnderline(lua_State*);

    //==============================================================================
    int getAscent(lua_State*);
    int getStringWidth(lua_State*);
    int boldened(lua_State*);
    int withHorizontalScale(lua_State*);
    int getAvailableStyles(lua_State*);
    int getDescent(lua_State*);
    int withStyle(lua_State*);
    int getHeightInPoints(lua_State*);
    int withTypefaceStyle(lua_State*);
    int withHeight(lua_State*);
    int getDescentInPoints(lua_State*);
    int toString(lua_State*);
    int getStringWidthFloat(lua_State*);
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
