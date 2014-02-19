#ifndef __LJUCE_DOCUMENT_WINDOW_H
#define __LJUCE_DOCUMENT_WINDOW_H

class LDocumentWindow : public LComponent,
                        public DocumentWindow,
                        private AsyncUpdater
{
public:
    LDocumentWindow(lua_State*);
    ~LDocumentWindow();
    int closeButtonPressed(lua_State*);
    void closeButtonPressed();
    
    int setContentOwned(lua_State*);
    int addChildComponent(lua_State*);
    int addAndMakeVisible(lua_State*);
    int setVisible(lua_State *L);


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

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (LDocumentWindow)
};

#endif // __LJUCE_DOCUMENT_WINDOW_H
