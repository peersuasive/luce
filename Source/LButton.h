/************************************************************

 LButton.h

    @author Christophe Berbizier (cberbizier@peersuasive.com)
    @license GPLv3
    @copyright 


(c) 2013, Peersuasive Technologies

*************************************************************/

#ifndef __LUCE_LBUTTON_H
#define __LUCE_LBUTTON_H

class LButton : public LComponent
{
public:
    LButton(lua_State*, Button* child = nullptr, const String& name = String::empty);
    ~LButton();
    
    //==============================================================================
    int setClickingTogglesState(lua_State*);
    int getClickingTogglesState(lua_State*);
    int setToggleState(lua_State*);
    int getToggleState(lua_State*);
    int setRadioGroupId(lua_State*);
    int getRadioGroupId(lua_State*);
    int setTooltip(lua_State*);
    int getTooltip(lua_State*);
    int setButtonText(lua_State*);
    int getButtonText(lua_State*);
    
    //==============================================================================
    //int removeListener(lua_State*);
    int setConnectedEdges(lua_State*);
    //int addListener(lua_State*);
    int addShortcut(lua_State*);
    int setState(lua_State*);
    int clearShortcuts(lua_State*);
    int setCommandToTrigger(lua_State*);
    int setTriggeredOnMouseDown(lua_State*);
    int setRepeatSpeed(lua_State*);
    
    //==============================================================================
    int getConnectedEdgeFlags(lua_State*);
    int isConnectedOnRight(lua_State*);
    int isConnectedOnTop(lua_State*);
    int isOver(lua_State*);
    int isDown(lua_State*);
    int isConnectedOnLeft(lua_State*);
    int isConnectedOnBottom(lua_State*);
    int isRegisteredForShortcut(lua_State*);
    int getMillisecondsSinceButtonDown(lua_State*);
    int getCommandID(lua_State*);
    int getToggleStateValue(lua_State*);
    
    //==============================================================================
    int paintButton(lua_State*);
    int clicked(lua_State*);
    int internalClickCallback(lua_State*);
    int triggerClick(lua_State*);
    int buttonStateChanged(lua_State*);
    
    // Button::Listener
    int buttonClicked(lua_State*);

    static const char className[];
    static const Luna<LButton>::Inheritence inherits[];
    static const Luna<LButton>::InheritenceF inheritsF[];
    static const Luna<LButton>::PropertyType properties[];
    static const Luna<LButton>::FunctionType methods[];
    
protected:
    //==============================================================================
    void lpaintButton( Graphics& g,bool isMouseOverButton,bool isButtonDown );
    void lclicked( const ModifierKeys& modifiers );
    void linternalClickCallback( const ModifierKeys& modifierKeys_ );
    void ltriggerClick();
    void lbuttonStateChanged();

    // Button::Listener
    void lbuttonClicked(Button*);
    
private:
    //==============================================================================
    ScopedPointer<Button> child;
    
    //==============================================================================
    lua_State *L;
    
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (LButton)
};

#endif // __LUCE_LBUTTON_H
