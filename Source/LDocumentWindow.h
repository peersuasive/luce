#ifndef __LJUCE_DOCUMENT_WINDOW_H
#define __LJUCE_DOCUMENT_WINDOW_H

class LDocumentWindow : public LComponent,
                        public DocumentWindow,
                        private AsyncUpdater
{
public:
    LDocumentWindow(lua_State*);
    ~LDocumentWindow();

    static int s_Displays(lua_State*);

    int closeButtonPressed(lua_State*);
    void closeButtonPressed();
    
    int setContentOwned(lua_State*);
    int addChildComponent(lua_State*);
    int addAndMakeVisible(lua_State*);
    int setVisible(lua_State *L);

    //==============================================================================
    int setConstrainer(lua_State*);
    int getConstrainer(lua_State*);
    int setFullScreen(lua_State*);
    int isFullScreen(lua_State*);
    int setResizable(lua_State*);
    int isResizable(lua_State*);
    int setBackgroundColour(lua_State*);
    int getBackgroundColour(lua_State*);
    int setMinimised(lua_State*);
    int isMinimised(lua_State*);

    //==============================================================================
    int getContentComponent(lua_State*);
    int getWindowStateAsString(lua_State*);
    int getContentComponentBorder(lua_State*);
    int getDesktopWindowStyleFlags(lua_State*);
    int restoreWindowStateFromString(lua_State*);
    int getBorderThickness(lua_State*);
    int isKioskMode(lua_State*);
    int setKioskMode(lua_State*);

    //==============================================================================
    int setContentNonOwned(lua_State*);
    int setBoundsConstrained(lua_State*);
    int activeWindowStatusChanged(lua_State*);
    int setResizeLimits(lua_State*);
    int clearContentComponent(lua_State*);
    int setContentComponentSize(lua_State*);


    //==============================================================================
    static ApplicationCommandManager& getApplicationCommandManager();
 
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
    static const Luna<LDocumentWindow>::Inheritence inherits[];
    static const Luna<LDocumentWindow>::InheritenceF inheritsF[];
    static const Luna<LDocumentWindow>::PropertyType properties[];
    static const Luna<LDocumentWindow>::FunctionType methods[];
    static const Luna<LDocumentWindow>::StaticType statics[];

    static const Luna<LDocumentWindow>::Enum enums[];
private:
    //==============================================================================

    virtual void handleAsyncUpdate() override;

    virtual bool keyPressed(const KeyPress&) override;
    virtual bool keyStateChanged(bool) override;

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (LDocumentWindow)
};

#endif // __LJUCE_DOCUMENT_WINDOW_H
