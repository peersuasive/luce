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

LDocumentWindow::LDocumentWindow(lua_State *L)
    :  LComponent(L, this),
       DocumentWindow( "DocumentWindow", Colours::lightgrey, DocumentWindow::allButtons )
{
    DocumentWindow::setName( myName );
    commandManager = new ApplicationCommandManager();

    reg( "closeButtonPressed" );

    DocumentWindow::addKeyListener (commandManager->getKeyMappings());
    triggerAsyncUpdate();

    setResizable( true, false );
}

LDocumentWindow::~LDocumentWindow() {
    commandManager = nullptr;
}

void LDocumentWindow::handleAsyncUpdate() {
    commandManager->registerAllCommandsForTarget (JUCEApplication::getInstance());
}

int LDocumentWindow::setContentOwned(lua_State*) {
    DocumentWindow::setContentOwned( LUA::to_juce<Component>(2), LUA::checkAndGetBoolean(2, true) );
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
    callback( "closeButtonPressed" );
    JUCEApplication::getInstance()->systemRequestedQuit();
}

int LDocumentWindow::closeButtonPressed(lua_State *L) {
    set("closeButtonPressed");
    return 0;
}
