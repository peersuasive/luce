/************************************************************

 LDrawableComposite.h

    @author Christophe Berbizier (cberbizier@peersuasive.com)
    @license GPLv3
    @copyright 


(c) 2014, Peersuasive Technologies

*************************************************************/

#ifndef __LUCE_LDRAWABLECOMPOSITE_H
#define __LUCE_LDRAWABLECOMPOSITE_H

class LDrawableComposite
    : public LDrawable,
      public DrawableComposite
{
public:
    LDrawableComposite(lua_State*);
    LDrawableComposite(lua_State*, const DrawableComposite&);
    ~LDrawableComposite();

    //==============================================================================
    static int s_contentLeftMarkerName(lua_State*);
    static int s_contentRightMarkerName(lua_State*);
    static int s_contentToptMarkerName(lua_State*);
    static int s_contentBottomMarkerName(lua_State*);
    static int s_valueTreeType(lua_State*);

    //==============================================================================
    int setBoundingBox(lua_State*);
    int getBoundingBox(lua_State*);
    int setContentArea(lua_State*);
    int getContentArea(lua_State*);

    //==============================================================================
    int createCopy(lua_State*);
    int createValueTree(lua_State*);
    int getDrawableBounds(lua_State*);
    int getMarkers(lua_State*);

    //==============================================================================
    int parentHierarchyChanged(lua_State*);
    int childrenChanged(lua_State*);
    int resetContentAreaAndBoundingBoxToFitChildren(lua_State*);
    int childBoundsChanged(lua_State*);
    int resetBoundingBoxToContentArea(lua_State*);
    int refreshFromValueTree(lua_State*);

    //==============================================================================
    static const char className[];
    static const Luna<LDrawableComposite>::Inheritence inherits[];
    static const Luna<LDrawableComposite>::InheritenceF inheritsF[];
    static const Luna<LDrawableComposite>::PropertyType properties[];
    static const Luna<LDrawableComposite>::FunctionType methods[];
    static const Luna<LDrawableComposite>::StaticType statics[];
    static const Luna<LDrawableComposite>::Enum enums[];

private:
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (LDrawableComposite)
};

#endif // __LUCE_LDRAWABLECOMPOSITE_H
