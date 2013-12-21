/************************************************************

 LTextButton.h

    @author Christophe Berbizier (cberbizier@peersuasive.com)
    @license GPLv3
    @copyright 


(c) 2013, Peersuasive Technologies

*************************************************************/

#ifndef __LUCE_TEXT_BUTTON_H
#define __LUCE_TEXT_BUTTON_H

class LTextButton : public LComponent,
                    public TextButton,
                    public ButtonListener
{
public:
    LTextButton(lua_State *L);
    ~LTextButton();

    int setButtonText(lua_State *L);
    int getButtonText(lua_State *L);
    void buttonClicked (Button* buttonThatWasClicked);
    int buttonClicked (lua_State *L);

    static const char className[];
    static const Luna<LTextButton>::Inheritence inherits[];
    static const Luna<LTextButton>::InheritenceF inheritsF[];
    static const Luna<LTextButton>::PropertyType properties[];
    static const Luna<LTextButton>::FunctionType methods[];

private:
    //==============================================================================
    virtual void resized() override;

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (LTextButton)
};

#endif // __LUCE_TEXT_BUTTON_H
