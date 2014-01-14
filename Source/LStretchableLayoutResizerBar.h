/************************************************************

 LStretchableLayoutResizerBar.h

    @author Christophe Berbizier (cberbizier@peersuasive.com)
    @license GPLv3
    @copyright 


(c) 2013, Peersuasive Technologies

*************************************************************/

#ifndef __LUCE_LSTRETCHABLELAYOUTRESIZERBAR_H
#define __LUCE_LSTRETCHABLELAYOUTRESIZERBAR_H

class LStretchableLayoutResizerBar
    : public LComponent,
      public StretchableLayoutResizerBar
{
public:
    LStretchableLayoutResizerBar(lua_State*);
    ~LStretchableLayoutResizerBar();

    //==============================================================================
    //int mouseDrag(lua_State*);
    //int paint(lua_State*);
    //int mouseDown(lua_State*);

    //==============================================================================
    int hasBeenMoved(lua_State*);

    int mouseDrag(lua_State*);

    static const char className[];
    static const Luna<LStretchableLayoutResizerBar>::Inheritence inherits[];
    static const Luna<LStretchableLayoutResizerBar>::InheritenceF inheritsF[];
    static const Luna<LStretchableLayoutResizerBar>::PropertyType properties[];
    static const Luna<LStretchableLayoutResizerBar>::FunctionType methods[];
    static const Luna<LStretchableLayoutResizerBar>::Enum enums[];

private:

    //==============================================================================
    // callbacks
    virtual void hasBeenMoved() override;
    void mouseDoubleClick (const MouseEvent&) override;

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (LStretchableLayoutResizerBar)
};

#endif // __LUCE_LSTRETCHABLELAYOUTRESIZERBAR_H
