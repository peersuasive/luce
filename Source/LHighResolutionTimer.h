/************************************************************

 LHighResolutionTimer.h

    @author Christophe Berbizier (cberbizier@peersuasive.com)
    @license GPLv3
    @copyright 


(c) 2014, Peersuasive Technologies

*************************************************************/

#ifndef __LUCE_LHIGHRESOLUTIONTIMER_H
#define __LUCE_LHIGHRESOLUTIONTIMER_H

class LHighResolutionTimer
    : public LBase,
      public HighResolutionTimer
{
public:
    LHighResolutionTimer(lua_State*);
    ~LHighResolutionTimer();

    //==============================================================================
    int isTimerRunning(lua_State*);
    int getTimerInterval(lua_State*);

    //==============================================================================
    int startTimer(lua_State*);
    int stopTimer(lua_State*);

    //==============================================================================
    int hiResTimerCallback(lua_State*);

    //==============================================================================
    static const char className[];
    static const Luna<LHighResolutionTimer>::Inheritence inherits[];
    static const Luna<LHighResolutionTimer>::InheritenceF inheritsF[];
    static const Luna<LHighResolutionTimer>::PropertyType properties[];
    static const Luna<LHighResolutionTimer>::FunctionType methods[];
    static const Luna<LHighResolutionTimer>::StaticType statics[];
    static const Luna<LHighResolutionTimer>::Enum enums[];

private:

    //==============================================================================
    // callbacks
    virtual void hiResTimerCallback() override;

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (LHighResolutionTimer)
};

#endif // __LUCE_LHIGHRESOLUTIONTIMER_H
