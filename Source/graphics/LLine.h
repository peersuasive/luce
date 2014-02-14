/************************************************************

 LLine.h

    @author Christophe Berbizier (cberbizier@peersuasive.com)
    @license GPLv3
    @copyright 


(c) 2014, Peersuasive Technologies

*************************************************************/

#ifndef __LUCE_LLINE_H
#define __LUCE_LLINE_H

class LLine
    : public LBase,
      public TextLayout::Line
{
public:
    LLine(lua_State*);
    LLine(lua_State*, const TextLayout::Line&);
    ~LLine();

    //==============================================================================
    int getLineBoundsX(lua_State*);
    
    //==============================================================================
    int getRuns(lua_State*);
    int setRuns(lua_State*);
    int getStringRange(lua_State*);
    int setStringRange(lua_State*);
    int getLineOrigin(lua_State*);
    int setLineOrigin(lua_State*);
    int getAscent(lua_State*);
    int setAscent(lua_State*);
    int getDescent(lua_State*);
    int setDescent(lua_State*);
    int getLeading(lua_State*);
    int setLeading(lua_State*);

    //==============================================================================
    static const char className[];
    static const Luna<LLine>::Inheritence inherits[];
    static const Luna<LLine>::InheritenceF inheritsF[];
    static const Luna<LLine>::PropertyType properties[];
    static const Luna<LLine>::FunctionType methods[];
    static const Luna<LLine>::StaticType statics[];
    static const Luna<LLine>::Enum enums[];

private:
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (LLine)
};

#endif // __LUCE_LLINE_H
