/************************************************************

 LModifierKeys.h

    @author Christophe Berbizier (cberbizier@peersuasive.com)
    @license GPLv3
    @copyright 


(c) 2013, Peersuasive Technologies

*************************************************************/

#ifndef __LUCE_LMODIFIERKEYS_H
#define __LUCE_LMODIFIERKEYS_H

class LModifierKeys
    : public LBase,
      public ModifierKeys
{
public:
    LModifierKeys(lua_State*);
    LModifierKeys(lua_State*, const ModifierKeys&);
    ~LModifierKeys();

    //==============================================================================
    int isLeftButtonDown(lua_State*);
    int getNumMouseButtonsDown(lua_State*);
    int isAnyMouseButtonDown(lua_State*);
    int isRightButtonDown(lua_State*);
    int isMiddleButtonDown(lua_State*);

    int isAnyModifierKeyDown(lua_State*);
    int isCtrlDown(lua_State*);
    int isCommandDown(lua_State*);
    int isShiftDown(lua_State*);
    int isAltDown(lua_State*);

    int isPopupMenu(lua_State*);

    int testFlags(lua_State*);
    int getRawFlags(lua_State*);

    int withOnlyMouseButtons(lua_State*);
    int withoutMouseButtons(lua_State*);
    int withFlags(lua_State*);
    int withoutFlags(lua_State*);

    int getCurrentModifiers(lua_State*);
    int getCurrentModifiersRealtime(lua_State*);

    //==============================================================================

    static const char className[];
    static const Luna<LModifierKeys>::Inheritence inherits[];
    static const Luna<LModifierKeys>::InheritenceF inheritsF[];
    static const Luna<LModifierKeys>::PropertyType properties[];
    static const Luna<LModifierKeys>::FunctionType methods[];
    static const Luna<LModifierKeys>::StaticType statics[];
    static const Luna<LModifierKeys>::Enum enums[];

private:

    //==============================================================================
    // callbacks

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (LModifierKeys)
};

#endif // __LUCE_LMODIFIERKEYS_H
