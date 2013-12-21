/************************************************************

 LLabel.h

    @author Christophe Berbizier (cberbizier@peersuasive.com)
    @license GPLv3
    @copyright 


(c) 2013, Peersuasive Technologies

*************************************************************/

#ifndef __LLABEL_BUTTON_H
#define __LLABEL_BUTTON_H

class LLabel : public LComponent,
               public Label,
               private Label::Listener
{
public:
    LLabel(lua_State *L);
    ~LLabel();
    

    int setText(lua_State*);
    int getText(lua_State*);

    int attachToComponent(lua_State*);
    int isAttachedOnLeft(lua_State*);
    int setEditable(lua_State*); // bool sc, bool dc, bool lostOfFocusDiscardChanges
    int isEditable(lua_State*);
    int labelTextChanged(lua_State*);

    int addListener(lua_State*);
    int removeListener(lua_State*);

    static const char className[];
    static const Luna<LLabel>::Inheritence inherits[];
    static const Luna<LLabel>::InheritenceF inheritsF[];
    static const Luna<LLabel>::PropertyType properties[];
    static const Luna<LLabel>::FunctionType methods[];

private:
    //==============================================================================
    virtual void labelTextChanged(Label*) override;

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (LLabel)
};

#endif // __LLABEL_BUTTON_H
