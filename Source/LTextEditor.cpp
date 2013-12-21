/************************************************************

 LTextEditor.cpp

    @author Christophe Berbizier (cberbizier@peersuasive.com)
    @license GPLv3
    @copyright 


(c) 2013, Peersuasive Technologies

*************************************************************/

#include "luce.h"

using namespace luce;

#include "LTextEditor_inh.h"
const char LTextEditor::className[] = "LTextEditor";

const Luna<LTextEditor>::PropertyType LTextEditor::properties[] = {
    {"multiLine", &LTextEditor::isMultiLine, &LTextEditor::setMultiLine},
    {"readOnly", &LTextEditor::isReadOnly, &LTextEditor::setReadOnly},
    {0,0}
};

const Luna<LTextEditor>::FunctionType LTextEditor::methods[] = {
    {0,0}
};

LTextEditor::LTextEditor(lua_State *L) 
    : LComponent(L, this),
      TextEditor()
{
    TextEditor::setName(myName);
    reg("textEditorTextChanged");
    reg("textEditorReturnKeyPressed");
    reg("textEditorEscapeKeyPressed");
    reg("textEditorFocusLost");

    TextEditor::addListener(this);
}

LTextEditor::~LTextEditor() {
}

/// widget methods

int LTextEditor::setMultiLine(lua_State*) {
    TextEditor::setMultiLine( LUA::getBoolean() );
    return 0;
}

int LTextEditor::isMultiLine(lua_State*) {
    return LUA::returnBoolean( TextEditor::isMultiLine() );
}

int LTextEditor::setReadOnly(lua_State*) {
    TextEditor::setMultiLine( LUA::getBoolean() );
    return 0;
}

int LTextEditor::isReadOnly(lua_State*) {
    return LUA::returnBoolean( TextEditor::isReadOnly() );
}

/// callbacks

void LTextEditor::textEditorTextChanged (TextEditor &t) {
    callback("textEditorTextChanged");
}
int LTextEditor::textEditorTextChanged(lua_State *L) {
    reg("textEditorTextChanged");
    return 0;
}

void LTextEditor::textEditorReturnKeyPressed (TextEditor &t) {
    callback("textEditorReturnKeyPressed");
}
int LTextEditor::textEditorReturnKeyPressed (lua_State *L) {
    reg("textEditorReturnKeyPressed");
    return 0;
}

void LTextEditor::textEditorEscapeKeyPressed (TextEditor &t) {
    callback("textEditorEscapeKeyPressed");
}
int LTextEditor::textEditorEscapeKeyPressed (lua_State *L) {
    reg("textEditorEscapeKeyPressed");
    return 0;
}

void LTextEditor::textEditorFocusLost (TextEditor &t) {
    callback("textEditorFocusLost");
}
int LTextEditor::textEditorFocusLost (lua_State *L) {
    reg("textEditorFocusLost");
    return 0;
}
