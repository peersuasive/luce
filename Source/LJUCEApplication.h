#ifndef __LJUCE_APPLICATION_H
#define __LJUCE_APPLICATION_H


class LJUCEApplication : public LBase,
                         public JUCEApplication,
                         private AsyncUpdater
{
public:
    //==============================================================================
    LJUCEApplication(lua_State *L);
    ~LJUCEApplication();

    //==============================================================================
    int getApplicationName(lua_State *L);
    const String getApplicationName();

    int getApplicationVersion(lua_State *L);
    const String getApplicationVersion();

    int moreThanOneInstanceAllowed(lua_State *L);
    bool moreThanOneInstanceAllowed();

    int setDoubleClickTimeout(lua_State*);

    //==============================================================================
    // luce specifics
    /*
     * initialised is usefull to start actions after the window has shown,
     * particularly on iOS or OSX, as events oriented architectures
     */
    static ApplicationCommandManager& getApplicationCommandManager();

    virtual void initialised(Component*);
    int initialised(lua_State*);
 
    static LJUCEApplication* getInstance() noexcept { return luceAppInstance; }
    void deleteWindow(Component*);

    static int s_userHomeDirectory(lua_State*);
    static int s_userDocumentsDirectory(lua_State*);
    static int s_userDesktopDirectory(lua_State*);
    static int s_userMusicDirectory(lua_State*);
    static int s_userMoviesDirectory(lua_State*);
    static int s_userPicturesDirectory(lua_State*);
    static int s_userApplicationDataDirectory(lua_State*);
    static int s_commonApplicationDataDirectory(lua_State*);
    static int s_commonDocumentsDirectory(lua_State*);
    static int s_tempDirectory(lua_State*);
    static int s_currentExecutableFile(lua_State*);
    static int s_currentApplicationFile(lua_State*);
    static int s_invokedExecutableFile(lua_State*);
    static int s_hostApplicationPath(lua_State*);
    static int s_globalApplicationsDirectory(lua_State*);

    //==============================================================================
    int initialise (lua_State *L);
    virtual void initialise (const String& commandLine) override;

    int quit(lua_State *L);

    int getApplicationReturnValue(lua_State*);
    int setApplicationReturnValue(lua_State*);

    int shutdown(lua_State *L);
    void shutdown();

    //==============================================================================
    int systemRequestedQuit(lua_State *L);
    void systemRequestedQuit();

    int anotherInstanceStarted (lua_State *L);
    void anotherInstanceStarted (const String& commandLine);

    //TODO
    int suspended(lua_State*);
    void suspended() override;
    int resumed(lua_State*);
    void resumed() override;
    int unhandledException(lua_State*);
    void unhandledException(const std::exception*, const String&, int) override;

    //== ApplicationCommandManager =================================================
    int clearCommands(lua_State*);
    int registerCommand(lua_State*);
    int registerAllCommandsForTarget(lua_State*);
    int removeCommand(lua_State*);
    int commandStatusChanged(lua_State*);
    int getNumCommands(lua_State*);
    int getCommandForIndex(lua_State*);
    int getCommandForID(lua_State*);
    int getNameOfCommand(lua_State*);
    int getDescriptionOfCommand(lua_State*);
    int getCommandCategories(lua_State*);
    int getCommandsInCategory(lua_State*);
    int getKeyMappings(lua_State*);
    int invokeDirectly(lua_State*);
    int invoke(lua_State*);
    int getFirstCommandTarget(lua_State*);
    int setFirstCommandTarget(lua_State*);
    int getTargetForCommand(lua_State*);
    int findDefaultComponentTarget(lua_State*);
    int findTargetForComponent(lua_State*);

    //==============================================================================
    static const char className[];
    static const Luna<LJUCEApplication>::Inheritence inherits[];
    static const Luna<LJUCEApplication>::InheritenceF inheritsF[];
    static const Luna<LJUCEApplication>::PropertyType properties[];
    static const Luna<LJUCEApplication>::FunctionType methods[];
    static const Luna<LJUCEApplication>::StaticType statics[];

    static const Luna<LJUCEApplication>::Enum enums[];
private:
    //==============================================================================
    static LJUCEApplication* luceAppInstance;
    
    //==============================================================================
    virtual void handleAsyncUpdate() override;

    //==============================================================================
    Array<ScopedPointer<Component>> mainWindows;

    //==============================================================================
    void initialise(lua_State*, int callbackReturnStatus);

    //==============================================================================
    var call_cb_get_value();

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (LJUCEApplication)
};

#endif //__LJUCE_APPLICATION_H
