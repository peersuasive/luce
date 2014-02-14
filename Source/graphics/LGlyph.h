/************************************************************

 LGlyph.h

    @author Christophe Berbizier (cberbizier@peersuasive.com)
    @license GPLv3
    @copyright 


(c) 2014, Peersuasive Technologies

*************************************************************/

#ifndef __LUCE_LGLYPH_H
#define __LUCE_LGLYPH_H

class LGlyph
    : public LBase,
      public TextLayout::Glyph
{
public:
    LGlyph(lua_State*);
    LGlyph(lua_State*, const TextLayout::Glyph&);
    ~LGlyph();

    //==============================================================================
    int getGlyphCode(lua_State*);
    int setGlyphCode(lua_State*);
    int getAnchor(lua_State*);
    int setAnchor(lua_State*);
    int getWidth(lua_State*);
    int setWidth(lua_State*);

    //==============================================================================
    static const char className[];
    static const Luna<LGlyph>::Inheritence inherits[];
    static const Luna<LGlyph>::InheritenceF inheritsF[];
    static const Luna<LGlyph>::PropertyType properties[];
    static const Luna<LGlyph>::FunctionType methods[];
    static const Luna<LGlyph>::StaticType statics[];
    static const Luna<LGlyph>::Enum enums[];

private:
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (LGlyph)
};

#endif // __LUCE_LGLYPH_H
