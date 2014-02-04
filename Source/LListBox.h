/************************************************************

 LListBox.h

    @author Christophe Berbizier (cberbizier@peersuasive.com)
    @license GPLv3
    @copyright 


(c) 2013, Peersuasive Technologies

*************************************************************/

#ifndef __LUCE_LLISTBOX_H
#define __LUCE_LLISTBOX_H

class LListBox
    : public LComponent,
      public ListBox,
      public ListBoxModel,
      public DragAndDropTarget
{
public:
    LListBox(lua_State*);
    ~LListBox();

    //==============================================================================
    int setRowHeight(lua_State*);
    int getRowHeight(lua_State*);
    int setOutlineThickness(lua_State*);
    int getOutlineThickness(lua_State*);
    int setSelectedRows(lua_State*);
    int getSelectedRows(lua_State*);
    int setVerticalPosition(lua_State*);
    int getVerticalPosition(lua_State*);
    // shouldn't need it
    //int setModel(lua_State*);
    //int getModel(lua_State*);

    //==============================================================================
    int setMultipleSelectionEnabled(lua_State*);
    int selectRow(lua_State*);
    int setHeaderComponent(lua_State*);
    int selectRowsBasedOnModifierKeys(lua_State*);
    int selectRangeOfRows(lua_State*);
    int setMinimumContentWidth(lua_State*);
    int repaintRow(lua_State*);
    int setMouseMoveSelectsRows(lua_State*);
    int scrollToEnsureRowIsOnscreen(lua_State*);
    int deselectAllRows(lua_State*);
    int flipRowSelection(lua_State*);
    int mouseUp(lua_State*);
    int deselectRow(lua_State*);
    int updateContent(lua_State*);

    //==============================================================================
    int isRowSelected(lua_State*);
    int getRowNumberOfComponent(lua_State*);
    int getVerticalScrollBar(lua_State*);
    int getComponentForRowNumber(lua_State*);
    int getVisibleRowWidth(lua_State*);
    int getVisibleContentWidth(lua_State*);
    int getLastRowSelected(lua_State*);
    int getViewport(lua_State*);
    int getHorizontalScrollBar(lua_State*);
    int getNumRowsOnScreen(lua_State*);
    int getRowPosition(lua_State*);
    int createSnapshotOfSelectedRows(lua_State*);
    int getNumSelectedRows(lua_State*);
    int getSelectedRow(lua_State*);
    int getInsertionIndexForPosition(lua_State*);
    int getRowContainingPosition(lua_State*);

    //==============================================================================
    // ListBoxModel
    int getMouseCursorForRow(lua_State*);
    int getTooltipForRow(lua_State*);
    int refreshComponentForRow(lua_State*);
    int getDragSourceDescription(lua_State*);
    int getNumRows(lua_State*);

    //==============================================================================
    int listBoxItemClicked(lua_State*);
    int listWasScrolled(lua_State*);
    int selectedRowsChanged(lua_State*);
    int deleteKeyPressed(lua_State*);
    int returnKeyPressed(lua_State*);
    int backgroundClicked(lua_State*);
    int paintListBoxItem(lua_State*);
    int listBoxItemDoubleClicked(lua_State*);
    
    //==============================================================================

    //==============================================================================
    // drag and drop
    int isInterestedInDragSource(lua_State*);
    int itemDropped(lua_State*);
    int itemDragEnter(lua_State*);
    int itemDragExit(lua_State*);

    int startDragAndDrop(lua_State*);
    //==============================================================================

    static const char className[];
    static const Luna<LListBox>::Inheritence inherits[];
    static const Luna<LListBox>::InheritenceF inheritsF[];
    static const Luna<LListBox>::PropertyType properties[];
    static const Luna<LListBox>::FunctionType methods[];
    static const Luna<LListBox>::StaticType statics[];
    static const Luna<LListBox>::Enum enums[];

private:
    //==============================================================================
    // callbacks (ListBoxModel)
    virtual int getNumRows() override;
    virtual void paintListBoxItem( int rowNumber, Graphics& g, int width, int height, bool rowIsSelected ) override;

    virtual void listBoxItemClicked( int row, const MouseEvent& e ) override;
    virtual void listWasScrolled() override;
    virtual void selectedRowsChanged( int lastRowSelected ) override;
    virtual void deleteKeyPressed( int lastRowSelected ) override;
    virtual void returnKeyPressed( int lastRowSelected ) override;
    virtual void backgroundClicked() override;
    virtual void listBoxItemDoubleClicked( int row, const MouseEvent& e ) override;
    virtual Component* refreshComponentForRow (int rowNumber, bool isRowSelected,
                                               Component* existingComponentToUpdate) override;
    virtual var getDragSourceDescription (const SparseSet<int>& currentlySelectedRows) override;
    virtual String getTooltipForRow (int row) override;
    virtual MouseCursor getMouseCursorForRow (int row) override;

    // drag and drop
    virtual bool isInterestedInDragSource (const DragAndDropTarget::SourceDetails& dragSourceDetails) override;
    virtual void itemDropped (const DragAndDropTarget::SourceDetails&) override;
    virtual void itemDragEnter(const DragAndDropTarget::SourceDetails& dragSourceDetails) override;
    virtual void itemDragExit(const DragAndDropTarget::SourceDetails& dragSourceDetails) override;

    //==============================================================================
    virtual void paint(Graphics&) override;

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (LListBox)
};

#endif // __LUCE_LLISTBOX_H
