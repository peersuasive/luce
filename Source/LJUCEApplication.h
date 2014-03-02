#ifndef __LJUCE_APPLICATION_H
#define __LJUCE_APPLICATION_H


class LJUCEApplication : public LBase,
                         public JUCEApplication
{
public:
    //==============================================================================
    LJUCEApplication(lua_State *L);
    ~LJUCEApplication();

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
    virtual void initialised();
    int initialised(lua_State*);

    //==============================================================================
    int initialise (lua_State *L);
    virtual void initialise (const String& commandLine) override;

    int quit(lua_State *L);

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
    ScopedPointer<Component> mainWindow;

    //==============================================================================
    var call_cb_get_value();

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (LJUCEApplication)
};

#endif //__LJUCE_APPLICATION_H
