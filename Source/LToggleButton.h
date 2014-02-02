/************************************************************

 LToggleButton.h

    @author Christophe Berbizier (cberbizier@peersuasive.com)
    @license GPLv3
    @copyright 


(c) 2013, Peersuasive Technologies

*************************************************************/

#ifndef __LUCE_LTOGGLEBUTTON_H
#define __LUCE_LTOGGLEBUTTON_H

class LToggleButton
    : public LButton,
      public ToggleButton,
      public Button::Listener
{
public:
    LToggleButton(lua_State*);
    ~LToggleButton();

    //==============================================================================
    int changeWidthToFitText(lua_State*);
    int paintButton(lua_State*);

    //==============================================================================
    int addListener(lua_State*);
    int removeListener(lua_State*);

    //==============================================================================
    static const char className[];
    static const Luna<LToggleButton>::Inheritence inherits[];
    static const Luna<LToggleButton>::InheritenceF inheritsF[];
    static const Luna<LToggleButton>::PropertyType properties[];
    static const Luna<LToggleButton>::FunctionType methods[];
    static const Luna<LToggleButton>::Enum enums[];

private:
    //==============================================================================
    // callbacks
    virtual void buttonStateChanged() override;
    virtual void buttonClicked (Button* buttonThatWasClicked) override;

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (LToggleButton)
};

#endif // __LUCE_LTOGGLEBUTTON_H
