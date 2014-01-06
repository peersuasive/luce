/************************************************************

 LMouseEvent.h

    @author Christophe Berbizier (cberbizier@peersuasive.com)
    @license GPLv3
    @copyright 


(c) 2013, Peersuasive Technologies

*************************************************************/

#ifndef __LUCE_LMOUSEEVENT_H
#define __LUCE_LMOUSEEVENT_H

class LMouseEvent
    : public LBase,
      public MouseEvent
{
public:
    LMouseEvent(lua_State*);
    LMouseEvent(lua_State*, const MouseEvent&);
    ~LMouseEvent();

    //==============================================================================
    int setDoubleClickTimeout(lua_State*);
    int getDoubleClickTimeout(lua_State*);

    //==============================================================================

    //==============================================================================
    int getMouseDownY(lua_State*);
    int getMouseDownScreenX(lua_State*);
    int getNumberOfClicks(lua_State*);
    int mouseWasClicked(lua_State*);
    int getEventRelativeTo(lua_State*);
    int getDistanceFromDragStartX(lua_State*);
    int getScreenPosition(lua_State*);
    int getPosition(lua_State*);
    int withNewPosition(lua_State*);
    int getMouseDownX(lua_State*);
    int getDistanceFromDragStartY(lua_State*);
    int getMouseDownScreenY(lua_State*);
    int getScreenX(lua_State*);
    int getScreenY(lua_State*);
    int getDistanceFromDragStart(lua_State*);
    int getMouseDownScreenPosition(lua_State*);
    int getOffsetFromDragStart(lua_State*);
    int getLengthOfMousePress(lua_State*);
    int getMouseDownPosition(lua_State*);

    //==============================================================================

    static const char className[];
    static const Luna<LMouseEvent>::Inheritence inherits[];
    static const Luna<LMouseEvent>::InheritenceF inheritsF[];
    static const Luna<LMouseEvent>::PropertyType properties[];
    static const Luna<LMouseEvent>::FunctionType methods[];
    static const Luna<LMouseEvent>::Enum enums[];

    //typedef ReferenceCountedObjectPtr<LMouseEvent> Ptr;

private:
    //==============================================================================

    //==============================================================================
    // callbacks

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (LMouseEvent)
};

#endif // __LUCE_LMOUSEEVENT_H
