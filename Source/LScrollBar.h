/************************************************************

 LScrollBar.h

    @author Christophe Berbizier (cberbizier@peersuasive.com)
    @license GPLv3
    @copyright 


(c) 2014, Peersuasive Technologies

*************************************************************/

#ifndef __LUCE_LSCROLLBAR_H
#define __LUCE_LSCROLLBAR_H

class LScrollBar
    : public LComponent,
      public ScrollBar
{
public:
    LScrollBar(lua_State*);
    LScrollBar(lua_State*, bool isVertical);
    static int lnew(lua_State*);
    ~LScrollBar();

    //==============================================================================
    int setCurrentRange(lua_State*);
    int getCurrentRange(lua_State*);
    int setCurrentRangeStart(lua_State*);
    int getCurrentRangeStart(lua_State*);

    //==============================================================================
    int autoHides(lua_State*);
    int getMaximumRangeLimit(lua_State*);
    int moveScrollbarInPages(lua_State*);
    int isVertical(lua_State*);
    int getRangeLimit(lua_State*);
    int scrollToBottom(lua_State*);
    int moveScrollbarInSteps(lua_State*);
    int getCurrentRangeSize(lua_State*);
    int getMinimumRangeLimit(lua_State*);
    int scrollToTop(lua_State*);

    //==============================================================================
    int addListener(lua_State*);
    int setOrientation(lua_State*);
    int removeListener(lua_State*);
    int setSingleStepSize(lua_State*);
    int setAutoHide(lua_State*);
    int setButtonRepeatSpeed(lua_State*);
    int setRangeLimits(lua_State*);

    //==============================================================================
    static const char className[];
    static const Luna<LScrollBar>::Inheritence inherits[];
    static const Luna<LScrollBar>::InheritenceF inheritsF[];
    static const Luna<LScrollBar>::PropertyType properties[];
    static const Luna<LScrollBar>::FunctionType methods[];
    static const Luna<LScrollBar>::StaticType statics[];
    static const Luna<LScrollBar>::Enum enums[];

private:
    virtual void mouseMove(const MouseEvent&) override;
    virtual void mouseEnter(const MouseEvent&) override;
    virtual void mouseExit(const MouseEvent&) override;
    virtual void mouseDown(const MouseEvent&) override;
    virtual void mouseDrag(const MouseEvent&) override;
    virtual void mouseUp(const MouseEvent&) override;
    virtual void mouseDoubleClick(const MouseEvent&) override;
    virtual void mouseWheelMove(const MouseEvent&, const MouseWheelDetails&) override;
    virtual bool keyPressed(const KeyPress&) override;

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (LScrollBar)
};

#endif // __LUCE_LSCROLLBAR_H
