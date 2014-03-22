/************************************************************

 LHighResolutionTimer.cpp

    @author Christophe Berbizier (cberbizier@peersuasive.com)
    @license GPLv3
    @copyright 


(c) 2014, Peersuasive Technologies

*************************************************************/

#include "LHighResolutionTimer_inh.h"

const char LHighResolutionTimer::className[] = "LHighResolutionTimer";
const Luna<LHighResolutionTimer>::PropertyType LHighResolutionTimer::properties[] = {
    {0,0}
};
const Luna<LHighResolutionTimer>::FunctionType LHighResolutionTimer::methods[] = {
    method( LHighResolutionTimer, isTimerRunning ),
    method( LHighResolutionTimer, getTimerInterval ),
    method( LHighResolutionTimer, startTimer ),
    method( LHighResolutionTimer, stopTimer ),
    method( LHighResolutionTimer, hiResTimerCallback ),
    {0,0}
};

const Luna<LHighResolutionTimer>::StaticType LHighResolutionTimer::statics[] = {
    {0,0}
};

LHighResolutionTimer::LHighResolutionTimer(lua_State *L)
    : LBase(L, "LHighResolutionTimer", true),
      HighResolutionTimer()
{
}

LHighResolutionTimer::~LHighResolutionTimer() {}

void LHighResolutionTimer::hiResTimerCallback() {
    if(hasCallback("hiResTimerCallback"))
        callback("hiResTimerCallback");
}
int LHighResolutionTimer::hiResTimerCallback(lua_State*){
    set("hiResTimerCallback");
    return 0;
}

int LHighResolutionTimer::isTimerRunning ( lua_State* ) {
    return LUA::returnBoolean( HighResolutionTimer::isTimerRunning() );
}

int LHighResolutionTimer::getTimerInterval ( lua_State* ) {
    return LUA::returnNumber( HighResolutionTimer::getTimerInterval() );
}

int LHighResolutionTimer::startTimer ( lua_State* ) {
    HighResolutionTimer::startTimer(LUA::getNumber<int>());
    return 0;
}

int LHighResolutionTimer::stopTimer ( lua_State* ) {
    HighResolutionTimer::stopTimer();
    return 0;
}
