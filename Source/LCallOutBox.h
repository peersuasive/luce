/************************************************************

 LCallOutBox.h

    @author Christophe Berbizier (cberbizier@peersuasive.com)
    @license GPLv3
    @copyright 


(c) 2014, Peersuasive Technologies

*************************************************************/

#ifndef __LUCE_LCALLOUTBOX_H
#define __LUCE_LCALLOUTBOX_H

class LCallOutBox
    : public LComponent,
      public CallOutBox
{
public:
    LCallOutBox(lua_State*);
    LCallOutBox(lua_State*, Component& content, const Rectangle<int>& area, Component* parent = nullptr );
    static int lnew(lua_State*);
    ~LCallOutBox();

    //==============================================================================
    static int s_launchAsynchronously(lua_State*);

    //==============================================================================
    int keyPressed(lua_State*);
    int hitTest(lua_State*);

    //==============================================================================
    int handleCommandMessage(lua_State*);
    int resized(lua_State*);
    int inputAttemptWhenModal(lua_State*);
    int setArrowSize(lua_State*);
    int moved(lua_State*);
    int childBoundsChanged(lua_State*);
    int paint(lua_State*);
    int updatePosition(lua_State*);

    //==============================================================================
    static const char className[];
    static const Luna<LCallOutBox>::Inheritence inherits[];
    static const Luna<LCallOutBox>::InheritenceF inheritsF[];
    static const Luna<LCallOutBox>::PropertyType properties[];
    static const Luna<LCallOutBox>::FunctionType methods[];
    static const Luna<LCallOutBox>::StaticType statics[];
    static const Luna<LCallOutBox>::Enum enums[];

private:
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (LCallOutBox)
};

#endif // __LUCE_LCALLOUTBOX_H
