/************************************************************

 LAffineTransform.h

    @author Christophe Berbizier (cberbizier@peersuasive.com)
    @license GPLv3
    @copyright 


(c) 2013, Peersuasive Technologies

*************************************************************/

#ifndef __LUCE_LAFFINETRANSFORM_H
#define __LUCE_LAFFINETRANSFORM_H

class LAffineTransform
    : public LBase,
      public AffineTransform
{
public:
    LAffineTransform(lua_State*);
    LAffineTransform(lua_State*, const AffineTransform&);
    int getIdentity(lua_State*); // TODO: implement static methods !
    ~LAffineTransform();

    static AffineTransform fromLuce( float mat00, float mat01, float mat02, 
            float mat10, float mat11, float mat12);
    static AffineTransform fromLuce( const Array<float>& );

    int dump(lua_State*);

    //==============================================================================
    int transformPoint(lua_State*);
    int transformPoints(lua_State*);

    //==============================================================================
    int rotation(lua_State*);
    int translated(lua_State*);
    int getScaleFactor(lua_State*);
    int withAbsoluteTranslation(lua_State*);
    int isSingularity(lua_State*);
    int translation(lua_State*);
    int getTranslationX(lua_State*);
    int verticalFlip(lua_State*);
    int shear(lua_State*);
    int rotated(lua_State*);
    int scaled(lua_State*);
    int isOnlyTranslation(lua_State*);
    int followedBy(lua_State*);
    int getTranslationY(lua_State*);
    int fromTargetPoints(lua_State*);
    int sheared(lua_State*);
    int scale(lua_State*);
    int inverted(lua_State*);
    int isIdentity(lua_State*);

    //==============================================================================

    static const char className[];
    static const Luna<LAffineTransform>::Inheritence inherits[];
    static const Luna<LAffineTransform>::InheritenceF inheritsF[];
    static const Luna<LAffineTransform>::PropertyType properties[];
    static const Luna<LAffineTransform>::FunctionType methods[];
    static const Luna<LAffineTransform>::StaticType statics[];
    static const Luna<LAffineTransform>::Enum enums[];

private:
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (LAffineTransform)
};

#endif // __LUCE_LAFFINETRANSFORM_H
