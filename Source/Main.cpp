#include <cstring>

#ifdef __cplusplus
extern "C" {
#endif

//==============================================================================
static LJUCEApplication *mainClass = nullptr;

static juce::JUCEApplicationBase* juce_CreateApplication() {
    jassert( mainClass != nullptr );
    return mainClass;
}

int lua_main(void) {
    juce::JUCEApplicationBase::createInstance = &juce_CreateApplication;
    // automatic
    int res = juce::JUCEApplicationBase::main();
    
    /*
    // manual
    if ( MessageManager::getInstanceWithoutCreating() != nullptr )
        printf("ok, it's there too\n");
    else
        printf("well... not here ?\n");

    const ScopedPointer<JUCEApplicationBase> app (juce::JUCEApplicationBase::createInstance());
    app->initialiseApp();
    MessageManager::getInstance()->runDispatchLoop();
    mainClass->shutdown();

    DeletedAtShutdown::deleteAll();
    MessageManager::deleteInstance();
    
    if ( MessageManager::getInstanceWithoutCreating() != nullptr )
        printf("definitively is there\n");
    else
        printf("ok, gone\n");
    */
    return 0;
}

String *myStr;
void *mm_cb(void*) {
    myStr = new String("yo?");
    std::cout << "loop ?" << std::endl;
    
    return myStr;
}   

int lua_main_manual(lua_State *L, const int& cb_ref) {
    juce::JUCEApplicationBase::createInstance = &juce_CreateApplication;
    
    const ScopedPointer<JUCEApplicationBase> app (juce::JUCEApplicationBase::createInstance());
    app->initialiseApp();

    MainThread myThread("Main luce Thread", L, cb_ref);
    myThread.run();

    //String anotherStr("other str");
    //instance->callFunctionOnMessageThread( mm_cb, &anotherStr );
    //MessageManager::getInstance()->runDispatchLoop();

    return 0;
}

int lua_shutdown(lua_State *L) {
    //mainClass->shutdown(); // can't be called from there because... No more Display ?
    //so let's lua call this for us

    DBG("START CLEANING");
    lua_gc(L, LUA_GCCOLLECT, 0 );
    // clean instanciated but never used objects
    if (LUA::objects.size()) {
        for (auto& it : LUA::objects) {
            if ( it.second ) {
                std::cout << "WARNING: object '" << it.second->myName() << "'"
                    << " instanciated but probably never used -- cleaning" << std::endl;
                it.second->selfKill();
            }
        }
    }
    lua_gc(L, LUA_GCCOLLECT, 0 );

    DeletedAtShutdown::deleteAll();
    MessageManager::deleteInstance();
    

    shutdownJuce_GUI();
    if ( MessageManager::getInstanceWithoutCreating() != nullptr ) {
        DBG("WARNING: an instance of MessageManager still exists !");
    }

    DBG("ENDED CLEANING");
    return 0;
}

//==============================================================================
int start( lua_State *L ) {
    juce::JUCEApplicationBase::createInstance = &juce_CreateApplication;
    
    LJUCEApplication *mc = Luna<LJUCEApplication>::check(L, 2);
    mainClass = mc;

    int rc = lua_main();
    // if ( rc ) luaL_error...
    DBG("END of START\n");
    return 0;
}
int start_manual( lua_State *L ) {
    LUA::Set(L);
    luaL_checktype(L, -1, LUA_TFUNCTION); // cb
    luaL_checktype(L, -2, LUA_TTABLE); // LJUCEApp

    int cb_ref = luaL_ref(L, LUA_REGISTRYINDEX);

    juce::JUCEApplicationBase::createInstance = &juce_CreateApplication;
    
    LJUCEApplication *mc = Luna<LJUCEApplication>::check(L, -1); // luaL_ref pop'ed the cb function
    mainClass = mc;

    int rc = lua_main_manual(L, cb_ref);
    // if ( rc ) luaL_error...
    DBG("END of START\n");
    return 0;
}

//==============================================================================
int l_JUCEApplication(lua_State *L) {
    Luna<LJUCEApplication>::Register(L);
    return 1;
}

int l_Component(lua_State *L) {
    Luna<LComponent>::Register(L);
    return 1;
}

int l_DocumentWindow(lua_State *L) {
    Luna<LDocumentWindow>::Register(L); //, "DocumentWindow");
    return 1;
}

int l_MainComponent(lua_State *L) {
    Luna<LMainComponent>::Register(L);
    return 1;
}

int l_TextButton(lua_State *L) {
    Luna<LTextButton>::Register(L);
    return 1;
}

// until I'm sure this is really collected by the gc, I'll stick to strings
void l_NotificationType(lua_State *L) {
    lua_newtable(L);
        //NotificationType *n1 = (NotificationType*)lua_newuserdata(L, sizeof(NotificationType));
        //*n1 = NotificationType::dontSendNotification;
        lua_pushstring(L, "dontSendNotification");
        lua_setfield(L, -2, "dontSendNotification");

        //NotificationType *n2 = (NotificationType*)lua_newuserdata(L, sizeof(NotificationType));
        //*n2 = NotificationType::sendNotification;
        lua_pushstring(L, "sendNotification");
        lua_setfield(L, -2, "sendNotification");

        //NotificationType *n3 = (NotificationType*)lua_newuserdata(L, sizeof(NotificationType));
        //*n3 = NotificationType::sendNotificationSync;
        lua_pushstring(L, "sendNotificationSync");
        lua_setfield(L, -2, "sendNotificationSync");

        //NotificationType *n4 = (NotificationType*)lua_newuserdata(L, sizeof(NotificationType));
        //*n4 = NotificationType::sendNotificationAsync;
        lua_pushstring(L, "sendNotificationAsync");
        lua_setfield(L, -2, "sendNotificationAsync");
    lua_setfield(L, -2, "NotificationType");
}

int l_Label(lua_State *L) {
    Luna<LLabel>::Register(L);
    return 1;
}

int l_TextEditor(lua_State *L) {
    Luna<LTextEditor>::Register(L);
    return 1;
}

int l_TreeView(lua_State *L) {
    Luna<LTreeView>::Register(L);
    return 1;
}

int l_TreeViewItem(lua_State *L) {
    Luna<LTreeViewItem>::Register(L);
    return 1;
}

int l_ModifierKeys(lua_State *L) {
    Luna<LModifierKeys>::Register(L);
    return 1;
}

int l_MouseEvent(lua_State *L) {
    Luna<LMouseEvent>::Register(L);
    return 1;
}

int l_StretchableLayoutManager(lua_State *L) {
    Luna<LStretchableLayoutManager>::Register(L);
    return 1;
}

int l_StretchableLayoutResizerBar(lua_State *L) {
    Luna<LStretchableLayoutResizerBar>::Register(L);
    return 1;
}



//int l_ValueTree(lua_State *L) {
//    Luna<LValueTree>::Register(L);
//    return 1;
//}

static const luaL_reg luce_lib [] = {
    { "JUCEApplication", l_JUCEApplication },
    { "LComponent", l_Component },
    { "DocumentWindow", l_DocumentWindow },
    { "MainComponent", l_MainComponent },
    { "TextButton", l_TextButton },
    { "TextEditor", l_TextEditor },
    { "Label", l_Label },
    { "TreeView", l_TreeView },
    { "TreeViewItem", l_TreeViewItem },
    { "ModifierKeys", l_ModifierKeys},
    { "MouseEvent", l_MouseEvent },
    { "StretchableLayoutManager", l_StretchableLayoutManager },
    { "StretchableLayoutResizerBar", l_StretchableLayoutResizerBar },
    //{ "ValueTree", l_ValueTree },
    { "start", start },
    { "start_manual", start_manual },
    { "shutdown", lua_shutdown },
    {NULL, NULL}
};

#ifdef DEBUG
int luaopen_luce_core_d (lua_State *L) {
#else
int luaopen_luce_core (lua_State *L) {
#endif
//int luaopen_luce (lua_State *L) {
    DBG("LUCE " JUCE_STRINGIFY(LUCE_VERSION_MAJOR) "." JUCE_STRINGIFY(LUCE_VERSION_MINOR))
    initialiseJuce_GUI();
    juce::JUCEApplicationBase::createInstance = &juce_CreateApplication;
    //luaL_register(L,"luce.core", luce_lib);
    //luaL_register(L,"luce", luce_lib);
    //l_NotificationType(L);

    lua_newtable(L);
    int i = lua_gettop(L);
    for (int f = 0; luce_lib[f].name ; ++f ) {
        DBG(String("adding ") +luce_lib[f].name );
        lua_pushstring(L,luce_lib[f].name);
        lua_pushcfunction(L, luce_lib[f].func);
        lua_settable(L, i);
    }
    
    l_NotificationType(L);

    return 1;
}

#ifdef __cplusplus
}
#endif
