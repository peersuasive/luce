/************************************************************

 LKeyPress.h

    @author Christophe Berbizier (cberbizier@peersuasive.com)
    @license GPLv3
    @copyright 


(c) 2013, Peersuasive Technologies

*************************************************************/

#ifndef __LUCE_LKEYPRESS_H
#define __LUCE_LKEYPRESS_H

class LKeyPress
    : public LBase,
      public KeyPress
{
public:
    LKeyPress(lua_State*);
    LKeyPress(lua_State*, const KeyPress& class_);
    static int lnew(lua_State*);
    ~LKeyPress();

    //==============================================================================
    int getTextCharacter(lua_State*);
    int getTextDescriptionWithIcons(lua_State*);
    int getTextDescription(lua_State*);
    int isCurrentlyDown(lua_State*);
    int getKeyCode(lua_State*);
    int isKeyCode(lua_State*);
    int isKeyCurrentlyDown(lua_State*);
    int createFromDescription(lua_State*);
    int isValid(lua_State*);
    int getModifiers(lua_State*);

    //==============================================================================

    static const char className[];
    static const Luna<LKeyPress>::Inheritence inherits[];
    static const Luna<LKeyPress>::InheritenceF inheritsF[];
    static const Luna<LKeyPress>::PropertyType properties[];
    static const Luna<LKeyPress>::FunctionType methods[];
    static const Luna<LKeyPress>::StaticType statics[];
    static const Luna<LKeyPress>::Enum enums[];

private:
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (LKeyPress)
};

#endif // __LUCE_LKEYPRESS_H
