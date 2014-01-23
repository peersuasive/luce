/************************************************************

 LLabel.h

    @author Christophe Berbizier (cberbizier@peersuasive.com)
    @license GPLv3
    @copyright 


(c) 2013, Peersuasive Technologies

*************************************************************/

#ifndef __LUCE_LLABEL_H
#define __LUCE_LLABEL_H

class LLabel
    : public LComponent,
      public Label, private Label::Listener
{
public:
    LLabel(lua_State*);
    ~LLabel();

    //==============================================================================
    int setJustificationType(lua_State*);
    int getJustificationType(lua_State*);
    int setEditable(lua_State*);
    int isEditable(lua_State*);
    int setMinimumHorizontalScale(lua_State*);
    int getMinimumHorizontalScale(lua_State*);
    int setFont(lua_State*);
    int getFont(lua_State*);
    int setText(lua_State*);
    int getText(lua_State*);

    //==============================================================================
    int textEditorFocusLost(lua_State*);
    int setBorderSize(lua_State*);

    int textEditorTextChanged(lua_State*);
    int valueChanged(lua_State*);
    int inputAttemptWhenModal(lua_State*);

    int textEditorReturnKeyPressed(lua_State*);
    int textEditorEscapeKeyPressed(lua_State*);
    int showEditor(lua_State*);
    
    int hideEditor(lua_State*);
    int attachToComponent(lua_State*);

    int addListener(lua_State*);
    int removeListener(lua_State*);
    
    //int componentVisibilityChanged(lua_State*);
    //int componentParentHierarchyChanged(lua_State*);
    //int callChangeListeners(lua_State*);

    //==============================================================================
    int getAttachedComponent(lua_State*);
    int isBeingEdited(lua_State*);
    int isEditableOnSingleClick(lua_State*);
    int getHorizontalBorderSize(lua_State*);
    int getVerticalBorderSize(lua_State*);
    int createEditorComponent(lua_State*);
    int doesLossOfFocusDiscardChanges(lua_State*);
    int getTextValue(lua_State*);
    int isEditableOnDoubleClick(lua_State*);
    int isAttachedOnLeft(lua_State*);
    int getCurrentTextEditor(lua_State*);

    //==============================================================================
    int labelTextChanged(lua_State*);

    int textWasChanged(lua_State*);
    int editorAboutToBeHidden(lua_State*);
    int editorShown(lua_State*);
    int textWasEdited(lua_State*);

    static const char className[];
    static const Luna<LLabel>::Inheritence inherits[];
    static const Luna<LLabel>::InheritenceF inheritsF[];
    static const Luna<LLabel>::PropertyType properties[];
    static const Luna<LLabel>::FunctionType methods[];
    static const Luna<LLabel>::Enum enums[];

private:
    //==============================================================================
    ScopedPointer<LFont> myFont;

    //==============================================================================
    // callbacks
    virtual void labelTextChanged(Label*) override;

    virtual void textWasChanged() override;
    virtual void editorAboutToBeHidden( TextEditor* textEditor_ ) override;
    virtual void editorShown( TextEditor* textEditor_ ) override;
    virtual void textWasEdited() override;

    virtual TextEditor* createEditorComponent() override;

    void textEditorReturnKeyPressed( TextEditor& ) override;
    void textEditorEscapeKeyPressed ( TextEditor& ) override;
    void textEditorTextChanged ( TextEditor& ) override;
    void textEditorFocusLost( TextEditor& te ) override;
    void valueChanged ( Value& ) override;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (LLabel)
};

#endif // __LUCE_LLABEL_H
