#include <cstring>

// TODO: create one of this for each specific environment, and more particularly for for android

#define LUCE_API __attribute__ ((visibility ("default")))

static luce::LJUCEApplication *mainClass = nullptr;
LUCE_API juce::JUCEApplicationBase* juce_CreateApplication() {
    jassert( mainClass != nullptr );
    return mainClass;
}

namespace luce {

#ifdef __cplusplus
extern "C" {
#endif

#if JUCE_ANDROID
    #include <jni.h>
    JNIEnv *env;
    jobject activity;
    extern void Java_org_peersuasive_luce_luce_resumeApp(JNIEnv *env_, jobject activity_);

    LUCE_API int luaopen_luce_core_and(lua_State *L, JNIEnv *env_, jobject activity_);
    LUCE_API int luaopen_core_and(lua_State *L, JNIEnv *env_, jobject activity_);
#endif

int lua_main(void) {
    //juce::JUCEApplicationBase::createInstance = &juce_CreateApplication;
    int res;
    #if defined JUCE_MAC || defined JUCE_IOS
    // will call initialiseNSApplication
    res = juce::JUCEApplicationBase::main(0, 0);
    #elif JUCE_ANDROID
    Java_org_peersuasive_luce_luce_resumeApp(env, activity);
    #else
    res = juce::JUCEApplicationBase::main();
    #endif
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
    
    #ifdef LUCE_MAC
    // init osx here
    //LUCEApplicationBase::altmain();
    #endif

    initialiseJuce_GUI();
    const ScopedPointer<JUCEApplicationBase> app (juce::JUCEApplicationBase::createInstance());

    if (!app->initialiseApp()) {
        lua_pushstring(L,"LUCE ERROR: Couldn't initialise app");
        lua_error(L);
        return 0;
    }

    MainThread myThread("Main luce Thread", L, cb_ref);
    myThread.run();

    //MessageManager::getInstance()->runDispatchLoop();
    return 0;
}

int lua_shutdown(lua_State *L) {
    // FIXME: crashed on android when in Release mode
    
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
    //juce::JUCEApplicationBase::createInstance = &juce_CreateApplication;
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

    //juce::JUCEApplicationBase::createInstance = &juce_CreateApplication;
    
    LJUCEApplication *mc = Luna<LJUCEApplication>::check(L, 2); // luaL_ref pop'ed the cb function
    mainClass = mc;
    int rc = lua_main_manual(L, cb_ref);
    // if ( rc ) luaL_error...
    DBG("END of START (manual)\n");
    return 0;
}

//==============================================================================
/*
 * for constants with value
 */
#define l_c(c) \
void l_C_##c(lua_State *L) \
{ \
    lua_newtable(L); \
    for(auto& it : LConstants::l##c) { \
        lua_pushnumber(L, it.second); \
        lua_setfield(L, -2, it.first); \
    } \
    lua_setfield(L, -2, #c); \
}
/*
 * for string constants
 */
#define l_cs(c) \
void l_C_##c(lua_State *L) \
{ \
    lua_newtable(L); \
    for(auto& it : LConstants::l##c) { \
        lua_pushstring(L, it); \
        lua_setfield(L, -2, it); \
    } \
    lua_setfield(L, -2, #c); \
}
#define dc(c) l_C_##c(L)

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
l_c(CurrentOS);

l_class(JUCEApplication);
l_class(Colour);
l_class(AffineTransform);
l_class(Path);
l_class(PathStrokeType);
l_class(Image);
l_class(Graphics);
l_class(GlyphArrangement);
l_class(PositionedGlyph);
l_class(Attribute);
l_class(AttributedString);
l_class(Glyph);
l_class(Run);
l_class(Line);
l_class(TextLayout);
l_class(DocumentWindow);
l_class(MainComponent);
l_class(JComponent);
l_class(Viewport);
l_class(OpenGLComponent);
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
l_class(Options);
l_class(PopupMenu);
l_class(StretchableLayoutManager);
l_class(StretchableLayoutResizerBar);
l_class(Font);
l_class(ListBox);
l_class(ComboBox);
l_class(Slider);
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
    d(Attribute),
    d(AttributedString),
    d(Glyph),
    d(Run),
    d(Line),
    d(TextLayout),
    d(DocumentWindow),
    d(MainComponent),
    { "Component", l_JComponent },
    d(Viewport),
    d(OpenGLComponent),
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
    d(Options),
    d(PopupMenu),
    d(StretchableLayoutManager),
    d(StretchableLayoutResizerBar),
    d(Font),
    d(ListBox),
    d(ComboBox),
    d(Slider),
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
    dc(NotificationType);
    dc(JustificationType);
    dc(Colours);
    dc(FocusChangeType);
    dc(CurrentOS);
}

#ifdef DEBUG
LUCE_API int luaopen_luce_core_d (lua_State *L) {
#else
LUCE_API int luaopen_luce_core (lua_State *L) {
#endif
    LUA::Set(L);
    DBG("LUCE " JUCE_STRINGIFY(LUCE_VERSION_MAJOR) "." JUCE_STRINGIFY(LUCE_VERSION_MINOR))
    juce::JUCEApplicationBase::createInstance = &juce_CreateApplication;
    initialiseJuce_GUI();

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

LUCE_API int luaopen_core(lua_State *L) {
    DBG("LUCE " JUCE_STRINGIFY(LUCE_VERSION_MAJOR) "." JUCE_STRINGIFY(LUCE_VERSION_MINOR))
    juce::JUCEApplicationBase::createInstance = &juce_CreateApplication;

    // X11 requires this at this point, but OS X can't stand it this soon
    #if !defined JUCE_MAC && ! defined JUCE_IOS && ! defined JUCE_ANDROID
    initialiseJuce_GUI();
    #endif

    #if LUA_VERSION_NUM > 501
    #ifdef DEBUG
    luaL_requiref(L, "luce.core", luaopen_luce_core_d, 1);
    #else
    luaL_requiref(L, "luce.core", luaopen_luce_core, 1);
    #endif
    #else
    luaL_register(L, "luce.core", luce_lib);
    register_enums(L);
    #endif

    return 0;
}

#if JUCE_ANDROID
    int luaopen_luce_core_and(lua_State *L, JNIEnv *env_, jobject activity_) {
        env = env_; activity = activity_;
        #ifdef DEBUG
        return luaopen_luce_core_d(L);
        #else
        return luaopen_luce_core(L);
        #endif
    }
    int luaopen_core_and(lua_State *L, JNIEnv *env_, jobject activity_) {
        env = env_; activity = activity_;
        return luaopen_core(L);
    }
#endif

#ifdef __cplusplus
}
#endif

} // end of namespace
