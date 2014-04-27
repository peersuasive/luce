/************************************************************

 LDrawableShape.h

    @author Christophe Berbizier (cberbizier@peersuasive.com)
    @license GPLv3
    @copyright 


(c) 2014, Peersuasive Technologies

*************************************************************/

#ifndef __LUCE_LDRAWABLESHAPE_H
#define __LUCE_LDRAWABLESHAPE_H

class LDrawableShape
    : public LDrawable
{
public:
    LDrawableShape(lua_State*, DrawableShape* = nullptr, const String& name = String::empty);
    ~LDrawableShape();

    //==============================================================================
    int setFill(lua_State*);
    int getFill(lua_State*);
    int setStrokeType(lua_State*);
    int getStrokeType(lua_State*);
    int setStrokeFill(lua_State*);
    int getStrokeFill(lua_State*);

    int setStrokeThickness(lua_State*);
    int hitTest(lua_State*);

    //==============================================================================
    //int paint(lua_State*);

    //== PROTECTED =================================================================
    virtual int pathChanged(lua_State*) = 0;
    virtual int strokeChanged(lua_State*) = 0;
    virtual int isStrokeVisible(lua_State*) = 0;
    virtual int refreshFillTypes(lua_State*) = 0;
    virtual int writeTo(lua_State*) = 0;

    //==============================================================================
    static const char className[];
    static const Luna<LDrawableShape>::Inheritence inherits[];
    static const Luna<LDrawableShape>::InheritenceF inheritsF[];
    static const Luna<LDrawableShape>::PropertyType properties[];
    static const Luna<LDrawableShape>::FunctionType methods[];
    static const Luna<LDrawableShape>::StaticType statics[];
    static const Luna<LDrawableShape>::Enum enums[];

private:
    //==============================================================================
    ScopedPointer<DrawableShape> child;

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (LDrawableShape)
};

#endif // __LUCE_LDRAWABLESHAPE_H
