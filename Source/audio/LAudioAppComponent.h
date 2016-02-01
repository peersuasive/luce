/************************************************************

 LAudioAppComponent.h

    @author Christophe Berbizier (cberbizier@peersuasive.com)
    @license GPLv3
    @copyright 


(c) 2014, Peersuasive Technologies

*************************************************************/

#ifndef __LUCE_LAUDIOAPPCOMPONENT_H
#define __LUCE_LAUDIOAPPCOMPONENT_H

class LAudioAppComponent
    : public LComponent,
      public Component,
      public AudioSource
{
public:
    LAudioAppComponent(lua_State*);
    ~LAudioAppComponent();

    //==============================================================================

    //==============================================================================
    void shutdownAudio();
    int setAudioChannels(lua_State*);
    int start(lua_State*);
    int stop(lua_State*);

    //==============================================================================
    virtual int prepareToPlay(lua_State*);
    virtual int getNextAudioBlock(lua_State*);
    virtual int releaseResources(lua_State*);

    //==============================================================================
    static const char className[];
    static const Luna<LAudioAppComponent>::Inheritence inherits[];
    static const Luna<LAudioAppComponent>::InheritenceF inheritsF[];
    static const Luna<LAudioAppComponent>::PropertyType properties[];
    static const Luna<LAudioAppComponent>::FunctionType methods[];
    static const Luna<LAudioAppComponent>::StaticType statics[];
    static const Luna<LAudioAppComponent>::Enum enums[];

    //==============================================================================
    AudioDeviceManager deviceManager;

private:
    //==============================================================================
    lua_State *Ls;
    //==============================================================================
    AudioSourcePlayer audioSourcePlayer;
    
    //==============================================================================
    // callbacks
    virtual void prepareToPlay( int samplesPerBlockExpected, double sampleRate ) override;
    virtual void getNextAudioBlock( const AudioSourceChannelInfo& bufferToFill ) override;
    virtual void releaseResources() override;

    /*
    virtual void mouseMove(const MouseEvent&) override;
    virtual void mouseEnter(const MouseEvent&) override;
    virtual void mouseExit(const MouseEvent&) override;
    virtual void mouseDown(const MouseEvent&) override;
    virtual void mouseDrag(const MouseEvent&) override;
    virtual void mouseUp(const MouseEvent&) override;
    virtual void mouseDoubleClick(const MouseEvent&) override;
    virtual void mouseWheelMove(const MouseEvent&, const MouseWheelDetails&) override;
    virtual void mouseMagnify(const MouseEvent&, float) override;
    virtual bool keyPressed(const KeyPress&) override;
    */
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (LAudioAppComponent)
};

#endif // __LUCE_LAUDIOAPPCOMPONENT_H
