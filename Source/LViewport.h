/************************************************************

 LViewport.h

    @author Christophe Berbizier (cberbizier@peersuasive.com)
    @license GPLv3
    @copyright 


(c) 2014, Peersuasive Technologies

*************************************************************/

#ifndef __LUCE_LVIEWPORT_H
#define __LUCE_LVIEWPORT_H

class LViewport
    : public LComponent,
      public Viewport
{
public:
    LViewport(lua_State*);
    ~LViewport();

    //==============================================================================
    static int s_respondsToKey(lua_State*);

    //==============================================================================
    int setViewPosition(lua_State*);
    int getViewPosition(lua_State*);
    int setScrollBarThickness(lua_State*);
    int getScrollBarThickness(lua_State*);
    int setViewedComponent(lua_State*);
    int getViewedComponent(lua_State*);

    //==============================================================================
    int useMouseWheelMoveIfNeeded(lua_State*);
    int getViewArea(lua_State*);
    int getVerticalScrollBar(lua_State*);
    int getHorizontalScrollBar(lua_State*);
    int getViewWidth(lua_State*);
    int getMaximumVisibleHeight(lua_State*);
    int getViewHeight(lua_State*);
    int autoScroll(lua_State*);
    int isHorizontalScrollBarShown(lua_State*);
    int isVerticalScrollBarShown(lua_State*);
    int getMaximumVisibleWidth(lua_State*);
    int getViewPositionY(lua_State*);
    int getViewPositionX(lua_State*);

    //==============================================================================
    int setViewPositionProportionately(lua_State*);
    int componentMovedOrResized(lua_State*);
    int scrollBarMoved(lua_State*);
    int setSingleStepSizes(lua_State*);
    int setScrollBarsShown(lua_State*);

    //==============================================================================
    int visibleAreaChanged(lua_State*);
    int viewedComponentChanged(lua_State*);

    //==============================================================================
    static const char className[];
    static const Luna<LViewport>::Inheritence inherits[];
    static const Luna<LViewport>::InheritenceF inheritsF[];
    static const Luna<LViewport>::PropertyType properties[];
    static const Luna<LViewport>::FunctionType methods[];
    static const Luna<LViewport>::StaticType statics[];
    static const Luna<LViewport>::Enum enums[];

private:

    //==============================================================================
    // callbacks
    virtual void visibleAreaChanged( const Rectangle<int>& newVisibleArea ) override;
    virtual void viewedComponentChanged( Component* newComponent ) override;

    virtual void mouseMove(const MouseEvent&) override;
    virtual void mouseEnter(const MouseEvent&) override;
    virtual void mouseExit(const MouseEvent&) override;
    virtual void mouseDown(const MouseEvent&) override;
    virtual void mouseDrag(const MouseEvent&) override;
    virtual void mouseUp(const MouseEvent&) override;
    virtual void mouseDoubleClick(const MouseEvent&) override;
    virtual void mouseWheelMove(const MouseEvent&, const MouseWheelDetails&) override;
    //virtual void mouseMagnify(const MouseEvent&, float&) override;
    virtual bool keyPressed(const KeyPress&) override;

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (LViewport)
};

#endif // __LUCE_LVIEWPORT_H
