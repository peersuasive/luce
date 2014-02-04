/************************************************************

 LTime.cpp

    @author Christophe Berbizier (cberbizier@peersuasive.com)
    @license GPLv3
    @copyright 


(c) 2014, Peersuasive Technologies

*************************************************************/

#include "LTime_inh.h"

const char LTime::className[] = "LTime";
const Luna<LTime>::PropertyType LTime::properties[] = {
    {0,0}
};
const Luna<LTime>::FunctionType LTime::methods[] = {
    method( LTime, getApproximateMillisecondCounter ),
    method( LTime, toMilliseconds ),
    method( LTime, getMonth ),
    method( LTime, getWeekdayName ),
    method( LTime, getMinutes ),
    method( LTime, highResolutionTicksToSeconds ),
    method( LTime, getMillisecondCounter ),
    method( LTime, getHours ),
    method( LTime, getHighResolutionTicksPerSecond ),
    method( LTime, getSeconds ),
    method( LTime, getDayOfMonth ),
    method( LTime, getMonthName ),
    method( LTime, getHighResolutionTicks ),
    method( LTime, getMilliseconds ),
    method( LTime, currentTimeMillis ),
    method( LTime, getDayOfYear ),
    method( LTime, setSystemTimeToThisTime ),
    method( LTime, getHoursInAmPmFormat ),
    method( LTime, getTimeZone ),
    method( LTime, toString ),
    method( LTime, formatted ),
    method( LTime, secondsToHighResolutionTicks ),
    method( LTime, getDayOfWeek ),
    method( LTime, getMillisecondCounterHiRes ),
    method( LTime, getYear ),
    method( LTime, getCurrentTime ),
    method( LTime, isDaylightSavingTime ),
    method( LTime, isAfternoon ),
    method( LTime, waitForMillisecondCounter ),
    {0,0}
};

const Luna<LTime>::StaticType LTime::statics[] = {
    {0,0}
};

LTime::LTime(lua_State *L)
    : LBase(L, "LTime", true),
      Time()
{
}

LTime::LTime(lua_State *L, const Time& class_)
    : LBase(L, "LTime (dyn)", true),
      Time( class_ )
{
}

LTime::~LTime() {}

int LTime::getCurrentTime (lua_State *L) {
    return LUA::storeAndReturnUserdata<LTime>( new LTime(L,
        Time::getCurrentTime()
    ));
}

int LTime::getApproximateMillisecondCounter ( lua_State* ) {
    return LUA::returnNumber( Time::getApproximateMillisecondCounter() );
}

int LTime::toMilliseconds ( lua_State* ) {
    return LUA::returnNumber( Time::toMilliseconds() );
}

int LTime::getMonth ( lua_State* ) {
    return LUA::returnNumber( Time::getMonth() );
}

int LTime::getWeekdayName ( lua_State *L ) {
    int dayNumber = -1;
    if(lua_gettop(L) > 2)
        dayNumber = LUA::getNumber<int>(2);
    bool threeLetterVersion = LUA::getBoolean(2);
    if(dayNumber<0)
        return LUA::returnString( Time::getWeekdayName( threeLetterVersion ) );
    else
        return LUA::returnString( Time::getWeekdayName( dayNumber, threeLetterVersion ) );
}

int LTime::getMinutes ( lua_State* ) {
    return LUA::returnNumber( Time::getMinutes() );
}

int LTime::highResolutionTicksToSeconds ( lua_State* ) {
    int64 ticks = LUA::getNumber<int64>(2);
    return LUA::returnNumber( Time::highResolutionTicksToSeconds( ticks ) );
}

int LTime::getMillisecondCounter ( lua_State* ) {
    return LUA::returnNumber( Time::getMillisecondCounter() );
}

int LTime::getHours ( lua_State* ) {
    return LUA::returnNumber( Time::getHours() );
}

int LTime::getHighResolutionTicksPerSecond ( lua_State* ) {
    return LUA::returnNumber( Time::getHighResolutionTicksPerSecond() );
}

int LTime::getSeconds ( lua_State* ) {
    return LUA::returnNumber( Time::getSeconds() );
}

int LTime::getDayOfMonth ( lua_State* ) {
    return LUA::returnNumber( Time::getDayOfMonth() );
}

int LTime::getMonthName ( lua_State *L ) {
    int monthNumber = -1;
    if(lua_gettop(L) > 2)
        monthNumber = LUA::getNumber<int>(2);
    bool threeLetterVersion = LUA::getBoolean(2);
    if(monthNumber<0)
        return LUA::returnString( Time::getWeekdayName( threeLetterVersion ) );
    else
        return LUA::returnString( Time::getWeekdayName( monthNumber, threeLetterVersion ) );
}

int LTime::getHighResolutionTicks ( lua_State* ) {
    return LUA::returnNumber( Time::getHighResolutionTicks() );
}

int LTime::getMilliseconds ( lua_State* ) {
    return LUA::returnNumber( Time::getMilliseconds() );
}

int LTime::currentTimeMillis ( lua_State* ) {
    return LUA::returnNumber( Time::currentTimeMillis() );
}

int LTime::getDayOfYear ( lua_State* ) {
    return LUA::returnNumber( Time::getDayOfYear() );
}

int LTime::setSystemTimeToThisTime ( lua_State* ) {
    return LUA::returnBoolean( Time::setSystemTimeToThisTime() );
}

int LTime::getHoursInAmPmFormat ( lua_State* ) {
    return LUA::returnNumber( Time::getHoursInAmPmFormat() );
}

int LTime::getTimeZone ( lua_State* ) {
    return LUA::returnString( Time::getTimeZone() );
}

int LTime::toString ( lua_State* ) {
    bool includeDate = LUA::getBoolean(2);
    bool includeTime = LUA::getBoolean(2);
    bool includeSeconds = LUA::checkAndGetBoolean(2, true);
    bool use24HourClock = LUA::checkAndGetBoolean(2, false);
    return LUA::returnString( Time::toString( includeDate, includeTime, includeSeconds, use24HourClock ) );
}

int LTime::formatted ( lua_State* ) {
    return LUA::returnString( Time::formatted( LUA::getString(2) ) );
}

int LTime::secondsToHighResolutionTicks ( lua_State* ) {
    return LUA::returnNumber( Time::secondsToHighResolutionTicks( LUA::getNumber<double>(2) ) );
}

int LTime::getDayOfWeek ( lua_State* ) {
    return LUA::returnNumber( Time::getDayOfWeek() );
}

int LTime::getMillisecondCounterHiRes ( lua_State* ) {
    return LUA::returnNumber( Time::getMillisecondCounterHiRes() );
}

int LTime::getYear ( lua_State* ) {
    return LUA::returnNumber( Time::getYear() );
}

int LTime::isDaylightSavingTime ( lua_State* ) {
    return LUA::returnBoolean( Time::isDaylightSavingTime() );
}

int LTime::isAfternoon ( lua_State* ) {
    return LUA::returnBoolean( Time::isAfternoon() );
}

int LTime::waitForMillisecondCounter ( lua_State* ) {
    Time::waitForMillisecondCounter(LUA::getNumber<uint32>());
    return 0;
}
