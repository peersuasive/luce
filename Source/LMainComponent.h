/************************************************************

 LMainComponent.h

    @author Christophe Berbizier (cberbizier@peersuasive.com)
    @license GPLv3
    @copyright 


(c) 2013, Peersuasive Technologies

*************************************************************/

#ifndef __LUCE_MAIN_COMPONENT_WINDOW_H
#define __LUCE_MAIN_COMPONENT_WINDOW_H

class LMainComponent : public LComponent,
                       public Component
{
public:
    LMainComponent(lua_State*);
    ~LMainComponent();

    static const char className[];
    static const Luna<LMainComponent>::Inheritence inherits[];
    static const Luna<LMainComponent>::InheritenceF inheritsF[];
    static const Luna<LMainComponent>::PropertyType properties[];
    static const Luna<LMainComponent>::FunctionType methods[];

    static const Luna<LMainComponent>::Enum enums[];
private:
    //==============================================================================
    virtual void paint (Graphics& g) override;
    virtual void resized () override;

    virtual void mouseMove (const MouseEvent&) override;
    virtual void mouseEnter (const MouseEvent&) override;
    virtual void mouseExit (const MouseEvent&) override;
    virtual void mouseDown (const MouseEvent&) override;
    virtual void mouseDrag (const MouseEvent&) override;
    virtual void mouseUp (const MouseEvent&) override;
    virtual void mouseDoubleClick (const MouseEvent&) override;
    virtual void mouseWheelMove (const MouseEvent&, const MouseWheelDetails&) override;
    virtual void mouseMagnify (const MouseEvent&, float scaleFactor) override;

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (LMainComponent)
};

#endif // __LUCE_MAIN_COMPONENT_WINDOW_H
