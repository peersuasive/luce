/************************************************************

 LImageButton.h

    @author Christophe Berbizier (cberbizier@peersuasive.com)
    @license GPLv3
    @copyright 


(c) 2013, Peersuasive Technologies

*************************************************************/

#ifndef __LUCE_LIMAGEBUTTON_H
#define __LUCE_LIMAGEBUTTON_H

class LImageButton
    : public LButton,
      public ImageButton,
      public Button::Listener
{
public:    
    LImageButton(lua_State*);
    ~LImageButton();
    
    //==============================================================================
    int setImages(lua_State*);
    int getNormalImage(lua_State*);
    int getOverImage(lua_State*);
    int getDownImage(lua_State*);
    
    //==============================================================================
    int addListener(lua_State*);
    int removeListener(lua_State*);

    //==============================================================================
    static const char className[];
    static const Luna<LImageButton>::Inheritence inherits[];
    static const Luna<LImageButton>::InheritenceF inheritsF[];
    static const Luna<LImageButton>::PropertyType properties[];
    static const Luna<LImageButton>::FunctionType methods[];
    static const Luna<LImageButton>::StaticType statics[];
    
    static const Luna<LImageButton>::Enum enums[];
private:    
    //==============================================================================
    virtual void paintButton(Graphics&, bool isMouseOverButton, bool isButtonDown) override;
    virtual void buttonStateChanged() override;
    virtual void buttonClicked (Button* buttonThatWasClicked) override;

    virtual void mouseMove (const MouseEvent&) override;
    virtual void mouseEnter (const MouseEvent&) override;
    virtual void mouseExit (const MouseEvent&) override;
    virtual void mouseDown (const MouseEvent&) override;
    virtual void mouseDrag (const MouseEvent&) override;
    virtual void mouseUp (const MouseEvent&) override;
    virtual void mouseDoubleClick (const MouseEvent&) override;
    virtual void mouseWheelMove (const MouseEvent&, const MouseWheelDetails&) override;
    virtual void mouseMagnify (const MouseEvent&, float scaleFactor) override;

    virtual bool keyPressed(const KeyPress&) override;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (LImageButton)
};

#endif // __LUCE_LIMAGEBUTTON
