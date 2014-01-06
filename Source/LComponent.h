/************************************************************

 LComponent.h

    @author Christophe Berbizier (cberbizier@peersuasive.com)
    @license GPLv3
    @copyright 


(c) 2013-2014, Peersuasive Technologies

*************************************************************/

#ifndef __LUCE_LCOMPONENT_H
#define __LUCE_LCOMPONENT_H

class LComponent : protected LBase
{
public:    
    LComponent(lua_State*, Component* child = nullptr, const String& name = String::empty);
    ~LComponent();
    
    //==============================================================================
    int setExplicitFocusOrder(lua_State*);
    int getExplicitFocusOrder(lua_State*);
    int setLookAndFeel(lua_State*);
    int getLookAndFeel(lua_State*);
    int setFocusContainer(lua_State*);
    int isFocusContainer(lua_State*);
    int setComponentEffect(lua_State*);
    int getComponentEffect(lua_State*);
    int setBounds(lua_State*);
    int getBounds(lua_State*);
    int setOpaque(lua_State*);
    int isOpaque(lua_State*);
    int setPositioner(lua_State*);
    int getPositioner(lua_State*);
    int setTransform(lua_State*);
    int getTransform(lua_State*);
    int setComponentID(lua_State*);
    int getComponentID(lua_State*);
    int setEnabled(lua_State*);
    int isEnabled(lua_State*);
    int setAlpha(lua_State*);
    int getAlpha(lua_State*);
    int setAlwaysOnTop(lua_State*);
    int isAlwaysOnTop(lua_State*);
    int setMouseCursor(lua_State*);
    int getMouseCursor(lua_State*);
    int setWantsKeyboardFocus(lua_State*);
    int getWantsKeyboardFocus(lua_State*);
    int setCachedComponentImage(lua_State*);
    int getCachedComponentImage(lua_State*);
    int setVisible(lua_State*);
    int isVisible(lua_State*);
    int setBroughtToFrontOnMouseClick(lua_State*);
    int isBroughtToFrontOnMouseClick(lua_State*);
    int setMouseClickGrabsKeyboardFocus(lua_State*);
    int getMouseClickGrabsKeyboardFocus(lua_State*);
    int setName(lua_State*);
    int getName(lua_State*);
    int setSize(lua_State*);
    int getSize(lua_State*);
    
    //==============================================================================
    int enterModalState(lua_State*);
    int setBoundsInset(lua_State*);
    int setRepaintsOnMouseActivity(lua_State*);
    int toFront(lua_State*);
    int addKeyListener(lua_State*);
    int addAndMakeVisible(lua_State*);
    int setTopLeftPosition(lua_State*);
    int removeKeyListener(lua_State*);
    int sendLookAndFeelChange(lua_State*);
    int getWindowHandle(lua_State*);
    int moveKeyboardFocusToSibling(lua_State*);
    int addChildComponent(lua_State*);
    int updateMouseCursor(lua_State*);
    int addMouseListener(lua_State*);
    int removeComponentListener(lua_State*);
    int setPaintingIsUnclipped(lua_State*);
    int unfocusAllComponents(lua_State*);
    int centreWithSize(lua_State*);
    int copyAllExplicitColoursTo(lua_State*);
    int exitModalState(lua_State*);
    int setInterceptsMouseClicks(lua_State*);
    int setTopRightPosition(lua_State*);
    int grabKeyboardFocus(lua_State*);
    int addToDesktop(lua_State*);
    int repaint(lua_State*);
    int setBufferedToImage(lua_State*);
    int setBoundsToFit(lua_State*);
    int addChildAndSetID(lua_State*);
    int getInterceptsMouseClicks(lua_State*);
    int removeMouseListener(lua_State*);
    int beginDragAutoRepeat(lua_State*);
    int setColour(lua_State*);
    int paintEntireComponent(lua_State*);
    int deleteAllChildren(lua_State*);
    int removeColour(lua_State*);
    int setBoundsRelative(lua_State*);
    int setCentrePosition(lua_State*);
    int removeFromDesktop(lua_State*);
    int getVisibleArea(lua_State*);
    int toBehind(lua_State*);
    int removeAllChildren(lua_State*);
    int postCommandMessage(lua_State*);
    int setCentreRelative(lua_State*);
    int toBack(lua_State*);
    int addComponentListener(lua_State*);
    
    //==============================================================================
    int findColour(lua_State*);
    int getRight(lua_State*);
    int getProperties(lua_State*);
    int isParentOf(lua_State*);
    int createComponentSnapshot(lua_State*);
    int getScreenPosition(lua_State*);
    int proportionOfHeight(lua_State*);
    int getX(lua_State*);
    int getY(lua_State*);
    int getHeight(lua_State*);
    int getTopLevelComponent(lua_State*);
    int isMouseOver(lua_State*);
    int reallyContains(lua_State*);
    int localAreaToGlobal(lua_State*);
    int getDesktopScaleFactor(lua_State*);
    int getCurrentlyModalComponent(lua_State*);
    int getParentWidth(lua_State*);
    int getNumCurrentlyModalComponents(lua_State*);
    int hasKeyboardFocus(lua_State*);
    int getScreenY(lua_State*);
    int findChildWithID(lua_State*);
    int hitTest(lua_State*);
    int isMouseOverOrDragging(lua_State*);
    int isTransformed(lua_State*);
    int getWidth(lua_State*);
    int getLocalPoint(lua_State*);
    int getComponentAt(lua_State*);
    int getScreenBounds(lua_State*);
    int getMouseXYRelative(lua_State*);
    int keyStateChanged(lua_State*);
    int getChildComponent(lua_State*);
    int getScreenX(lua_State*);
    int getParentMonitorArea(lua_State*);
    int getLocalArea(lua_State*);
    int isColourSpecified(lua_State*);
    int canModalEventBeSentToComponent(lua_State*);
    int isCurrentlyBlockedByAnotherModalComponent(lua_State*);
    int findParentComponentOfClass(lua_State*);
    int getNumChildComponents(lua_State*);
    int isMouseButtonDownAnywhere(lua_State*);
    int createFocusTraverser(lua_State*);
    int isMouseButtonDown(lua_State*);
    int localPointToGlobal(lua_State*);
    int getPosition(lua_State*);
    int getMarkers(lua_State*);
    int getBoundsInParent(lua_State*);
    int getParentHeight(lua_State*);
    int proportionOfWidth(lua_State*);
    int getBottom(lua_State*);
    int getIndexOfChildComponent(lua_State*);
    int contains(lua_State*);
    int keyPressed(lua_State*);
    int getPeer(lua_State*);
    int isShowing(lua_State*);
    int getLocalBounds(lua_State*);
    int getParentComponent(lua_State*);
    int isCurrentlyModal(lua_State*);
    int getCurrentlyFocusedComponent(lua_State*);
    int isOnDesktop(lua_State*);
    
    //==============================================================================
    int childrenChanged(lua_State*);
    int parentHierarchyChanged(lua_State*);
    int colourChanged(lua_State*);
    int mouseWheelMove(lua_State*);
    int lookAndFeelChanged(lua_State*);
    int userTriedToCloseWindow(lua_State*);
    int modifierKeysChanged(lua_State*);
    int broughtToFront(lua_State*);
    int parentSizeChanged(lua_State*);
    int visibilityChanged(lua_State*);
    int mouseDoubleClick(lua_State*);
    int inputAttemptWhenModal(lua_State*);
    int paint(lua_State*);
    int handleCommandMessage(lua_State*);
    int resized(lua_State*);
    int focusGained(lua_State*);
    int mouseDrag(lua_State*);
    int paintOverChildren(lua_State*);
    int moved(lua_State*);
    int childBoundsChanged(lua_State*);
    int mouseMove(lua_State*);
    int focusLost(lua_State*);
    int mouseExit(lua_State*);
    int minimisationStateChanged(lua_State*);
    int mouseEnter(lua_State*);
    int mouseMagnify(lua_State*);
    int mouseUp(lua_State*);
    int enablementChanged(lua_State*);
    int mouseDown(lua_State*);
    int focusOfChildComponentChanged(lua_State*);
    
    //==============================================================================
    static const char className[];
    static const Luna<LComponent>::Inheritence inherits[];
    static const Luna<LComponent>::InheritenceF inheritsF[];
    static const Luna<LComponent>::PropertyType properties[];
    static const Luna<LComponent>::FunctionType methods[];
    
    static const Luna<LComponent>::Enum enums[];
protected:    
    //==============================================================================
    String myName;

    //==============================================================================
    // now in LBase
    //void reg( const String& );
    //void set( const String& r, int lua_type = LUA_TFUNCTION, int pos = -1);
    //int callback(const String&, int nb_res = 0, const std::list<var>& args = {}) const;

    enum xFocusChangeType
    {
        focusChangedByMouseClick,   /**< Means that the user clicked the mouse to change focus. */
        focusChangedByTabKey,       /**< Means that the user pressed the tab key to move the focus. */
        focusChangedDirectly        /**< Means that the focus was changed by a call to grabKeyboardFocus(). */
    };


    //==============================================================================
    void lchildrenChanged();
    void lparentHierarchyChanged();
    void lcolourChanged();
    void lmouseWheelMove( const MouseEvent& event,const MouseWheelDetails& wheel );
    void llookAndFeelChanged();
    void luserTriedToCloseWindow();
    void lmodifierKeysChanged( const ModifierKeys& modifiers );
    void lbroughtToFront();
    void lparentSizeChanged();
    void lvisibilityChanged();
    void lmouseDoubleClick( const MouseEvent& event );
    void linputAttemptWhenModal();
    void lpaint( Graphics& g );
    void lhandleCommandMessage( int commandId );
    void lresized();
    void lfocusGained( Component::FocusChangeType cause );
    void lmouseDrag( const MouseEvent& event );
    void lpaintOverChildren( Graphics& g );
    void lmoved();
    void lchildBoundsChanged( Component* child );
    void lmouseMove( const MouseEvent& event );
    void lfocusLost( Component::FocusChangeType cause );
    void lmouseExit( const MouseEvent& event );
    void lminimisationStateChanged( bool isNowMinimised );
    void lmouseEnter( const MouseEvent& event );
    void lmouseMagnify( const MouseEvent& event,float scaleFactor );
    void lmouseUp( const MouseEvent& event );
    void lenablementChanged();
    void lmouseDown( const MouseEvent& event );
    void lfocusOfChildComponentChanged( Component::FocusChangeType cause );
    
private:    
    //==============================================================================
    ScopedPointer<Component> child;
    
    //==============================================================================
    lua_State *L;
    
    //==============================================================================
    // LBase
    //HashMap<String,int> cb;

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (LComponent)
};

#endif // __LUCE_LCOMPONENT_H
