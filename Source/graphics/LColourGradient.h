/************************************************************

 LColourGradient.h

    @author Christophe Berbizier (cberbizier@peersuasive.com)
    @license GPLv3
    @copyright 


(c) 2014, Peersuasive Technologies

*************************************************************/

#ifndef __LUCE_LCOLOURGRADIENT_H
#define __LUCE_LCOLOURGRADIENT_H

class LColourGradient
    : public LBase,
      public ColourGradient
{
public:
    LColourGradient(lua_State*);
    LColourGradient(lua_State*, const ColourGradient&);
    static int lnew(lua_State*);
    ~LColourGradient();

    //==============================================================================
    int clearColours(lua_State*);
    int addColour(lua_State*);
    int removeColour(lua_State*);
    int multiplyOpacity(lua_State*);
    int getNumColours(lua_State*);
    int getColourPosition(lua_State*);
    int getColour(lua_State*);
    int setColour(lua_State*);
    int getColourAtPosition(lua_State*);
    int createLookupTable(lua_State*);
    int isOpaque(lua_State*);
    int isInvisible(lua_State*);

    int getPoint1(lua_State*);
    int getPoint2(lua_State*);
    int isRadial(lua_State*);

    //==============================================================================
    static const char className[];
    static const Luna<LColourGradient>::Inheritence inherits[];
    static const Luna<LColourGradient>::InheritenceF inheritsF[];
    static const Luna<LColourGradient>::PropertyType properties[];
    static const Luna<LColourGradient>::FunctionType methods[];
    static const Luna<LColourGradient>::StaticType statics[];
    static const Luna<LColourGradient>::Enum enums[];

private:
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (LColourGradient)
};

#endif // __LUCE_LCOLOURGRADIENT_H
