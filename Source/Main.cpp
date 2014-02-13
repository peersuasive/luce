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

int lua_main_manual(lua_State *L, const int& cb_ref) {
    juce::JUCEApplicationBase::createInstance = &juce_CreateApplication;
    
    const ScopedPointer<JUCEApplicationBase> app (juce::JUCEApplicationBase::createInstance());
    app->initialiseApp();

    MainThread myThread("Main luce Thread", L, cb_ref);
    myThread.run();

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
#define l_c(c) \
void l_C_##c(lua_State *L) \
{ \
    lua_newtable(L); \
    int n = lua_gettop(L); \
    for(auto& it : LConstants::l##c) { \
        lua_pushnumber(L, it.second); \
        lua_setfield(L, -2, it.first); \
    } \
    lua_setfield(L, -2, #c); \
}
#define l_cs(c) \
void l_C_##c(lua_State *L) \
{ \
    lua_newtable(L); \
    int n = lua_gettop(L); \
    for(auto& it : LConstants::l##c) { \
        lua_pushstring(L, it); \
        lua_setfield(L, -2, it); \
    } \
    lua_setfield(L, -2, #c); \
}
#define dc(c,L) l_C_##c(L)

#define l_class(c) \
int l_##c (lua_State *L) \
{\
    Luna<L##c>::Register(L); \
    return 1; \
}
#define d(c) {#c, l_##c}

l_c(NotificationType);
l_c(JustificationType);
l_c(FocusChangeType);
l_cs(Colours);

l_class(JUCEApplication);
l_class(Colour);
l_class(AffineTransform);
l_class(Path);
l_class(PathStrokeType);
l_class(Image);
l_class(Graphics);
l_class(GlyphArrangement);
l_class(PositionedGlyph);
l_class(DocumentWindow);
l_class(MainComponent);
l_class(JComponent);
l_class(TextButton);
l_class(ToggleButton);
l_class(HyperlinkButton);
l_class(Label);
l_class(TextEditor);
l_class(TreeView);
l_class(TreeViewItem);
l_class(ModifierKeys);
l_class(KeyPress);
l_class(MouseEvent);
l_class(SourceDetails);
l_class(Timer);
l_class(StretchableLayoutManager);
l_class(StretchableLayoutResizerBar);
l_class(Font);
l_class(ListBox);
l_class(ComboBox);
// core
l_class(Time);
l_class(BigInteger);
l_class(Random);

static const luaL_Reg luce_lib [] = {
    d(JUCEApplication),
    d(Colour),
    d(AffineTransform),
    d(Path),
    d(PathStrokeType),
    d(Image),
    d(Graphics),
    d(GlyphArrangement),
    d(PositionedGlyph),
    d(DocumentWindow),
    d(MainComponent),
    { "Component", l_JComponent },
    d(TextButton),
    d(ToggleButton),
    d(HyperlinkButton),
    d(TextEditor),
    d(Label),
    d(TreeView),
    d(TreeViewItem),
    d(ModifierKeys),
    d(KeyPress),
    d(MouseEvent),
    d(SourceDetails),
    d(Timer),
    d(StretchableLayoutManager),
    d(StretchableLayoutResizerBar),
    d(Font),
    d(ListBox),
    d(ComboBox),
    // core
    d(Time),
    d(BigInteger),
    d(Random),

    { "start", start },
    { "start_manual", start_manual },
    { "shutdown", lua_shutdown },
    {NULL, NULL}
};

void register_enums(lua_State *L) {
    dc(NotificationType, L);
    dc(JustificationType, L);
    dc(Colours, L);
    dc(FocusChangeType, L);
}

#ifdef DEBUG
int luaopen_luce_core_d (lua_State *L) {
#else
int luaopen_luce_core (lua_State *L) {
#endif
    DBG("LUCE " JUCE_STRINGIFY(LUCE_VERSION_MAJOR) "." JUCE_STRINGIFY(LUCE_VERSION_MINOR))
    initialiseJuce_GUI();
    juce::JUCEApplicationBase::createInstance = &juce_CreateApplication;

    lua_newtable(L);
    int i = lua_gettop(L);
    for (int f = 0; luce_lib[f].name ; ++f ) {
        DBG(String("adding ") +luce_lib[f].name );
        lua_pushstring(L,luce_lib[f].name);
        lua_pushcfunction(L, luce_lib[f].func);
        lua_settable(L, i);
    }
    register_enums(L);
    return 1;
}

static const luaL_Reg lucecore_lib [] = {
#ifdef DEBUG
    {"core", luaopen_luce_core_d},
#else
    {"core", luaopen_luce_core},
#endif
    {NULL, NULL}
};

int luaopen_core(lua_State *L) {
    DBG("LUCE " JUCE_STRINGIFY(LUCE_VERSION_MAJOR) "." JUCE_STRINGIFY(LUCE_VERSION_MINOR))
    initialiseJuce_GUI();
    juce::JUCEApplicationBase::createInstance = &juce_CreateApplication;
 
#if LUA_VERSION_NUM > 501
    luaL_requiref(L, "luce.core", luaopen_luce_core, 1);
#else
    luaL_register(L, "luce.core", luce_lib);
    register_enums(L);
#endif

    return 0;
}

#ifdef __cplusplus
}
#endif
