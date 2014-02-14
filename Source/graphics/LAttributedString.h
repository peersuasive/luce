/************************************************************

 LAttributedString.h

    @author Christophe Berbizier (cberbizier@peersuasive.com)
    @license GPLv3
    @copyright 


(c) 2014, Peersuasive Technologies

*************************************************************/

#ifndef __LUCE_LATTRIBUTEDSTRING_H
#define __LUCE_LATTRIBUTEDSTRING_H

class LAttributedString
    : public LBase,
      public AttributedString
{
public:
    LAttributedString(lua_State*);
    LAttributedString(lua_State*, const AttributedString&);
    ~LAttributedString();

    //==============================================================================
    int setJustification(lua_State*);
    int getJustification(lua_State*);
    int setLineSpacing(lua_State*);
    int getLineSpacing(lua_State*);
    int setReadingDirection(lua_State*);
    int getReadingDirection(lua_State*);
    int setWordWrap(lua_State*);
    int getWordWrap(lua_State*);
    int setText(lua_State*);
    int getText(lua_State*);

    //==============================================================================
    int getNumAttributes(lua_State*);
    int getAttribute(lua_State*);

    //==============================================================================
    int append(lua_State*);
    int setColour(lua_State*);
    int draw(lua_State*);
    int setFont(lua_State*);
    int clear(lua_State*);

    //==============================================================================
    static const char className[];
    static const Luna<LAttributedString>::Inheritence inherits[];
    static const Luna<LAttributedString>::InheritenceF inheritsF[];
    static const Luna<LAttributedString>::PropertyType properties[];
    static const Luna<LAttributedString>::FunctionType methods[];
    static const Luna<LAttributedString>::StaticType statics[];
    static const Luna<LAttributedString>::Enum enums[];

private:
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (LAttributedString)
};

#endif // __LUCE_LATTRIBUTEDSTRING_H
