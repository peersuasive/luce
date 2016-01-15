/************************************************************

 LSystemTrayIconComponent.h

    @author Christophe Berbizier (cberbizier@peersuasive.com)
    @license GPLv3
    @copyright 


(c) 2016, Peersuasive Technologies

*************************************************************/

#ifndef __LUCE_LSYSTEMTRAYICONCOMPONENT_H
#define __LUCE_LSYSTEMTRAYICONCOMPONENT_H

class LSystemTrayIconComponent
    : public LComponent,
      public SystemTrayIconComponent
{
public:
    LSystemTrayIconComponent(lua_State*);
    ~LSystemTrayIconComponent();

    //==============================================================================
    int setIconImage(lua_State*);
    int setIconTooltip(lua_State*);
    int setHighlighted(lua_State*);
    int showInfoBubble(lua_State*);
    int hideInfoBubble(lua_State*);

    //==============================================================================
    static const char className[];
    static const Luna<LSystemTrayIconComponent>::Inheritence inherits[];
    static const Luna<LSystemTrayIconComponent>::InheritenceF inheritsF[];
    static const Luna<LSystemTrayIconComponent>::PropertyType properties[];
    static const Luna<LSystemTrayIconComponent>::FunctionType methods[];
    static const Luna<LSystemTrayIconComponent>::StaticType statics[];
    static const Luna<LSystemTrayIconComponent>::Enum enums[];

private:
    //==============================================================================
    virtual void mouseEnter(const MouseEvent&) override;
    virtual void mouseExit(const MouseEvent&) override;
    virtual void mouseDown(const MouseEvent&) override;
    virtual void mouseUp(const MouseEvent&) override;
    virtual void mouseDoubleClick(const MouseEvent&) override;

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (LSystemTrayIconComponent)
};

#endif // __LUCE_LSYSTEMTRAYICONCOMPONENT_H
