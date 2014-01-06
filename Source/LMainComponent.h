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

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (LMainComponent)
};

#endif // __LUCE_MAIN_COMPONENT_WINDOW_H
