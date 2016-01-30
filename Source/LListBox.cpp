/************************************************************

 LListBox.cpp

    @author Christophe Berbizier (cberbizier@peersuasive.com)
    @license GPLv3
    @copyright 


(c) 2014, Peersuasive Technologies

*************************************************************/

#include "LListBox_inh.h"

////// static methods
const char LListBox::className[] = "LListBox";
const Luna<LListBox>::PropertyType LListBox::properties[] = {
    {"rowHeight", &LListBox::getRowHeight, &LListBox::setRowHeight},
    {"outlineThickness", &LListBox::getOutlineThickness, &LListBox::setOutlineThickness},
    {"selectedRows", &LListBox::getSelectedRows, &LListBox::setSelectedRows},
    {"verticalPosition", &LListBox::getVerticalPosition, &LListBox::setVerticalPosition},
    {"multipleSelectionEnabled", &LBase::writeOnly, &LListBox::setMultipleSelectionEnabled},
    //{"model", &LListBox::getModel, &LListBox::setModel},
    {0,0}
};

const Luna<LListBox>::FunctionType LListBox::methods[] = {
    method( LListBox, isRowSelected ),
    method( LListBox, getRowNumberOfComponent ),
    method( LListBox, getRowHeight ),
    method( LListBox, setRowHeight ),
    method( LListBox, getVerticalScrollBar ),
    method( LListBox, getComponentForRowNumber ),
    method( LListBox, getVisibleRowWidth ),
    method( LListBox, getOutlineThickness ),
    method( LListBox, setOutlineThickness ),
    method( LListBox, getVisibleContentWidth ),
    method( LListBox, getLastRowSelected ),
    method( LListBox, getViewport ),
    method( LListBox, getHorizontalScrollBar ),
    method( LListBox, getNumRowsOnScreen ),
    method( LListBox, getRowPosition ),
    method( LListBox, createSnapshotOfSelectedRows ),
    method( LListBox, getSelectedRows ),
    method( LListBox, setSelectedRows ),
    method( LListBox, getNumSelectedRows ),
    method( LListBox, getSelectedRow ),
    method( LListBox, getVerticalPosition ),
    method( LListBox, setVerticalPosition ),
    //method( LListBox, getModel ),
    //method( LListBox, setModel ),
    method( LListBox, getInsertionIndexForPosition ),
    method( LListBox, getRowContainingPosition ),
    method( LListBox, setMultipleSelectionEnabled ),
    method( LListBox, selectRow ),
    method( LListBox, selectRowsBasedOnModifierKeys ),
    method( LListBox, setHeaderComponent ),

    method( LListBox, selectRangeOfRows ),
    method( LListBox, setMinimumContentWidth ),
    method( LListBox, repaintRow ),
    method( LListBox, setMouseMoveSelectsRows ),
    method( LListBox, scrollToEnsureRowIsOnscreen ),
    method( LListBox, deselectAllRows ),
    method( LListBox, flipRowSelection ),
    method( LListBox, deselectRow ),
    method( LListBox, updateContent ),

    method( LListBox, startDragAndDrop ),
    method( LListBox, isInterestedInDragSource),
    method( LListBox, itemDropped),
    method( LListBox, itemDragEnter),
    method( LListBox, itemDragExit),

    method( LListBox, isInterestedInFileDrag),
    method( LListBox, filesDropped),
    method( LListBox, fileDragEnter),
    method( LListBox, fileDragMove),
    method( LListBox, fileDragExit),

    method( LListBox, paintListBoxItem ),
    method( LListBox, getMouseCursorForRow ),
    method( LListBox, getTooltipForRow ),
    method( LListBox, refreshComponentForRow ),
    method( LListBox, getDragSourceDescription ),
    method( LListBox, getNumRows ),
    method( LListBox, listWasScrolled ),
    method( LListBox, selectedRowsChanged ),
    method( LListBox, deleteKeyPressed ),
    method( LListBox, returnKeyPressed ),
    method( LListBox, backgroundClicked ),
    method( LListBox, listBoxItemClicked ),
    method( LListBox, listBoxItemDoubleClicked ),

    {0,0}
};

/////// ctor/dtor
const Luna<LListBox>::StaticType LListBox::statics[] = {
    {0,0}
};

LListBox::LListBox(lua_State *L)
    : LComponent(L, this),
      ListBox("LListBox", this)
{
    ListBox::setName(myName());
    REGISTER_CLASS(LListBox);
}

LListBox::~LListBox() {}

/////// callbacks

bool LListBox::isInterestedInDragSource (const DragAndDropTarget::SourceDetails& sd) {
    if(hasCallback("isInterestedInDragSource")) {
        ScopedPointer<LSourceDetails> lsd = new LSourceDetails(LUA::Get(), sd);
        if( callback("isInterestedInDragSource", 1,
            { new LRefBase("SourceDetails", lsd ) } ) )
            //{ new LRefBase("SourceDetails", new LSourceDetails(LUA::Get(), sd)) }) ) 
        {
            return LUA::getBoolean();
        }
    }
    return false;
}
int LListBox::isInterestedInDragSource(lua_State*) {
    set("isInterestedInDragSource");
    return 0;
}

void LListBox::itemDropped (const DragAndDropTarget::SourceDetails& sd) {
    ScopedPointer<LSourceDetails> lsd = new LSourceDetails(LUA::Get(), sd);
    callback("itemDropped", 0,
            { new LRefBase("SourceDetails", lsd) });
            //{ new LRefBase("SourceDetails", new LSourceDetails(LUA::Get(), sd)) });
}
int LListBox::itemDropped(lua_State*) {
    set("itemDropped");
    return 0;
}

void LListBox::itemDragEnter(const DragAndDropTarget::SourceDetails& sd) {
    if(hasCallback("itemDragEnter")) {
        ScopedPointer<LSourceDetails> lsd = new LSourceDetails(LUA::Get(), sd);
        callback("itemDragEnter", 0,
                { new LRefBase("SourceDetails", lsd) });
                //{ new LRefBase("SourceDetails", new LSourceDetails(LUA::Get(), sd)) });
    }
}
int LListBox::itemDragEnter(lua_State*) {
    set("itemDragEnter");
    return 0;
}

void LListBox::itemDragExit(const DragAndDropTarget::SourceDetails& sd) {
    if(hasCallback("itemDragExit")) {
        ScopedPointer<LSourceDetails> lsd = new LSourceDetails(LUA::Get(), sd);
        callback("itemDragExit", 0,
                { new LRefBase("SourceDetails", lsd) });
                //{ new LRefBase("SourceDetails", new LSourceDetails(LUA::Get(), sd)) });
    }
}
int LListBox::itemDragExit(lua_State*) {
    set("itemDragExit");
    return 0;
}

int LListBox::startDragAndDrop ( lua_State* ) {
    MouseEvent *me = LUA::from_luce<LMouseEvent, MouseEvent>(2);
    SparseSet<int> rowsToDrag = LUA::getSparseSet(2);
    var dragDescription = LUA::getString(2);
    bool allowDraggingToOtherWindows = LUA::getBoolean(2);
    ListBox::startDragAndDrop( *me, rowsToDrag, dragDescription, allowDraggingToOtherWindows);
    return 0;
}


bool LListBox::isInterestedInFileDrag (const StringArray& files) {
    if(hasCallback("isInterestedInFileDrag")) {
        LUCE::luce_pushtable(files);
        int files = lua_gettop(LUA::Get());
        if( callback("isInterestedInFileDrag", 1,
            { new LRefBase( files ) } 
            )
        )
        {
            return LUA::checkAndGetBoolean(-1, false);
        }
    }
    return false;
}
int LListBox::isInterestedInFileDrag(lua_State*) {
    set("isInterestedInFileDrag");
    return 0;
}

void LListBox::filesDropped (const StringArray& files, int x, int y) {
    if(hasCallback("filesDropped")) {
        LUCE::luce_pushtable(files);
        int files = lua_gettop(LUA::Get());
        callback("filesDropped", 0,
            { new LRefBase( files ), x, y });
    }
}
int LListBox::filesDropped(lua_State*) {
    set("filesDropped");
    return 0;
}

void LListBox::fileDragEnter(const StringArray& files, int x, int y) {
    if(hasCallback("fileDragEnter")) {
        LUCE::luce_pushtable(files);
        int files = lua_gettop(LUA::Get());
        callback("fileDragEnter", 0,
            { new LRefBase( files ), x, y});
    }
}
int LListBox::fileDragEnter(lua_State*) {
    set("fileDragEnter");
    return 0;
}

void LListBox::fileDragMove(const StringArray& files, int x, int y) {
    if(hasCallback("fileDragMove")) {
        LUCE::luce_pushtable(files);
        int files = lua_gettop(LUA::Get());
        callback("fileDragMove", 0,
            { new LRefBase( files ), x, y });
    }
}
int LListBox::fileDragMove(lua_State*) {
    set("fileDragMove");
    return 0;
}

void LListBox::fileDragExit(const StringArray& files) {
    if(hasCallback("fileDragExit")) {
        LUCE::luce_pushtable(files);
        int files = lua_gettop(LUA::Get());
        callback("fileDragExit", 0,
            { new LRefBase( files ) });
    }
}
int LListBox::fileDragExit(lua_State*) {
    set("fileDragExit");
    return 0;
}



/*
void LListBox::paintListBoxItem( int rowNumber, Graphics& g, int width, int height, bool rowIsSelected ) {
    if( callback("paintListBoxItem", 1, { rowNumber, width, height, rowIsSelected } ) ) {
        //std::cout << "top: " << lua_gettop(LUA::Get()) << std::endl;
        String text = LUA::getString();
        //std::cout << "item name: " << text.toStdString() << std::endl;
        //int w = LUA::checkAndGetNumber(2, width);
        //int h = LUA::checkAndGetNumber(2, height);

        if (rowIsSelected)
            g.fillAll (Colours::yellow.withAlpha(0.2f));

        g.setColour (Colours::black);
        g.setFont (height * 0.7f);
    
        //g.drawText ( text , 5, 0, w, h, Justification::left, true );
        g.drawText ( text , 5, 0, width, height, Justification::left, true );
    }
}
*/

void LListBox::paintListBoxItem( int rowNumber, Graphics& g, int width, int height, bool rowIsSelected ) {
    LGraphics lg(LUA::Get(), g);
    callback("paintListBoxItem", 0, { 
            rowNumber,
            new LRefBase("Graphics", &lg),
            width, height, rowIsSelected } );

}
int LListBox::paintListBoxItem(lua_State*) {
    set("paintListBoxItem");
    return 0;
}

int LListBox::getNumRows() {
    callback("getNumRows", 1);
    return LUA::checkAndGetNumber();
}
int LListBox::getNumRows(lua_State*) {
    set("getNumRows");
    return 0;
}

void LListBox::paint(Graphics& g) {
    if(hasCallback("paint"))
        LComponent::lpaint(g);
    else
        ListBox::paint(g);
}

void LListBox::listWasScrolled() {
    if(hasCallback("listWasScrolled"))
        callback("listWasScrolled");
}
int LListBox::listWasScrolled(lua_State*) {
    set("listWasScrolled");
    return 0;
}

void LListBox::selectedRowsChanged( int lastRowSelected ) {
    if(hasCallback("selectedRowsChanged"))
        callback("selectedRowsChanged", 0, { lastRowSelected });
}
int LListBox::selectedRowsChanged(lua_State*) {
    set("selectedRowsChanged");
    return 0;
}

void LListBox::deleteKeyPressed( int lastRowSelected ) {
    if(hasCallback("deleteKeyPressed"))
        callback("deleteKeyPressed", 0, { lastRowSelected } );
}
int LListBox::deleteKeyPressed(lua_State*) {
    set("deleteKeyPressed");
    return 0;
}

void LListBox::returnKeyPressed( int lastRowSelected ) {
    if(hasCallback("returnKeyPressed"))
        callback("returnKeyPressed", 0, { lastRowSelected } );
}
int LListBox::returnKeyPressed(lua_State*) {
    set("returnKeyPressed");
    return 0;
}

void LListBox::backgroundClicked(const MouseEvent& e) {
    if(hasCallback("backgroundClicked"))
        callback("backgroundClicked", 0, { new LRefBase("MouseEvent", &e) } );
}
int LListBox::backgroundClicked(lua_State*) {
    set("backgroundClicked");
    return 0;
}

void LListBox::listBoxItemClicked( int row, const MouseEvent& e ) {
    if(hasCallback("listBoxItemClicked"))
        callback("listBoxItemClicked", 0, { row, new LRefBase("MouseEvent", &e) } );
}
int LListBox::listBoxItemClicked(lua_State*) {
    set("listBoxItemClicked");
    return 0;
}

void LListBox::listBoxItemDoubleClicked( int row, const MouseEvent& e ) {
    if(hasCallback("listBoxItemDoubleClicked"))
        callback("listBoxItemDoubleClicked", 0, { row, new LRefBase("MouseEvent", &e) } );
}
int LListBox::listBoxItemDoubleClicked(lua_State*) {
    set("listBoxItemDoubleClicked");
    return 0;
}

Component* LListBox::refreshComponentForRow (int rowNumber, bool isRowSelected, 
                    Component* existingComponentToUpdate) 
{
    if(hasCallback("refreshComponentForRow")) {
        callback("refreshComponentForRow", 1,
            { rowNumber, isRowSelected, new LRefBase("Component", existingComponentToUpdate) });
        if( lua_isnoneornil(LUA::Get(), -1) ) {
            if(existingComponentToUpdate)
                delete existingComponentToUpdate;
            return nullptr;
        } else {
            return LUA::from_luce<LJComponent, Component>();
        }
    }
    else
        return nullptr;
}
int LListBox::refreshComponentForRow (lua_State*) {
    set("refreshComponentForRow");
    return 0;
}

// TODO: implement tables in args
var LListBox::getDragSourceDescription (const SparseSet<int>& currentlySelectedRows) {
    //if(hasCallback("getDragSourceDescription")) {
    //    callback("getDragSourceDescription", 1, );
    //    return LUA::getString();
    //}
    //else return var();
    return var();
}
int LListBox::getDragSourceDescription (lua_State*) {
    set("getDragSourceDescription");
    return 0;
}

String LListBox::getTooltipForRow (int row) {
    if(hasCallback("getTooltipForRow")) {
        if(callback("getTooltipForRow"))
            return LUA::getString();
    }
    return String::empty;
}
int LListBox::getTooltipForRow (lua_State*) {
    set("getTooltipForRow");
    return 0;
}

// TODO: MouseCursor
MouseCursor LListBox::getMouseCursorForRow (int row) {
    if(hasCallback("getMouseCursorForRow"))
        callback("getMouseCursorForRow");
    return MouseCursor::NormalCursor;
}
int LListBox::getMouseCursorForRow (lua_State*) {
    //set("getMouseCursorForRow");

    return 0;
}

/////// getters/setters
int LListBox::getRowHeight ( lua_State* ) {
    return LUA::returnNumber( ListBox::getRowHeight() );
}
int LListBox::setRowHeight ( lua_State* ) {
    ListBox::setRowHeight(LUA::getNumber());
    return 0;
}

int LListBox::getOutlineThickness ( lua_State* ) {
    return LUA::returnNumber( ListBox::getOutlineThickness() );
}
int LListBox::setOutlineThickness ( lua_State* ) {
    ListBox::setOutlineThickness(LUA::getNumber());
    return 0;
}

int LListBox::getSelectedRows ( lua_State* ) {
    return LUCE::luce_pushtable( ListBox::getSelectedRows() );
}
int LListBox::setSelectedRows ( lua_State* ) {
    SparseSet<int> setOfRowsToBeSelected = LUA::getSparseSet(2);
    NotificationType shouldNotify = (NotificationType)LUA::checkAndGetNumber<int>(2, NotificationType::sendNotification);
    ListBox::setSelectedRows( setOfRowsToBeSelected, shouldNotify );
    return 0;
}

int LListBox::getVerticalPosition ( lua_State* ) {
    return LUA::returnNumber( ListBox::getVerticalPosition() );
}
int LListBox::setVerticalPosition ( lua_State* ) {
    ListBox::setVerticalPosition(LUA::getNumber());
    return 0;
}

// I shouldn't need it...
/*
int LListBox::getModel ( lua_State* ) {
    // return LUA::TODO_RETURN_OBJECT_ListBoxModel( ListBox::getModel() );
    lua_settop(LUA::Get(), 1); // added by TODO
    return LUA::TODO_OBJECT( "ListBoxModel getModel()" );
}
int LListBox::setModel ( lua_State* ) {
    // ListBox::setModel(LUA::TODO_OBJECT_ListBoxModel);
    LUA::TODO_OBJECT( "setModel, LUA::TODO_OBJECT_ListBoxModel" );
    lua_settop(LUA::Get(), 1); // added by TODO
    return 0;
}
*/

/////// getters
int LListBox::isRowSelected ( lua_State* ) {
    return LUA::returnBoolean( ListBox::isRowSelected( LUA::getNumber(2) ) );
}

int LListBox::getRowNumberOfComponent ( lua_State* ) {
    return LUA::returnNumber( ListBox::getRowNumberOfComponent(LUA::from_luce<LComponent, Component>(2)) );
}

int LListBox::getComponentForRowNumber ( lua_State* ) {
    return LUA::returnUserdata<LMainComponent, Component>( ListBox::getComponentForRowNumber( LUA::getNumber(2) ) );
}

int LListBox::getVisibleRowWidth ( lua_State* ) {
    return LUA::returnNumber( ListBox::getVisibleRowWidth() );
}

int LListBox::getVisibleContentWidth ( lua_State* ) {
    return LUA::returnNumber( ListBox::getVisibleContentWidth() );
}

int LListBox::getLastRowSelected ( lua_State* ) {
    return LUA::returnNumber( ListBox::getLastRowSelected() );
}

int LListBox::getNumRowsOnScreen ( lua_State* ) {
    return LUA::returnNumber( ListBox::getNumRowsOnScreen() );
}

int LListBox::getRowPosition ( lua_State* ) {
    int rowNumber = LUA::getNumber(2);
    bool relativeToComponentTopLeft = LUA::getBoolean(2);
    return LUCE::luce_pushtable( ListBox::getRowPosition(rowNumber, relativeToComponentTopLeft) );
}

int LListBox::getNumSelectedRows ( lua_State* ) {
    return LUA::returnNumber( ListBox::getNumSelectedRows() );
}

int LListBox::getSelectedRow ( lua_State* ) {
    return LUA::returnNumber( ListBox::getSelectedRow( LUA::checkAndGetNumber(2, 0) ) );
}

int LListBox::getInsertionIndexForPosition ( lua_State* ) {
    Array<int> pos = LUA::getList<int>(2);
    return LUA::returnNumber( ListBox::getInsertionIndexForPosition( pos[0], pos[1] ) );
}

int LListBox::getRowContainingPosition ( lua_State* ) {
    Array<int> pos = LUA::getList<int>(2);
    return LUA::returnNumber( ListBox::getRowContainingPosition( pos[0], pos[1] ) );
}

/////// setters
int LListBox::setMultipleSelectionEnabled ( lua_State* ) {
    ListBox::setMultipleSelectionEnabled(LUA::getBoolean());
    return 0;
}

int LListBox::selectRow ( lua_State* ) {
    int rowNumber = LUA::getNumber(2);
    bool dontScrollToShowThisRow = LUA::checkAndGetBoolean(2, false);
    bool deselectOthersFirst = LUA::checkAndGetBoolean(2, true);
    ListBox::selectRow( rowNumber, dontScrollToShowThisRow, deselectOthersFirst );
    return 0;
}

int LListBox::setHeaderComponent ( lua_State* ) {
    ListBox::setHeaderComponent( LUA::from_luce<LComponent, Component>(2) );
    return 0;
}

int LListBox::selectRangeOfRows ( lua_State* ) {
    Array<int> range = LUA::getList<int>(2);
    ListBox::selectRangeOfRows( range[0], range[1] );
    return 0;
}

int LListBox::setMinimumContentWidth ( lua_State* ) {
    ListBox::setMinimumContentWidth(LUA::getNumber());
    return 0;
}

int LListBox::repaintRow ( lua_State* ) {
    ListBox::repaintRow(LUA::getNumber());
    return 0;
}

int LListBox::setMouseMoveSelectsRows ( lua_State* ) {
    ListBox::setMouseMoveSelectsRows(LUA::getBoolean());
    return 0;
}

int LListBox::scrollToEnsureRowIsOnscreen ( lua_State* ) {
    ListBox::scrollToEnsureRowIsOnscreen(LUA::getNumber());
    return 0;
}

int LListBox::deselectAllRows ( lua_State* ) {
    ListBox::deselectAllRows();
    return 0;
}

int LListBox::flipRowSelection ( lua_State* ) {
    ListBox::flipRowSelection(LUA::getNumber());
    return 0;
}

int LListBox::deselectRow ( lua_State* ) {
    ListBox::deselectRow(LUA::getNumber());
    return 0;
}

int LListBox::updateContent ( lua_State* ) {
    ListBox::updateContent();
    return 0;
}

// TODO
//getters
int LListBox::getHorizontalScrollBar ( lua_State* ) {
    // return LUA::TODO_RETURN_OBJECT_ScrollBar( ListBox::getHorizontalScrollBar() );
    lua_settop(LUA::Get(), 1); // added by TODO
    return LUA::TODO_OBJECT( "ScrollBar getHorizontalScrollBar()" );
}

int LListBox::getVerticalScrollBar ( lua_State* ) {
    // return LUA::TODO_RETURN_OBJECT_ScrollBar( ListBox::getVerticalScrollBar() );
    lua_settop(LUA::Get(), 1); // added by TODO
    return LUA::TODO_OBJECT( "ScrollBar getVerticalScrollBar()" );
}

int LListBox::getViewport ( lua_State* ) {
    // return LUA::TODO_RETURN_OBJECT_Viewport( ListBox::getViewport() );
    lua_settop(LUA::Get(), 1); // added by TODO
    return LUA::TODO_OBJECT( "Viewport getViewport()" );
}

int LListBox::createSnapshotOfSelectedRows ( lua_State* ) {
    int x = LUA::getNumber(2);
    int y = LUA::getNumber(2);
    // return LUA::TODO_RETURN_OBJECT_Image( ListBox::createSnapshotOfSelectedRows( x, y ) );
    lua_settop(LUA::Get(), 1); // added by TODO
    return LUA::TODO_OBJECT( "Image createSnapshotOfSelectedRows( x, y )" );
}

int LListBox::selectRowsBasedOnModifierKeys ( lua_State* ) {
    int rowThatWasClickedOn = LUA::getNumber(2);
    // ModifierKeys modifiers = LUA::TODO_OBJECT_ModifierKeys;
    bool isMouseUpEvent = LUA::getBoolean(4);
    // ListBox::selectRowsBasedOnModifierKeys( rowThatWasClickedOn, modifiers, isMouseUpEvent );
    LUA::TODO_OBJECT( "selectRowsBasedOnModifierKeys,  rowThatWasClickedOn, modifiers, isMouseUpEvent " );
    lua_settop(LUA::Get(), 1); // added by TODO
    return 0;
}
