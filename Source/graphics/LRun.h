/************************************************************

 LRun.h

    @author Christophe Berbizier (cberbizier@peersuasive.com)
    @license GPLv3
    @copyright 


(c) 2014, Peersuasive Technologies

*************************************************************/

#ifndef __LUCE_LRUN_H
#define __LUCE_LRUN_H

class LRun
    : public LBase,
      public TextLayout::Run
{
public:
    LRun(lua_State*);
    LRun(lua_State*, const TextLayout::Run&);
    ~LRun();

    //==============================================================================
    int getFont(lua_State*);
    int setFont(lua_State*);
    int getColour(lua_State*);
    int setColour(lua_State*);
    int getGlyphs(lua_State*);
    int setGlyphs(lua_State*);
    int getStringRange(lua_State*);
    int setStringRange(lua_State*);

    //==============================================================================
    static const char className[];
    static const Luna<LRun>::Inheritence inherits[];
    static const Luna<LRun>::InheritenceF inheritsF[];
    static const Luna<LRun>::PropertyType properties[];
    static const Luna<LRun>::FunctionType methods[];
    static const Luna<LRun>::StaticType statics[];
    static const Luna<LRun>::Enum enums[];

private:
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (LRun)
};

#endif // __LUCE_LRUN_H
