#ifndef __LUCE_LUA_COMMON_H
#define __LUCE_LUA_COMMON_H

namespace LUA_COMMON {
    extern std::map<int, WeakReference<LSelfKill>> objects;
    extern bool LUCE_LIVE_CODING;
    namespace {
        void LUCE_API store(int addr, WeakReference<LSelfKill> o) {
            objects[addr] = o;
        }
        void LUCE_API liveCoding(bool b) {
            LUCE_LIVE_CODING = b;
        }
        bool LUCE_API liveCoding() {
            return LUCE_LIVE_CODING;
        }
    }
};

#endif // __LUCE_LUA_COMMON_H
