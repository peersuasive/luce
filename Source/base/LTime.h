/************************************************************

 LTime.h

    @author Christophe Berbizier (cberbizier@peersuasive.com)
    @license GPLv3
    @copyright 


(c) 2014, Peersuasive Technologies

*************************************************************/

#ifndef __LUCE_LTIME_H
#define __LUCE_LTIME_H

class LTime
    : public LBase,
      public Time
{
public:
    LTime(lua_State*);
    LTime(lua_State*, const Time&);
    ~LTime();

    //==============================================================================
    static int s_getMillisecondCounterHiRes(lua_State*);
    static int s_currentTimeMillis(lua_State*);
    static int s_getWeekdayName(lua_State*);
    static int s_waitForMillisecondCounter(lua_State*);
    static int s_getMillisecondCounter(lua_State*);
    static int s_getMonthName(lua_State*);
    static int s_secondsToHighResolutionTicks(lua_State*);
    static int s_highResolutionTicksToSeconds(lua_State*);
    static int s_getCurrentTime(lua_State*);
    static int s_getHighResolutionTicksPerSecond(lua_State*);
    static int s_getHighResolutionTicks(lua_State*);
    static int s_getApproximateMillisecondCounter(lua_State*);

    //==============================================================================
    int toMilliseconds(lua_State*);
    int getMonth(lua_State*);
    int getTimeZone(lua_State*);
    int getHours(lua_State*);
    int getSeconds(lua_State*);
    int getDayOfMonth(lua_State*);
    int getMilliseconds(lua_State*);
    int getDayOfYear(lua_State*);
    int getHoursInAmPmFormat(lua_State*);
    int setSystemTimeToThisTime(lua_State*);
    int toString(lua_State*);
    int formatted(lua_State*);
    int getWeekdayName(lua_State*);
    int getDayOfWeek(lua_State*);
    int getMonthName(lua_State*);
    int getYear(lua_State*);
    int getMinutes(lua_State*);
    int isDaylightSavingTime(lua_State*);
    int isAfternoon(lua_State*);

    //==============================================================================
    static const char className[];
    static const Luna<LTime>::Inheritence inherits[];
    static const Luna<LTime>::InheritenceF inheritsF[];
    static const Luna<LTime>::PropertyType properties[];
    static const Luna<LTime>::FunctionType methods[];
    static const Luna<LTime>::StaticType statics[];
    static const Luna<LTime>::Enum enums[];

private:
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (LTime)
};

#endif // __LUCE_LTIME_H
