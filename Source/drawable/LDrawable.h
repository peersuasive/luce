/************************************************************

 LDrawable.h

    @author Christophe Berbizier (cberbizier@peersuasive.com)
    @license GPLv3
    @copyright 


(c) 2014, Peersuasive Technologies

*************************************************************/

#ifndef __LUCE_LDRAWABLE_H
#define __LUCE_LDRAWABLE_H

class LDrawable
    : public LComponent
{
public:
    LDrawable(lua_State*, Drawable* child = nullptr, const String& name = String::empty);
    ~LDrawable();

    //==============================================================================
    static int s_createFromImageFile(lua_State*);
    static int s_createFromSVG(lua_State*);
    static int s_createFromImageDataStream(lua_State*);
    static int s_createFromImageData(lua_State*);
    static int s_parseSVGPath(lua_State*);
    static int s_createFromValueTree(lua_State*);
    static int s_registerDrawableTypeHandlers(lua_State*);

    //==============================================================================
    int createValueTree(lua_State*);

    int getDrawableBounds(lua_State*);

    int replaceColour(lua_State*);
    int getParent(lua_State*);

    //==============================================================================
    int setTransformToFit(lua_State*);
    int draw(lua_State*);
    int drawAt(lua_State*);
    int drawWithin(lua_State*);
    int setOriginWithOriginalSize(lua_State*);

    //==============================================================================
    static const char className[];
    static const Luna<LDrawable>::Inheritence inherits[];
    static const Luna<LDrawable>::InheritenceF inheritsF[];
    static const Luna<LDrawable>::PropertyType properties[];
    static const Luna<LDrawable>::FunctionType methods[];
    static const Luna<LDrawable>::StaticType statics[];
    static const Luna<LDrawable>::Enum enums[];

private:
    //==============================================================================
    ScopedPointer<Drawable> child;

    //==============================================================================
    lua_State *L;

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (LDrawable)
};

#endif // __LUCE_LDRAWABLE_H
