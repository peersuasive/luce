/************************************************************

 LHyperlinkButton.h

    @author Christophe Berbizier (cberbizier@peersuasive.com)
    @license GPLv3
    @copyright 


(c) 2014, Peersuasive Technologies

*************************************************************/

#ifndef __LUCE_LHYPERLINKBUTTON_H
#define __LUCE_LHYPERLINKBUTTON_H

class LHyperlinkButton
    : public LButton,
      public HyperlinkButton,
      public Button::Listener

{
public:
    LHyperlinkButton(lua_State*);
    ~LHyperlinkButton();
    
    //==============================================================================
    int addListener(lua_State*);
    int removeListener(lua_State*);

    //==============================================================================
    int setURL(lua_State*);
    int getURL(lua_State*);

    //==============================================================================
    int setFont(lua_State*);
    int changeWidthToFitText(lua_State*);

    //==============================================================================
    static const char className[];
    static const Luna<LHyperlinkButton>::Inheritence inherits[];
    static const Luna<LHyperlinkButton>::InheritenceF inheritsF[];
    static const Luna<LHyperlinkButton>::PropertyType properties[];
    static const Luna<LHyperlinkButton>::FunctionType methods[];
    static const Luna<LHyperlinkButton>::StaticType statics[];
    static const Luna<LHyperlinkButton>::Enum enums[];

private:
    //==============================================================================
    // callbacks
    virtual void paintButton(Graphics&, bool, bool) override;
    virtual void buttonStateChanged() override;
    virtual void buttonClicked (Button* buttonThatWasClicked) override;

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (LHyperlinkButton)
};

#endif // __LUCE_LHYPERLINKBUTTON_H
