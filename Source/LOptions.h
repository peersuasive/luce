/************************************************************

 LOptions.h

    @author Christophe Berbizier (cberbizier@peersuasive.com)
    @license GPLv3
    @copyright 


(c) 2014, Peersuasive Technologies

*************************************************************/

#ifndef __LUCE_LOPTIONS_H
#define __LUCE_LOPTIONS_H

class LOptions
    : public LBase,
      public PopupMenu::Options
{
public:
    LOptions(lua_State*);
    ~LOptions();

    //==============================================================================
    int withTargetComponent(lua_State*);
    int withTargetScreenArea(lua_State*);
    int withMinimumWidth(lua_State*);
    int withMaximumNumColumns(lua_State*);
    int withStandardItemHeight(lua_State*);
    int withItemThatMustBeVisible(lua_State*);

    //==============================================================================
    static const char className[];
    static const Luna<LOptions>::Inheritence inherits[];
    static const Luna<LOptions>::InheritenceF inheritsF[];
    static const Luna<LOptions>::PropertyType properties[];
    static const Luna<LOptions>::FunctionType methods[];
    static const Luna<LOptions>::StaticType statics[];
    static const Luna<LOptions>::Enum enums[];

private:
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (LOptions)
};

#endif // __LUCE_LOPTIONS_H
