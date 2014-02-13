/************************************************************

 LTextEditor.cpp

    @author Christophe Berbizier (cberbizier@peersuasive.com)
    @license GPLv3
    @copyright 


(c) 2014, Peersuasive Technologies

*************************************************************/

#include "LTextEditor_inh.h"

////// static methods
const char LTextEditor::className[] = "LTextEditor";
const Luna<LTextEditor>::PropertyType LTextEditor::properties[] = {
    {"popupMenuEnabled", &LTextEditor::isPopupMenuEnabled, &LTextEditor::setPopupMenuEnabled},
    {"font", &LTextEditor::getFont, &LTextEditor::setFont},
    {"multiLine", &LTextEditor::isMultiLine, &LTextEditor::setMultiLine},
    {"returnKeyStartsNewLine", &LTextEditor::getReturnKeyStartsNewLine, &LTextEditor::setReturnKeyStartsNewLine},
    {"caretPosition", &LTextEditor::getCaretPosition, &LTextEditor::setCaretPosition},
    {"caretVisible", &LTextEditor::isCaretVisible, &LTextEditor::setCaretVisible},
    {"border", &LTextEditor::getBorder, &LTextEditor::setBorder},
    {"text", &LTextEditor::getText, &LTextEditor::setText},
    {"readOnly", &LTextEditor::isReadOnly, &LTextEditor::setReadOnly},
    {"passwordCharacter", &LTextEditor::getPasswordCharacter, &LTextEditor::setPasswordCharacter},
    {"tabKeyUsedAsCharacter", &LTextEditor::isTabKeyUsedAsCharacter, &LTextEditor::setTabKeyUsedAsCharacter},
    {"scrollbarsShown", &LTextEditor::areScrollbarsShown, &LTextEditor::setScrollbarsShown},
    {0,0}
};
const Luna<LTextEditor>::FunctionType LTextEditor::methods[] = {
    method( LTextEditor, isEmpty ),
    method( LTextEditor, moveCaretToEnd ),
    method( LTextEditor, moveCaretRight ),
    method( LTextEditor, moveCaretDown ),
    method( LTextEditor, moveCaretToEndOfLine ),
    method( LTextEditor, moveCaretLeft ),
    method( LTextEditor, moveCaretToStartOfLine ),
    method( LTextEditor, moveCaretToTop ),
    method( LTextEditor, moveCaretUp ),
    method( LTextEditor, getHighlightedRegion ),
    method( LTextEditor, setHighlightedRegion ),
    method( LTextEditor, redo ),
    method( LTextEditor, isPopupMenuCurrentlyActive ),
    method( LTextEditor, copyToClipboard ),
    method( LTextEditor, isTextInputActive ),
    method( LTextEditor, scrollDown ),
    method( LTextEditor, isPopupMenuEnabled ),
    method( LTextEditor, setPopupMenuEnabled ),
    method( LTextEditor, getFont ),
    method( LTextEditor, setFont ),
    method( LTextEditor, areScrollbarsShown ),
    method( LTextEditor, keyStateChanged ),
    method( LTextEditor, isMultiLine ),
    method( LTextEditor, setMultiLine ),
    method( LTextEditor, getCaretRectangle ),
    method( LTextEditor, getReturnKeyStartsNewLine ),
    method( LTextEditor, setReturnKeyStartsNewLine ),
    method( LTextEditor, getCaretPosition ),
    method( LTextEditor, setCaretPosition ),
    method( LTextEditor, scrollUp ),
    method( LTextEditor, undo ),
    method( LTextEditor, isCaretVisible ),
    method( LTextEditor, setCaretVisible ),
    method( LTextEditor, getTextInRange ),
    method( LTextEditor, getBorder ),
    method( LTextEditor, setBorder ),
    method( LTextEditor, getText ),
    method( LTextEditor, setText ),
    method( LTextEditor, cutToClipboard ),
    method( LTextEditor, deleteBackwards ),
    method( LTextEditor, isReadOnly ),
    method( LTextEditor, setReadOnly ),
    method( LTextEditor, getTextHeight ),
    method( LTextEditor, getTotalNumChars ),
    method( LTextEditor, getTextIndexAt ),
    method( LTextEditor, getTextValue ),
    method( LTextEditor, deleteForwards ),
    method( LTextEditor, getPasswordCharacter ),
    method( LTextEditor, setPasswordCharacter ),
    method( LTextEditor, selectAll ),
    method( LTextEditor, getTextWidth ),
    method( LTextEditor, getHighlightedText ),
    method( LTextEditor, pasteFromClipboard ),
    method( LTextEditor, isTabKeyUsedAsCharacter ),
    method( LTextEditor, setTabKeyUsedAsCharacter ),
    method( LTextEditor, pageUp ),
    method( LTextEditor, pageDown ),
    method( LTextEditor, insertTextAtCaret ),
    method( LTextEditor, applyFontToAllText ),
    method( LTextEditor, setEscapeAndReturnKeysConsumed ),
    method( LTextEditor, setInputRestrictions ),
    method( LTextEditor, scrollToMakeSureCursorIsVisible ),
    method( LTextEditor, removeListener ),
    method( LTextEditor, paste ),
    method( LTextEditor, addPopupMenuItems ),
    method( LTextEditor, setScrollbarsShown ),
    method( LTextEditor, setTextToShowWhenEmpty ),
    method( LTextEditor, setTemporaryUnderlining ),
    method( LTextEditor, setScrollBarThickness ),
    method( LTextEditor, scrollEditorToPositionCaret ),
    method( LTextEditor, setSelectAllWhenFocused ),
    method( LTextEditor, newTransaction ),
    method( LTextEditor, textChanged ),
    method( LTextEditor, cut ),
    method( LTextEditor, copy ),
    method( LTextEditor, clear ),
    method( LTextEditor, setIndents ),
    method( LTextEditor, setInputFilter ),
    method( LTextEditor, setScrollToShowCursor ),
    method( LTextEditor, performPopupMenuAction ),
    method( LTextEditor, returnPressed ),
    method( LTextEditor, escapePressed ),

    method( LTextEditor, addListener ),
    method( LTextEditor, removeListener ),

    method( LTextEditor, textEditorTextChanged ),
    method( LTextEditor, textEditorReturnKeyPressed ),
    method( LTextEditor, textEditorEscapeKeyPressed ),
    method( LTextEditor, textEditorFocusLost ),

    {0,0}
};

/////// ctor/dtor
const Luna<LTextEditor>::StaticType LTextEditor::statics[] = {
    {0,0}
};

LTextEditor::LTextEditor(lua_State *L)
    : LComponent(L, this),
      TextEditor( /* TODO: add args */ )
{
    REGISTER_CLASS(LTextEditor);
    TextEditor::setName(myName());
    TextEditor::addListener(this);
}
LTextEditor::~LTextEditor(){}

/////// callbacks
int LTextEditor::addListener(lua_State *L) {
    TextEditor::addListener(this);
    return 0;
}
int LTextEditor::removeListener(lua_State *L) {
    TextEditor::removeListener(this);
    return 0;
}
void LTextEditor::escapePressed() {
    if ( hasCallback("escapePressed") )
        callback("escapePressed");
    else
        TextEditor::escapePressed();
}
int LTextEditor::escapePressed(lua_State*){
    set("escapePressed");
    return 0;
}

void LTextEditor::returnPressed() {
    if (hasCallback("returnTable"))
        callback("returnPressed");
    else
        TextEditor::returnPressed();
}
int LTextEditor::returnPressed(lua_State*){
    set("returnPressed");
    return 0;
}

bool LTextEditor::keyPressed(const KeyPress& k) {
    if(hasCallback("keyPressed"))
        return LComponent::lkeyPressed(k);
    else
        return TextEditor::keyPressed(k);
}

void LTextEditor::performPopupMenuAction( int menuItemID ) {
    if (hasCallback("performPopupMenuAction"))
        callback("performPopupMenuAction", 0, { menuItemID } );
    else
        TextEditor::performPopupMenuAction(menuItemID);
}
int LTextEditor::performPopupMenuAction(lua_State*) {
    set("performPopupMenuAction");
    return 0;
}

void LTextEditor::textEditorTextChanged (TextEditor &t) {
    if (hasCallback("textEditorTextChanged"))
        callback("textEditorTextChanged");
}
int LTextEditor::textEditorTextChanged(lua_State *L) {
    set("textEditorTextChanged");
    return 0;
}

void LTextEditor::textEditorReturnKeyPressed (TextEditor &t) {
    if(hasCallback("textEditorReturnKeyPressed"))
        callback("textEditorReturnKeyPressed");
}
int LTextEditor::textEditorReturnKeyPressed (lua_State *L) {
    set("textEditorReturnKeyPressed");
    return 0;
}

void LTextEditor::textEditorEscapeKeyPressed (TextEditor &t) {
    if(hasCallback("textEditorEscapeKeyPressed"))
        callback("textEditorEscapeKeyPressed");
}
int LTextEditor::textEditorEscapeKeyPressed (lua_State *L) {
    set("textEditorEscapeKeyPressed");
    return 0;
}

void LTextEditor::textEditorFocusLost (TextEditor &t) {
    if (hasCallback("textEditorFocusLost"))
        callback("textEditorFocusLost");
}
int LTextEditor::textEditorFocusLost (lua_State *L) {
    set("textEditorFocusLost");
    return 0;
}

/////// getters/setters
int LTextEditor::moveCaretToEnd (lua_State* L) {
    if ( lua_type(L,-1) == LUA_TBOOLEAN )
        return LUA::returnBoolean( TextEditor::moveCaretToEnd( LUA::getBoolean() ) );
    else {
        TextEditor::moveCaretToEnd();
        return 0;
    }
}

int LTextEditor::moveCaretRight ( lua_State* ) {
    bool moveInWholeWordSteps = LUA::getBoolean(2);
    bool selecting = LUA::getBoolean(2);
    return LUA::returnBoolean( TextEditor::moveCaretRight( LUA::getBoolean(), LUA::getBoolean() ) );
}

int LTextEditor::moveCaretDown ( lua_State* ) {
    return LUA::returnBoolean( TextEditor::moveCaretDown( LUA::getBoolean() ) );
}

int LTextEditor::moveCaretToEndOfLine ( lua_State* ) {
    bool selecting = LUA::getBoolean();
    return LUA::returnBoolean( TextEditor::moveCaretToEndOfLine( selecting ) );
}

int LTextEditor::moveCaretLeft ( lua_State* ) {
    bool moveInWholeWordSteps = LUA::getBoolean();
    bool selecting = LUA::getBoolean(2);
    return LUA::returnBoolean( TextEditor::moveCaretLeft( moveInWholeWordSteps, selecting ) );
}

int LTextEditor::moveCaretToStartOfLine ( lua_State* ) {
    bool selecting = LUA::getBoolean();
    return LUA::returnBoolean( TextEditor::moveCaretToStartOfLine( selecting ) );
}

int LTextEditor::moveCaretToTop ( lua_State* ) {
    bool selecting = LUA::getBoolean();
    return LUA::returnBoolean( TextEditor::moveCaretToTop( selecting ) );
}

int LTextEditor::pageUp ( lua_State* ) {
    bool selecting = LUA::getBoolean();
    return LUA::returnBoolean( TextEditor::pageUp( selecting ) );
}

int LTextEditor::moveCaretUp ( lua_State* ) {
    bool selecting = LUA::getBoolean();
    return LUA::returnBoolean( TextEditor::moveCaretUp( selecting ) );
}

int LTextEditor::getHighlightedRegion ( lua_State* ) {
    return LUA::returnTable( TextEditor::getHighlightedRegion() );
}
int LTextEditor::setHighlightedRegion ( lua_State* ) {
    TextEditor::setHighlightedRegion( LUA::getRange() );
    return 0;
}

int LTextEditor::isPopupMenuEnabled ( lua_State* ) {
    return LUA::returnBoolean( TextEditor::isPopupMenuEnabled() );
}
int LTextEditor::setPopupMenuEnabled ( lua_State* ) {
    TextEditor::setPopupMenuEnabled(LUA::getBoolean());
    return 0;
}

int LTextEditor::isMultiLine ( lua_State* ) {
    return LUA::returnBoolean( TextEditor::isMultiLine() );
}
int LTextEditor::setMultiLine ( lua_State* ) {
    bool a = LUA::getBoolean(2);
    TextEditor::setMultiLine( a, LUA::checkAndGetBoolean(2, true) );
    return 0;
}

int LTextEditor::getReturnKeyStartsNewLine ( lua_State* ) {
    return LUA::returnBoolean( TextEditor::getReturnKeyStartsNewLine() );
}
int LTextEditor::setReturnKeyStartsNewLine ( lua_State* ) {
    TextEditor::setReturnKeyStartsNewLine(LUA::getBoolean());
    return 0;
}

int LTextEditor::getCaretPosition ( lua_State* ) {
    return LUA::returnNumber( TextEditor::getCaretPosition() );
}
int LTextEditor::setCaretPosition ( lua_State* ) {
    TextEditor::setCaretPosition(LUA::getNumber());
    return 0;
}

int LTextEditor::isCaretVisible ( lua_State* ) {
    return LUA::returnBoolean( TextEditor::isCaretVisible() );
}
int LTextEditor::setCaretVisible ( lua_State* ) {
    TextEditor::setCaretVisible(LUA::getBoolean());
    return 0;
}

int LTextEditor::getBorder ( lua_State* ) {
    BorderSize<int> b = TextEditor::getBorder();
    return LUA::returnTable( std::list<var>{ b.getTop(), b.getLeft(), b.getBottom(), b.getRight() } );
}
int LTextEditor::setBorder ( lua_State* ) {
    Array<var> b = LUA::getList();
    TextEditor::setBorder( { b[0], b[1], b[2], b[3] } );
    return 0;
}

int LTextEditor::getText ( lua_State* ) {
    return LUA::returnString( TextEditor::getText() );
}
int LTextEditor::setText ( lua_State* ) {
    String newText = LUA::getString(2);
    bool sendTextChangeMessage = LUA::checkAndGetBoolean(2, true);
    TextEditor::setText( newText, sendTextChangeMessage );
    return 0;
}

int LTextEditor::isReadOnly ( lua_State* ) {
    return LUA::returnBoolean( TextEditor::isReadOnly() );
}
int LTextEditor::setReadOnly ( lua_State* ) {
    TextEditor::setReadOnly(LUA::getBoolean());
    return 0;
}

int LTextEditor::getPasswordCharacter ( lua_State* ) {
    return LUA::returnString( String(TextEditor::getPasswordCharacter()) );
}
int LTextEditor::setPasswordCharacter ( lua_State* ) {
    TextEditor::setPasswordCharacter( *LUA::getString().toWideCharPointer() );
    return 0;
}

int LTextEditor::isTabKeyUsedAsCharacter ( lua_State* ) {
    return LUA::returnBoolean( TextEditor::isTabKeyUsedAsCharacter() );
}
int LTextEditor::setTabKeyUsedAsCharacter ( lua_State* ) {
    TextEditor::setTabKeyUsedAsCharacter(LUA::getBoolean());
    return 0;
}

/////// getters
int LTextEditor::isEmpty ( lua_State* ) {
    return LUA::returnBoolean( TextEditor::isEmpty() );
}

int LTextEditor::redo ( lua_State* ) {
    return LUA::returnBoolean( TextEditor::redo() );
}

int LTextEditor::isPopupMenuCurrentlyActive ( lua_State* ) {
    return LUA::returnBoolean( TextEditor::isPopupMenuCurrentlyActive() );
}

int LTextEditor::copyToClipboard ( lua_State* ) {
    return LUA::returnBoolean( TextEditor::copyToClipboard() );
}

int LTextEditor::isTextInputActive ( lua_State* ) {
    return LUA::returnBoolean( TextEditor::isTextInputActive() );
}

int LTextEditor::scrollDown ( lua_State* ) {
    return LUA::returnBoolean( TextEditor::scrollDown() );
}

int LTextEditor::areScrollbarsShown ( lua_State* ) {
    return LUA::returnBoolean( TextEditor::areScrollbarsShown() );
}

int LTextEditor::keyStateChanged ( lua_State* ) {
    bool bool_ = LUA::getBoolean(1);
    return LUA::returnBoolean( TextEditor::keyStateChanged( bool_ ) );
}

int LTextEditor::getCaretRectangle ( lua_State* ) {
    return LUA::returnTable( TextEditor::getCaretRectangle() );
}

int LTextEditor::scrollUp ( lua_State* ) {
    return LUA::returnBoolean( TextEditor::scrollUp() );
}

int LTextEditor::undo ( lua_State* ) {
    return LUA::returnBoolean( TextEditor::undo() );
}

int LTextEditor::getTextInRange ( lua_State* ) {
    return LUA::returnString( TextEditor::getTextInRange( LUA::getRange() ) );
}

int LTextEditor::cutToClipboard ( lua_State* ) {
    return LUA::returnBoolean( TextEditor::cutToClipboard() );
}

int LTextEditor::deleteBackwards ( lua_State* ) {
    bool moveInWholeWordSteps = LUA::getBoolean(1);
    return LUA::returnBoolean( TextEditor::deleteBackwards( moveInWholeWordSteps ) );
}

int LTextEditor::getTextHeight ( lua_State* ) {
    return LUA::returnNumber( TextEditor::getTextHeight() );
}

int LTextEditor::getTotalNumChars ( lua_State* ) {
    return LUA::returnNumber( TextEditor::getTotalNumChars() );
}

int LTextEditor::getTextIndexAt ( lua_State* ) {
    Array<var> ind = LUA::getList();
    return LUA::returnNumber( TextEditor::getTextIndexAt( ind[0], ind[1] ) );
}

int LTextEditor::selectAll ( lua_State* ) {
    return LUA::returnBoolean( TextEditor::selectAll() );
}

int LTextEditor::getTextWidth ( lua_State* ) {
    return LUA::returnNumber( TextEditor::getTextWidth() );
}

int LTextEditor::getHighlightedText ( lua_State* ) {
    return LUA::returnString( TextEditor::getHighlightedText() );
}

int LTextEditor::pasteFromClipboard ( lua_State* ) {
    return LUA::returnBoolean( TextEditor::pasteFromClipboard() );
}

int LTextEditor::deleteForwards ( lua_State* ) {
    bool moveInWholeWordSteps = LUA::getBoolean();
    return LUA::returnBoolean( TextEditor::deleteForwards( moveInWholeWordSteps ) );
}

int LTextEditor::pageDown ( lua_State* ) {
    bool selecting = LUA::getBoolean();
    return LUA::returnBoolean( TextEditor::pageDown( selecting ) );
}

/////// setters
int LTextEditor::insertTextAtCaret ( lua_State* ) {
    TextEditor::insertTextAtCaret(LUA::getString());
    return 0;
}

int LTextEditor::setEscapeAndReturnKeysConsumed ( lua_State* ) {
    TextEditor::setEscapeAndReturnKeysConsumed(LUA::getBoolean());
    return 0;
}

int LTextEditor::setInputRestrictions ( lua_State* ) {
    int maxTextLength = LUA::getNumber();
    String allowedCharacters = LUA::checkAndGetString(2, String::empty);
    TextEditor::setInputRestrictions( maxTextLength, allowedCharacters );
    return 0;
}

int LTextEditor::scrollToMakeSureCursorIsVisible ( lua_State* ) {
    TextEditor::scrollToMakeSureCursorIsVisible();
    return 0;
}

int LTextEditor::paste ( lua_State* ) {
    TextEditor::paste();
    return 0;
}

int LTextEditor::setScrollbarsShown ( lua_State* ) {
    TextEditor::setScrollbarsShown(LUA::getBoolean());
    return 0;
}

int LTextEditor::setTextToShowWhenEmpty ( lua_State* ) {
    String text = LUA::getString(2);
    Colour colourToUse = Colours::findColourForName( LUA::getString(2), Colours::black );
    TextEditor::setTextToShowWhenEmpty( text, colourToUse );
    return 0;
}

int LTextEditor::setScrollBarThickness ( lua_State* ) {
    TextEditor::setScrollBarThickness(LUA::getNumber());
    return 0;
}

int LTextEditor::scrollEditorToPositionCaret ( lua_State* ) {
    int desiredCaretX = LUA::getNumber(2);
    int desiredCaretY = LUA::getNumber(2);
    TextEditor::scrollEditorToPositionCaret( desiredCaretX, desiredCaretY );
    return 0;
}

int LTextEditor::setSelectAllWhenFocused ( lua_State* ) {
    TextEditor::setSelectAllWhenFocused(LUA::getBoolean());
    return 0;
}

int LTextEditor::newTransaction ( lua_State* ) {
    TextEditor::newTransaction();
    return 0;
}

int LTextEditor::textChanged ( lua_State* ) {
    TextEditor::textChanged();
    return 0;
}

int LTextEditor::cut ( lua_State* ) {
    TextEditor::cut();
    return 0;
}

int LTextEditor::copy ( lua_State* ) {
    TextEditor::copy();
    return 0;
}

int LTextEditor::clear ( lua_State* ) {
    TextEditor::clear();
    return 0;
}

int LTextEditor::setIndents ( lua_State* ) {
    Array<var> ind = LUA::getList();
    TextEditor::setIndents( ind[0], ind[1] );
    return 0;
}

int LTextEditor::setScrollToShowCursor ( lua_State* ) {
    TextEditor::setScrollToShowCursor(LUA::getBoolean());
    return 0;
}

// TODO:
// getters
int LTextEditor::setTemporaryUnderlining ( lua_State* ) {
    //TextEditor::setTemporaryUnderlining(LUA::getList());
    LUA::TODO_OBJECT( "TextEditor::setTemporaryUnderlining(LUA::getList())" );
    lua_settop(LUA::Get(), 1);
    return 0;
}

int LTextEditor::getFont ( lua_State *L ) {
    return LUA::storeAndReturnUserdata<LFont>( new LFont(L, 
        TextEditor::getFont()
    ));
}
int LTextEditor::setFont ( lua_State* ) {
    TextEditor::setFont( *LUA::from_luce<LFont>(2) );
    return 0;
}

int LTextEditor::keyPressed ( lua_State* ) {
    // KeyPress keypress_ = LUA::TODO_OBJECT_KeyPress;
    // return LUA::returnBoolean( TextEditor::keyPressed( keypress_ ) );
    lua_settop(LUA::Get(), 1); // added by TODO
    return LUA::TODO_OBJECT( "bool keyPressed( keypress_ )" );
}

int LTextEditor::getTextValue ( lua_State* ) {
    // return LUA::TODO_RETURN_OBJECT_Value( TextEditor::getTextValue() );
    lua_settop(LUA::Get(), 1); // added by TODO
    return LUA::TODO_OBJECT( "Value getTextValue()" );
}

// setters
int LTextEditor::applyFontToAllText ( lua_State* ) {
    // TextEditor::applyFontToAllText(LUA::TODO_OBJECT_Font);
    LUA::TODO_OBJECT( "applyFontToAllText, LUA::TODO_OBJECT_Font" );
    lua_settop(LUA::Get(), 1); // added by TODO
    return 0;
}

int LTextEditor::addPopupMenuItems ( lua_State* ) {
    // PopupMenu menuToAddTo = LUA::TODO_OBJECT_PopupMenu;
    // MouseEvent* mouseClickEvent = LUA::TODO_OBJECT_MouseEvent;
    // TextEditor::addPopupMenuItems( menuToAddTo, mouseClickEvent );
    LUA::TODO_OBJECT( "addPopupMenuItems,  menuToAddTo, mouseClickEvent " );
    lua_settop(LUA::Get(), 1); // added by TODO
    return 0;
}

int LTextEditor::setInputFilter ( lua_State* ) {
    // InputFilter* newFilter = LUA::TODO_OBJECT_InputFilter;
    // bool takeOwnership = LUA::getBoolean(2);
    // TextEditor::setInputFilter( newFilter, takeOwnership );
    LUA::TODO_OBJECT( "setInputFilter,  newFilter, takeOwnership " );
    lua_settop(LUA::Get(), 1); // added by TODO
    return 0;
}


