/************************************************************

 LTextEditor.h

    @author Christophe Berbizier (cberbizier@peersuasive.com)
    @license GPLv3
    @copyright 


(c) 2013, Peersuasive Technologies

*************************************************************/

#ifndef __LUCE_LTEXTEDITOR_H
#define __LUCE_LTEXTEDITOR_H

class LTextEditor
    : public LComponent,
      public TextEditor, private TextEditor::Listener
{
public:
    LTextEditor(lua_State*);
    ~LTextEditor();

    //==============================================================================
    int setHighlightedRegion(lua_State*);
    int getHighlightedRegion(lua_State*);
    int setPopupMenuEnabled(lua_State*);
    int isPopupMenuEnabled(lua_State*);
    int setFont(lua_State*);
    int getFont(lua_State*);
    int setMultiLine(lua_State*);
    int isMultiLine(lua_State*);
    int setReturnKeyStartsNewLine(lua_State*);
    int getReturnKeyStartsNewLine(lua_State*);
    int setCaretPosition(lua_State*);
    int getCaretPosition(lua_State*);
    int setCaretVisible(lua_State*);
    int isCaretVisible(lua_State*);
    int setBorder(lua_State*);
    int getBorder(lua_State*);
    int setText(lua_State*);
    int getText(lua_State*);
    int setReadOnly(lua_State*);
    int isReadOnly(lua_State*);
    int setPasswordCharacter(lua_State*);
    int getPasswordCharacter(lua_State*);
    int setTabKeyUsedAsCharacter(lua_State*);
    int isTabKeyUsedAsCharacter(lua_State*);

    //==============================================================================
    int moveCaretToEnd(lua_State*);
    int insertTextAtCaret(lua_State*);
    int applyFontToAllText(lua_State*);
    int setEscapeAndReturnKeysConsumed(lua_State*);
    int setInputRestrictions(lua_State*);
    int scrollToMakeSureCursorIsVisible(lua_State*);
    int paste(lua_State*);
    int addPopupMenuItems(lua_State*);
    int setScrollbarsShown(lua_State*);
    int setTextToShowWhenEmpty(lua_State*);
    int setTemporaryUnderlining(lua_State*);
    int setScrollBarThickness(lua_State*);
    int scrollEditorToPositionCaret(lua_State*);
    int setSelectAllWhenFocused(lua_State*);
    int newTransaction(lua_State*);
    int textChanged(lua_State*);
    int cut(lua_State*);
    int copy(lua_State*);
    int clear(lua_State*);
    int setIndents(lua_State*);
    int setInputFilter(lua_State*);
    int setScrollToShowCursor(lua_State*);

    //==============================================================================
    int isEmpty(lua_State*);
    int moveCaretRight(lua_State*);
    int redo(lua_State*);
    int isPopupMenuCurrentlyActive(lua_State*);
    int copyToClipboard(lua_State*);
    int isTextInputActive(lua_State*);
    int scrollDown(lua_State*);
    int areScrollbarsShown(lua_State*);
    int keyStateChanged(lua_State*);
    int getCaretRectangle(lua_State*);
    int scrollUp(lua_State*);
    int undo(lua_State*);
    int getTextInRange(lua_State*);
    int cutToClipboard(lua_State*);
    int deleteBackwards(lua_State*);
    int moveCaretDown(lua_State*);
    int getTextHeight(lua_State*);
    int getTotalNumChars(lua_State*);
    int moveCaretToEndOfLine(lua_State*);
    int moveCaretLeft(lua_State*);
    int getTextIndexAt(lua_State*);
    int getTextValue(lua_State*);
    int moveCaretToStartOfLine(lua_State*);
    int deleteForwards(lua_State*);
    int selectAll(lua_State*);
    int getTextWidth(lua_State*);
    int getHighlightedText(lua_State*);
    int pasteFromClipboard(lua_State*);
    int moveCaretToTop(lua_State*);
    int pageUp(lua_State*);
    int moveCaretUp(lua_State*);
    int pageDown(lua_State*);

    //==============================================================================
    int addListener(lua_State*);
    int removeListener(lua_State*);

    int escapePressed(lua_State*);
    int returnPressed(lua_State*);
    int performPopupMenuAction(lua_State*);

    int textEditorTextChanged(lua_State*);
    int textEditorReturnKeyPressed(lua_State*);
    int textEditorEscapeKeyPressed(lua_State*);
    int textEditorFocusLost(lua_State*);

    static const char className[];
    static const Luna<LTextEditor>::Inheritence inherits[];
    static const Luna<LTextEditor>::InheritenceF inheritsF[];
    static const Luna<LTextEditor>::PropertyType properties[];
    static const Luna<LTextEditor>::FunctionType methods[];
    static const Luna<LTextEditor>::StaticType statics[];
    static const Luna<LTextEditor>::Enum enums[];

private:
    //==============================================================================
    virtual void textEditorTextChanged (TextEditor &) override;
    virtual void textEditorReturnKeyPressed (TextEditor &) override;
    virtual void textEditorEscapeKeyPressed (TextEditor &) override;
    virtual void textEditorFocusLost (TextEditor &) override;
 
    virtual void escapePressed() override;
    virtual void returnPressed() override;
    virtual void performPopupMenuAction( int menuItemID ) override;

    virtual bool keyPressed(const KeyPress&) override;

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (LTextEditor)
};

#endif // __LUCE_LTEXTEDITOR_H
