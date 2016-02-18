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
    void shutdownAudio();
    void stopPlaying();
    int setAudioChannels(lua_State*);
    int start(lua_State*);
    int stop(lua_State*);
    int close(lua_State*);

    //==============================================================================
    int setVolume(lua_State*);
    int getVolume(lua_State*);

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
    // callbacks
    virtual void prepareToPlay( int samplesPerBlockExpected, double sampleRate ) override;
    virtual void getNextAudioBlock( const AudioSourceChannelInfo& bufferToFill ) override;
    virtual void releaseResources() override;

    //==============================================================================
    AudioDeviceManager deviceManager;

private:
    //==============================================================================
    lua_State *Ls;

    //==============================================================================
    bool stopped, audioOpen;
    AudioSourcePlayer audioSourcePlayer;
    
    //==============================================================================
    float volume;

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (LAudioAppComponent)
};

#endif // __LUCE_LAUDIOAPPCOMPONENT_H
