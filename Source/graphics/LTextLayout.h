/************************************************************

 LTextLayout.h

    @author Christophe Berbizier (cberbizier@peersuasive.com)
    @license GPLv3
    @copyright 


(c) 2014, Peersuasive Technologies

*************************************************************/

#ifndef __LUCE_LTEXTLAYOUT_H
#define __LUCE_LTEXTLAYOUT_H

class LTextLayout
    : public LBase,
      public TextLayout
{
public:
    LTextLayout(lua_State*);
    LTextLayout(lua_State*, const TextLayout&);
    ~LTextLayout();

    //==============================================================================
    int getNumLines(lua_State*);
    int getLine(lua_State*);
    int getWidth(lua_State*);
    int getHeight(lua_State*);

    //==============================================================================
    int addLine(lua_State*);
    int createLayoutWithBalancedLineLengths(lua_State*);
    int ensureStorageAllocated(lua_State*);
    int createLayout(lua_State*);
    int draw(lua_State*);

    //==============================================================================
    static const char className[];
    static const Luna<LTextLayout>::Inheritence inherits[];
    static const Luna<LTextLayout>::InheritenceF inheritsF[];
    static const Luna<LTextLayout>::PropertyType properties[];
    static const Luna<LTextLayout>::FunctionType methods[];
    static const Luna<LTextLayout>::StaticType statics[];
    static const Luna<LTextLayout>::Enum enums[];

private:
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (LTextLayout)
};

#endif // __LUCE_LTEXTLAYOUT_H
