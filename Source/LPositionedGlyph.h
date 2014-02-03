/************************************************************

 LPositionedGlyph.h

    @author Christophe Berbizier (cberbizier@peersuasive.com)
    @license GPLv3
    @copyright 


(c) 2013, Peersuasive Technologies

*************************************************************/

#ifndef __LUCE_LPOSITIONEDGLYPH_H
#define __LUCE_LPOSITIONEDGLYPH_H

class LPositionedGlyph
    : public LBase,
      public PositionedGlyph
{
public:
    LPositionedGlyph(lua_State*);
    LPositionedGlyph(lua_State*, const PositionedGlyph&);
    ~LPositionedGlyph();

    //==============================================================================
    int createPath(lua_State*);
    int draw(lua_State*);
    int moveBy(lua_State*);

    //==============================================================================
    int getLeft(lua_State*);
    int getTop(lua_State*);
    int getBaselineY(lua_State*);
    int getRight(lua_State*);
    int getBounds(lua_State*);
    int isWhitespace(lua_State*);
    int getCharacter(lua_State*);
    int getBottom(lua_State*);
    int hitTest(lua_State*);

    //==============================================================================
    static const char className[];
    static const Luna<LPositionedGlyph>::Inheritence inherits[];
    static const Luna<LPositionedGlyph>::InheritenceF inheritsF[];
    static const Luna<LPositionedGlyph>::PropertyType properties[];
    static const Luna<LPositionedGlyph>::FunctionType methods[];
    static const Luna<LPositionedGlyph>::Enum enums[];

private:
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (LPositionedGlyph)
};

#endif // __LUCE_LPOSITIONEDGLYPH_H
