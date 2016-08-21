/************************************************************

 LMouseInputSource.h

    @author Christophe Berbizier (cberbizier@peersuasive.com)
    @license GPLv3
    @copyright 


(c) 2014, Peersuasive Technologies

*************************************************************/

#ifndef __LUCE_LMOUSEINPUTSOURCE_H
#define __LUCE_LMOUSEINPUTSOURCE_H

class LMouseInputSource
    : public LBase,
      public MouseInputSource
{
public:
    LMouseInputSource(lua_State*);
    LMouseInputSource(lua_State*, const MouseInputSource*);
    LMouseInputSource(lua_State*, const MouseInputSource&);

    ~LMouseInputSource();

    //==============================================================================
    int setScreenPosition(lua_State*);
    int getScreenPosition(lua_State*);

    //==============================================================================
    int getIndex(lua_State*);
    int getLastMouseDownPosition(lua_State*);
    int getComponentUnderMouse(lua_State*);
    int getCurrentPressure(lua_State*);
    int hasMouseWheel(lua_State*);
    int getCurrentModifiers(lua_State*);
    int isPressureValid(lua_State*);
    int hasMouseCursor(lua_State*);
    int isUnboundedMouseMovementEnabled(lua_State*);
    int getLastMouseDownTime(lua_State*);
    int canDoUnboundedMovement(lua_State*);
    int isTouch(lua_State*);
    int isMouse(lua_State*);
    int canHover(lua_State*);
    int hasMouseMovedSignificantlySincePressed(lua_State*);
    int getNumberOfMultipleClicks(lua_State*);
    int isDragging(lua_State*);

    //==============================================================================
    int forceMouseCursorUpdate(lua_State*);
    int hideCursor(lua_State*);
    int showMouseCursor(lua_State*);
    int triggerFakeMove(lua_State*);
    int revealCursor(lua_State*);
    int enableUnboundedMouseMovement(lua_State*);

    //==============================================================================
    static const char className[];
    static const Luna<LMouseInputSource>::Inheritence inherits[];
    static const Luna<LMouseInputSource>::InheritenceF inheritsF[];
    static const Luna<LMouseInputSource>::PropertyType properties[];
    static const Luna<LMouseInputSource>::FunctionType methods[];
    static const Luna<LMouseInputSource>::StaticType statics[];
    static const Luna<LMouseInputSource>::Enum enums[];

private:
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (LMouseInputSource)
};

#endif // __LUCE_LMOUSEINPUTSOURCE_H
