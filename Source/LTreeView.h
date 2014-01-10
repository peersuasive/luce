/************************************************************

 LTreeView.h

    @author Christophe Berbizier (cberbizier@peersuasive.com)
    @license GPLv3
    @copyright 


(c) 2013, Peersuasive Technologies

*************************************************************/

// TODO: add dnd callbacks

#ifndef __LUCE_LTREEVIEW_H
#define __LUCE_LTREEVIEW_H

class LTreeView
    : public LComponent,
      public TreeView
{
public:
    LTreeView(lua_State*);
    ~LTreeView();

    //==============================================================================
    int setIndentSize(lua_State*);
    int getIndentSize(lua_State*);
    int setMultiSelectEnabled(lua_State*);
    int isMultiSelectEnabled(lua_State*);
    int setRootItem(lua_State*);
    int getRootItem(lua_State*);
    int setRootItemVisible(lua_State*);
    int isRootItemVisible(lua_State*);

    //==============================================================================
    int clearSelectedItems(lua_State*);
    int moveSelectedRow(lua_State*);
    int setDefaultOpenness(lua_State*);
    int restoreOpennessState(lua_State*);
    int setOpenCloseButtonsVisible(lua_State*);
    int deleteRootItem(lua_State*);
    int scrollToKeepItemVisible(lua_State*);

    //==============================================================================
    int getNumRowsInTree(lua_State*);
    int getNumSelectedItems(lua_State*);
    int getItemOnRow(lua_State*);
    int getItemAt(lua_State*);
    int areItemsOpenByDefault(lua_State*);
    int getViewport(lua_State*);
    int findItemFromIdentifierString(lua_State*);
    int getSelectedItem(lua_State*);
    int areOpenCloseButtonsVisible(lua_State*);
    int getOpennessState(lua_State*);

    //==============================================================================
    // already set by LComponent
    // int paint(lua_State*);
    // int resized(lua_State*);
    // int keyPressed(lua_State*);
    // int colourChanged(lua_State*);
    // int enablementChanged(lua_State*);

    // TODO: dnd listeners
    //int isInterestedInFileDrag(lua_State*);
    //int fileDragEnter(lua_State*);
    //int fileDragMove(lua_State*);
    //int fileDragExit(lua_State*);
    //int filesDropped(lua_State*);

    //int isInterestedInDragSource(lua_State*);
    //int itemDragEnter(lua_State*);
    //int itemDragMove(lua_State*);
    //int itemDragExit(lua_State*);
    //int itemDropped(lua_State*);

    //==============================================================================
    static const char className[];
    static const Luna<LTreeView>::Inheritence inherits[];
    static const Luna<LTreeView>::InheritenceF inheritsF[];
    static const Luna<LTreeView>::PropertyType properties[];
    static const Luna<LTreeView>::FunctionType methods[];

    static const Luna<LTreeView>::Enum enums[];
private:
    //==============================================================================
    // callbacks
    // already set by LComponent
    // void paint (Graphics&) override;
    // void resized() override;
    // bool keyPressed (const KeyPress&) override;
    // void colourChanged() override;
    // void enablementChanged() override;

    //bool isInterestedInFileDrag (const StringArray& files) override;
    //void fileDragEnter (const StringArray& files, int x, int y) override;
    //void fileDragMove (const StringArray& files, int x, int y) override;
    //void fileDragExit (const StringArray& files) override;
    //void filesDropped (const StringArray& files, int x, int y) override;

    //bool isInterestedInDragSource (const SourceDetails&) override;
    //void itemDragEnter (const SourceDetails&) override;
    //void itemDragMove (const SourceDetails&) override;
    //void itemDragExit (const SourceDetails&) override;
    //void itemDropped (const SourceDetails&) override;

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (LTreeView)
};

#endif // __LUCE_LTREEVIEW_H
