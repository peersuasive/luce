/************************************************************

 LSlider.h

    @author Christophe Berbizier (cberbizier@peersuasive.com)
    @license GPLv3
    @copyright 


(c) 2014, Peersuasive Technologies

*************************************************************/

#ifndef __LUCE_LSLIDER_H
#define __LUCE_LSLIDER_H

class LSlider
    : public LComponent,
      public Slider, private Slider::Listener
{
public:
    LSlider(lua_State*);
    ~LSlider();

    //==============================================================================
    int setTextValueSuffix(lua_State*);
    int getTextValueSuffix(lua_State*);
    int setSliderSnapsToMousePosition(lua_State*);
    int getSliderSnapsToMousePosition(lua_State*);
    int setVelocityBasedMode(lua_State*);
    int getVelocityBasedMode(lua_State*);
    int setDoubleClickReturnValue(lua_State*);
    int getDoubleClickReturnValue(lua_State*);
    int setMaxValue(lua_State*);
    int getMaxValue(lua_State*);
    int setSliderStyle(lua_State*);
    int getSliderStyle(lua_State*);
    int setValue(lua_State*);
    int getValue(lua_State*);
    int setMinValue(lua_State*);
    int getMinValue(lua_State*);
    int setMouseDragSensitivity(lua_State*);
    int getMouseDragSensitivity(lua_State*);
    int setSkewFactor(lua_State*);
    int getSkewFactor(lua_State*);

    //==============================================================================
    int isHorizontal(lua_State*);
    int getVelocityOffset(lua_State*);
    int snapValue(lua_State*);
    int getMinimum(lua_State*);
    int isTextBoxEditable(lua_State*);
    int getValueFromText(lua_State*);
    int getTextBoxWidth(lua_State*);
    int getNumDecimalPlacesToDisplay(lua_State*);
    int getThumbBeingDragged(lua_State*);
    int getPositionOfValue(lua_State*);
    int getInterval(lua_State*);
    int getTextBoxPosition(lua_State*);
    int getMaximum(lua_State*);
    int getMaxValueObject(lua_State*);
    int getMinValueObject(lua_State*);
    int proportionOfLengthToValue(lua_State*);
    int valueToProportionOfLength(lua_State*);
    int getTextFromValue(lua_State*);
    int isVertical(lua_State*);
    int getValueObject(lua_State*);
    int getCurrentPopupDisplay(lua_State*);
    int getVelocityThreshold(lua_State*);
    int getTextBoxHeight(lua_State*);
    int getVelocitySensitivity(lua_State*);
    int getVelocityModeIsSwappable(lua_State*);

    //==============================================================================
    int setSkewFactorFromMidPoint(lua_State*);
    int setScrollWheelEnabled(lua_State*);
    int setTextBoxStyle(lua_State*);
    int setChangeNotificationOnlyOnRelease(lua_State*);
    int setTextBoxIsEditable(lua_State*);
    int showTextBox(lua_State*);
    int setVelocityModeParameters(lua_State*);
    int setPopupDisplayEnabled(lua_State*);
    int removeListener(lua_State*);
    int addListener(lua_State*);
    int setMinAndMaxValues(lua_State*);
    int updateText(lua_State*);
    int setPopupMenuEnabled(lua_State*);
    int setRotaryParameters(lua_State*);
    int setIncDecButtonsMode(lua_State*);
    int hideTextBox(lua_State*);
    int setRange(lua_State*);

    //==============================================================================
    int stoppedDragging(lua_State*);
    int startedDragging(lua_State*);
    int valueChanged(lua_State*);

    int sliderValueChanged(lua_State*);
    int sliderDragStarted(lua_State*);
    int sliderDragEnded(lua_State*);

    //==============================================================================
    static const char className[];
    static const Luna<LSlider>::Inheritence inherits[];
    static const Luna<LSlider>::InheritenceF inheritsF[];
    static const Luna<LSlider>::PropertyType properties[];
    static const Luna<LSlider>::FunctionType methods[];
    static const Luna<LSlider>::StaticType statics[];
    static const Luna<LSlider>::Enum enums[];

private:

    //==============================================================================
    // callbacks
    virtual void stoppedDragging() override;
    virtual void startedDragging() override;
    virtual void valueChanged() override;

    virtual void sliderValueChanged(Slider*) override;
    virtual void sliderDragStarted(Slider*) override;
    virtual void sliderDragEnded(Slider*) override;

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
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (LSlider)
};

#endif // __LUCE_LSLIDER_H
