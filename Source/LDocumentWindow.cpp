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
    {0,0}
};

const Luna<LDocumentWindow>::FunctionType LDocumentWindow::methods[] = {
    method( LDocumentWindow, closeButtonPressed ),
    method( LDocumentWindow, setVisible ),
    method( LDocumentWindow, addChildComponent ),
    method( LDocumentWindow, addAndMakeVisible ),
    method( LDocumentWindow, setContentOwned ),
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

    setResizable( true, false );
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
