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
                if ( dynamic_cast<LComponent*>( (LSelfKill*)it.second ) )
                    std::cout << "WARNING: object '" << it.second->myName() << "'"
                        << " instanciated but not cleaned (probably never used) -- cleaning" << std::endl;
                DBG(String("Cleaning object: ") + it.second->myName());
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

int l_Colour(lua_State *L) {
    Luna<LColour>::Register(L);
    return 1;
}

int l_AffineTransform(lua_State *L) {
    Luna<LAffineTransform>::Register(L);
    return 1;
}

int l_Path(lua_State *L) {
    Luna<LPath>::Register(L);
    return 1;
}

int l_Graphics(lua_State *L) {
    Luna<LGraphics>::Register(L);
    return 1;
}

//int l_Component(lua_State *L) {
//    Luna<LComponent>::Register(L);
//    return 1;
//}

int l_DocumentWindow(lua_State *L) {
    Luna<LDocumentWindow>::Register(L); //, "DocumentWindow");
    return 1;
}

int l_MainComponent(lua_State *L) {
    Luna<LMainComponent>::Register(L);
    return 1;
}
int l_JComponent(lua_State *L) {
    Luna<LJComponent>::Register(L);
    return 1;
}

int l_TextButton(lua_State *L) {
    Luna<LTextButton>::Register(L);
    return 1;
}

void l_NotificationType(lua_State *L) {
    lua_newtable(L);
    int n = lua_gettop(L);
    for(auto& it : LConstants::lnotification) {
        lua_pushnumber(L, it.second);
        lua_setfield(L, -2, it.first);
    }
    lua_setfield(L, -2, "NotificationType");
}

void l_JustificationType(lua_State *L) {
    lua_newtable(L);
    for(auto& it : LConstants::ljustification) {
        lua_pushnumber(L, it.second);
        lua_setfield(L, -2, it.first);
    }
    lua_setfield(L, -2, "JustificationType");
}

void l_Colours(lua_State *L) {
    lua_newtable(L);
    int n = lua_gettop(L);
    for(auto& it : LConstants::lcolours) {
        lua_pushstring(L, it);
        lua_setfield(L, -2, it);
    }
    lua_setfield(L, -2, "Colours");
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

int l_SourceDetails(lua_State *L) {
    Luna<LSourceDetails>::Register(L);
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

int l_Font(lua_State *L) {
    Luna<LFont>::Register(L);
    return 1;
}

int l_ListBox(lua_State *L) {
    Luna<LListBox>::Register(L);
    return 1;
}

//int l_ValueTree(lua_State *L) {
//    Luna<LValueTree>::Register(L);
//    return 1;
//}

static const luaL_reg luce_lib [] = {
    { "JUCEApplication", l_JUCEApplication },
    //{ "LComponent", l_Component },
    { "Colour", l_Colour },
    { "AffineTransform", l_AffineTransform },
    { "Path", l_Path },
    { "Graphics", l_Graphics },
    { "DocumentWindow", l_DocumentWindow },
    { "MainComponent", l_MainComponent },
    { "Component", l_JComponent },
    { "TextButton", l_TextButton },
    { "TextEditor", l_TextEditor },
    { "Label", l_Label },
    { "TreeView", l_TreeView },
    { "TreeViewItem", l_TreeViewItem },
    { "ModifierKeys", l_ModifierKeys},
    { "MouseEvent", l_MouseEvent },
    { "SourceDetails", l_SourceDetails },
    { "StretchableLayoutManager", l_StretchableLayoutManager },
    { "StretchableLayoutResizerBar", l_StretchableLayoutResizerBar },
    { "Font", l_Font },
    { "ListBox", l_ListBox},
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

    lua_newtable(L);
    int i = lua_gettop(L);
    for (int f = 0; luce_lib[f].name ; ++f ) {
        DBG(String("adding ") +luce_lib[f].name );
        lua_pushstring(L,luce_lib[f].name);
        lua_pushcfunction(L, luce_lib[f].func);
        lua_settable(L, i);
    }
    
    l_NotificationType(L);
    l_JustificationType(L);
    l_Colours(L);

    return 1;
}

#ifdef __cplusplus
}
#endif
