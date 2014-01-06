/************************************************************

 LTreeViewItem.h

    @author Christophe Berbizier (cberbizier@peersuasive.com)
    @license GPLv3
    @copyright 


(c) 2013, Peersuasive Technologies

*************************************************************/

#ifndef __LUCE_LTREEVIEWITEM_H
#define __LUCE_LTREEVIEWITEM_H

class LTreeViewItem
    : public LBase,
      public TreeViewItem
{
public:
    LTreeViewItem(lua_State*);
    ~LTreeViewItem();

    //==============================================================================
    int setOpen(lua_State*);
    int isOpen(lua_State*);
    int setSelected(lua_State*);
    int isSelected(lua_State*);

    //==============================================================================
    int addSubItem(lua_State*);
    int addSubItemSorted(lua_State*);
    int setLinesDrawnForSubItems(lua_State*);
    int clearSubItems(lua_State*);
    int sortSubItems(lua_State*);
    int restoreOpennessState(lua_State*);
    int setDrawsInLeftMargin(lua_State*);
    int removeSubItem(lua_State*);
    int repaintItem(lua_State*);
    int treeHasChanged(lua_State*);

    //==============================================================================
    int getItemHeight(lua_State*);
    int getNumSubItems(lua_State*);
    int canBeSelected(lua_State*);

    int getSubItem(lua_State*);
    int createItemComponent(lua_State*);
    int isLastOfSiblings(lua_State*);
    int getOwnerView(lua_State*);
    int getItemWidth(lua_State*);
    int getItemPosition(lua_State*);
    int getItemIdentifierString(lua_State*);
    int isInterestedInFileDrag(lua_State*);
    int getTooltip(lua_State*);
    int getOpennessState(lua_State*);
    int isInterestedInDragSource(lua_State*);
    int areAllParentsOpen(lua_State*);
    int getParentItem(lua_State*);
    int getIndexInParent(lua_State*);
    int getRowNumberInTree(lua_State*);

    //==============================================================================
    int itemOpennessChanged(lua_State*);
    int paintOpenCloseButton(lua_State*);
    int itemDropped(lua_State*);
    int paintItem(lua_State*);
    int filesDropped(lua_State*);
    int paintHorizontalConnectingLine(lua_State*);
    int paintVerticalConnectingLine(lua_State*);
    int itemClicked(lua_State*);
    int itemSelectionChanged(lua_State*);
    int itemDoubleClicked(lua_State*);

    // extra callbacks
    virtual var getDragSourceDescription() override;
    int getDragSourceDescription(lua_State*);

    virtual String getUniqueName() const override;
    int getUniqueName(lua_State*);

    virtual bool mightContainSubItems() override;
    int mightContainSubItems(lua_State*);

    // basic comparator
    const int compareElements( TreeViewItem *first, TreeViewItem *second );
    int compareElements(lua_State*); 

    //==============================================================================
    static const char className[];
    static const Luna<LTreeViewItem>::Inheritence inherits[];
    static const Luna<LTreeViewItem>::InheritenceF inheritsF[];
    static const Luna<LTreeViewItem>::PropertyType properties[];
    static const Luna<LTreeViewItem>::FunctionType methods[];

    static const Luna<LTreeViewItem>::Enum enums[];
private:
    struct LComparator : private LBase {
        LComparator(lua_State* L) : LBase(L) { reg("compareElements"); }
        const int compareElements( TreeViewItem *first, TreeViewItem *second ) {
            if ( callback("compareElements", 1, { var(first), var(second) } ) ) { // not yet implemented...
                return LUA::getBoolean();
            } else {
                String a = first->getUniqueName();
                String b = second->getUniqueName();
                return a.compareLexicographically( b );
            }
        }
        int compareElements(lua_State*) {
            set("compareElements");
        }
    };

    LComparator comparator;

    //==============================================================================
    // callbacks
    virtual void itemOpennessChanged( bool isNowOpen ) override;
    virtual void paintOpenCloseButton( Graphics& graphics_, const Rectangle<float>& area, 
            Colour backgroundColour, bool isMouseOver ) override;
    virtual void itemDropped( const DragAndDropTarget::SourceDetails& dragSourceDetails, int insertIndex ) override;
    virtual void paintItem( Graphics& g, int width, int height ) override;
    virtual void filesDropped( const StringArray& files, int insertIndex ) override;
    virtual void paintHorizontalConnectingLine( Graphics& graphics_, const Line<float>& line ) override;
    virtual void paintVerticalConnectingLine( Graphics& graphics_, const Line<float>& line ) override;
    virtual void itemClicked( const MouseEvent& e ) override;
    virtual void itemSelectionChanged( bool isNowSelected ) override;
    virtual void itemDoubleClicked( const MouseEvent& e ) override;

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (LTreeViewItem)
};

#endif // __LUCE_LTREEVIEWITEM_H
