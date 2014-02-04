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
    method( LTime, toMilliseconds ),
    method( LTime, getMonth ),
    method( LTime, getTimeZone ),
    method( LTime, getHours ),
    method( LTime, getSeconds ),
    method( LTime, getDayOfMonth ),
    method( LTime, getMilliseconds ),
    method( LTime, getDayOfYear ),
    method( LTime, getHoursInAmPmFormat ),
    method( LTime, setSystemTimeToThisTime ),
    method( LTime, toString ),
    method( LTime, formatted ),
    method( LTime, getWeekdayName ),
    method( LTime, getDayOfWeek ),
    method( LTime, getMonthName ),
    method( LTime, getYear ),
    method( LTime, getMinutes ),
    method( LTime, isDaylightSavingTime ),
    method( LTime, isAfternoon ),
    {0,0}
};

const Luna<LTime>::StaticType LTime::statics[] = {
    smethod( LTime, getMillisecondCounterHiRes ),
    smethod( LTime, currentTimeMillis ),
    smethod( LTime, getWeekdayName ),
    smethod( LTime, waitForMillisecondCounter ),
    smethod( LTime, getMillisecondCounter ),
    smethod( LTime, getMonthName ),
    smethod( LTime, secondsToHighResolutionTicks ),
    smethod( LTime, highResolutionTicksToSeconds ),
    smethod( LTime, getCurrentTime ),
    smethod( LTime, getHighResolutionTicksPerSecond ),
    smethod( LTime, getHighResolutionTicks ),
    smethod( LTime, getApproximateMillisecondCounter ),
    {0,0}
};

LTime::LTime(lua_State *L)
    : LBase(L, "LTime", true),
      Time( /* TODO: add args */ )
{
}

LTime::LTime(lua_State *L, const Time& class_)
    : LBase(L, "LTime", true),
      Time( class_ )
{
}

LTime::~LTime() {}

/////// statics
int LTime::s_getMillisecondCounterHiRes ( lua_State* ) {
    return LUA::returnNumber( Time::getMillisecondCounterHiRes() );
}

int LTime::s_currentTimeMillis ( lua_State* ) {
    return LUA::returnNumber( Time::currentTimeMillis() );
}

int LTime::s_getWeekdayName ( lua_State* ) {
    int dayNumber = LUA::getNumber<int>(2);
    bool threeLetterVersion = LUA::getBoolean(2);
    return LUA::returnString( Time::getWeekdayName( dayNumber, threeLetterVersion ) );
}

int LTime::s_waitForMillisecondCounter ( lua_State* ) {
    uint32 targetTime = LUA::getNumber<uint32>(2);
    Time::waitForMillisecondCounter( targetTime );
    return 0;
}

int LTime::s_getMillisecondCounter ( lua_State* ) {
    return LUA::returnNumber( Time::getMillisecondCounter() );
}

int LTime::s_getMonthName ( lua_State* ) {
    int monthNumber = LUA::getNumber<int>(2);
    bool threeLetterVersion = LUA::getBoolean(2);
    return LUA::returnString( Time::getMonthName( monthNumber, threeLetterVersion ) );
}

int LTime::s_secondsToHighResolutionTicks ( lua_State* ) {
    double seconds = LUA::getNumber<double>(2);
    return LUA::returnNumber( Time::secondsToHighResolutionTicks( seconds ) );
}

int LTime::s_highResolutionTicksToSeconds ( lua_State* ) {
    int64 ticks = LUA::getNumber<int64>(2);
    return LUA::returnNumber( Time::highResolutionTicksToSeconds( ticks ) );
}

int LTime::s_getCurrentTime ( lua_State *L ) {
    return LUA::storeAndReturnUserdata<LTime>( new LTime(L,
        Time::getCurrentTime()
    ));
}

int LTime::s_getHighResolutionTicksPerSecond ( lua_State* ) {
    return LUA::returnNumber( Time::getHighResolutionTicksPerSecond() );
}

int LTime::s_getHighResolutionTicks ( lua_State* ) {
    return LUA::returnNumber( Time::getHighResolutionTicks() );
}

int LTime::s_getApproximateMillisecondCounter ( lua_State* ) {
    return LUA::returnNumber( Time::getApproximateMillisecondCounter() );
}

/////// getters
int LTime::toMilliseconds ( lua_State* ) {
    return LUA::returnNumber( Time::toMilliseconds() );
}

int LTime::getMonth ( lua_State* ) {
    return LUA::returnNumber( Time::getMonth() );
}

int LTime::getTimeZone ( lua_State* ) {
    return LUA::returnString( Time::getTimeZone() );
}

int LTime::getHours ( lua_State* ) {
    return LUA::returnNumber( Time::getHours() );
}

int LTime::getSeconds ( lua_State* ) {
    return LUA::returnNumber( Time::getSeconds() );
}

int LTime::getDayOfMonth ( lua_State* ) {
    return LUA::returnNumber( Time::getDayOfMonth() );
}

int LTime::getMilliseconds ( lua_State* ) {
    return LUA::returnNumber( Time::getMilliseconds() );
}

int LTime::getDayOfYear ( lua_State* ) {
    return LUA::returnNumber( Time::getDayOfYear() );
}

int LTime::getHoursInAmPmFormat ( lua_State* ) {
    return LUA::returnNumber( Time::getHoursInAmPmFormat() );
}

int LTime::setSystemTimeToThisTime ( lua_State* ) {
    return LUA::returnBoolean( Time::setSystemTimeToThisTime() );
}

int LTime::toString ( lua_State* ) {
    bool includeDate = LUA::getBoolean(2);
    bool includeTime = LUA::getBoolean(2);
    bool includeSeconds = LUA::checkAndGetBoolean(2, true);
    bool use24HourClock = LUA::checkAndGetBoolean(2, false);
    return LUA::returnString( Time::toString( includeDate, includeTime, includeSeconds, use24HourClock ) );
}

int LTime::formatted ( lua_State* ) {
    String format = LUA::getString(2);
    return LUA::returnString( Time::formatted( format ) );
}

int LTime::getWeekdayName ( lua_State* ) {
    bool threeLetterVersion = LUA::getBoolean(2);
    return LUA::returnString( Time::getWeekdayName( threeLetterVersion ) );
}

int LTime::getDayOfWeek ( lua_State* ) {
    return LUA::returnNumber( Time::getDayOfWeek() );
}

int LTime::getMonthName ( lua_State* ) {
    bool threeLetterVersion = LUA::getBoolean(2);
    return LUA::returnString( Time::getMonthName( threeLetterVersion ) );
}

int LTime::getYear ( lua_State* ) {
    return LUA::returnNumber( Time::getYear() );
}

int LTime::getMinutes ( lua_State* ) {
    return LUA::returnNumber( Time::getMinutes() );
}

int LTime::isDaylightSavingTime ( lua_State* ) {
    return LUA::returnBoolean( Time::isDaylightSavingTime() );
}

int LTime::isAfternoon ( lua_State* ) {
    return LUA::returnBoolean( Time::isAfternoon() );
}
