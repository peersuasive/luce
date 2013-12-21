/************************************************************

 LTextEditor.h

    @author Christophe Berbizier (cberbizier@peersuasive.com)
    @license GPLv3
    @copyright 


(c) 2013, Peersuasive Technologies

*************************************************************/

#ifndef __LUCE_TEXT_EDITOR_H
#define __LUCE_TEXT_EDITOR_H

#include "luce.h"

using namespace luce;

class LTextEditor : public LComponent,
                    public TextEditor,
                    private TextEditor::Listener
{
public:
    LTextEditor(lua_State*);
    ~LTextEditor();

    // behaviour
    int setMultiLine(lua_State*);
    int isMultiLine(lua_State*);
    int setReadOnly(lua_State*);
    int isReadOnly(lua_State*);

    //int setReturnKeyStartsNewLine(lua_State*);
    //int getReturnKeyStartsNewLine(lua_State*);

    //int setPopupMenuEnabled(lua_State*);

    //int setCaretVisible(lua_State*);
    //int isCaretVisible(lua_State*);

    //// editor
    //int getText(lua_State*);
    //int setText(lua_State*);

    //int clear(lua_State*);

    //int undo(lua_State*);
    //int redo(lua_State*);

    //// listener
    //int addListener(lua_State*);
    //int removeListener(lua_State*);

    int textEditorTextChanged(lua_State*);
    int textEditorReturnKeyPressed(lua_State*);
    int textEditorEscapeKeyPressed(lua_State*);
    int textEditorFocusLost(lua_State*);

    // luna~5
    static const char className[];
    static const Luna<LTextEditor>::Inheritence inherits[];
    static const Luna<LTextEditor>::InheritenceF inheritsF[];
    static const Luna<LTextEditor>::PropertyType properties[];
    static const Luna<LTextEditor>::FunctionType methods[];

private:
    //=============================================================================

    virtual void textEditorTextChanged (TextEditor &) override;
    virtual void textEditorReturnKeyPressed (TextEditor &) override;
    virtual void textEditorEscapeKeyPressed (TextEditor &) override;
    virtual void textEditorFocusLost (TextEditor &) override;

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (LTextEditor)
};

#endif // __LUCE_TEXT_EDITOR_H
