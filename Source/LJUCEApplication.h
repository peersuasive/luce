#ifndef __LJUCE_APPLICATION_H
#define __LJUCE_APPLICATION_H

class LJUCEApplication : public LComponent,
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

    //==============================================================================
    int initialise (lua_State *L);
    void initialise (const String& commandLine);

    int quit(lua_State *L);

    int shutdown(lua_State *L);
    void shutdown();

    //==============================================================================
    int systemRequestedQuit(lua_State *L);
    void systemRequestedQuit();

    int anotherInstanceStarted (lua_State *L);
    void anotherInstanceStarted (const String& commandLine);

    //==============================================================================
    static const char className[];
    static const Luna<LJUCEApplication>::Inheritence inherits[];
    static const Luna<LJUCEApplication>::InheritenceF inheritsF[];
    static const Luna<LJUCEApplication>::PropertyType properties[];
    static const Luna<LJUCEApplication>::FunctionType methods[];

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
