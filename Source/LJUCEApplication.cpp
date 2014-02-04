/************************************************************

 LJUCEApplication.cpp

    @author Christophe Berbizier (cberbizier@peersuasive.com)
    @license GPLv3
    @copyright 


(c) 2013, Peersuasive Technologies

*************************************************************/

#include "LJUCEApplication_inh.h"
const char LJUCEApplication::className[] = "LJUCEApplication";

const Luna<LJUCEApplication>::PropertyType LJUCEApplication::properties[] = {
    {0,0}
};

const Luna<LJUCEApplication>::FunctionType LJUCEApplication::methods[] = {
    method( LJUCEApplication, getApplicationName ),
    method( LJUCEApplication, getApplicationVersion ),
    method( LJUCEApplication, moreThanOneInstanceAllowed ),
    method( LJUCEApplication, initialise ),
    method( LJUCEApplication, shutdown ),
    method( LJUCEApplication, systemRequestedQuit ),
    method( LJUCEApplication, anotherInstanceStarted ),
    method( LJUCEApplication, quit ),

    // artificial
    method( LJUCEApplication, setDoubleClickTimeout ),

    {0,0}
};

const Luna<LJUCEApplication>::StaticType LJUCEApplication::statics[] = {
    {0,0}
};

LJUCEApplication::LJUCEApplication(lua_State *L)
    : LBase(L, "LJUCEApplication", false)
{
    myName( LUA::checkAndGetString(2, "LJUCEApplication") );
}

LJUCEApplication::~LJUCEApplication() {
    DBG("destroying MW...");
    if ( mainWindow )
        mainWindow = nullptr;

    DBG("END OF LJUCEApplication");
}

void LJUCEApplication::initialise (const String& commandLine) {
    int rc = callback("initialise", 1);
    if (rc != 1 )
        std::cout << "error at initialise method ("<<rc<<"): " << LUA::getError() << std::endl;
    else
        mainWindow = LUA::from_luce<LComponent,Component>();
}

int LJUCEApplication::initialise( lua_State *L ) {
    set("initialise");
    return 0;
}

void LJUCEApplication::systemRequestedQuit() {
    int rc = callback( "systemRequestedQuit" );
    if (rc != 1)
        JUCEApplication::quit();
}
int LJUCEApplication::systemRequestedQuit(lua_State *L) {
    set("systemRequestedQuit");
    return 0;
}

int LJUCEApplication::quit(lua_State *L) {
    JUCEApplication::quit();
    return 0;
}

const String LJUCEApplication::getApplicationName() {
    int rc = callback("getApplicationName");
    // retrieve name...
    if(rc) {
        //return call_cb_get_value();
        return ProjectInfo::projectName;
    }
    else
        return ProjectInfo::projectName;
}
int LJUCEApplication::getApplicationName(lua_State *L) { 
    set("getApplicationName");
    return 0;
}

const String LJUCEApplication::getApplicationVersion() {
    int rc = callback("getApplicationVersion");
    if(rc) {
        //return call_cb_get_value();
        return ProjectInfo::versionString;
    }
    else
        return ProjectInfo::versionString; 
}
int LJUCEApplication::getApplicationVersion(lua_State *L) {
    set("getApplicationVersion");
    return 0;
}

bool LJUCEApplication::moreThanOneInstanceAllowed() {
    if ( hasCallback("moreThanOneInstanceAllowed") )
        if( callback("moreThanOneInstanceAllowed") )
            return LUA::getBoolean();
    return true;
}
int LJUCEApplication::moreThanOneInstanceAllowed(lua_State *L) { 
    set("moreThanOneInstanceAllowed");
    return 0;
}

/// not a cb !
void LJUCEApplication::shutdown() {
    //callback("shutdown");
}
int LJUCEApplication::shutdown(lua_State *L) {
    // set("shutdown");
    this->shutdown();
    return 0;
}

void LJUCEApplication::anotherInstanceStarted (const String& commandLine) {
    callback("anotherInstanceStarted");
}
int LJUCEApplication::anotherInstanceStarted (lua_State *L) {
    set("anotherInstanceStarted");
    return 0;
}

int LJUCEApplication::setDoubleClickTimeout(lua_State*) {
    MouseEvent::setDoubleClickTimeout(LUA::getNumber());
    return 0;
}
