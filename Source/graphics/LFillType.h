/************************************************************

 LFillType.h

    @author Christophe Berbizier (cberbizier@peersuasive.com)
    @license GPLv3
    @copyright 


(c) 2014, Peersuasive Technologies

*************************************************************/

#ifndef __LUCE_LFILLTYPE_H
#define __LUCE_LFILLTYPE_H

class LFillType
    : public LBase,
      public FillType
{
public:
    LFillType(lua_State*);
    LFillType(lua_State*, const FillType&);
    static int lnew(lua_State*);
    ~LFillType();

    //==============================================================================
    int isTiledImage(lua_State*);
    int getImage(lua_State*);
    int getTransform(lua_State*);
    int setTiledImage(lua_State*);
    int isGradient(lua_State*);
    int getGradient(lua_State*);
    int setGradient(lua_State*);
    int isColour(lua_State*);
    int getColour(lua_State*);
    int setColour(lua_State*);
    int getOpacity(lua_State*);
    int setOpacity(lua_State*);

    //==============================================================================
    int isInvisible(lua_State*);
    int transformed(lua_State*);

    //==============================================================================
    static const char className[];
    static const Luna<LFillType>::Inheritence inherits[];
    static const Luna<LFillType>::InheritenceF inheritsF[];
    static const Luna<LFillType>::PropertyType properties[];
    static const Luna<LFillType>::FunctionType methods[];
    static const Luna<LFillType>::StaticType statics[];
    static const Luna<LFillType>::Enum enums[];

private:
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (LFillType)
};

#endif // __LUCE_LFILLTYPE_H
