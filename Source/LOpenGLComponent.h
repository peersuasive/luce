/************************************************************

 LOpenGLComponent.h

    @author Christophe Berbizier (cberbizier@peersuasive.com)
    @license GPLv3
    @copyright 


(c) 2013, Peersuasive Technologies

*************************************************************/

#ifndef __LUCE_OPENGL_COMPONENT_WINDOW_H
#define __LUCE_OPENGL_COMPONENT_WINDOW_H

class LOpenGLComponent : public LComponent,
                         public Component,
                         private OpenGLRenderer
{
public:
    LOpenGLComponent(lua_State*);
    ~LOpenGLComponent();
    
    //==============================================================================
    int newOpenGLContextCreated(lua_State*);
    int renderOpenGL(lua_State*);
    int openGLContextClosing(lua_State*);

    //==============================================================================
    int triggerRepaint(lua_State*);
    int setContinuousRepainting(lua_State*);
    int swapBuffers(lua_State*);
    int setSwapInterval(lua_State*);
    int getSwapInterval(lua_State*);


    int setMultisamplingEnabled(lua_State*);
    int areShadersAvailable(lua_State*);
    
    int getRenderingScale(lua_State*);
    int copyTexture(lua_State*);

    int makeActive(lua_State*);
    int isActive(lua_State*);

    int attach(lua_State*);
    int attachTo(lua_State*);
    int detach(lua_State*);
    int setComponentPaintingEnabled(lua_State*);
    int getTargetComponent(lua_State*);
    // TODO: setPixelFormat

    int OpenGLShaderProgram(lua_State*);
    int clearGL(lua_State*);


    //==============================================================================
    static const char className[];
    static const Luna<LOpenGLComponent>::Inheritence inherits[];
    static const Luna<LOpenGLComponent>::InheritenceF inheritsF[];
    static const Luna<LOpenGLComponent>::PropertyType properties[];
    static const Luna<LOpenGLComponent>::FunctionType methods[];
    static const Luna<LOpenGLComponent>::StaticType statics[];

    static const Luna<LOpenGLComponent>::Enum enums[];
private:
    //==============================================================================
    OpenGLContext openGLContext;
    ScopedPointer<OpenGLGraphicsContextCustomShader> shader;
    void renderGLSL(Graphics&);

    //==============================================================================
    virtual void newOpenGLContextCreated() override;
    virtual void renderOpenGL() override;
    virtual void openGLContextClosing() override;

    //==============================================================================
    virtual void paint (Graphics& g) override;
    virtual void resized () override;

    virtual void mouseMove (const MouseEvent&) override;
    virtual void mouseEnter (const MouseEvent&) override;
    virtual void mouseExit (const MouseEvent&) override;
    virtual void mouseDown (const MouseEvent&) override;
    virtual void mouseDrag (const MouseEvent&) override;
    virtual void mouseUp (const MouseEvent&) override;
    virtual void mouseDoubleClick (const MouseEvent&) override;
    virtual void mouseWheelMove (const MouseEvent&, const MouseWheelDetails&) override;
    virtual void mouseMagnify (const MouseEvent&, float scaleFactor) override;

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (LOpenGLComponent)
};

#endif // __LUCE_OPENGL_COMPONENT_WINDOW_H
