/************************************************************

 LDocumentWindow.cpp

    @author Christophe Berbizier (cberbizier@peersuasive.com)
    @license GPLv3
    @copyright 


(c) 2013, Peersuasive Technologies

*************************************************************/

#include "LDocumentWindow_inh.h"
const char LDocumentWindow::className[] = "LDocumentWindow";

const Luna<LDocumentWindow>::PropertyType LDocumentWindow::properties[] = {
    {"visible", &LComponent::isVisible, &LDocumentWindow::setVisible},

    {"kioskMode", &LDocumentWindow::isKioskMode, &LDocumentWindow::setKioskMode},
    {"constrainer", &LDocumentWindow::getConstrainer, &LDocumentWindow::setConstrainer},
    {"fullScreen", &LDocumentWindow::isFullScreen, &LDocumentWindow::setFullScreen},
    {"resizable", &LDocumentWindow::isResizable, &LDocumentWindow::setResizable},
    {"backgroundColour", &LDocumentWindow::getBackgroundColour, &LDocumentWindow::setBackgroundColour},
    {"minimised", &LDocumentWindow::isMinimised, &LDocumentWindow::setMinimised},

    {0,0}
};

const Luna<LDocumentWindow>::FunctionType LDocumentWindow::methods[] = {
    method( LDocumentWindow, closeButtonPressed ),
    method( LDocumentWindow, setVisible ),
    method( LDocumentWindow, addChildComponent ),
    method( LDocumentWindow, addAndMakeVisible ),
    method( LDocumentWindow, setContentOwned ),

    method( LDocumentWindow, getConstrainer ),
    method( LDocumentWindow, setConstrainer ),
    method( LDocumentWindow, isFullScreen ),
    method( LDocumentWindow, setFullScreen ),
    method( LDocumentWindow, getContentComponent ),
    method( LDocumentWindow, isResizable ),
    method( LDocumentWindow, setResizable ),
    method( LDocumentWindow, getWindowStateAsString ),
    method( LDocumentWindow, getContentComponentBorder ),
    method( LDocumentWindow, getDesktopWindowStyleFlags ),
    method( LDocumentWindow, restoreWindowStateFromString ),
    method( LDocumentWindow, getBackgroundColour ),
    method( LDocumentWindow, setBackgroundColour ),
    method( LDocumentWindow, getBorderThickness ),
    method( LDocumentWindow, isKioskMode ),
    method( LDocumentWindow, setKioskMode ),
    method( LDocumentWindow, isMinimised ),
    method( LDocumentWindow, setMinimised ),
    method( LDocumentWindow, setContentNonOwned ),
    method( LDocumentWindow, setBoundsConstrained ),
    method( LDocumentWindow, activeWindowStatusChanged ),
    method( LDocumentWindow, setResizeLimits ),
    method( LDocumentWindow, clearContentComponent ),
    method( LDocumentWindow, setContentComponentSize ),

    {0,0}
};

const Luna<LDocumentWindow>::StaticType LDocumentWindow::statics[] = {
    {0,0}
};

static ScopedPointer<ApplicationCommandManager> commandManager;
LDocumentWindow::LDocumentWindow(lua_State *L)
    :  LComponent(L, this),
       DocumentWindow( "DocumentWindow", Colours::lightgrey, DocumentWindow::allButtons )
{
    REGISTER_CLASS(LDocumentWindow);

    DocumentWindow::setName( myName() );
    commandManager = new ApplicationCommandManager();

    DocumentWindow::addKeyListener (commandManager->getKeyMappings());
    triggerAsyncUpdate();

    DocumentWindow::setResizable( true, false );
}

LDocumentWindow::~LDocumentWindow() {
    if(commandManager)
        commandManager = nullptr;
}

ApplicationCommandManager& LDocumentWindow::getApplicationCommandManager() {
    if (!commandManager)
        commandManager = new ApplicationCommandManager();
    return *commandManager;
}


void LDocumentWindow::handleAsyncUpdate() {
    commandManager->registerAllCommandsForTarget (JUCEApplication::getInstance());
}

int LDocumentWindow::setContentOwned(lua_State*) {
    DocumentWindow::setContentOwned( LUA::from_luce<LComponent,Component>(2), LUA::checkAndGetBoolean(2, true) );
    return 0;
}

int LDocumentWindow::setVisible(lua_State *L) {
    bool v = LUA::getBoolean(2);
    if(v) {
        DocumentWindow::setVisible (true);
        setUsingNativeTitleBar( true );
    }
    else
        DocumentWindow::setVisible(false);

    return 0;
}

// TODO: remove
int LDocumentWindow::addChildComponent(lua_State *L) {
    // must not use this method
    return 0;
}

// TODO: remove
int LDocumentWindow::addAndMakeVisible(lua_State *L) {
    // must not use this method
    return 0;
}

void LDocumentWindow::closeButtonPressed() {
    if(hasCallback("closeButtonPressed")) {
        if ( callback( "closeButtonPressed", 1 ) ) {
            bool r = LUA::checkAndGetBoolean(-1, true);
            if(!r) return;
        }
    }
    JUCEApplication::getInstance()->systemRequestedQuit();
}

int LDocumentWindow::closeButtonPressed(lua_State *L) {
    set("closeButtonPressed");
    return 0;
}

bool LDocumentWindow::keyPressed(const KeyPress& k) {
    if(hasCallback("keyPressed"))
        return LComponent::lkeyPressed(k);
    else
        return DocumentWindow::keyPressed(k);
}

bool LDocumentWindow::keyStateChanged(bool d) {
    if(hasCallback("keyStateChanged"))
        return LComponent::lkeyStateChanged(d);
    else
        return DocumentWindow::keyStateChanged(d);
}


//==============================================================================
/////// getters/setters
int LDocumentWindow::getConstrainer ( lua_State *L ) {
    // CHECK
    // return LUA::storeAndReturnUserdata<LComponentBoundsConstrainer>( new LComponentBoundsConstrainer(L,
    //     DocumentWindow::getConstrainer()
    // ));
    lua_settop(LUA::Get(), 1); // added by TODO
    return LUA::TODO_OBJECT( "ComponentBoundsConstrainer getConstrainer()" );
}
int LDocumentWindow::setConstrainer ( lua_State* ) {
    // DocumentWindow::setConstrainer(LUA::from_luce<LComponentBoundsConstrainer>(2); // TODO);
    LUA::TODO_OBJECT( "setConstrainer, LUA::from_luce<LComponentBoundsConstrainer>(2); // TODO" );
    lua_settop(LUA::Get(), 1); // added by TODO
    return 0;
}

int LDocumentWindow::isFullScreen ( lua_State* ) {
    return LUA::returnBoolean( DocumentWindow::isFullScreen() );
}
int LDocumentWindow::setFullScreen ( lua_State* ) {
    DocumentWindow::setFullScreen(LUA::getBoolean(2));
    return 0;
}

int LDocumentWindow::isResizable ( lua_State* ) {
    return LUA::returnBoolean( DocumentWindow::isResizable() );
}
int LDocumentWindow::setResizable ( lua_State* ) {
    bool shouldBeResizable = LUA::getBoolean(2);
    bool useBottomRightCornerResizer = LUA::getBoolean(2);
    DocumentWindow::setResizable( shouldBeResizable, useBottomRightCornerResizer );
    return 0;
}

int LDocumentWindow::getBackgroundColour ( lua_State *L ) {
    return LUA::storeAndReturnUserdata<LColour>( new LColour(L,
        DocumentWindow::getBackgroundColour()
    ));
}
int LDocumentWindow::setBackgroundColour ( lua_State *L ) {
    Colour colour;
    if( lua_isstring(L,2) )
        colour = Colours::findColourForName( LUA::getString(2), Colours::white );
    else
        colour = *LUA::from_luce<LColour>(2);
    DocumentWindow::setBackgroundColour( colour );
    return 0;
}

int LDocumentWindow::isMinimised ( lua_State* ) {
    return LUA::returnBoolean( DocumentWindow::isMinimised() );
}
int LDocumentWindow::setMinimised ( lua_State* ) {
    DocumentWindow::setMinimised(LUA::getBoolean());
    return 0;
}

/////// getters
int LDocumentWindow::getContentComponent ( lua_State *L ) {
    return LUA::returnUserdata<LJComponent, Component>( DocumentWindow::getContentComponent() );
}

int LDocumentWindow::getWindowStateAsString ( lua_State* ) {
    return LUA::returnString( DocumentWindow::getWindowStateAsString() );
}

int LDocumentWindow::getContentComponentBorder ( lua_State *L ) {
    // CHECK
    // return LUA::storeAndReturnUserdata<LBorderSize>( new LBorderSize(L,
    //     DocumentWindow::getContentComponentBorder()
    // ));
    lua_settop(LUA::Get(), 1); // added by TODO
    return LUA::TODO_OBJECT( "BorderSize getContentComponentBorder()" );
}

int LDocumentWindow::getDesktopWindowStyleFlags ( lua_State* ) {
    return LUA::returnNumber( DocumentWindow::getDesktopWindowStyleFlags() );
}

int LDocumentWindow::restoreWindowStateFromString ( lua_State* ) {
    String previousState = LUA::getString(2);
    return LUA::returnBoolean( DocumentWindow::restoreWindowStateFromString( previousState ) );
}

int LDocumentWindow::getBorderThickness ( lua_State *L ) {
    // CHECK
    // return LUA::storeAndReturnUserdata<LBorderSize>( new LBorderSize(L,
    //     DocumentWindow::getBorderThickness()
    // ));
    lua_settop(LUA::Get(), 1); // added by TODO
    return LUA::TODO_OBJECT( "BorderSize getBorderThickness()" );
}

int LDocumentWindow::isKioskMode ( lua_State* ) {
    return LUA::returnBoolean( DocumentWindow::isKioskMode() );
}

int LDocumentWindow::setKioskMode( lua_State* ) {
    bool state = LUA::getBoolean(2);
    bool allowMenusAndBars = LUA::checkAndGetBoolean(2);
    if(state)
        Desktop::getInstance().setKioskModeComponent( this, allowMenusAndBars );
    else
        Desktop::getInstance().setKioskModeComponent( nullptr, false );

    return 0;
}

/////// setters
int LDocumentWindow::setContentNonOwned ( lua_State* ) {
    Component *newContentComponent = LUA::from_luce<LComponent, Component>(2);
    bool resizeToFitWhenContentChangesSize = LUA::getBoolean(2);
    DocumentWindow::setContentNonOwned( newContentComponent, resizeToFitWhenContentChangesSize );
    return 0;
}

int LDocumentWindow::setBoundsConstrained ( lua_State* ) {
    DocumentWindow::setBoundsConstrained(LUA::getRectangle(2));
    return 0;
}

int LDocumentWindow::activeWindowStatusChanged ( lua_State* ) {
    DocumentWindow::activeWindowStatusChanged();
    return 0;
}

int LDocumentWindow::setResizeLimits ( lua_State* ) {
    int newMinimumWidth = LUA::getNumber<int>(2);
    int newMinimumHeight = LUA::getNumber<int>(2);
    int newMaximumWidth = LUA::getNumber<int>(2);
    int newMaximumHeight = LUA::getNumber<int>(2);
    DocumentWindow::setResizeLimits( newMinimumWidth, newMinimumHeight, newMaximumWidth, newMaximumHeight );
    return 0;
}

int LDocumentWindow::clearContentComponent ( lua_State* ) {
    DocumentWindow::clearContentComponent();
    return 0;
}

int LDocumentWindow::setContentComponentSize ( lua_State* ) {
    int width = LUA::getNumber<int>(2);
    int height = LUA::getNumber<int>(2);
    DocumentWindow::setContentComponentSize( width, height );
    return 0;
}


//==============================================================================

int LDocumentWindow::clearCommands(lua_State*) {
    commandManager->clearCommands();
    return 0;
}

int LDocumentWindow::registerCommand(lua_State*) {
    //TODO
    return 0;
}

int LDocumentWindow::registerAllCommandsForTarget(lua_State*) {
    //TODO
    return 0;
}

int LDocumentWindow::removeCommand(lua_State*) {
    //TODO commandid
    return 0;
}

int LDocumentWindow::commandStatusChanged(lua_State*) {
    commandManager->commandStatusChanged();
    return 0;
}

int LDocumentWindow::getNumCommands(lua_State*) {
    return LUA::getNumber( commandManager->getNumCommands() );
    return 0;
}

int LDocumentWindow::getCommandForIndex(lua_State*) {
    // TODO
    //return LUA::returnUserdata<LApplicationCommandInfo>( commandManager->getCommandForIndex() );
    return 0;
}

int LDocumentWindow::getCommandForID(lua_State*) {
    // TODO
    //return LUA::returnUserdata<LApplicationCommandInfo>( 
    //        commandManager->getCommandForIndex(LUA::getNumber<int>(2)) );
    return 0;
}

int LDocumentWindow::getNameOfCommand(lua_State*) {
    return LUA::returnString( commandManager->getNameOfCommand( (CommandID)LUA::getNumber<int>(2) ) );
}

int LDocumentWindow::getDescriptionOfCommand(lua_State*) {
    return LUA::returnString( commandManager->getDescriptionOfCommand( (CommandID)LUA::getNumber<int>(2) ) );
}

int LDocumentWindow::getCommandCategories(lua_State*) {
    return LUCE::luce_pushtable( commandManager->getCommandCategories() );
}

int LDocumentWindow::getCommandsInCategory(lua_State*) {
    return LUCE::luce_pushtable( commandManager->getCommandsInCategory( LUA::getString(2) ) );
}

int LDocumentWindow::getKeyMappings(lua_State*) {
    //return LUA::returnUserdata<LKeyPressMappingSet>( commandManager->getKeyMappings() );
    return 0;
}

int LDocumentWindow::invokeDirectly(lua_State*) {
    commandManager->invokeDirectly( (CommandID)LUA::getNumber<int>(2), LUA::getBoolean(3) );
    return 0;
}

int LDocumentWindow::invoke(lua_State *L) {
    // TODO
    return 0;
}

int LDocumentWindow::getFirstCommandTarget(lua_State*) {
    return 0;
}

int LDocumentWindow::setFirstCommandTarget(lua_State*) {
    return 0;
}

int LDocumentWindow::getTargetForCommand(lua_State*) {
    return 0;
}


// statics
int LDocumentWindow::findDefaultComponentTarget(lua_State*) {
    return 0;
}

int LDocumentWindow::findTargetForComponent(lua_State*) {
    return 0;
}
