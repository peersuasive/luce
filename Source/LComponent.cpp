/************************************************************

 LComponent.cpp

    @author Christophe Berbizier (cberbizier@peersuasive.com)
    @license GPLv3
    @copyright 


(c) 2013-2014, Peersuasive Technologies

*************************************************************/

#include "LComponent_inh.h"
const char LComponent::className[] = "LComponent";

const Luna<LComponent>::PropertyType LComponent::properties[] = {
    {0,0}
};

const Luna<LComponent>::FunctionType LComponent::methods[] = {
    {0,0}
};

LComponent::LComponent(lua_State *Ls, Component* child_, const String& name_)
    : LBase(Ls),
      child(child_)
{
    L = Ls;
    
    if ( lua_isstring(L, 2) )        
        myName = lua_tostring(L, 2);
    else        
        myName = name_;
    
    reg("childrenChanged");
    reg("parentHierarchyChanged");
    reg("colourChanged");
    reg("lookAndFeelChanged");
    reg("userTriedToCloseWindow");
    reg("modifierKeysChanged");
    reg("broughtToFront");
    reg("parentSizeChanged");
    reg("visibilityChanged");
    reg("inputAttemptWhenModal");
    reg("paint");
    reg("handleCommandMessage");
    reg("resized");
    reg("focusGained");
    reg("paintOverChildren");
    reg("moved");
    reg("childBoundsChanged");
    reg("focusLost");
    reg("minimisationStateChanged");
    reg("mouseMove");
    reg("mouseEnter");
    reg("mouseExit");
    reg("mouseDown");
    reg("mouseDrag");
    reg("mouseUp");
    reg("mouseDoubleClick");
    reg("mouseWheelMove");
    reg("mouseMagnify");
    reg("enablementChanged");
    reg("focusOfChildComponentChanged");
}

LComponent::~LComponent(){
    if (child) {
        child.release();
        child = nullptr;
    }
}

// get/set
int LComponent::setBounds(lua_State *L) {
    if(child)
        child->setBounds( LUA::getRectangle() );
    return 0;
}

int LComponent::getBounds(lua_State *L) {
    if (child)
        return LUA::returnTable( child->getBounds() );
    else return 0;
}

int LComponent::setSize(lua_State *L) {
    Array<var> b(LUA::getList());
    if(child)
        child->setSize( b[0], b[1] );
    return 0;
}

int LComponent::getSize(lua_State *L) {
    if(child) {
        return LUA::returnTable( child->getBounds() );
    }
    else return 0;
}

int LComponent::setVisible(lua_State *L) {
    if(child)
        child->setVisible( LUA::getBoolean() );
    return 0;
}

int LComponent::isVisible(lua_State*) {
    if(child)
        return LUA::getBoolean(child->isVisible());
    return 0;
}

int LComponent::addAndMakeVisible(lua_State *L) {
    if(child)
        child->addAndMakeVisible( LUA::to_juce<Component>(2) );
    return 0;
}

int LComponent::addChildComponent(lua_State *L) {
    if(child)
        child->addChildComponent( LUA::to_juce<Component>(2) );
    return 0;
}


// callbacks
int LComponent::repaint(lua_State *L) {
    if(child)
        child->repaint();
    lua_pop(L,1);
    return 0;
}

/////// getters/setters

int LComponent::getExplicitFocusOrder ( lua_State* ) {
    if (child)
        return LUA::returnNumber( child->getExplicitFocusOrder() );
    else 
        return 0;
}
int LComponent::setExplicitFocusOrder ( lua_State* ) {
    if (child)
        child->setExplicitFocusOrder(LUA::getNumber());
    return 0;
}

int LComponent::isFocusContainer ( lua_State* ) {
    if (child)
        return LUA::returnBoolean( child->isFocusContainer() );
    else return 0;
}
int LComponent::setFocusContainer ( lua_State* ) {
    if (child)
        child->setFocusContainer(LUA::getBoolean());
    return 0;
}

int LComponent::isOpaque ( lua_State* ) {
    if (child)
        return LUA::returnBoolean( child->isOpaque() );
    else return 0;
}
int LComponent::setOpaque ( lua_State* ) {
    if (child)
        child->setOpaque(LUA::getBoolean());
    return 0;
}

int LComponent::getComponentID ( lua_State* ) {
    if (child)
        return LUA::returnString( child->getComponentID() );
    else return 0;
}
int LComponent::setComponentID ( lua_State* ) {
    if (child)
        child->setComponentID(LUA::getString());
    return 0;
}

int LComponent::isEnabled ( lua_State* ) {
    if (child)
        return LUA::returnBoolean( child->isEnabled() );
    else return 0;
}
int LComponent::setEnabled ( lua_State* ) {
    if (child)
        child->setEnabled(LUA::getBoolean());
    return 0;
}

int LComponent::getAlpha ( lua_State* ) {
    if (child)
        return LUA::returnNumber( child->getAlpha() );
    else return 0;
}
int LComponent::setAlpha ( lua_State* ) {
    if (child)
        child->setAlpha(LUA::getNumber());
    return 0;
}

int LComponent::isAlwaysOnTop ( lua_State* ) {
    if (child)
        return LUA::returnBoolean( child->isAlwaysOnTop() );
    else return 0;
}
int LComponent::setAlwaysOnTop ( lua_State* ) {
    if (child)
        child->setAlwaysOnTop(LUA::getBoolean());
    return 0;
}

int LComponent::getWantsKeyboardFocus ( lua_State* ) {
    if (child)
        return LUA::returnBoolean( child->getWantsKeyboardFocus() );
    else return 0;
}
int LComponent::setWantsKeyboardFocus ( lua_State* ) {
    if (child)
        child->setWantsKeyboardFocus(LUA::getBoolean());
    return 0;
}

int LComponent::isBroughtToFrontOnMouseClick ( lua_State* ) {
    if (child)
        return LUA::returnBoolean( child->isBroughtToFrontOnMouseClick() );
    else return 0;
}
int LComponent::setBroughtToFrontOnMouseClick ( lua_State* ) {
    if (child)
        child->setBroughtToFrontOnMouseClick(LUA::getBoolean());
    return 0;
}

int LComponent::getMouseClickGrabsKeyboardFocus ( lua_State* ) {
    if (child)
        return LUA::returnBoolean( child->getMouseClickGrabsKeyboardFocus() );
    else return 0;
}
int LComponent::setMouseClickGrabsKeyboardFocus ( lua_State* ) {
    if (child)
        child->setMouseClickGrabsKeyboardFocus(LUA::getBoolean());
    return 0;
}

int LComponent::getName ( lua_State* ) {
    if (child)
        return LUA::returnString( child->getName() );
    else return 0;
}
int LComponent::setName ( lua_State* ) {
    if (child)
        child->setName(LUA::getString());
    return 0;
}

/////// getters
int LComponent::getRight ( lua_State* ) {
    if (child)
        return LUA::returnNumber( child->getRight() );
    else return 0;
}

int LComponent::getScreenPosition ( lua_State* ) {
    if (child)
        return LUA::returnTable( child->getScreenPosition() );
    else return 0;
}

int LComponent::proportionOfHeight ( lua_State* ) {
    if (child)
        return LUA::returnNumber( child->proportionOfHeight( LUA::getNumber() ) );
    else return 0;
}

int LComponent::getX ( lua_State* ) {
    if (child)
        return LUA::returnNumber( child->getX() );
    else return 0;
}

int LComponent::getY ( lua_State* ) {
    if (child)
        return LUA::returnNumber( child->getY() );
    else return 0;
}

int LComponent::getHeight ( lua_State* ) {
    if (child)
        return LUA::returnNumber( child->getHeight() );
    else return 0;
}

int LComponent::isMouseOver ( lua_State* ) {
    if (child)
        return LUA::returnBoolean( child->isMouseOver( LUA::checkAndGetBoolean(1, false) ) );
    else return 0;
}

int LComponent::reallyContains ( lua_State* ) {
    if (child) {
        Point<int> localPoint( LUA::getPoint() );
        bool returnTrueIfWithinAChild = LUA::getBoolean();
        return LUA::returnBoolean( child->reallyContains( localPoint, returnTrueIfWithinAChild ) );
    } else return 0;
}

int LComponent::localAreaToGlobal ( lua_State* ) {
    if (child)
        return LUA::returnTable( child->localAreaToGlobal( LUA::getRectangle() ) );
    else return 0;
}

int LComponent::getDesktopScaleFactor ( lua_State* ) {
    if (child) {
        return LUA::returnNumber( child->getDesktopScaleFactor() );
    } else return 0;
}

int LComponent::getParentWidth ( lua_State* ) {
    if (child)
        return LUA::returnNumber( child->getParentWidth() );
    else return 0;
}

int LComponent::getNumCurrentlyModalComponents ( lua_State* ) {
    if (child)
        return LUA::returnNumber( child->getNumCurrentlyModalComponents() );
    else return 0;
}

int LComponent::hasKeyboardFocus ( lua_State* ) {
    if (child)
        return LUA::returnBoolean( child->hasKeyboardFocus( LUA::getBoolean() ) );
    else return 0;
}

int LComponent::getScreenY ( lua_State* ) {
    if (child)
        return LUA::returnNumber( child->getScreenY() );
    else return 0;
}

int LComponent::hitTest ( lua_State* ) {
    Array<var> r( LUA::getList() );
    if (child)
        return LUA::returnBoolean( child->hitTest( r[0], r[1] ) );
    else return 0;
}

int LComponent::isMouseOverOrDragging ( lua_State* ) {
    if (child)
        return LUA::returnBoolean( child->isMouseOverOrDragging() );
    else return 0;
}

int LComponent::isTransformed ( lua_State* ) {
    if (child)
        return LUA::returnBoolean( child->isTransformed() );
    else return 0;
}

int LComponent::getWidth ( lua_State* ) {
    if (child)
        return LUA::returnNumber( child->getWidth() );
    else return 0;
}

int LComponent::getScreenBounds ( lua_State* ) {
    if (child)
        return LUA::returnTable( child->getScreenBounds() );
    else return 0;
}

int LComponent::getMouseXYRelative ( lua_State* ) {
    if (child)
        return LUA::returnTable( child->getMouseXYRelative() );
    else return 0;
}

int LComponent::keyStateChanged ( lua_State* ) {
    if (child)
        return LUA::returnBoolean( child->keyStateChanged( LUA::getBoolean() ) );
    else return 0;
}

int LComponent::getScreenX ( lua_State* ) {
    if (child)
        return LUA::returnNumber( child->getScreenX() );
    else return 0;
}

int LComponent::getParentMonitorArea ( lua_State* ) {
    if (child)
        return LUA::returnTable( child->getParentMonitorArea() );
    else return 0;
}

int LComponent::isColourSpecified ( lua_State* ) {
    if (child)
        return LUA::returnBoolean( child->isColourSpecified( LUA::getNumber() ) );
    else return 0;
}

int LComponent::isCurrentlyBlockedByAnotherModalComponent ( lua_State* ) {
    if (child)
        return LUA::returnBoolean( child->isCurrentlyBlockedByAnotherModalComponent() );
    else return 0;
}

int LComponent::getNumChildComponents ( lua_State* ) {
    if (child)
        return LUA::returnNumber( child->getNumChildComponents() );
    else return 0;
}

int LComponent::isMouseButtonDownAnywhere ( lua_State* ) {
    if (child)
        return LUA::returnBoolean( child->isMouseButtonDownAnywhere() );
    else return 0;
}

int LComponent::isMouseButtonDown ( lua_State* ) {
    if (child)
        return LUA::returnBoolean( child->isMouseButtonDown() );
    else return 0;
}

int LComponent::localPointToGlobal ( lua_State* ) {
    if (child)
        return LUA::returnTable( child->localPointToGlobal( LUA::getPoint() ) );
    else return 0;
}

int LComponent::getPosition ( lua_State* ) {
    if (child)
        return LUA::returnTable( child->getPosition() );
    else return 0;
}

int LComponent::getBoundsInParent ( lua_State* ) {
    if (child)
        return LUA::returnTable( child->getBoundsInParent() );
    else return 0;
}

int LComponent::getParentHeight ( lua_State* ) {
    if (child)
        return LUA::returnNumber( child->getParentHeight() );
    else return 0;
}

int LComponent::proportionOfWidth ( lua_State* ) {
    if (child) {
        float proportion = LUA::getNumber();
        return LUA::returnNumber( child->proportionOfWidth( proportion ) );
    } else return 0;
}

int LComponent::getBottom ( lua_State* ) {
    if (child)
        return LUA::returnNumber( child->getBottom() );
    else return 0;
}

int LComponent::contains ( lua_State* ) {
    if (child)
        return LUA::returnBoolean( child->contains( LUA::getPoint() ) );
    else return 0;
}

int LComponent::isShowing ( lua_State* ) {
    if (child)
        return LUA::returnBoolean( child->isShowing() );
    else return 0;
}

int LComponent::getLocalBounds ( lua_State* ) {
    if (child)
        return LUA::returnTable( child->getLocalBounds() );
    else return 0;
}

int LComponent::isCurrentlyModal ( lua_State* ) {
    if (child)
        return LUA::returnBoolean( child->isCurrentlyModal() );
    else return 0;
}

int LComponent::isOnDesktop ( lua_State* ) {
    if (child) {
        return LUA::returnBoolean( child->isOnDesktop() );
    } else return 0;
}

/////// setters
int LComponent::setBoundsInset ( lua_State* ) {
    Array<var> r(LUA::getList());
    if (child) {
        if ( r.size() == 1 ) {
            child->setBoundsInset( BorderSize<int>(r[0]) );
        } else if ( r.size() == 4 ) {
            child->setBoundsInset( BorderSize<int>(r[0], r[1], r[2], r[3] ) );
        } else {
            LUA::throwError("Wrong number of arguments");
        }
    }
    return 0;
}

int LComponent::setRepaintsOnMouseActivity ( lua_State* ) {
    if (child)
        child->setRepaintsOnMouseActivity(LUA::getBoolean());
    return 0;
}

int LComponent::toFront ( lua_State* ) {
    if (child)
        child->toFront(LUA::getBoolean());
    return 0;
}

int LComponent::setTopLeftPosition ( lua_State* ) {
    Point<int> r( LUA::getPoint() );
    if (child)
        child->setTopLeftPosition( r );
    return 0;
}

int LComponent::sendLookAndFeelChange ( lua_State* ) {
    if (child)
        child->sendLookAndFeelChange();
    return 0;
}

int LComponent::moveKeyboardFocusToSibling ( lua_State* ) {
    if (child) {
        child->moveKeyboardFocusToSibling(LUA::getBoolean());
    }
    return 0;
}

int LComponent::updateMouseCursor ( lua_State* ) {
    if (child)
        child->updateMouseCursor();
    return 0;
}

int LComponent::setPaintingIsUnclipped ( lua_State* ) {
    if (child)
        child->setPaintingIsUnclipped(LUA::getBoolean());
    return 0;
}

int LComponent::unfocusAllComponents ( lua_State* ) {
    if (child)
        child->unfocusAllComponents();
    return 0;
}

int LComponent::centreWithSize ( lua_State* ) {
    Array<var> r( LUA::getList() );
    if (child)
        child->centreWithSize( r[0], r[1] );
    return 0;
}

int LComponent::exitModalState ( lua_State* ) {
    if (child)
        child->exitModalState(LUA::getNumber());
    return 0;
}

int LComponent::setInterceptsMouseClicks ( lua_State* ) {
    if (child) {
        bool allowClicksOnThisComponent = LUA::getBoolean();
        bool allowClicksOnChildComponents = LUA::getBoolean();
        child->setInterceptsMouseClicks( allowClicksOnThisComponent, allowClicksOnChildComponents );
    }
    return 0;
}

int LComponent::setTopRightPosition ( lua_State* ) {
    Array<var> r(LUA::getList());
    if (child)
        child->setTopRightPosition( r[0], r[1] );
    return 0;
}

int LComponent::grabKeyboardFocus ( lua_State* ) {
    if (child)
        child->grabKeyboardFocus();
    return 0;
}

int LComponent::setBufferedToImage ( lua_State* ) {
    if (child)
        child->setBufferedToImage(LUA::getBoolean());
    return 0;
}

int LComponent::getInterceptsMouseClicks ( lua_State* ) {
    if (child) {
        bool allowsClicksOnThisComponent = LUA::getBoolean();
        bool allowsClicksOnChildComponents = LUA::getBoolean();
        child->getInterceptsMouseClicks( allowsClicksOnThisComponent, allowsClicksOnChildComponents );
    }
    return 0;
}

int LComponent::beginDragAutoRepeat ( lua_State* ) {
    if (child)
        child->beginDragAutoRepeat(LUA::getNumber());
    return 0;
}

int LComponent::deleteAllChildren ( lua_State* ) {
    if (child)
        child->deleteAllChildren();
    return 0;
}

int LComponent::removeColour ( lua_State* ) {
    if (child)
        child->removeColour(LUA::getNumber());
    return 0;
}

int LComponent::setBoundsRelative ( lua_State* ) {
    Array<var> r(LUA::getList());
    if (child)
        child->setBoundsRelative( r[0], r[1], r[2], r[3] );
    return 0;
}

int LComponent::setCentrePosition ( lua_State* ) {
    Array<var> r(LUA::getList());
    if (child)
        child->setCentrePosition( r[0], r[1] );
    return 0;
}

int LComponent::removeFromDesktop ( lua_State* ) {
    if (child) {
        child->removeFromDesktop();
    }
    return 0;
}

int LComponent::removeAllChildren ( lua_State* ) {
    if (child)
        child->removeAllChildren();
    return 0;
}

int LComponent::postCommandMessage ( lua_State* ) {
    if (child)
        child->postCommandMessage(LUA::getNumber());
    return 0;
}

int LComponent::setCentreRelative ( lua_State* ) {
    Array<var> r(LUA::getList());
    if (child)
        child->setCentreRelative( r[0], r[1] );
    return 0;
}

int LComponent::toBack ( lua_State* ) {
    if (child)
        child->toBack();
    return 0;
}

/////// callbacks
void LComponent::lchildrenChanged() {
    if (child)
        callback("childrenChanged");
}
int LComponent::childrenChanged(lua_State*){
    if (child)
        set("childrenChanged");
    return 0;
}

void LComponent::lparentHierarchyChanged() {
    if (child)
        callback("parentHierarchyChanged");
}
int LComponent::parentHierarchyChanged(lua_State*){
    if (child)
        set("parentHierarchyChanged");
    return 0;
}

void LComponent::lcolourChanged() {
    if (child)
        callback("colourChanged");
}
int LComponent::colourChanged(lua_State*){
    if (child)
        set("colourChanged");
    return 0;
}

void LComponent::llookAndFeelChanged() {
    if (child)
        callback("lookAndFeelChanged");
}
int LComponent::lookAndFeelChanged(lua_State*){
    if (child)
        set("lookAndFeelChanged");
    return 0;
}

void LComponent::luserTriedToCloseWindow() {
    if (child)
        callback("userTriedToCloseWindow");
}
int LComponent::userTriedToCloseWindow(lua_State*){
    if (child)
        set("userTriedToCloseWindow");
    return 0;
}

void LComponent::lmodifierKeysChanged( const ModifierKeys& modifiers ) {
    if (child)
        callback("modifierKeysChanged");
}
int LComponent::modifierKeysChanged(lua_State*){
    if (child)
        set("modifierKeysChanged");
    return 0;
}

void LComponent::lbroughtToFront() {
    if (child)
        callback("broughtToFront");
}
int LComponent::broughtToFront(lua_State*){
    if (child)
        set("broughtToFront");
    return 0;
}

void LComponent::lparentSizeChanged() {
    if (child)
        callback("parentSizeChanged");
}
int LComponent::parentSizeChanged(lua_State*){
    if (child)
        set("parentSizeChanged");
    return 0;
}

void LComponent::lvisibilityChanged() {
    if (child)
        callback("visibilityChanged");
}
int LComponent::visibilityChanged(lua_State*){
    if (child)
        set("visibilityChanged");
    return 0;
}

void LComponent::linputAttemptWhenModal() {
    if (child)
        callback("inputAttemptWhenModal");
}
int LComponent::inputAttemptWhenModal(lua_State*){
    if (child)
        set("inputAttemptWhenModal");
    return 0;
}

void LComponent::lpaint( Graphics& g ) {
    if (child)
        callback("paint");
}
int LComponent::paint(lua_State*) {
    if (child)
        set("paint");
    return 0;
}

void LComponent::lhandleCommandMessage( int commandId ) {
    if (child)
        callback("handleCommandMessage");
}
int LComponent::handleCommandMessage(lua_State*){
    if (child)
        set("handleCommandMessage");
    return 0;
}

void LComponent::lresized() {
    if (child)
        callback("resized");
}
int LComponent::resized(lua_State*){
    if (child)
        set("resized");
    return 0;
}

void LComponent::lfocusGained( Component::FocusChangeType cause ) {
    if (child)
        callback("focusGained");
}
int LComponent::focusGained(lua_State*){
    if (child)
        set("focusGained");
    return 0;
}

void LComponent::lpaintOverChildren( Graphics& g ) {
    if (child)
        callback("paintOverChildren");
}
int LComponent::paintOverChildren(lua_State*){
    if (child)
        set("paintOverChildren");
    return 0;
}

void LComponent::lmoved() {
    if (child)
        callback("moved");
}
int LComponent::moved(lua_State*){
    if (child)
        set("moved");
    return 0;
}

void LComponent::lchildBoundsChanged( Component* child ) {
    if (child)
        callback("childBoundsChanged");
}
int LComponent::childBoundsChanged(lua_State*){
    if (child)
        set("childBoundsChanged");
    return 0;
}

void LComponent::lfocusLost( Component::FocusChangeType cause ) {
    if (child)
        callback("focusLost");
}
int LComponent::focusLost(lua_State*){
    if (child)
        set("focusLost");
    return 0;
}

int LComponent::addMouseListener ( lua_State* ) {
    if (child) child->addMouseListener( child, LUA::checkAndGetBoolean(2, false) );
    return 0;
}

int LComponent::removeMouseListener ( lua_State* ) {
    if (child) child->removeMouseListener(child);
    return 0;
}

void LComponent::lmouseMove( const MouseEvent& event ) {
    if (child) callback("mouseMove");
}
int LComponent::mouseMove(lua_State*){
    if (child) set("mouseMove");
    return 0;
}

void LComponent::lmouseEnter( const MouseEvent& event ) {
    if (child)
        callback("mouseEnter");
}
int LComponent::mouseEnter(lua_State*){
    if (child)
        set("mouseEnter");
    return 0;
}

void LComponent::lmouseExit( const MouseEvent& event ) {
    if (child) callback("mouseExit");
}
int LComponent::mouseExit(lua_State*){
    if (child) set("mouseExit");
    return 0;
}

void LComponent::lmouseDown( const MouseEvent& event ) {
    if (child) callback("mouseDown");
}
int LComponent::mouseDown(lua_State*){
    if (child) set("mouseDown");
    return 0;
}

void LComponent::lmouseDrag( const MouseEvent& event ) {
    if (child) callback("mouseDrag");
}
int LComponent::mouseDrag(lua_State*){
    if (child) set("mouseDrag");
    return 0;
}

void LComponent::lmouseUp( const MouseEvent& event ) {
    if (child) callback("mouseUp");
}
int LComponent::mouseUp(lua_State*){
    if (child) set("mouseUp");
    return 0;
}

void LComponent::lmouseDoubleClick( const MouseEvent& e ) {
    if (child)
        callback("mouseDoubleClick", 0, { new LRefBase("MouseEvent", new MouseEvent(e)) } );
}
int LComponent::mouseDoubleClick(lua_State*) {
    if (child) set("mouseDoubleClick");
    return 0;
}

void LComponent::lmouseWheelMove( const MouseEvent& event,const MouseWheelDetails& wheel ) {
    if (child) callback("mouseWheelMove");
}
int LComponent::mouseWheelMove(lua_State*) {
    if (child) set("mouseWheelMove");
    return 0;
}

void LComponent::lmouseMagnify( const MouseEvent& event,float scaleFactor ) {
    if (child) callback("mouseMagnify");
}
int LComponent::mouseMagnify(lua_State*) {
    if (child) set("mouseMagnify");
    return 0;
}

void LComponent::lminimisationStateChanged( bool isNowMinimised ) {
    if (child)
        callback("minimisationStateChanged");
}
int LComponent::minimisationStateChanged(lua_State*){
    if (child)
        set("minimisationStateChanged");
    return 0;
}

void LComponent::lenablementChanged() {
    if (child)
        callback("enablementChanged");
}
int LComponent::enablementChanged(lua_State*){
    if (child)
        set("enablementChanged");
    return 0;
}

void LComponent::lfocusOfChildComponentChanged( Component::FocusChangeType cause ) {
    if (child)
        callback("focusOfChildComponentChanged");
}
int LComponent::focusOfChildComponentChanged(lua_State*){
    if (child)
        set("focusOfChildComponentChanged");
    return 0;
}

/// TODO

// get/set
int LComponent::getLookAndFeel ( lua_State* ) {
    if (child) {
        // return LUA::TODO_RETURN_OBJECT_LookAndFeel( child->getLookAndFeel() );
        lua_settop(LUA::Get(), 1); // added by TODO
        return LUA::TODO_OBJECT( "LookAndFeel getLookAndFeel()" );
    } else return 0;
}
int LComponent::setLookAndFeel ( lua_State* ) {
    if (child) {
        int lnf = LUA::getNumber();
        switch ( lnf ) {
            case 1:
                child->setLookAndFeel(&lookAndFeelV1);
                break;
            case 2:
                child->setLookAndFeel(&lookAndFeelV2);
                break;
            case 3:
                child->setLookAndFeel(&lookAndFeelV3);
                break;
            case 4:
                child->setLookAndFeel(&myLookAndFeel);
                break;
            default:
                LUA::throwError("Unknown LookAndFeel");
                break;
        }
    }
    return 0;
}

int LComponent::getComponentEffect ( lua_State* ) {
    if (child) {
        // return LUA::TODO_RETURN_OBJECT_ImageEffectFilter( child->getComponentEffect() );
        lua_settop(LUA::Get(), 1); // added by TODO
        return LUA::TODO_OBJECT( "ImageEffectFilter getComponentEffect()" );
    } else return 0;
}
int LComponent::setComponentEffect ( lua_State* ) {
    if (child) {
        // child->setComponentEffect(LUA::TODO_OBJECT_ImageEffectFilter);
        LUA::TODO_OBJECT( "setComponentEffect, LUA::TODO_OBJECT_ImageEffectFilter" );
        lua_settop(LUA::Get(), 1); // added by TODO
    }
    return 0;
}

int LComponent::getPositioner ( lua_State* ) {
    if (child) {
        // return LUA::TODO_RETURN_OBJECT_Positioner( child->getPositioner() );
        lua_settop(LUA::Get(), 1); // added by TODO
        return LUA::TODO_OBJECT( "Positioner getPositioner()" );
    } else return 0;
}
int LComponent::setPositioner ( lua_State* ) {
    if (child) {
        // child->setPositioner(LUA::TODO_OBJECT_Positioner);
        LUA::TODO_OBJECT( "setPositioner, LUA::TODO_OBJECT_Positioner" );
        lua_settop(LUA::Get(), 1); // added by TODO
    }
    return 0;
}

int LComponent::getTransform ( lua_State* ) {
    if (child) {
        // return LUA::TODO_RETURN_OBJECT_AffineTransform( child->getTransform() );
        lua_settop(LUA::Get(), 1); // added by TODO
        return LUA::TODO_OBJECT( "AffineTransform getTransform()" );
    } else return 0;
}
int LComponent::setTransform ( lua_State* ) {
    if (child) {
        // child->setTransform(LUA::TODO_OBJECT_AffineTransform);
        LUA::TODO_OBJECT( "setTransform, LUA::TODO_OBJECT_AffineTransform" );
        lua_settop(LUA::Get(), 1); // added by TODO
    }
    return 0;
}

int LComponent::getMouseCursor ( lua_State* ) {
    if (child) {
        // return LUA::TODO_RETURN_OBJECT_MouseCursor( child->getMouseCursor() );
        lua_settop(LUA::Get(), 1); // added by TODO
        return LUA::TODO_OBJECT( "MouseCursor getMouseCursor()" );
    } else return 0;
}
int LComponent::setMouseCursor ( lua_State* ) {
    if (child) {
        // child->setMouseCursor(LUA::TODO_OBJECT_MouseCursor);
        LUA::TODO_OBJECT( "setMouseCursor, LUA::TODO_OBJECT_MouseCursor" );
        lua_settop(LUA::Get(), 1); // added by TODO
    }
    return 0;
}

int LComponent::getCachedComponentImage ( lua_State* ) {
    if (child) {
        // return LUA::TODO_RETURN_OBJECT_CachedComponentImage( child->getCachedComponentImage() );
        lua_settop(LUA::Get(), 1); // added by TODO
        return LUA::TODO_OBJECT( "CachedComponentImage getCachedComponentImage()" );
    } else return 0;
}
int LComponent::setCachedComponentImage ( lua_State* ) {
    if (child) {
        // child->setCachedComponentImage(LUA::TODO_OBJECT_CachedComponentImage);
        LUA::TODO_OBJECT( "setCachedComponentImage, LUA::TODO_OBJECT_CachedComponentImage" );
        lua_settop(LUA::Get(), 1); // added by TODO
    }
    return 0;
}

/// getters
int LComponent::findColour ( lua_State* ) {
    if (child) {
        int colourId = LUA::getNumber(2);
        bool inheritFromParent = LUA::checkAndGetBoolean(2, false);
        //return LUA::returnString( (child->findColour( colourId, inheritFromParent )).toString() );
        return LUA::returnString( (child->findColour( colourId, inheritFromParent )).toDisplayString(true) );
    } else return 0;
}

int LComponent::getProperties ( lua_State* ) {
    
    // override
    if (child) {
        // return LUA::TODO_RETURN_OBJECT_NamedValueSet( child->getProperties() );
        lua_settop(LUA::Get(), 1); // added by TODO
        return LUA::TODO_OBJECT( "NamedValueSet getProperties()" );
    } else return 0;
    
    // override
    if (child) {
        // return LUA::TODO_RETURN_OBJECT_NamedValueSet( child->getProperties() );
        lua_settop(LUA::Get(), 1); // added by TODO
        return LUA::TODO_OBJECT( "NamedValueSet getProperties()" );
    } else return 0;
}

int LComponent::isParentOf ( lua_State* ) {
    if (child) {
        // Component* possibleChild = LUA::TODO_OBJECT_Component;
        // return LUA::returnBoolean( child->isParentOf( possibleChild ) );
        lua_settop(LUA::Get(), 1); // added by TODO
        return LUA::TODO_OBJECT( "bool isParentOf( possibleChild )" );
    } else return 0;
}

int LComponent::createComponentSnapshot ( lua_State* ) {
    if (child) {
        // Rectangle<int> areaToGrab = LUA::TODO_OBJECT_Rectangle;
        bool clipImageToComponentBounds = LUA::checkAndGetBoolean(2, true);
        float scaleFactor = LUA::checkAndGetNumber(3, 1.0f);
        // return LUA::TODO_RETURN_OBJECT_Image( child->createComponentSnapshot( areaToGrab, clipImageToComponentBounds, scaleFactor ) );
        lua_settop(LUA::Get(), 1); // added by TODO
        return LUA::TODO_OBJECT( "Image createComponentSnapshot( areaToGrab, clipImageToComponentBounds, scaleFactor )" );
    } else return 0;
}

int LComponent::addComponentListener ( lua_State* ) {
    if (child) {
        // child->addComponentListener(LUA::TODO_OBJECT_ComponentListener);
        LUA::TODO_OBJECT( "addComponentListener, LUA::TODO_OBJECT_ComponentListener" );
        lua_settop(LUA::Get(), 1); // added by TODO
    }
    return 0;
}

int LComponent::getTopLevelComponent ( lua_State* ) {
    if (child) {
        // return LUA::TODO_RETURN_OBJECT_Component( child->getTopLevelComponent() );
        lua_settop(LUA::Get(), 1); // added by TODO
        return LUA::TODO_OBJECT( "Component getTopLevelComponent()" );
    } else return 0;
}

int LComponent::getCurrentlyModalComponent ( lua_State* ) {
    if (child) {
        int index = LUA::checkAndGetNumber(1, 0);
        // return LUA::TODO_RETURN_OBJECT_Component( child->getCurrentlyModalComponent( index ) );
        lua_settop(LUA::Get(), 1); // added by TODO
        return LUA::TODO_OBJECT( "Component getCurrentlyModalComponent( index )" );
    } else return 0;
}

int LComponent::findChildWithID ( lua_State* ) {
    if (child) {
        // StringRef componentID = LUA::TODO_OBJECT_StringRef;
        // return LUA::TODO_RETURN_OBJECT_Component( child->findChildWithID( componentID ) );
        lua_settop(LUA::Get(), 1); // added by TODO
        return LUA::TODO_OBJECT( "Component findChildWithID( componentID )" );
    } else return 0;
}

int LComponent::getLocalPoint ( lua_State* ) {
    if (child) {
        // Component* sourceComponent = LUA::TODO_OBJECT_Component;
        // Point<int> pointRelativeToSourceComponent = LUA::TODO_OBJECT_Point;
        // return LUA::TODO_RETURN_OBJECT_Point( child->getLocalPoint( sourceComponent, pointRelativeToSourceComponent ) );
        lua_settop(LUA::Get(), 1); // added by TODO
        return LUA::TODO_OBJECT( "Point getLocalPoint( sourceComponent, pointRelativeToSourceComponent )" );
    } else return 0;
}

int LComponent::getComponentAt ( lua_State* ) {
    
    // override
    if (child) {
        int x = LUA::getNumber(1);
        int y = LUA::getNumber(2);
        // return LUA::TODO_RETURN_OBJECT_Component( child->getComponentAt( x, y ) );
        lua_settop(LUA::Get(), 1); // added by TODO
        return LUA::TODO_OBJECT( "Component getComponentAt( x, y )" );
    } else return 0;
    
    // override
    if (child) {
        // Point<int> position = LUA::TODO_OBJECT_Point;
        // return LUA::TODO_RETURN_OBJECT_Component( child->getComponentAt( position ) );
        lua_settop(LUA::Get(), 1); // added by TODO
        return LUA::TODO_OBJECT( "Component getComponentAt( position )" );
    } else return 0;
}

int LComponent::copyAllExplicitColoursTo ( lua_State* ) {
    if (child) {
        // child->copyAllExplicitColoursTo(LUA::TODO_OBJECT_Component);
        LUA::TODO_OBJECT( "copyAllExplicitColoursTo, LUA::TODO_OBJECT_Component" );
        lua_settop(LUA::Get(), 1); // added by TODO
    }
    return 0;
}

int LComponent::addToDesktop ( lua_State* ) {
    if (child) {
        int windowStyleFlags = LUA::getNumber(2);
        // void* nativeWindowToAttachTo = LUA::TODO_OBJECT_void;
        // child->addToDesktop( windowStyleFlags, nativeWindowToAttachTo );
        LUA::TODO_OBJECT( "addToDesktop,  windowStyleFlags, nativeWindowToAttachTo " );
        lua_settop(LUA::Get(), 1); // added by TODO
    }
    return 0;
}

int LComponent::setBoundsToFit ( lua_State* ) {
    if (child) {
        Array<var> r(LUA::getList());
        // Justification justification = LUA::TODO_OBJECT_Justification;
        // bool onlyReduceInSize = LUA::getBoolean();
        // child->setBoundsToFit( r[0], r[1], r[2], r[3], justification, onlyReduceInSize );
        LUA::TODO_OBJECT( "setBoundsToFit,  x, y, width, height, justification, onlyReduceInSize " );
        lua_settop(LUA::Get(), 1); // added by TODO
    }
    return 0;
}

int LComponent::addChildAndSetID ( lua_State* ) {
    if (child) {
        // Component* child = LUA::TODO_OBJECT_Component;
        String componentID = LUA::getString(3);
        // child->addChildAndSetID( child, componentID );
        LUA::TODO_OBJECT( "addChildAndSetID,  child, componentID " );
        lua_settop(LUA::Get(), 1); // added by TODO
    }
    return 0;
}

int LComponent::setColour ( lua_State* ) {
    if (child) {
        int id = LUA::getNumber(2);
        if ( lua_isnumber(L, -1) ) {
            // TODO: convert from lua number (double) to uint32
            var val = LUA::getNumber();
            //std::cout << "val: " << val << std::endl;
            //child->setColour( id, Colour( (uint32)((int)val)) );
        } else if ( lua_isstring(L, -1) ) {
            String name = LUA::getString();
            child->setColour( id, Colours::findColourForName( name, Colours::transparentWhite ) );
        } else {
            LUA::throwError( "Missing colour value (name or ARGB)" );
        }
    }
    return 0;
}

int LComponent::paintEntireComponent ( lua_State* ) {
    if (child) {
        // Graphics context = LUA::TODO_OBJECT_Graphics;
        bool ignoreAlphaLevel = LUA::getBoolean(3);
        // child->paintEntireComponent( context, ignoreAlphaLevel );
        LUA::TODO_OBJECT( "paintEntireComponent,  context, ignoreAlphaLevel " );
        lua_settop(LUA::Get(), 1); // added by TODO
    }
    return 0;
}

int LComponent::toBehind ( lua_State* ) {
    if (child) {
        // child->toBehind(LUA::TODO_OBJECT_Component);
        LUA::TODO_OBJECT( "toBehind, LUA::TODO_OBJECT_Component" );
        lua_settop(LUA::Get(), 1); // added by TODO
    }
    return 0;
}

int LComponent::getVisibleArea ( lua_State* ) {
    if (child) {
        //bool includeSiblings = LUA::getBoolean();
        //Rectangle<int> result;
        //child->getVisibleArea( result, includeSiblings );
        //return returnTable( result );
        LUA::TODO_OBJECT( "getVisibleArea, LUA::TODO_OBJECT_RectangleList" );
        lua_settop(LUA::Get(), 1); // added by TODO
    }
    return 0;
}

int LComponent::getChildComponent ( lua_State* ) {
    if (child) {
        int index = LUA::getNumber(1);
        // return LUA::TODO_RETURN_OBJECT_Component( child->getChildComponent( index ) );
        lua_settop(LUA::Get(), 1); // added by TODO
        return LUA::TODO_OBJECT( "Component getChildComponent( index )" );
    } else return 0;
}

int LComponent::getLocalArea ( lua_State* ) {
    if (child) {
        // Component* sourceComponent = LUA::TODO_OBJECT_Component;
        // Rectangle<int> areaRelativeToSourceComponent = LUA::TODO_OBJECT_Rectangle;
        // return LUA::TODO_RETURN_OBJECT_Rectangle( child->getLocalArea( sourceComponent, areaRelativeToSourceComponent ) );
        lua_settop(LUA::Get(), 1); // added by TODO
        return LUA::TODO_OBJECT( "Rectangle getLocalArea( sourceComponent, areaRelativeToSourceComponent )" );
    } else return 0;
}

int LComponent::canModalEventBeSentToComponent ( lua_State* ) {
    if (child) {
        // Component* targetComponent = LUA::TODO_OBJECT_Component;
        // return LUA::returnBoolean( child->canModalEventBeSentToComponent( targetComponent ) );
        lua_settop(LUA::Get(), 1); // added by TODO
        return LUA::TODO_OBJECT( "bool canModalEventBeSentToComponent( targetComponent )" );
    } else return 0;
}

int LComponent::findParentComponentOfClass ( lua_State* ) {
    if (child) {
        // return LUA::TODO_RETURN_OBJECT_TargetClass( child->findParentComponentOfClass() );
        lua_settop(LUA::Get(), 1); // added by TODO
        return LUA::TODO_OBJECT( "TargetClass findParentComponentOfClass()" );
    } else return 0;
}

int LComponent::createFocusTraverser ( lua_State* ) {
    if (child) {
        // return LUA::TODO_RETURN_OBJECT_KeyboardFocusTraverser( child->createFocusTraverser() );
        lua_settop(LUA::Get(), 1); // added by TODO
        return LUA::TODO_OBJECT( "KeyboardFocusTraverser createFocusTraverser()" );
    } else return 0;
}

int LComponent::getMarkers ( lua_State* ) {
    if (child) {
        bool xAxis = LUA::getBoolean(1);
        // return LUA::TODO_RETURN_OBJECT_MarkerList( child->getMarkers( xAxis ) );
        lua_settop(LUA::Get(), 1); // added by TODO
        return LUA::TODO_OBJECT( "MarkerList getMarkers( xAxis )" );
    } else return 0;
}

int LComponent::getIndexOfChildComponent ( lua_State* ) {
    if (child) {
        // Component* child = LUA::TODO_OBJECT_Component;
        // return LUA::returnNumber( child->getIndexOfChildComponent( child ) );
        lua_settop(LUA::Get(), 1); // added by TODO
        return LUA::TODO_OBJECT( "int getIndexOfChildComponent( child )" );
    } else return 0;
}

int LComponent::keyPressed ( lua_State* ) {
    if (child) {
        // KeyPress key = LUA::TODO_OBJECT_KeyPress;
        // return LUA::returnBoolean( child->keyPressed( key ) );
        lua_settop(LUA::Get(), 1); // added by TODO
        return LUA::TODO_OBJECT( "bool keyPressed( key )" );
    } else return 0;
}

int LComponent::getPeer ( lua_State* ) {
    if (child) {
        // return LUA::TODO_RETURN_OBJECT_ComponentPeer( child->getPeer() );
        lua_settop(LUA::Get(), 1); // added by TODO
        return LUA::TODO_OBJECT( "ComponentPeer getPeer()" );
    } else return 0;
}

int LComponent::getParentComponent ( lua_State* ) {
    if (child) {
        // return LUA::TODO_RETURN_OBJECT_Component( child->getParentComponent() );
        lua_settop(LUA::Get(), 1); // added by TODO
        return LUA::TODO_OBJECT( "Component getParentComponent()" );
    } else return 0;
}

int LComponent::getCurrentlyFocusedComponent ( lua_State* ) {
    if (child) {
        // return LUA::TODO_RETURN_OBJECT_Component( child->getCurrentlyFocusedComponent() );
        lua_settop(LUA::Get(), 1); // added by TODO
        return LUA::TODO_OBJECT( "Component getCurrentlyFocusedComponent()" );
    } else return 0;
}

/// setters
int LComponent::enterModalState ( lua_State* ) {
    if (child) {
        bool takeKeyboardFocus = LUA::checkAndGetBoolean(2, true);
        // ModalComponentManager::Callback* callback = LUA::TODO_OBJECT_ModalComponentManager::Callback;
        bool deleteWhenDismissed = LUA::checkAndGetBoolean(4, false);
        // child->enterModalState( takeKeyboardFocus, callback, deleteWhenDismissed );
        LUA::TODO_OBJECT( "enterModalState,  takeKeyboardFocus, callback, deleteWhenDismissed " );
        lua_settop(LUA::Get(), 1); // added by TODO
    }
    return 0;
}

int LComponent::addKeyListener ( lua_State* ) {
    if (child) {
        // child->addKeyListener(LUA::TODO_OBJECT_KeyListener);
        LUA::TODO_OBJECT( "addKeyListener, LUA::TODO_OBJECT_KeyListener" );
        lua_settop(LUA::Get(), 1); // added by TODO
    }
    return 0;
}

int LComponent::removeKeyListener ( lua_State* ) {
    if (child) {
        // child->removeKeyListener(LUA::TODO_OBJECT_KeyListener);
        LUA::TODO_OBJECT( "removeKeyListener, LUA::TODO_OBJECT_KeyListener" );
        lua_settop(LUA::Get(), 1); // added by TODO
    }
    return 0;
}

int LComponent::getWindowHandle ( lua_State* ) {
    if (child) {
        // return void* child->getWindowHandle();
        return LUA::TODO_OBJECT( "void* getWindowHandle()" );
    }
    return 0;
}

int LComponent::removeComponentListener ( lua_State* ) {
    if (child) child->removeMouseListener(child);
    return 0;
}


