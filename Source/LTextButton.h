/************************************************************

 LTextButton.h

    @author Christophe Berbizier (cberbizier@peersuasive.com)
    @license GPLv3
    @copyright 


(c) 2013, Peersuasive Technologies

*************************************************************/

#ifndef __LUCE_LTEXTBUTTON_H
#define __LUCE_LTEXTBUTTON_H

class LTextButton
    : public LButton,
      public TextButton,
      public Button::Listener
{
public:    
    LTextButton(lua_State*);
    ~LTextButton();
    
    //==============================================================================
    int changeWidthToFitText(lua_State*);
    int paintButton(lua_State*);
    int colourChanged(lua_State*);
    
    //==============================================================================
    int getFont(lua_State*);
    
    //==============================================================================
    int addListener(lua_State*);
    int removeListener(lua_State*);

    //==============================================================================
    static const char className[];
    static const Luna<LTextButton>::Inheritence inherits[];
    static const Luna<LTextButton>::InheritenceF inheritsF[];
    static const Luna<LTextButton>::PropertyType properties[];
    static const Luna<LTextButton>::FunctionType methods[];
    static const Luna<LTextButton>::StaticType statics[];
    
    static const Luna<LTextButton>::Enum enums[];
private:    
    
    //==============================================================================
    // callbacks
    virtual void buttonStateChanged() override;
    virtual void buttonClicked (Button* buttonThatWasClicked) override;

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (LTextButton)
};

#endif // __LUCE_LTEXTBUTTON_H
