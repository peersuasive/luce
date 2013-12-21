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

    static const char className[];
    static const Luna<LDocumentWindow>::Inheritence inherits[];
    static const Luna<LDocumentWindow>::InheritenceF inheritsF[];
    static const Luna<LDocumentWindow>::PropertyType properties[];
    static const Luna<LDocumentWindow>::FunctionType methods[];

private:
    //==============================================================================
    ScopedPointer<ApplicationCommandManager> commandManager;
    virtual void handleAsyncUpdate() override;

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (LDocumentWindow)
};

#endif // __LJUCE_DOCUMENT_WINDOW_H
