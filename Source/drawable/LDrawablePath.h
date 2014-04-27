/************************************************************

 LDrawablePath.h

    @author Christophe Berbizier (cberbizier@peersuasive.com)
    @license GPLv3
    @copyright 


(c) 2014, Peersuasive Technologies

*************************************************************/

#ifndef __LUCE_LDRAWABLEPATH_H
#define __LUCE_LDRAWABLEPATH_H

class LDrawablePath
    : public LDrawableShape,
      public DrawablePath
{
public:
    LDrawablePath(lua_State*);
    LDrawablePath(lua_State*, const DrawablePath&);
    ~LDrawablePath();

    //==============================================================================
    int setPath(lua_State*);
    int getPath(lua_State*);

    //==============================================================================
    int createValueTree(lua_State*);
    int getStrokePath(lua_State*);
    int createCopy(lua_State*);

    //== PROTECTED =================================================================
    virtual int pathChanged(lua_State*);
    virtual int strokeChanged(lua_State*);
    virtual int isStrokeVisible(lua_State*);
    virtual int refreshFillTypes(lua_State*);
    virtual int writeTo(lua_State*);

    //==============================================================================
    int refreshFromValueTree(lua_State*);

    //==============================================================================
    static const char className[];
    static const Luna<LDrawablePath>::Inheritence inherits[];
    static const Luna<LDrawablePath>::InheritenceF inheritsF[];
    static const Luna<LDrawablePath>::PropertyType properties[];
    static const Luna<LDrawablePath>::FunctionType methods[];
    static const Luna<LDrawablePath>::StaticType statics[];
    static const Luna<LDrawablePath>::Enum enums[];

private:
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (LDrawablePath)
};

#endif // __LUCE_LDRAWABLEPATH_H
