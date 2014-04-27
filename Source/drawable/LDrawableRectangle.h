/************************************************************

 LDrawableRectangle.h

    @author Christophe Berbizier (cberbizier@peersuasive.com)
    @license GPLv3
    @copyright 


(c) 2014, Peersuasive Technologies

*************************************************************/

#ifndef __LUCE_LDrawableRectangle_H
#define __LUCE_LDrawableRectangle_H

class LDrawableRectangle
    : public LDrawableShape,
      public DrawableRectangle
{
public:
    LDrawableRectangle(lua_State*);
    LDrawableRectangle(lua_State*, const DrawableRectangle&);
    ~LDrawableRectangle();

    //==============================================================================
    int getPath(lua_State*);
    int setPath(lua_State*);
    int getStrokePath(lua_State*);
    int setStrokePath(lua_State*);

    //==============================================================================
    int setRectangle(lua_State*);
    int getRectangle(lua_State*);
    int setCornerSize(lua_State*);
    int getCornerSize(lua_State*);

    //==============================================================================
    int createCopy(lua_State*);

    //== PROTECTED =================================================================
    virtual int pathChanged(lua_State*);
    virtual int strokeChanged(lua_State*);
    virtual int isStrokeVisible(lua_State*);
    virtual int refreshFillTypes(lua_State*);
    virtual int writeTo(lua_State*);

    //==============================================================================
    int refreshFromValueTree(lua_State*);
    int createValueTree(lua_State*);

    //==============================================================================
    static const char className[];
    static const Luna<LDrawableRectangle>::Inheritence inherits[];
    static const Luna<LDrawableRectangle>::InheritenceF inheritsF[];
    static const Luna<LDrawableRectangle>::PropertyType properties[];
    static const Luna<LDrawableRectangle>::FunctionType methods[];
    static const Luna<LDrawableRectangle>::StaticType statics[];
    static const Luna<LDrawableRectangle>::Enum enums[];

private:
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (LDrawableRectangle)
};

#endif // __LUCE_LDrawableRectangle_H
