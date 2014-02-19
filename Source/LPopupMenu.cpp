/************************************************************

 LPopupMenu.cpp

    @author Christophe Berbizier (cberbizier@peersuasive.com)
    @license GPLv3
    @copyright 


(c) 2014, Peersuasive Technologies

*************************************************************/

// TODO: menu iterator

#include "LPopupMenu_inh.h"

const char LPopupMenu::className[] = "LPopupMenu";
const Luna<LPopupMenu>::PropertyType LPopupMenu::properties[] = {
    {0,0}
};
const Luna<LPopupMenu>::FunctionType LPopupMenu::methods[] = {
    method( LPopupMenu, containsCommandItem ),
    method( LPopupMenu, getNumItems ),
    method( LPopupMenu, containsAnyActiveItems ),
    method( LPopupMenu, addColouredItem ),
    method( LPopupMenu, showMenuAsync ),
    method( LPopupMenu, show ),
    method( LPopupMenu, addSubMenu ),
    method( LPopupMenu, addSectionHeader ),
    method( LPopupMenu, addItem ),
    method( LPopupMenu, addCommandItem ),
    method( LPopupMenu, setLookAndFeel ),
    method( LPopupMenu, addSeparator ),
    method( LPopupMenu, clear ),
    method( LPopupMenu, addCustomItem ),
    method( LPopupMenu, menuInvocationCallback ),
    {0,0}
};

const Luna<LPopupMenu>::StaticType LPopupMenu::statics[] = {
    smethod( LPopupMenu, dismissAllActiveMenus ),
    smethod( LPopupMenu, Options ),
    {0,0}
};

LPopupMenu::LPopupMenu(lua_State *L)
    : LBase(L, "LPopupMenu", true),
      PopupMenu()
{
}

LPopupMenu::LPopupMenu(lua_State *L, const PopupMenu& class_)
    : LBase(L, "LPopupMenu", true),
      PopupMenu( class_ )
{
}

LPopupMenu::~LPopupMenu() {
    std::cout << "DELETING" << std::endl;
    if(cbComp)
        cbComp = nullptr;
}

/////// statics
int LPopupMenu::s_dismissAllActiveMenus ( lua_State* ) {
    return LUA::returnBoolean( PopupMenu::dismissAllActiveMenus() );
}

int LPopupMenu::s_Options(lua_State *L) {
    return LUA::storeAndReturnUserdata<LOptions>( new LOptions(L) );
}

/////// getters
int LPopupMenu::containsCommandItem ( lua_State* ) {
    int commandID = LUA::getNumber<int>(2);
    return LUA::returnBoolean( PopupMenu::containsCommandItem( commandID ) );
}

int LPopupMenu::getNumItems ( lua_State* ) {
    return LUA::returnNumber( PopupMenu::getNumItems() );
}

int LPopupMenu::containsAnyActiveItems ( lua_State* ) {
    return LUA::returnBoolean( PopupMenu::containsAnyActiveItems() );
}

/////// setters
int LPopupMenu::addColouredItem ( lua_State* ) {
    int itemResultID      = LUA::getNumber<int>(2);
    String itemText       = LUA::getString(2);
    Colour itemTextColour = *LUA::from_luce<LColour>(2);
    bool isEnabled        = LUA::checkAndGetBoolean(2, true);
    bool isTicked         = LUA::checkAndGetBoolean(2, false);
    Image iconToUse       = *LUA::from_luce<LImage>(2);
    PopupMenu::addColouredItem( itemResultID, itemText, itemTextColour, isEnabled, isTicked, iconToUse );
    return 0;
}

int LPopupMenu::addSubMenu ( lua_State *L ) {
    String subMenuName  = LUA::getString(2);
    PopupMenu subMenu   ( *LUA::from_luce<LPopupMenu>(2) );
    bool isEnabled      = LUA::checkAndGetBoolean(2, true);
    if(!lua_isnoneornil(L,2)) {
        bool isTicked = LUA::checkAndGetBoolean(3, false);
        int itemResultID = LUA::checkAndGetNumber(3, 0);
        if(LUCE::luce_isofclass(LImage, 2))
            PopupMenu::addSubMenu(subMenuName, subMenu, isEnabled, 
                    *LUA::from_luce<LImage>(2), isTicked, itemResultID);
        // TODO
        //else
        //    PopupMenu::addSubMenu(subMenuName, subMenu, isEnabled, 
        //            *LUA::from_luce<LDrawable, Drawable>(2), isTicked, itemResultID);
    }
    else
        PopupMenu::addSubMenu(subMenuName, subMenu, isEnabled, nullptr, false, 0);

    return 0;
}

int LPopupMenu::addSectionHeader ( lua_State* ) {
    PopupMenu::addSectionHeader(LUA::getString());
    return 0;
}

int LPopupMenu::addItem ( lua_State *L ) {
    int itemResultID    = LUA::getNumber<int>(2);
    String itemText     = LUA::getString(2);
    bool   isEnabled    = LUA::checkAndGetBoolean(2, true);
    bool   isTicked     = LUA::checkAndGetBoolean(2, false);
    if(!lua_isnoneornil(L,2)) {
        if(LUCE::luce_isofclass(LImage, 2))
            PopupMenu::addItem( itemResultID, itemText, isEnabled, isTicked,
                    *LUA::from_luce<LImage>(2));
        // TODO
        //else
        //    PopupMenu::addItem( itemResultID, itemText, isEnabled, isTicked,
        //            *LUA::from_luce<LDrawable, Drawable>(2));
    }
    else
        PopupMenu::addItem(itemResultID, itemText, isEnabled, isTicked);

    return 0;
}

int LPopupMenu::addCommandItem ( lua_State* ) {
    ApplicationCommandManager *commandManager = &LDocumentWindow::getApplicationCommandManager();
    CommandID commandID = (CommandID)LUA::getNumber<int>(2);
    String displayName  = LUA::checkAndGetString(2, String::empty);
    PopupMenu::addCommandItem( commandManager, commandID, displayName );
    return 0;
}

int LPopupMenu::addSeparator ( lua_State* ) {
    PopupMenu::addSeparator();
    return 0;
}

int LPopupMenu::clear ( lua_State* ) {
    PopupMenu::clear();
    return 0;
}

int LPopupMenu::addCustomItem ( lua_State *L ) {
    int itemResultID = LUA::getNumber<int>(2);
    Component *comp  = LUA::from_luce<LJComponent, Component>(2);
    int idealWidth   = LUA::getNumber<int>(2);
    bool triggerMenuItemAutomaticallyWhenClicked = LUA::getBoolean(2);
    LPopupMenu *popupMenu = nullptr;
    if(!lua_isnoneornil(L, 2))
        popupMenu = LUA::from_luce<LPopupMenu>(2);
    
    PopupMenu::addCustomItem( itemResultID, comp, idealWidth, triggerMenuItemAutomaticallyWhenClicked, popupMenu );
    return 0;
}

void LPopupMenu::menuInvocationCallback(int id) {
    if(hasCallback("menuInvocationCallback")) {
        lua_State *LL = LUA::Get();
        this->incRefCount();
        callback("menuInvocationCallback", 0, { id , new LRefBase( "PopupMenu", this ) } );
        //callback("menuInvocationCallback", 0, { id , new LRefBase( LUA::SELF, this ) } );
    }
}
int LPopupMenu::menuInvocationCallback(lua_State *L) {
    set("menuInvocationCallback");
    return 0;
}

// that's a short story long... 
// reimplement JUCE's ModalComponentManager/Callbacks with c++11 lambda
// or fully reimplement PopupMenu
int LPopupMenu::showMenuAsync ( lua_State* ) {
    if(!cbComp)
        cbComp = new LCallbackComponent(this);

    Options options = *LUA::from_luce<LOptions>(2);
    ModalComponentManager::Callback* callback = 
        ModalCallbackFunction::forComponent(
                LPopupMenu::LCallbackComponent::menuInvocationCallback, cbComp.get() );
    PopupMenu::showMenuAsync( options, callback );
    return 0;
}

int LPopupMenu::show(lua_State*) {
    return LUA::returnNumber<int>( PopupMenu::show() );
}

int LPopupMenu::setLookAndFeel ( lua_State* ) {
    // arg ! this class doesn't inherit LComponent...
    PopupMenu::setLookAndFeel( LComponent::getLookAndFeel(LUA::getNumber<int>(2)) );
    return 0;
}
