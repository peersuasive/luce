#ifndef __LUCE_MAIN_THREAD_H
#define __LUCE_MAIN_THREAD_H

class MainThread : public Thread 
{
public:
    MainThread( const String& name, lua_State *L, const int& ref = LUA_REFNIL );
    ~MainThread();

    void run();

private:
    int cb_ref;
};

#endif // __LUCE_MAIN_THREAD_H
