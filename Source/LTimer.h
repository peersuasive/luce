/************************************************************

 LTimer.h

    @author Christophe Berbizier (cberbizier@peersuasive.com)
    @license GPLv3
    @copyright 


(c) 2014, Peersuasive Technologies

*************************************************************/

#ifndef __LUCE_LTIMER_H
#define __LUCE_LTIMER_H

class LTimer
    : public LBase,
      public Timer
{
public:
    LTimer(lua_State*);
    LTimer(lua_State*, const Timer&);
    ~LTimer();

    //==============================================================================
    static int s_callPendingTimersSynchronously(lua_State*);

    //==============================================================================
    int isTimerRunning(lua_State*);
    int getTimerInterval(lua_State*);

    //==============================================================================
    int startTimer(lua_State*);
    int stopTimer(lua_State*);

    //==============================================================================
    int timerCallback(lua_State*);

    //==============================================================================
    static const char className[];
    static const Luna<LTimer>::Inheritence inherits[];
    static const Luna<LTimer>::InheritenceF inheritsF[];
    static const Luna<LTimer>::PropertyType properties[];
    static const Luna<LTimer>::FunctionType methods[];
    static const Luna<LTimer>::StaticType statics[];
    static const Luna<LTimer>::Enum enums[];

private:
    //==============================================================================
    // callbacks
    virtual void timerCallback() override;

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (LTimer)
};

#endif // __LUCE_LTIMER_H
