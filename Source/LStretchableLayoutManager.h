/************************************************************

 LStretchableLayoutManager.h

    @author Christophe Berbizier (cberbizier@peersuasive.com)
    @license GPLv3
    @copyright 


(c) 2013, Peersuasive Technologies

*************************************************************/

#ifndef __LUCE_LSTRETCHABLELAYOUTMANAGER_H
#define __LUCE_LSTRETCHABLELAYOUTMANAGER_H

class LStretchableLayoutManager
    : public LBase,
      public StretchableLayoutManager
{
public:
    LStretchableLayoutManager(lua_State*);
    ~LStretchableLayoutManager();

    //==============================================================================
    int setItemLayout(lua_State*);
    int getItemLayout(lua_State*);

    //==============================================================================
    int clearAllItems(lua_State*);
    int setItemPosition(lua_State*);
    int layOutComponents(lua_State*);

    //==============================================================================
    int getItemCurrentPosition(lua_State*);
    int getItemCurrentRelativeSize(lua_State*);
    int getItemCurrentAbsoluteSize(lua_State*);

    //==============================================================================

    static const char className[];
    static const Luna<LStretchableLayoutManager>::Inheritence inherits[];
    static const Luna<LStretchableLayoutManager>::InheritenceF inheritsF[];
    static const Luna<LStretchableLayoutManager>::PropertyType properties[];
    static const Luna<LStretchableLayoutManager>::FunctionType methods[];
    static const Luna<LStretchableLayoutManager>::StaticType statics[];
    static const Luna<LStretchableLayoutManager>::Enum enums[];

private:

    //==============================================================================
    // callbacks

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (LStretchableLayoutManager)
};

#endif // __LUCE_LSTRETCHABLELAYOUTMANAGER_H
