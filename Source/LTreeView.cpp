/************************************************************

 LTreeView.cpp

    @author Christophe Berbizier (cberbizier@peersuasive.com)
    @license GPLv3
    @copyright 


(c) 2014, Peersuasive Technologies

*************************************************************/

#include "LTreeView_inh.h"

////// static methods
const char LTreeView::className[] = "LTreeView";
const Luna<LTreeView>::PropertyType LTreeView::properties[] = {
    {"indentSize", &LTreeView::getIndentSize, &LTreeView::setIndentSize},
    {"multiSelectEnabled", &LTreeView::isMultiSelectEnabled, &LTreeView::setMultiSelectEnabled},
    {"rootItem", &LTreeView::getRootItem, &LTreeView::setRootItem},
    {"rootItemVisible", &LTreeView::isRootItemVisible, &LTreeView::setRootItemVisible},
    {"defaultOpenness", &LTreeView::areItemsOpenByDefault, &LTreeView::setDefaultOpenness},
    {"openCloseButtonsVisible", &LTreeView::areOpenCloseButtonsVisible , &LTreeView::setOpenCloseButtonsVisible},
    {"rootItemVisible", &LTreeView::isRootItemVisible, &LTreeView::setRootItemVisible},
    {"numSelectedItems", &LTreeView::getNumSelectedItems, &LBase::readOnly},
    {0,0}
};

const Luna<LTreeView>::FunctionType LTreeView::methods[] = {
    method( LTreeView, getNumRowsInTree ),
    method( LTreeView, getIndentSize ),
    method( LTreeView, setIndentSize ),
    method( LTreeView, getNumSelectedItems ),
    method( LTreeView, getItemOnRow ),
    method( LTreeView, isMultiSelectEnabled ),
    method( LTreeView, setMultiSelectEnabled ),
    method( LTreeView, getItemAt ),
    method( LTreeView, getRootItem ),
    method( LTreeView, setRootItem ),
    method( LTreeView, isRootItemVisible ),
    method( LTreeView, setRootItemVisible ),

    method( LTreeView, areItemsOpenByDefault ),
    method( LTreeView, getViewport ),
    method( LTreeView, findItemFromIdentifierString ),
    method( LTreeView, getSelectedItem ),
    method( LTreeView, areOpenCloseButtonsVisible ),
    method( LTreeView, getOpennessState ),
    method( LTreeView, clearSelectedItems ),
    method( LTreeView, setDefaultOpenness ),
    method( LTreeView, moveSelectedRow ),
    method( LTreeView, deleteRootItem ),
    method( LTreeView, restoreOpennessState ),
    method( LTreeView, setOpenCloseButtonsVisible ),
    method( LTreeView, scrollToKeepItemVisible ),

    // TODO: create a dnd base class
    //method( LTreeView, isInterestedInFileDrag ),
    //method( LTreeView, fileDragEnter ),
    //method( LTreeView, fileDragMove ),
    //method( LTreeView, fileDragExit ),
    //method( LTreeView, filesDropped ),

    method( LTreeView, isInterestedInDragSource ),
    method( LTreeView, itemDragEnter ),
    method( LTreeView, itemDragMove ),
    method( LTreeView, itemDragExit ),
    method( LTreeView, itemDropped ),
    {0,0}
};

/////// ctor/dtor
LTreeView::LTreeView(lua_State *L)
    : LComponent(L, this),
      TreeView( /* TODO: add args */ )
{
    TreeView::setName(myName());
}

LTreeView::~LTreeView() {
    TreeView::deleteRootItem();
}

/////// callbacks
// TODO: add dnd callbacks

void LTreeView::mouseMove(const MouseEvent& e) {
    LComponent::lmouseMove(e);
}

void LTreeView::mouseEnter(const MouseEvent& e) {
    LComponent::lmouseEnter(e);
}

void LTreeView::mouseExit(const MouseEvent& e) {
    LComponent::lmouseExit(e);
}

void LTreeView::mouseDown(const MouseEvent& e) {
    LComponent::lmouseDown(e);
}

void LTreeView::mouseDrag(const MouseEvent& e) {
    LComponent::lmouseDrag(e);
}

void LTreeView::mouseUp(const MouseEvent& e) {
    LComponent::lmouseUp(e);
}

void LTreeView::mouseDoubleClick(const MouseEvent& e) {
    LComponent::lmouseDoubleClick(e);
}

void LTreeView::mouseWheelMove (const MouseEvent& e, const MouseWheelDetails& wheel) {
    LComponent::lmouseWheelMove(e, wheel);
}

void LTreeView::mouseMagnify (const MouseEvent& e, float scaleFactor) {
    LComponent::lmouseMagnify(e, scaleFactor);
}


//bool LTreeView::isInterestedInFileDrag (const DragAndDropTarget::SourceDetails& dragSourceDetails) {
//    if(hasCallback("isInterestedInDragSource")) {
//        callback("isInterestedInDragSource", 1, 
//                { new LRefBase( "SourceDetails", new LSourceDetails(LUA::Get(), dragSourceDetails) ) } );
//        return LUA::getBoolean();
//    }
//    return false;
//}
//
//int LTreeView::isInterestedInFileDrag ( lua_State* ) {
//    set("isInterestedInDragSource");
//}
//
//
//int LTreeView::fileDragEnter ( lua_State* ) {
//    // StringArray files = LUA::TODO_OBJECT_StringArray;
//    //int x = LUA::getNumber();
//    //int y = LUA::getNumber();
//    // TreeView::fileDragEnter( files, x, y );
//    LUA::TODO_OBJECT( "fileDragEnter,  files, x, y " );
//    lua_settop(LUA::Get(), 1); // added by TODO
//    return 0;
//}
//
//int LTreeView::fileDragMove ( lua_State* ) {
//    // StringArray files = LUA::TODO_OBJECT_StringArray;
//    //int x = LUA::getNumber();
//    //int y = LUA::getNumber();
//    // TreeView::fileDragMove( files, x, y );
//    LUA::TODO_OBJECT( "fileDragMove,  files, x, y " );
//    lua_settop(LUA::Get(), 1); // added by TODO
//    return 0;
//}
//
//int LTreeView::fileDragExit ( lua_State* ) {
//    // TreeView::fileDragExit(LUA::TODO_OBJECT_StringArray);
//    LUA::TODO_OBJECT( "fileDragExit, LUA::TODO_OBJECT_StringArray" );
//    lua_settop(LUA::Get(), 1); // added by TODO
//    return 0;
//}
//
//int LTreeView::filesDropped ( lua_State* ) {
//    // StringArray files = LUA::TODO_OBJECT_StringArray;
//    //int x = LUA::getNumber();
//    //int y = LUA::getNumber();
//    // TreeView::filesDropped( files, x, y );
//    LUA::TODO_OBJECT( "filesDropped,  files, x, y " );
//    lua_settop(LUA::Get(), 1); // added by TODO
//    return 0;
//}
//
//
bool LTreeView::isInterestedInDragSource (const SourceDetails&) {
    if(hasCallback("isInterestedInDragSource")) {
        if ( callback("isInterestedInDragSource", 1) )
            return LUA::getBoolean();
    }
    return false;
}
int LTreeView::isInterestedInDragSource ( lua_State* ) {
    set("isInterestedInDragSource");
}

void LTreeView::itemDragEnter (const SourceDetails& sd) {
    if(hasCallback("itemDragEnter"))
        callback("itemDragEnter", 0, 
                { new LRefBase( "SourceDetails", new LSourceDetails(LUA::Get(), sd ) ) } );
}
int LTreeView::itemDragEnter ( lua_State* ) {
    set("itemDragEnter");
}

void LTreeView::itemDragMove (const SourceDetails& sd) {
    if(hasCallback("itemDragMove"))
        callback("itemDragMove", 0, 
                { new LRefBase( "SourceDetails", new LSourceDetails(LUA::Get(), sd ) ) } );
}
int LTreeView::itemDragMove ( lua_State* ) {
    set("itemDragMove");
}

void LTreeView::itemDragExit (const SourceDetails& sd) {
    if(hasCallback("itemDragExit"))
        callback("itemDragExit", 0, 
                { new LRefBase( "SourceDetails", new LSourceDetails(LUA::Get(), sd ) ) } );
}
int LTreeView::itemDragExit ( lua_State* ) {
    set("itemDragExit");
}

void LTreeView::itemDropped (const SourceDetails& sd) {
    if(hasCallback("itemDropped"))
        callback("itemDropped", 0, 
                { new LRefBase( "SourceDetails", new LSourceDetails(LUA::Get(), sd ) ) } );
}
int LTreeView::itemDropped ( lua_State* ) {
    set("itemDropped");
}


/////// getters/setters
int LTreeView::getIndentSize ( lua_State* ) {
    return LUA::returnNumber( TreeView::getIndentSize() );
}
int LTreeView::setIndentSize ( lua_State* ) {
    TreeView::setIndentSize(LUA::getNumber());
    return 0;
}

int LTreeView::isMultiSelectEnabled ( lua_State* ) {
    return LUA::returnBoolean( TreeView::isMultiSelectEnabled() );
}
int LTreeView::setMultiSelectEnabled ( lua_State* ) {
    TreeView::setMultiSelectEnabled(LUA::getBoolean());
    return 0;
}

int LTreeView::getRootItem ( lua_State* ) {
    return LUA::returnUserdata<LTreeViewItem>( TreeView::getRootItem() );
}
int LTreeView::setRootItem ( lua_State* L) {
    if ( lua_isnil(L, 2) )
        TreeView::setRootItem(nullptr);
    else {
        TreeView::deleteRootItem();
        //TreeView::setRootItem( LUA::toUserdata<LTreeViewItem>(2) );
        TreeView::setRootItem( LUA::from_luce<LTreeViewItem, TreeViewItem>(2) );
    }

    return 0;
}

int LTreeView::isRootItemVisible ( lua_State* ) {
    return LUA::returnBoolean( TreeView::isRootItemVisible() );
}
int LTreeView::setRootItemVisible ( lua_State* ) {
    TreeView::setRootItemVisible(LUA::getBoolean());
    return 0;
}

/////// getters
int LTreeView::getNumRowsInTree ( lua_State* ) {
    return LUA::returnNumber( TreeView::getNumRowsInTree() );
}

int LTreeView::getNumSelectedItems ( lua_State* ) {
    int maximumDepthToSearchTo = LUA::checkAndGetNumber(2, -1);
    return LUA::returnNumber( TreeView::getNumSelectedItems( maximumDepthToSearchTo ) );
}

int LTreeView::getItemOnRow ( lua_State* ) {
    return LUA::returnUserdata<LTreeViewItem>( TreeView::getItemOnRow( LUA::getNumber() ) );
}

int LTreeView::getItemAt ( lua_State* ) {
    return LUA::returnUserdata<LTreeViewItem>( TreeView::getItemAt( LUA::getNumber() ) );
}

int LTreeView::areItemsOpenByDefault ( lua_State* ) {
    return LUA::returnBoolean( TreeView::areItemsOpenByDefault() );
}

int LTreeView::findItemFromIdentifierString ( lua_State* ) {
    return LUA::returnUserdata<LTreeViewItem>( TreeView::findItemFromIdentifierString( LUA::getString() ) );
}

int LTreeView::getSelectedItem ( lua_State* ) {
    return LUA::returnUserdata<LTreeViewItem>( TreeView::getSelectedItem( LUA::getNumber() ) );
}

int LTreeView::areOpenCloseButtonsVisible ( lua_State* ) {
    return LUA::returnBoolean( TreeView::areOpenCloseButtonsVisible() );
}

/////// setters
int LTreeView::clearSelectedItems ( lua_State* ) {
    TreeView::clearSelectedItems();
    return 0;
}

int LTreeView::setDefaultOpenness ( lua_State* ) {
    TreeView::setDefaultOpenness(LUA::getBoolean());
    return 0;
}

int LTreeView::moveSelectedRow ( lua_State* ) {
    TreeView::moveSelectedRow(LUA::getNumber());
    return 0;
}

int LTreeView::deleteRootItem ( lua_State* ) {
    TreeView::deleteRootItem();
    return 0;
}

int LTreeView::setOpenCloseButtonsVisible ( lua_State* ) {
    TreeView::setOpenCloseButtonsVisible(LUA::getBoolean());
    return 0;
}

int LTreeView::scrollToKeepItemVisible ( lua_State* ) {
    TreeView::scrollToKeepItemVisible( LUA::toUserdata<LTreeViewItem>(2) );
}

// TODO
// getters
int LTreeView::getViewport ( lua_State* ) {
    // return LUA::TODO_RETURN_OBJECT_Viewport( TreeView::getViewport() );
    lua_settop(LUA::Get(), 1); // added by TODO
    return LUA::TODO_OBJECT( "Viewport getViewport()" );
}

int LTreeView::getOpennessState ( lua_State* ) {
    //bool alsoIncludeScrollPosition = LUA::getBoolean(2);
    // return LUA::TODO_RETURN_OBJECT_XmlElement( TreeView::getOpennessState( alsoIncludeScrollPosition ) );
    lua_settop(LUA::Get(), 1); // added by TODO
    return LUA::TODO_OBJECT( "XmlElement getOpennessState( alsoIncludeScrollPosition )" );
}

// setters
int LTreeView::restoreOpennessState ( lua_State* ) {
    // XmlElement newState = LUA::TODO_OBJECT_XmlElement;
    //bool restoreStoredSelection = LUA::getBoolean(2);
    // TreeView::restoreOpennessState( newState, restoreStoredSelection );
    LUA::TODO_OBJECT( "restoreOpennessState,  newState, restoreStoredSelection " );
    lua_settop(LUA::Get(), 1); // added by TODO
    return 0;
}
