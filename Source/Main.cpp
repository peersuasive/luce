#include <cstring>

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
int lua_shutdown(lua_State*);
int lua_main(void);
int lua_main_manual(lua_State*, const int&);
int start(lua_State*);
int start_manual(lua_State*);
int reload(lua_State*);

#if JUCE_ANDROID
    #include <jni.h>
    JNIEnv *env;
    jobject activity;
    extern void Java_org_peersuasive_luce_luce_resumeApp(JNIEnv *env_, jobject activity_);

    LUCE_API int luaopen_luce_core_and(lua_State *L, JNIEnv *env_, jobject activity_);
    LUCE_API int luaopen_core_and(lua_State *L, JNIEnv *env_, jobject activity_);
#endif

int lua_main(void) {
    int res = 0;
    #if JUCE_MAC || JUCE_IOS
    res = juce::JUCEApplicationBase::main(0, 0);
    #elif JUCE_ANDROID
    Java_org_peersuasive_luce_luce_resumeApp(env, activity);
    #else
    res = juce::JUCEApplicationBase::main();
    #endif
    
    return res;
}

int lua_main_manual(lua_State *L, const int& cb_ref) {
    juce::JUCEApplicationBase::createInstance = &juce_CreateApplication;

    MainThread myThread("Main luce Thread", L, cb_ref);

    #if JUCE_IOS
    // not ready yet
    // luce_iOSMain(0, 0, &myThread);
    #else
    if (LUCEApplicationBase::run(myThread)) {
        lua_pushstring(L,"LUCE ERROR: Couldn't initialise app");
        lua_error(L);
        return 0;
    }
    #endif
    return 0;
}

int lua_shutdown(lua_State *L) {
    DBG("START CLEANING");
    lua_gc(L, LUA_GCCOLLECT, 0 );
    // clean instanciated but never used or orphan objects
    if (LUA::objects.size()) {
        for (auto& it : LUA::objects) {
            if ( it.second ) {
                if ( dynamic_cast<LComponent*>( (LSelfKill*)it.second ) )
                    #if DEBUG
                    std::cout << "WARNING: object '" << it.second->myName() << "'"
                        << " instanciated but not cleaned (probably never used) -- cleaning" << std::endl;
                    #endif
                DBG(String("Cleaning object: ") + it.second->myName());
                it.second->selfKill();
            }
        }
    }
    lua_gc(L, LUA_GCCOLLECT, 0 );

    // for Android, quitApp calls appWillTerminateByForce,
    // which already calls these
    // after having called shutdown()
    #if ! JUCE_ANDROID
    DeletedAtShutdown::deleteAll();
    if ( MessageManager::getInstanceWithoutCreating() != nullptr )
        MessageManager::deleteInstance();
    shutdownJuce_GUI();
    #endif

    #if DEBUG
    if ( MessageManager::getInstanceWithoutCreating() != nullptr ) {
        DBG("WARNING: an instance of MessageManager still exists !");
    }
    #endif
    DBG("ENDED CLEANING");
    return 0;
}

//==============================================================================

/**
 * expect a MainWindow class
 * and some optional parameters
 *
 * dans l'idéal, on récupère des chunks, ou plutôt des objets, qui sont
 * des componsants
 * si le composant existe, on le vire et on le remplace par le code
 * s'il n'existe pas ?...
 *
 **/
int reload(lua_State *L) {
    LUA::liveCoding(true);
    // check what we have
    if(!lua_isfunction(L,2)) {
        lua_pushnil(L);
        lua_pushfstring(L,"luceLiveReload: expected function, got '%s'", lua_typename(L, lua_type(L,1)));
        return 2;
    }
    // TODO: get and remove params
    // call function
    // push result to luceLiveReload
    //
    // meanwhile:
    //lua_pop(L, lua_gettop(L)-2);

    lua_pushstring(L, "LUCE_LIVE_CODING");
    lua_pushnumber(L, 1);
    // if LUA == 501...
    // else lua_pushglobalstable...
    lua_settable(L, LUA_GLOBALSINDEX);

    int nb_args = 0;
    if ( lua_pcall(L, nb_args, 1, 0) != 0 ) {
        lua_pushnil(L);
        lua_pushvalue(L, -2);
        return 2;
    }
    if(lua_isnoneornil(L,-1)) {
        lua_pushnil(L);
        lua_pushfstring(L, "Wrong or malformed MainWindow: expected Component, got nil");
        return 2;
    }
    int res = mainClass->luceLiveReload(L);
    return res;
}

int start( lua_State *L ) {
    LUA::Set(L);
    LJUCEApplication *mc = Luna<LJUCEApplication>::check(L, 2);
    mainClass = mc;

    int rc = lua_main();
    
    #if ! JUCE_ANDROID
    lua_shutdown(L);
    #endif

    DBG("END of START\n");
    lua_pushnumber(L, rc);
    return 1;
}
int start_manual( lua_State *L ) {
    LUA::Set(L);
    luaL_checktype(L, -1, LUA_TFUNCTION); // cb
    luaL_checktype(L, -2, LUA_TTABLE); // LJUCEApp

    int cb_ref = luaL_ref(L, LUA_REGISTRYINDEX);

    LJUCEApplication *mc = Luna<LJUCEApplication>::check(L, 2); // luaL_ref pop'ed the cb function
    mainClass = mc;
    int rc = lua_main_manual(L, cb_ref);
    
    lua_shutdown(L);
    
    DBG("END of START (manual)\n");
    lua_pushnumber(L, rc);
    return 1;
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
l_c(StandardCursorType);

l_class(JUCEApplication);
l_class(LookAndFeel);
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
l_class(ColourGradient);
l_class(FillType);
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
l_class(HighResolutionTimer);
l_class(Options);
l_class(PopupMenu);
l_class(StretchableLayoutManager);
l_class(StretchableLayoutResizerBar);
l_class(Font);
l_class(ListBox);
l_class(ComboBox);
l_class(Slider);
l_class(ScrollBar);
// core
l_class(Time);
l_class(BigInteger);
l_class(Random);

static const luaL_Reg luce_lib [] = {
    d(JUCEApplication),
    d(LookAndFeel),
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
    d(ColourGradient),
    d(FillType),
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
    d(HighResolutionTimer),
    d(Options),
    d(PopupMenu),
    d(StretchableLayoutManager),
    d(StretchableLayoutResizerBar),
    d(Font),
    d(ListBox),
    d(ComboBox),
    d(Slider),
    d(ScrollBar),
    // core
    d(Time),
    d(BigInteger),
    d(Random),

    { "start", start },
    { "start_manual", start_manual },
    { "reload", reload },
    { "shutdown", lua_shutdown },
    {NULL, NULL}
};

void register_enums(lua_State *L) {
    dc(NotificationType);
    dc(JustificationType);
    dc(Colours);
    dc(FocusChangeType);
    dc(CurrentOS);
    dc(StandardCursorType);
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
    LUA::Set(L);
    DBG("LUCE " JUCE_STRINGIFY(LUCE_VERSION_MAJOR) "." JUCE_STRINGIFY(LUCE_VERSION_MINOR))
    juce::JUCEApplicationBase::createInstance = &juce_CreateApplication;

    // X11 requires this at this point, but OS X can't stand it this soon
    #if ! JUCE_MAC && ! JUCE_IOS && ! JUCE_ANDROID
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
