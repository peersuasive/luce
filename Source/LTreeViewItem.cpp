/************************************************************

 LTreeViewItem.cpp

    @author Christophe Berbizier (cberbizier@peersuasive.com)
    @license GPLv3
    @copyright 


(c) 2014, Peersuasive Technologies

*************************************************************/

#include "LTreeViewItem_inh.h"

#include <cstdlib>

////// static methods
const char LTreeViewItem::className[] = "LTreeViewItem";
const Luna<LTreeViewItem>::PropertyType LTreeViewItem::properties[] = {
    {"open", &LTreeViewItem::isOpen, &LTreeViewItem::setOpen},
    // read-only
    {"numSubItems", &LTreeViewItem::getNumSubItems, &LBase::readOnly},
    {"uniqueName", &LTreeViewItem::getUniqueName, &LBase::readOnly},
    {"selected", &LTreeViewItem::isSelected, &LTreeViewItem::setSelected},
    {"rowNumberInTree", &LTreeViewItem::getRowNumberInTree, &LBase::readOnly},
    {0,0}
};
const Luna<LTreeViewItem>::FunctionType LTreeViewItem::methods[] = {
    method( LTreeViewItem, getItemHeight ),
    method( LTreeViewItem, getNumSubItems ),
    method( LTreeViewItem, getUniqueName ),
    method( LTreeViewItem, canBeSelected ),
    method( LTreeViewItem, getDragSourceDescription ),
    method( LTreeViewItem, mightContainSubItems ),
    method( LTreeViewItem, getSubItem ),
    method( LTreeViewItem, createItemComponent ),
    method( LTreeViewItem, isLastOfSiblings ),
    method( LTreeViewItem, getOwnerView ),
    method( LTreeViewItem, isOpen ),
    method( LTreeViewItem, setOpen ),
    method( LTreeViewItem, getItemWidth ),
    method( LTreeViewItem, getItemPosition ),
    method( LTreeViewItem, getItemIdentifierString ),
    method( LTreeViewItem, isInterestedInFileDrag ),
    method( LTreeViewItem, getTooltip ),
    method( LTreeViewItem, getOpennessState ),
    method( LTreeViewItem, isInterestedInDragSource ),
    method( LTreeViewItem, areAllParentsOpen ),
    method( LTreeViewItem, getParentItem ),
    method( LTreeViewItem, getIndexInParent ),
    method( LTreeViewItem, getRowNumberInTree ),
    method( LTreeViewItem, isSelected ),
    method( LTreeViewItem, setSelected ),
    method( LTreeViewItem, addSubItem ),
    method( LTreeViewItem, addSubItemSorted ),
    method( LTreeViewItem, setLinesDrawnForSubItems ),
    method( LTreeViewItem, clearSubItems ),
    method( LTreeViewItem, sortSubItems ),
    method( LTreeViewItem, restoreOpennessState ),
    method( LTreeViewItem, setDrawsInLeftMargin ),
    method( LTreeViewItem, removeSubItem ),
    method( LTreeViewItem, repaintItem ),
    method( LTreeViewItem, treeHasChanged ),
    method( LTreeViewItem, itemOpennessChanged ),
    method( LTreeViewItem, paintItem ),
    method( LTreeViewItem, paintOpenCloseButton ),
    method( LTreeViewItem, paintHorizontalConnectingLine ),
    method( LTreeViewItem, paintVerticalConnectingLine ),
    method( LTreeViewItem, itemClicked ),
    method( LTreeViewItem, itemDoubleClicked ),
    method( LTreeViewItem, itemSelectionChanged ),
    method( LTreeViewItem, filesDropped ),
    method( LTreeViewItem, itemDropped ),

    method( LTreeViewItem, compareElements ),
    {0,0}
};

/////// ctor/dtor
LTreeViewItem::LTreeViewItem(lua_State *L)
    : LBase(L),
      TreeViewItem( /* TODO: add args */ ),
      comparator(L)
{
    myName("LTreeViewItem");
}

LTreeViewItem::~LTreeViewItem() {
    TreeViewItem::clearSubItems();
}

/////// callbacks
void LTreeViewItem::itemOpennessChanged( bool isNowOpen ) {
    if ( hasCallback("itemOpennessChanged") ) {
        callback("itemOpennessChanged", 0, { isNowOpen });
    }
}
int LTreeViewItem::itemOpennessChanged(lua_State*) {
    set("itemOpennessChanged");
    return 0;
}

void LTreeViewItem::paintOpenCloseButton( Graphics& graphics_, const Rectangle<float>& area, Colour backgroundColour, bool isMouseOver ) {
    if ( ! hasCallback("paintOpenCloseButton") )
        TreeViewItem::paintOpenCloseButton(graphics_, area, backgroundColour, isMouseOver);
    else
        callback("paintOpenCloseButton");
}
int LTreeViewItem::paintOpenCloseButton(lua_State*){
    set("paintOpenCloseButton");
    return 0;
}

void LTreeViewItem::itemDropped( const DragAndDropTarget::SourceDetails& dragSourceDetails, int insertIndex ) {
    callback("itemDropped");
}
int LTreeViewItem::itemDropped(lua_State*){
    set("itemDropped");
    return 0;
}

void LTreeViewItem::paintItem( Graphics& g, int width, int height ) {
    if (hasCallback("paintItem"))
        if ( callback("paintItem", 1) ) {
            String name = LUA::checkAndGetString(-1, String::empty);
            if (TreeViewItem::isSelected())
                g.fillAll( Colours::blue.withAlpha( 0.3f ));
            g.setColour(Colours::black);
            g.setFont(height * 0.7f);

            g.drawText( name, 4, 0, width - 4, height, Justification::centredLeft, true );
        } else {
            std::cout << "failed to execute painItem callback: " << LUA::getError() << std::endl;
        }
    else if ( ! hasCallback("paintItem") && ! hasCallback("createItemComponent") ) {
        if (TreeViewItem::isSelected())
            g.fillAll( Colours::blue.withAlpha( 0.3f ));
        g.setColour(Colours::black);
        g.setFont(height * 0.7f);
        g.drawText( getUniqueName(), 4, 0, width - 4, height, Justification::centredLeft, true );
    }
}
int LTreeViewItem::paintItem(lua_State*){
    set("paintItem");
    return 0;
}

void LTreeViewItem::filesDropped( const StringArray& files, int insertIndex ) {
    callback("filesDropped");
}
int LTreeViewItem::filesDropped(lua_State*){
    set("filesDropped");
    return 0;
}

void LTreeViewItem::paintHorizontalConnectingLine( Graphics& graphics_, const Line<float>& line ) {
    if (! hasCallback("paintHorizontalConnectingLine") )
        TreeViewItem::paintHorizontalConnectingLine(graphics_, line);
    else
        callback("paintHorizontalConnectingLine");
}
int LTreeViewItem::paintHorizontalConnectingLine(lua_State*){
    set("paintHorizontalConnectingLine");
    return 0;
}

void LTreeViewItem::paintVerticalConnectingLine( Graphics& graphics_, const Line<float>& line ) {
    if (! hasCallback("paintVerticalConnectingLine") )
        TreeViewItem::paintVerticalConnectingLine(graphics_, line);
    else
        callback("paintVerticalConnectingLine");
}
int LTreeViewItem::paintVerticalConnectingLine(lua_State*){
    set("paintVerticalConnectingLine");
    return 0;
}

void LTreeViewItem::itemClicked( const MouseEvent& e ) {
    if (! hasCallback("itemClicked") ) {
        TreeViewItem::itemClicked(e);
    }
    else
        callback("itemClicked", 0, { new LRefBase("MouseEvent", &e) });
}
int LTreeViewItem::itemClicked(lua_State* L) {
    if ( lua_gettop(L) > 1 ) {
        if ( lua_type(L,2) == LUA_TFUNCTION )
            set("itemClicked");
        else
            TreeViewItem::itemClicked( *LUA::toUserdata<LMouseEvent>(2) );
    }
    return 0;
}

void LTreeViewItem::itemSelectionChanged( bool isNowSelected ) {
    if(hasCallback("itemSelectionChanged"))
        callback("itemSelectionChanged");
}
int LTreeViewItem::itemSelectionChanged(lua_State*){
    set("itemSelectionChanged");
    return 0;
}

void LTreeViewItem::itemDoubleClicked( const MouseEvent& e ) {
    if (! hasCallback("itemDoubleClicked") ) {
        if (mightContainSubItems())
            TreeViewItem::setOpen (! TreeViewItem::isOpen());
    }
    else
        callback("itemDoubleClicked", 0, { new LRefBase("MouseEvent", &e) });
}
int LTreeViewItem::itemDoubleClicked(lua_State* L) {
    if ( lua_gettop(L) > 1 ) {
        if ( lua_type(L,2) == LUA_TFUNCTION )
            set("itemDoubleClicked");
        else
            TreeViewItem::itemDoubleClicked( *LUA::toUserdata<LMouseEvent>(2) );
    }
    return 0;
}

var LTreeViewItem::getDragSourceDescription() {
    if ( callback("getDragSourceDescription", 1) ) {
        return var( LUA::getString );
    } else {
        return TreeViewItem::getDragSourceDescription();
    }
}
int LTreeViewItem::getDragSourceDescription ( lua_State* ) {
    set("getDragSourceDescription");
}

// FIXME: maybe we could just set some variables instead of using callbacks here
bool LTreeViewItem::mightContainSubItems() {
    if ( callback("mightContainSubItems", 1) )
        return LUA::getBoolean();
    else
        return false;
}
int LTreeViewItem::mightContainSubItems ( lua_State* L ) {
    if ( lua_type(L, 2) == LUA_TFUNCTION )
        set("mightContainSubItems");
    else
        return LUA::returnBoolean( mightContainSubItems() );
}

String LTreeViewItem::getUniqueName() const {
    if ( callback("getUniqueName", 1) )
        return LUA::getString();
    else
        return String::empty;
}
int LTreeViewItem::getUniqueName ( lua_State* L ) {
    if ( lua_type(L, 2) == LUA_TFUNCTION )
        set("getUniqueName");
    else
        return LUA::returnString( getUniqueName() );
}

Component *LTreeViewItem::createItemComponent() {
    if (hasCallback("createItemComponent")) {
        if ( callback("createItemComponent", 1) ) {
            Component *comp = LUA::from_luce<LComponent,Component>(-1);
            return comp;
        }
    }
    return nullptr;
}
int LTreeViewItem::createItemComponent ( lua_State* ) {
    set("createItemComponent");
    return 0;
}

/// end of callbacks


// TODO
/////// getters
int LTreeViewItem::isOpen ( lua_State* ) {
    return LUA::returnBoolean( TreeViewItem::isOpen() );
}

int LTreeViewItem::isSelected ( lua_State* ) {
    return LUA::returnBoolean( TreeViewItem::isSelected() );
}

int LTreeViewItem::getItemHeight ( lua_State* ) {
    return LUA::returnNumber( TreeViewItem::getItemHeight() );
}

int LTreeViewItem::getNumSubItems ( lua_State* ) {
    return LUA::returnNumber( TreeViewItem::getNumSubItems() );
}

bool LTreeViewItem::canBeSelected() const {
    if(hasCallback("canBeSelected")) {
        if(callback("canBeSelected"))
            return LUA::getBoolean();
    }
    return true;
}
int LTreeViewItem::canBeSelected (lua_State* L) {
    if(lua_isfunction(L,2))
        set("canBeSelected");
    else
        return this->canBeSelected();
}

int LTreeViewItem::getSubItem ( lua_State* ) {
    return LUA::returnUserdata<LTreeViewItem, TreeViewItem>( TreeViewItem::getSubItem(LUA::getNumber()) );
}

int LTreeViewItem::isLastOfSiblings ( lua_State* ) {
    return LUA::returnBoolean( TreeViewItem::isLastOfSiblings() );
}

int LTreeViewItem::getOwnerView ( lua_State* ) {
    // owner = TreeView, not implemented yet
    //return LUA::returnUserdata<LTreeView, TreeView>(TreeViewItem::getOwnerView());
    return 0;
}

int LTreeViewItem::getItemWidth ( lua_State* ) {
    return LUA::returnNumber( TreeViewItem::getItemWidth() );
}

int LTreeViewItem::getItemPosition ( lua_State* ) {
    return LUA::returnTable(TreeViewItem::getItemPosition(LUA::getBoolean()));
}

int LTreeViewItem::getItemIdentifierString ( lua_State* ) {
    return LUA::returnString( TreeViewItem::getItemIdentifierString() );
}

int LTreeViewItem::getTooltip ( lua_State* ) {
    // TODO: TreeViewItem returns String::empty anyway
    //       so instanciate a Tooltip or something appropriate here
    return LUA::returnString( TreeViewItem::getTooltip() );
}

int LTreeViewItem::areAllParentsOpen ( lua_State* ) {
    return LUA::returnBoolean( TreeViewItem::areAllParentsOpen() );
}

int LTreeViewItem::getParentItem ( lua_State* ) {
    return LUA::returnUserdata<LTreeViewItem, TreeViewItem>( TreeViewItem::getParentItem() );
}

int LTreeViewItem::getIndexInParent ( lua_State* ) {
    return LUA::returnNumber( TreeViewItem::getIndexInParent() );
}

int LTreeViewItem::getRowNumberInTree ( lua_State* ) {
    return LUA::returnNumber( TreeViewItem::getRowNumberInTree() );
}

/////// setters
int LTreeViewItem::setOpen ( lua_State* ) {
    TreeViewItem::setOpen(LUA::getBoolean());
    return 0;
}

/**
    deselectOtherItemFirst: defaults to true   
*/
int LTreeViewItem::setSelected ( lua_State* ) {
    bool shouldBeSelected = LUA::getBoolean(2);
    bool deselectOtherItemsFirst = LUA::checkAndGetBoolean(2, true);
    NotificationType shouldNotify = LNotificationType::get(LUA::checkAndGetString(2, "sendNotification"));
    TreeViewItem::setSelected( shouldBeSelected, deselectOtherItemsFirst, shouldNotify );
    return 0;
}

int LTreeViewItem::addSubItem ( lua_State* ) {
    LTreeViewItem *tvi = LUA::from_luce<LTreeViewItem>(2);
    int insertPosition = LUA::checkAndGetNumber(2, -1);
    TreeViewItem::addSubItem( tvi, insertPosition );
    return 0;
}

// set a comparator callback
int LTreeViewItem::compareElements(lua_State* L) {
    comparator.compareElements(L);
}
// NOTE: could even set a full callback here, instead of using comparator
int LTreeViewItem::addSubItemSorted ( lua_State* ) {
    TreeViewItem::addSubItemSorted( comparator, LUA::toUserdata<LTreeViewItem>(2) );
    return 0;
}

int LTreeViewItem::setLinesDrawnForSubItems ( lua_State* ) {
    TreeViewItem::setLinesDrawnForSubItems(LUA::getBoolean());
    return 0;
}

int LTreeViewItem::sortSubItems ( lua_State* ) {
    TreeViewItem::sortSubItems( comparator );
    return 0;
}

int LTreeViewItem::setDrawsInLeftMargin ( lua_State* ) {
    TreeViewItem::setDrawsInLeftMargin(LUA::getBoolean());
    return 0;
}

int LTreeViewItem::clearSubItems ( lua_State* L) {
    TreeViewItem::clearSubItems();
    return 0;
}

int LTreeViewItem::removeSubItem ( lua_State* ) {
    int index = LUA::getNumber(2);
    bool deleteItem = LUA::checkAndGetBoolean(2, true);
    TreeViewItem::removeSubItem( index, deleteItem );
    return 0;
}

int LTreeViewItem::repaintItem ( lua_State* ) {
    TreeViewItem::repaintItem();
    return 0;
}

int LTreeViewItem::treeHasChanged ( lua_State* ) {
    TreeViewItem::treeHasChanged();
    return 0;
}

// TODO
int LTreeViewItem::isInterestedInFileDrag ( lua_State* ) {
    // StringArray files = LUA::TODO_OBJECT_StringArray;
    // return LUA::returnBoolean( TreeViewItem::isInterestedInFileDrag( files ) );
    lua_settop(LUA::Get(), 1); // added by TODO
    return LUA::TODO_OBJECT( "bool isInterestedInFileDrag( files )" );
}

int LTreeViewItem::getOpennessState ( lua_State* ) {
    // return LUA::TODO_RETURN_OBJECT_XmlElement( TreeViewItem::getOpennessState() );
    lua_settop(LUA::Get(), 1); // added by TODO
    return LUA::TODO_OBJECT( "XmlElement getOpennessState()" );
}

int LTreeViewItem::isInterestedInDragSource ( lua_State* ) {
    // DragAndDropTarget::SourceDetails dragSourceDetails = LUA::TODO_OBJECT_DragAndDropTarget::SourceDetails;
    // return LUA::returnBoolean( TreeViewItem::isInterestedInDragSource( dragSourceDetails ) );
    lua_settop(LUA::Get(), 1); // added by TODO
    return LUA::TODO_OBJECT( "bool isInterestedInDragSource( dragSourceDetails )" );
}

int LTreeViewItem::restoreOpennessState ( lua_State* ) {
    // TreeViewItem::restoreOpennessState(LUA::TODO_OBJECT_XmlElement);
    LUA::TODO_OBJECT( "restoreOpennessState, LUA::TODO_OBJECT_XmlElement" );
    lua_settop(LUA::Get(), 1); // added by TODO
    return 0;
}
