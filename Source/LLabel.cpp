/************************************************************

 LLabel.cpp

    @author Christophe Berbizier (cberbizier@peersuasive.com)
    @license GPLv3
    @copyright 


(c) 2014, Peersuasive Technologies

*************************************************************/

#include "LLabel_inh.h"

////// static methods
const char LLabel::className[] = "LLabel";
const Luna<LLabel>::PropertyType LLabel::properties[] = {
    {"justificationType", &LLabel::getJustificationType, &LLabel::setJustificationType},
    {"editable", &LLabel::isEditable, &LLabel::setEditable},
    {"minimumHorizontalScale", &LLabel::getMinimumHorizontalScale, &LLabel::setMinimumHorizontalScale},
    {"font", &LLabel::getFont, &LLabel::setFont},
    {"text", &LLabel::getText, &LLabel::setText},
    {0,0}
};
const Luna<LLabel>::FunctionType LLabel::methods[] = {
    method( LLabel, getText ),
    method( LLabel, setText ),

    method( LLabel, getJustificationType ),
    method( LLabel, setJustificationType ),
    method( LLabel, isAttachedOnLeft ),
    method( LLabel, getAttachedComponent ),
    method( LLabel, getFont ),
    method( LLabel, setFont ),
    method( LLabel, getHorizontalBorderSize ),
    method( LLabel, getVerticalBorderSize ),
    method( LLabel, getMinimumHorizontalScale ),
    method( LLabel, setMinimumHorizontalScale ),

    method( LLabel, isEditable ),
    method( LLabel, setEditable ),
    method( LLabel, isEditableOnSingleClick ),
    method( LLabel, isEditableOnDoubleClick ),
    method( LLabel, createEditorComponent ),
    method( LLabel, isBeingEdited ),
    method( LLabel, getCurrentTextEditor ),
    method( LLabel, showEditor ),

    method( LLabel, doesLossOfFocusDiscardChanges ),
    method( LLabel, getTextValue ),

    method( LLabel, setBorderSize ),

    method( LLabel, addListener ),
    method( LLabel, removeListener ),

    method( LLabel, hideEditor ),

    method( LLabel, attachToComponent ),
    method( LLabel, textWasEdited ),
    method( LLabel, textWasChanged ),
    method( LLabel, editorShown ),
    method( LLabel, editorAboutToBeHidden ),

    method( LLabel, labelTextChanged ),

    method( LLabel, textEditorReturnKeyPressed ),
    method( LLabel, textEditorEscapeKeyPressed ),
    method( LLabel, textEditorFocusLost ),
    method( LLabel, textEditorTextChanged ),
    method( LLabel, valueChanged ),

    //method( LLabel, componentVisibilityChanged ),
    //method( LLabel, callChangeListeners ),
    //method( LLabel, componentParentHierarchyChanged ),
    {0,0}
};

/////// ctor/dtor
const Luna<LLabel>::StaticType LLabel::statics[] = {
    {0,0}
};

LLabel::LLabel(lua_State *L)
    : LComponent(L, this),
      Label(),
      myFont()
{
    Label::setName(myName());
    Label::addListener(this);
    REGISTER_CLASS(LLabel);
}

LLabel::~LLabel() {
    if(myFont)
        myFont = nullptr;
}

int LLabel::addListener(lua_State *L) {
    Label::addListener(this);
    return 0;
}

int LLabel::removeListener(lua_State *L) {
    Label::removeListener(this);
    return 0;
}

/////// callbacks
void LLabel::labelTextChanged(Label *label) {
    if(hasCallback("labelTextChanged"))
        callback("labelTextChanged");
}
int LLabel::labelTextChanged(lua_State *L) {
    set("labelTextChanged");
    return 0;
}

void LLabel::textWasChanged() {
    if(hasCallback("textWasChanged"))
        callback("textWasChanged");
}
int LLabel::textWasChanged(lua_State*){
    set("textWasChanged");
    return 0;
}

void LLabel::editorAboutToBeHidden( TextEditor* textEditor_ ) {
    if(hasCallback("editorAboutToBeHidden"))
        callback("editorAboutToBeHidden");
    else
        Label::editorAboutToBeHidden(textEditor_);
}
int LLabel::editorAboutToBeHidden(lua_State*){
    set("editorAboutToBeHidden");
    return 0;
}

void LLabel::editorShown( TextEditor* textEditor_ ) {
    if(hasCallback("editorShown"))
        callback("editorShown");
}
int LLabel::editorShown(lua_State*){
    set("editorShown");
    return 0;
}

void LLabel::textWasEdited() {
    if(hasCallback("textWasEdited"))
        callback("textWasEdited");
}
int LLabel::textWasEdited(lua_State*){
    set("textWasEdited");
    return 0;
}

void LLabel::textEditorReturnKeyPressed( TextEditor& te) {
    if(hasCallback("textEditorReturnKeyPressed"))
        callback("textEditorReturnKeyPressed");
    else
        Label::textEditorReturnKeyPressed(te);
}
int LLabel::textEditorReturnKeyPressed ( lua_State* ) {
    set("textEditorReturnKeyPressed");
    return 0;
}

void LLabel::textEditorEscapeKeyPressed ( TextEditor& te) {
    if(hasCallback("textEditorEscapeKeyPressed"))
        callback("textEditorEscapeKeyPressed");
    else
        Label::textEditorEscapeKeyPressed(te);
}
int LLabel::textEditorEscapeKeyPressed ( lua_State* ) {
    set("textEditorEscapeKeyPressed");
    return 0;
}

void LLabel::textEditorTextChanged ( TextEditor& te) {
    if(hasCallback("textEditorTextChanged"))
        callback("textEditorTextChanged");
    else
        Label::textEditorTextChanged(te);
}
int LLabel::textEditorTextChanged ( lua_State* ) {
    set("textEditorTextChanged");
    return 0;
}

void LLabel::textEditorFocusLost( TextEditor& te ) {
    if(hasCallback("textEditorFocusLost"))
        callback("textEditorFocusLost");
    else
        Label::textEditorFocusLost(te);
}
int LLabel::textEditorFocusLost ( lua_State* ) {
    set("textEditorFocusLost");
    return 0;
}

void LLabel::valueChanged ( Value& v ) {
    if(hasCallback("valueChanged"))
        callback("valueChanged");
    else
        Label::valueChanged(v);
}
int LLabel::valueChanged ( lua_State* ) {
    set("valueChanged");
    return 0;
}


/////// getters/setters
int LLabel::getText(lua_State*) {
    return LUA::returnString( Label::getText(LUA::checkAndGetBoolean(2, false)) );
}
int LLabel::setText(lua_State *L) {
    String text = LUA::getString(2);
    if( lua_isstring(L, 2)  )
        Label::setText( text, (NotificationType)LUA::getNumber<int>(2) );
    else 
        Label::setText( text, NotificationType::dontSendNotification );
    return 0;
}

// not really sure about a Value implementation... return getText() at the moment
int LLabel::getTextValue ( lua_State* ) {
    return LUA::returnString( Label::getText(LUA::checkAndGetBoolean(2, false)) );
    // return LUA::TODO_RETURN_OBJECT_Value( Label::getTextValue() );
}

int LLabel::attachToComponent(lua_State *) {
    Component *comp = LUA::from_luce<LComponent,Component>(2);
    bool onLeft = ( LUA::checkAndGetBoolean(2, true) );
    Label::attachToComponent(comp, onLeft);
    return 0;
}

int LLabel::isAttachedOnLeft(lua_State*) {
    return LUA::returnBoolean(Label::isAttachedOnLeft());
}

int LLabel::isEditable(lua_State*) {
    return LUA::returnBoolean(Label::isEditable());
}
int LLabel::setEditable(lua_State*) {
    bool editOnSingleClick = LUA::getBoolean(2);
    bool editOnDoubleClick = LUA::checkAndGetBoolean(2, false);
    bool lossOfFocusDiscardChanged = LUA::checkAndGetBoolean(2, false);
    Label::setEditable(editOnSingleClick, editOnDoubleClick, lossOfFocusDiscardChanged);
    return 0;
}

int LLabel::getMinimumHorizontalScale(lua_State*) {
    return LUA::returnNumber( Label::getMinimumHorizontalScale() );
}
int LLabel::setMinimumHorizontalScale(lua_State*) {
    Label::setMinimumHorizontalScale( (float)LUA::getNumber() );
    return 0;
}

int LLabel::getJustificationType(lua_State*) {
    return LUA::returnNumber( Label::getJustificationType().getFlags() );
}
int LLabel::setJustificationType(lua_State*) {
    Label::setJustificationType( (int)LUA::getNumber() );
    return 0;
}

int LLabel::getFont ( lua_State *L ) {
    LFont *f = new LFont( L, Label::getFont() );
    return LUA::storeAndReturnUserdata<LFont>( f );
    //myFont = new LFont( L, Label::getFont() );
    //myFont->setPureBase(false);
    //return LUA::storeAndReturnUserdata<LFont>( myFont.get() );
}
int LLabel::setFont ( lua_State *L ) {
    Font font;
    if(!lua_isnumber(L,2) && lua_isstring(L,2)) {
        String name = LUA::getString(2);
        float size = LUA::checkAndGetNumber<float>(2, 10.0f);
        int style = LUA::checkAndGetNumber<int>(2, Font::plain);
        font = Font(name, size, style);
    }
    else
       font = *LUA::from_luce<LFont>(2);
    Label::setFont( font );
    return 0;
}

/////// getters
int LLabel::isBeingEdited ( lua_State* ) {
    return LUA::returnBoolean( Label::isBeingEdited() );
}

int LLabel::isEditableOnSingleClick ( lua_State* ) {
    return LUA::returnBoolean( Label::isEditableOnSingleClick() );
}

int LLabel::getHorizontalBorderSize ( lua_State* ) {
    return LUA::returnNumber( Label::getHorizontalBorderSize() );
}

int LLabel::getVerticalBorderSize ( lua_State* ) {
    return LUA::returnNumber( Label::getVerticalBorderSize() );
}

int LLabel::doesLossOfFocusDiscardChanges ( lua_State* ) {
    return LUA::returnBoolean( Label::doesLossOfFocusDiscardChanges() );
}

int LLabel::isEditableOnDoubleClick ( lua_State* ) {
    return LUA::returnBoolean( Label::isEditableOnDoubleClick() );
}

int LLabel::getAttachedComponent ( lua_State* ) {
    return LUA::returnUserdata<LJComponent, Component>( Label::getAttachedComponent() );
}

int LLabel::getCurrentTextEditor ( lua_State* ) {
    return LUA::returnUserdata<LTextEditor, TextEditor>( Label::getCurrentTextEditor() );
}

TextEditor* LLabel::createEditorComponent() {
    if(hasCallback("createEditorComponent")) {
        if(callback("createEditorComponent"))
            return LUA::from_luce<LTextEditor, TextEditor>();
        else
            return nullptr;
    }
    else
        return Label::createEditorComponent();
}
int LLabel::createEditorComponent ( lua_State *L ) {
    if(lua_isfunction(L,2)) {
        set("createEditorComponent");
        return 0;
    }
    else
        return LUA::returnUserdata<LTextEditor, TextEditor>( Label::createEditorComponent() );
}

/////// setters
int LLabel::setBorderSize ( lua_State* ) {
    int horizontalBorder = LUA::getNumber(2);
    int verticalBorder = LUA::getNumber(3);
    Label::setBorderSize( horizontalBorder, verticalBorder );
    return 0;
}

int LLabel::showEditor ( lua_State* ) {
    Label::showEditor();
    return 0;
}

int LLabel::hideEditor ( lua_State* ) {
    Label::hideEditor(LUA::getBoolean());
    return 0;
}
