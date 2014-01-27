/************************************************************

 LJComponent.h

    @author Christophe Berbizier (cberbizier@peersuasive.com)
    @license GPLv3
    @copyright 


(c) 2013, Peersuasive Technologies

*************************************************************/

#ifndef __LUCE_J_COMPONENT_WINDOW_H
#define __LUCE_J_COMPONENT_WINDOW_H

class LJComponent : public LComponent,
                    public Component
{
public:
    LJComponent(lua_State*);
    ~LJComponent();

    static const char className[];
    static const Luna<LJComponent>::Inheritence inherits[];
    static const Luna<LJComponent>::InheritenceF inheritsF[];
    static const Luna<LJComponent>::PropertyType properties[];
    static const Luna<LJComponent>::FunctionType methods[];

    static const Luna<LJComponent>::Enum enums[];
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
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (LJComponent)
};

#endif // __LUCE_J_COMPONENT_WINDOW_H
