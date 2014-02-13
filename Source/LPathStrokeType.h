/************************************************************

 LPathStrokeType.h

    @author Christophe Berbizier (cberbizier@peersuasive.com)
    @license GPLv3
    @copyright 


(c) 2014, Peersuasive Technologies

*************************************************************/

#ifndef __LUCE_LPATHSTROKETYPE_H
#define __LUCE_LPATHSTROKETYPE_H

class LPathStrokeType
    : public LBase,
      public PathStrokeType
{
public:
    LPathStrokeType(lua_State*);
    LPathStrokeType(lua_State*, const PathStrokeType&);
    static int lnew(lua_State*);
    ~LPathStrokeType();

    //==============================================================================
    int setJointStyle(lua_State*);
    int getJointStyle(lua_State*);
    int setStrokeThickness(lua_State*);
    int getStrokeThickness(lua_State*);
    int setEndStyle(lua_State*);
    int getEndStyle(lua_State*);

    //==============================================================================
    int createDashedStroke(lua_State*);
    int createStrokeWithArrowheads(lua_State*);
    int createStrokedPath(lua_State*);

    //==============================================================================
    static const char className[];
    static const Luna<LPathStrokeType>::Inheritence inherits[];
    static const Luna<LPathStrokeType>::InheritenceF inheritsF[];
    static const Luna<LPathStrokeType>::PropertyType properties[];
    static const Luna<LPathStrokeType>::FunctionType methods[];
    static const Luna<LPathStrokeType>::StaticType statics[];
    static const Luna<LPathStrokeType>::Enum enums[];

private:
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (LPathStrokeType)
};

#endif // __LUCE_LPATHSTROKETYPE_H
