/************************************************************

 LTimer.cpp

    @author Christophe Berbizier (cberbizier@peersuasive.com)
    @license GPLv3
    @copyright 


(c) 2014, Peersuasive Technologies

*************************************************************/

#include "LTimer_inh.h"

const char LTimer::className[] = "LTimer";
const Luna<LTimer>::PropertyType LTimer::properties[] = {
    {"timerRunning", &LTimer::isTimerRunning, &LBase::readOnly},
    {"timerInterval", &LTimer::getTimerInterval, &LBase::readOnly},
    {0,0}
};
const Luna<LTimer>::FunctionType LTimer::methods[] = {
    method( LTimer, isTimerRunning ),
    method( LTimer, getTimerInterval ),
    method( LTimer, startTimer ),
    method( LTimer, stopTimer ),
    method( LTimer, timerCallback ),
    {0,0}
};

const Luna<LTimer>::StaticType LTimer::statics[] = {
    smethod( LTimer, callPendingTimersSynchronously ),
    {0,0}
};

LTimer::LTimer(lua_State *L)
    : LBase(L, "LTimer", true),
      Timer()
{
}

LTimer::LTimer(lua_State *L, const Timer& class_)
    : LBase(L, "LTimer", true),
      Timer( class_ )
{
}

LTimer::~LTimer() {}

/////// callbacks
void LTimer::timerCallback() {
    callback("timerCallback");
}
int LTimer::timerCallback(lua_State*){
    set("timerCallback");
    return 0;
}

/////// statics
int LTimer::s_callPendingTimersSynchronously ( lua_State* ) {
    Timer::callPendingTimersSynchronously();
    return 0;
}

/////// getters
int LTimer::isTimerRunning ( lua_State* ) {
    return LUA::returnBoolean( Timer::isTimerRunning() );
}

int LTimer::getTimerInterval ( lua_State* ) {
    return LUA::returnNumber( Timer::getTimerInterval() );
}

/////// setters
int LTimer::startTimer ( lua_State* ) {
    Timer::startTimer(LUA::getNumber<int>());
    return 0;
}

int LTimer::stopTimer ( lua_State* ) {
    Timer::stopTimer();
    return 0;
}
