/************************************************************

 LGlyphArrangement.h

    @author Christophe Berbizier (cberbizier@peersuasive.com)
    @license GPLv3
    @copyright 


(c) 2013, Peersuasive Technologies

*************************************************************/

#ifndef __LUCE_LGLYPHARRANGEMENT_H
#define __LUCE_LGLYPHARRANGEMENT_H

class LGlyphArrangement
    : public LBase,
      public GlyphArrangement
{
public:
    LGlyphArrangement(lua_State*);
    LGlyphArrangement(lua_State*, const GlyphArrangement&);
    ~LGlyphArrangement();

    //==============================================================================
    int removeRangeOfGlyphs(lua_State*);
    int addLineOfText(lua_State*);
    int addGlyph(lua_State*);
    int addCurtailedLineOfText(lua_State*);
    int justifyGlyphs(lua_State*);
    int stretchRangeOfGlyphs(lua_State*);
    int draw(lua_State*);
    int addGlyphArrangement(lua_State*);
    int addFittedText(lua_State*);
    int createPath(lua_State*);
    int moveRangeOfGlyphs(lua_State*);
    int clear(lua_State*);
    int addJustifiedText(lua_State*);

    //==============================================================================
    int findGlyphIndexAt(lua_State*);
    int getNumGlyphs(lua_State*);
    int getBoundingBox(lua_State*);
    int getGlyph(lua_State*);

    //==============================================================================
    static const char className[];
    static const Luna<LGlyphArrangement>::Inheritence inherits[];
    static const Luna<LGlyphArrangement>::InheritenceF inheritsF[];
    static const Luna<LGlyphArrangement>::PropertyType properties[];
    static const Luna<LGlyphArrangement>::FunctionType methods[];
    static const Luna<LGlyphArrangement>::Enum enums[];

private:
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (LGlyphArrangement)
};

#endif // __LUCE_LGLYPHARRANGEMENT_H
