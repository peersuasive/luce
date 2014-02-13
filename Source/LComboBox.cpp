/************************************************************

 LComboBox.cpp

    @author Christophe Berbizier (cberbizier@peersuasive.com)
    @license GPLv3
    @copyright 


(c) 2014, Peersuasive Technologies

*************************************************************/

#include "LComboBox_inh.h"

const char LComboBox::className[] = "LComboBox";
const Luna<LComboBox>::PropertyType LComboBox::properties[] = {
    {"justificationType", &LComboBox::getJustificationType, &LComboBox::setJustificationType},
    {"tooltip", &LComboBox::getTooltip, &LComboBox::setTooltip},
    {"textWhenNoChoicesAvailable", &LComboBox::getTextWhenNoChoicesAvailable, &LComboBox::setTextWhenNoChoicesAvailable},
    {"textWhenNothingSelected", &LComboBox::getTextWhenNothingSelected, &LComboBox::setTextWhenNothingSelected},
    {"selectedId", &LComboBox::getSelectedId, &LComboBox::setSelectedId},
    {"text", &LComboBox::getText, &LComboBox::setText},
    {"selectedItemIndex", &LComboBox::getSelectedItemIndex, &LComboBox::setSelectedItemIndex},
    {"itemEnabled", &LComboBox::isItemEnabled, &LComboBox::setItemEnabled},
    {0,0}
};
const Luna<LComboBox>::FunctionType LComboBox::methods[] = {
    method( LComboBox, getJustificationType ),
    method( LComboBox, setJustificationType ),
    method( LComboBox, getTooltip ),
    method( LComboBox, setTooltip ),
    method( LComboBox, getTextWhenNoChoicesAvailable ),
    method( LComboBox, setTextWhenNoChoicesAvailable ),
    method( LComboBox, getTextWhenNothingSelected ),
    method( LComboBox, setTextWhenNothingSelected ),
    method( LComboBox, isTextEditable ),
    method( LComboBox, getSelectedId ),
    method( LComboBox, setSelectedId ),
    method( LComboBox, indexOfItemId ),
    method( LComboBox, getText ),
    method( LComboBox, setText ),
    method( LComboBox, getSelectedItemIndex ),
    method( LComboBox, setSelectedItemIndex ),
    method( LComboBox, isItemEnabled ),
    method( LComboBox, setItemEnabled ),
    method( LComboBox, getItemText ),
    method( LComboBox, getSelectedIdAsValue ),
    method( LComboBox, getNumItems ),
    method( LComboBox, getItemId ),
    method( LComboBox, setEditableText ),
    method( LComboBox, addSectionHeading ),
    method( LComboBox, valueChanged ),
    method( LComboBox, showPopup ),
    method( LComboBox, labelTextChanged ),
    method( LComboBox, addListener ),
    method( LComboBox, handleAsyncUpdate ),
    method( LComboBox, removeListener ),
    method( LComboBox, showEditor ),
    method( LComboBox, changeItemText ),
    method( LComboBox, addItem ),
    method( LComboBox, addItemList ),
    method( LComboBox, addSeparator ),
    method( LComboBox, clear ),
    {0,0}
};

const Luna<LComboBox>::StaticType LComboBox::statics[] = {
    {0,0}
};

LComboBox::LComboBox(lua_State *L)
    : LComponent(L, this),
      ComboBox()
{
    ComboBox::setName(myName());
    ComboBox::addListener(this);

    REGISTER_CLASS(LComboBox);
}

LComboBox::~LComboBox() {}

int LComboBox::addListener(lua_State*) {
    ComboBox::addListener(this);
    return 0;
}

int LComboBox::removeListener(lua_State*) {
    ComboBox::removeListener(this);
    return 0;
}

void LComboBox::comboBoxChanged(ComboBox *c) {
    if(hasCallback("comboBoxChanged"))
        callback("comboBoxChanged");
}
int LComboBox::comboBoxChanged(lua_State*) {
    set("comboBoxChanged");
    return 0;
}

void LComboBox::valueChanged(Value& v) {
    if(hasCallback("valueChanged"))
        callback("valueChanged", 0, { v.toString() });
    else
        ComboBox::valueChanged(v);
}
int LComboBox::valueChanged ( lua_State* ) {
    set("valueChanged");
    return 0;
}

void LComboBox::labelTextChanged(Label* l) {
    if(hasCallback("labelTextChanged"))
        callback("labelTextChanged", 0, { l->getText(true) });
    else
        ComboBox::labelTextChanged(l);
}
int LComboBox::labelTextChanged ( lua_State* ) {
    set("labelTextChanged");
    return 0;
}

void LComboBox::paint(Graphics& g) {
    if(hasCallback("paint"))
        LComponent::lpaint(g);
    else
        ComboBox::paint(g);
}

void LComboBox::mouseMove(const MouseEvent& e) {
    if(hasCallback("mouseMove"))
        LComponent::lmouseMove(e);
    else
        ComboBox::mouseMove(e);
}

void LComboBox::mouseEnter(const MouseEvent& e) {
    if(hasCallback("mouseEnter"))
        LComponent::lmouseEnter(e);
    else
        ComboBox::mouseEnter(e);
}

void LComboBox::mouseExit(const MouseEvent& e) {
    if(hasCallback("mouseExit"))
        LComponent::lmouseExit(e);
    else
        ComboBox::mouseExit(e);
}

void LComboBox::mouseDown(const MouseEvent& e) {
    if(hasCallback("mouseDown"))
        LComponent::lmouseDown(e);
    else
        ComboBox::mouseDown(e);
}

void LComboBox::mouseDrag(const MouseEvent& e) {
    if(hasCallback("mouseDrag"))
        LComponent::lmouseDrag(e);
    else
        ComboBox::mouseDrag(e);
}

void LComboBox::mouseUp(const MouseEvent& e) {
    if(hasCallback("mouseUp"))
        LComponent::lmouseUp(e);
    else
        ComboBox::mouseUp(e);
}

void LComboBox::mouseDoubleClick(const MouseEvent& e) {
    if(hasCallback("mouseDoubleClick"))
        LComponent::lmouseDoubleClick(e);
    else
        ComboBox::mouseDoubleClick(e);
}

void LComboBox::mouseWheelMove(const MouseEvent& e, const MouseWheelDetails& wheel) {
    if(hasCallback("mouseWheelMove"))
        LComponent::lmouseWheelMove(e, wheel);
    else
        ComboBox::mouseWheelMove(e, wheel);
}

void LComboBox::mouseMagnify(const MouseEvent& e, float scaleFactor) {
    if(hasCallback("mouseMagnify"))
        LComponent::lmouseMagnify(e, scaleFactor);
    else
        ComboBox::mouseMagnify(e, scaleFactor);
}

bool LComboBox::keyPressed(const KeyPress& k) {
    if(hasCallback("keyPressed"))
        return LComponent::lkeyPressed(k);
    else
        return ComboBox::keyPressed(k);
}

/////// getters/setters
int LComboBox::getJustificationType ( lua_State* ) {
    return LUA::returnNumber( ComboBox::getJustificationType().getFlags() );
}
int LComboBox::setJustificationType ( lua_State* ) {
    ComboBox::setJustificationType((Justification)LUA::getNumber<int>(2));
    return 0;
}

int LComboBox::getTooltip ( lua_State* ) {
    return LUA::returnString( ComboBox::getTooltip() );
}
int LComboBox::setTooltip ( lua_State* ) {
    ComboBox::setTooltip(LUA::getString());
    return 0;
}

int LComboBox::getTextWhenNoChoicesAvailable ( lua_State* ) {
    return LUA::returnString( ComboBox::getTextWhenNoChoicesAvailable() );
}
int LComboBox::setTextWhenNoChoicesAvailable ( lua_State* ) {
    ComboBox::setTextWhenNoChoicesAvailable(LUA::getString());
    return 0;
}

int LComboBox::getTextWhenNothingSelected ( lua_State* ) {
    return LUA::returnString( ComboBox::getTextWhenNothingSelected() );
}
int LComboBox::setTextWhenNothingSelected ( lua_State* ) {
    ComboBox::setTextWhenNothingSelected(LUA::getString());
    return 0;
}

int LComboBox::getSelectedId ( lua_State* ) {
    return LUA::returnNumber( ComboBox::getSelectedId() );
}
int LComboBox::setSelectedId ( lua_State* ) {
    int newItemId = LUA::getNumber<int>(2);
    NotificationType notif = (NotificationType)LUA::checkAndGetNumber<int>(2, NotificationType::sendNotificationAsync);
    ComboBox::setSelectedId( newItemId, notif );
    return 0;
}

int LComboBox::getText ( lua_State* ) {
    return LUA::returnString( ComboBox::getText() );
}
int LComboBox::setText ( lua_State* ) {
    String newText = LUA::getString(2);
    NotificationType notif = (NotificationType)LUA::checkAndGetNumber<int>(2, NotificationType::sendNotificationAsync);
    ComboBox::setText( newText, notif );
    return 0;
}

int LComboBox::getSelectedItemIndex ( lua_State* ) {
    return LUA::returnNumber( ComboBox::getSelectedItemIndex() );
}
int LComboBox::setSelectedItemIndex ( lua_State* ) {
    int newItemIndex = LUA::getNumber<int>(2);
    NotificationType notif = (NotificationType)LUA::checkAndGetNumber<int>(2, NotificationType::sendNotificationAsync);
    ComboBox::setSelectedItemIndex( newItemIndex, notif );
    return 0;
}

int LComboBox::isItemEnabled ( lua_State* ) {
    int itemId = LUA::getNumber<int>(2);
    return LUA::returnBoolean( ComboBox::isItemEnabled( itemId ) );
}
int LComboBox::setItemEnabled ( lua_State* ) {
    int itemId = LUA::getNumber<int>(2);
    bool shouldBeEnabled = LUA::getBoolean(2);
    ComboBox::setItemEnabled( itemId, shouldBeEnabled );
    return 0;
}

/////// getters
int LComboBox::isTextEditable ( lua_State* ) {
    return LUA::returnBoolean( ComboBox::isTextEditable() );
}

int LComboBox::indexOfItemId ( lua_State* ) {
    int itemId = LUA::getNumber<int>(2);
    return LUA::returnNumber( ComboBox::indexOfItemId( itemId ) );
}

int LComboBox::getItemText ( lua_State* ) {
    int index = LUA::getNumber<int>(2);
    return LUA::returnString( ComboBox::getItemText( index ) );
}

int LComboBox::getSelectedIdAsValue ( lua_State *L ) {
    return LUA::returnString( ComboBox::getSelectedIdAsValue().toString() );
}

int LComboBox::getNumItems ( lua_State* ) {
    return LUA::returnNumber( ComboBox::getNumItems() );
}

int LComboBox::getItemId ( lua_State* ) {
    int index = LUA::getNumber<int>(2);
    return LUA::returnNumber( ComboBox::getItemId( index ) );
}

/////// setters
int LComboBox::setEditableText ( lua_State* ) {
    ComboBox::setEditableText(LUA::getBoolean(2));
    return 0;
}

int LComboBox::addSectionHeading ( lua_State* ) {
    ComboBox::addSectionHeading(LUA::getString(2));
    return 0;
}

int LComboBox::showPopup ( lua_State* ) {
    ComboBox::showPopup();
    return 0;
}

int LComboBox::handleAsyncUpdate ( lua_State* ) {
    ComboBox::handleAsyncUpdate();
    return 0;
}

int LComboBox::showEditor ( lua_State* ) {
    ComboBox::showEditor();
    return 0;
}

int LComboBox::changeItemText ( lua_State* ) {
    int itemId = LUA::getNumber<int>(2);
    String newText = LUA::getString(2);
    ComboBox::changeItemText( itemId, newText );
    return 0;
}

int LComboBox::addItem ( lua_State* ) {
    String newItemText = LUA::getString(2);
    int newItemId = LUA::getNumber<int>(2);
    ComboBox::addItem( newItemText, newItemId );
    return 0;
}

int LComboBox::addItemList ( lua_State* ) {
    StringArray items = LUCE::luce_tostringarray(2);
    int firstItemIdOffset = LUA::getNumber<int>(2);
    ComboBox::addItemList( items, firstItemIdOffset );
    return 0;
}

int LComboBox::addSeparator ( lua_State* ) {
    ComboBox::addSeparator();
    return 0;
}

int LComboBox::clear ( lua_State* ) {
    NotificationType notif = (NotificationType)LUA::checkAndGetNumber<int>(2, NotificationType::sendNotificationAsync);
    ComboBox::clear(notif);
    return 0;
}
