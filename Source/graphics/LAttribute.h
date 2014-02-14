/************************************************************

 LAttribute.h

    @author Christophe Berbizier (cberbizier@peersuasive.com)
    @license GPLv3
    @copyright 


(c) 2014, Peersuasive Technologies

*************************************************************/

#ifndef __LUCE_LATTRIBUTE_H
#define __LUCE_LATTRIBUTE_H

class LAttribute
    : public LBase,
      public AttributedString::Attribute
{
public:
    LAttribute(lua_State*);
    LAttribute(lua_State*, const Attribute&);
    ~LAttribute();

    //==============================================================================
    int getRange(lua_State*);

    //==============================================================================
    int getColour(lua_State*);
    int getFont(lua_State*);

    //==============================================================================
    static const char className[];
    static const Luna<LAttribute>::Inheritence inherits[];
    static const Luna<LAttribute>::InheritenceF inheritsF[];
    static const Luna<LAttribute>::PropertyType properties[];
    static const Luna<LAttribute>::FunctionType methods[];
    static const Luna<LAttribute>::StaticType statics[];
    static const Luna<LAttribute>::Enum enums[];

private:
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (LAttribute)
};

#endif // __LUCE_LATTRIBUTE_H
