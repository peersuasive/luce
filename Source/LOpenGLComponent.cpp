/************************************************************

 LOpenGLComponent.cpp

    @author Christophe Berbizier (cberbizier@peersuasive.com)
    @license GPLv3
    @copyright 


(c) 2013, Peersuasive Technologies

*************************************************************/

#include "LOpenGLComponent_inh.h"
const char LOpenGLComponent::className[] = "LOpenGLComponent";

const Luna<LOpenGLComponent>::PropertyType LOpenGLComponent::properties[] = {
    { "swapInterval", &LOpenGLComponent::getSwapInterval, &LOpenGLComponent::setSwapInterval },
    {0,0}
};

const Luna<LOpenGLComponent>::FunctionType LOpenGLComponent::methods[] = {
    method(LOpenGLComponent, newOpenGLContextCreated),
    method(LOpenGLComponent, openGLContextClosing),
    method(LOpenGLComponent, renderOpenGL),

    method(LOpenGLComponent, triggerRepaint),
    method(LOpenGLComponent, setContinuousRepainting),
    method(LOpenGLComponent, swapBuffers),

    method(LOpenGLComponent, setSwapInterval),
    method(LOpenGLComponent, getSwapInterval),


    method(LOpenGLComponent, setMultisamplingEnabled),
    method(LOpenGLComponent, areShadersAvailable),

    method(LOpenGLComponent, getRenderingScale),
    method(LOpenGLComponent, copyTexture),

    method(LOpenGLComponent, isActive),
    method(LOpenGLComponent, makeActive),

    method(LOpenGLComponent, attach),
    method(LOpenGLComponent, attachTo),
    method(LOpenGLComponent, detach),
    method(LOpenGLComponent, setComponentPaintingEnabled),
    method(LOpenGLComponent, getTargetComponent),
    // TODO: setPixelFormat

    {0,0}
};

const Luna<LOpenGLComponent>::StaticType LOpenGLComponent::statics[] = {
    {0,0}
};

LOpenGLComponent::LOpenGLComponent(lua_State *L) 
    : LComponent(L, this),
      Component()
{
    Component::setName(myName());

    Component::setOpaque(true); // test perfs without
    
    openGLContext.setRenderer(this);
    openGLContext.setComponentPaintingEnabled(false);
    openGLContext.setMultisamplingEnabled(true);
    openGLContext.setContinuousRepainting(true);

    //openGLContext.attachTo(*this);
    //openGLContext.attachTo(*Component::getTopLevelComponent());

    REGISTER_CLASS(LOpenGLComponent);
}

LOpenGLComponent::~LOpenGLComponent() {
    // remove opengl stuff
    openGLContext.detach();
    Component::deleteAllChildren();
}

void LOpenGLComponent::newOpenGLContextCreated() {
    if(hasCallback("newOpenGLContextCreated"))
        callback("newOpenGLContextCreated");
}
int LOpenGLComponent::newOpenGLContextCreated(lua_State*) {
    set("newOpenGLContextCreated");
    return 0;
}

void LOpenGLComponent::renderOpenGL() {
    callback("renderOpenGL");
}
int LOpenGLComponent::renderOpenGL(lua_State*) {
    set("renderOpenGL");
    return 0;
}

void LOpenGLComponent::openGLContextClosing() {
    if(hasCallback("openGLContextClosing"))
        callback("openGLContextClosing");
}
int LOpenGLComponent::openGLContextClosing(lua_State*) {
    set("openGLContextClosing");
    return 0;
}

int LOpenGLComponent::triggerRepaint(lua_State*) {
    openGLContext.triggerRepaint();
    return 0;
}

int LOpenGLComponent::setContinuousRepainting(lua_State*) {
    openGLContext.setContinuousRepainting(LUA::getBoolean(2));
    return 0;
}

int LOpenGLComponent::swapBuffers(lua_State*) {
    openGLContext.swapBuffers();
    return 0;
}

int LOpenGLComponent::setSwapInterval(lua_State*) {
    return LUA::returnBoolean( openGLContext.setSwapInterval(LUA::getNumber<int>(2)) );
}
int LOpenGLComponent::getSwapInterval(lua_State*) {
    return LUA::returnNumber(openGLContext.getSwapInterval());
}

int LOpenGLComponent::setMultisamplingEnabled(lua_State*) {
    openGLContext.setMultisamplingEnabled(LUA::getBoolean(2));
    return 0;
}

int LOpenGLComponent::areShadersAvailable(lua_State*) {
    return LUA::returnBoolean( openGLContext.areShadersAvailable() );
}

int LOpenGLComponent::getRenderingScale(lua_State*) {
    return LUA::returnNumber( openGLContext.getRenderingScale() );
}

int LOpenGLComponent::copyTexture(lua_State*) {
    Rectangle<int> targetClipArea = LUCE::luce_torectangle<int>(2);
    Rectangle<int> anchorPosAndTextureSize = LUCE::luce_torectangle<int>(2);
    int contextWidth = LUA::getNumber<int>(2);
    int contextHeight = LUA::getNumber<int>(2);
    bool textureOriginBottomLeft = LUA::getBoolean(2);

    openGLContext.copyTexture( targetClipArea, anchorPosAndTextureSize, 
                contextWidth, contextHeight, textureOriginBottomLeft );
    return 0;
}

int LOpenGLComponent::isActive(lua_State*) {
    return LUA::returnBoolean( openGLContext.isActive() );
}
int LOpenGLComponent::makeActive(lua_State*) {
    openGLContext.makeActive();
    return 0;
}

int LOpenGLComponent::attach(lua_State*) {
    openGLContext.attachTo( *this );
    return 0;
}
int LOpenGLComponent::attachTo(lua_State*) {
    if(openGLContext.isAttached())
        openGLContext.detach();
    openGLContext.attachTo( *LUA::from_luce<LJComponent>(2) );
    return 0;
}

int LOpenGLComponent::detach(lua_State*) {
    openGLContext.detach();
    return 0;
}

int LOpenGLComponent::setComponentPaintingEnabled(lua_State*) {
    openGLContext.setComponentPaintingEnabled(LUA::getBoolean(2));
    return 0;
}

int LOpenGLComponent::getTargetComponent(lua_State*) {
    return LUA::returnUserdata<LJComponent>( openGLContext.getTargetComponent() );
}


// TODO: setPixelFormat

void LOpenGLComponent::paint(Graphics& g) {
    if ( hasCallback("paint") ) {
        LComponent::lpaint(g);
    } else {
        Component::paint(g);
    }
}

void LOpenGLComponent::resized() {
    if ( hasCallback("resized") ) {
        LComponent::lresized();
    } else {
        Component::resized();
    }
}

void LOpenGLComponent::mouseMove(const MouseEvent& e) {
    if ( hasCallback("mouseMove") ) {
        LComponent::lmouseMove(e);
    } else {
        Component::mouseMove(e);
    }
}

void LOpenGLComponent::mouseEnter(const MouseEvent& e) {
    if ( hasCallback("mouseEnter") ) {
        LComponent::lmouseEnter(e);
    } else {
        Component::mouseEnter(e);
    }
}

void LOpenGLComponent::mouseExit(const MouseEvent& e) {
    if ( hasCallback("mouseExit") ) {
        LComponent::lmouseExit(e);
    } else {
        Component::mouseExit(e);
    }
}

void LOpenGLComponent::mouseDown(const MouseEvent& e) {
    if ( hasCallback("mouseDown") ) {
        LComponent::lmouseDown(e);
    } else {
        Component::mouseDown(e);
    }
}

void LOpenGLComponent::mouseDrag(const MouseEvent& e) {
    if ( hasCallback("mouseDrag") )
        LComponent::lmouseDrag(e);
}

void LOpenGLComponent::mouseUp(const MouseEvent& e) {
    if ( hasCallback("mouseUp") ) {
        LComponent::lmouseUp(e);
    } else {
        Component::mouseUp(e);
    }
}

void LOpenGLComponent::mouseDoubleClick(const MouseEvent& e) {
    if ( hasCallback("mouseDoubleClick") ) {
        LComponent::lmouseDoubleClick(e);
    } else {
        Component::mouseDoubleClick(e);
    }
}

void LOpenGLComponent::mouseWheelMove (const MouseEvent& e, const MouseWheelDetails& wheel) {
    if ( hasCallback("mouseWheelMove") ) {
        LComponent::lmouseWheelMove(e, wheel);
    } else {
        Component::mouseWheelMove(e, wheel);
    }
}

void LOpenGLComponent::mouseMagnify (const MouseEvent& e, float scaleFactor) {
    if ( hasCallback("mouseMagnify") ) {
        LComponent::lmouseMagnify(e, scaleFactor);
    } else {
        Component::mouseMagnify(e, scaleFactor);
    }
}
