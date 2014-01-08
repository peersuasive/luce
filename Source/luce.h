#ifndef __LUCE_H
#define __LUCE_H

#include <list>
#include <map>

#include "JuceHeader.h"

#ifdef LUA52
#define LUA_COMPAT_MODULE
#endif

namespace luce {

#include <lua.hpp>
#include "luna5.h"
class LMouseEvent;
#include "LRefBase.h"
namespace LUA {
    namespace {
        const int call_cb(int ref, int nb_ret = 0, const std::list<var>& args = {} );
        const int call_cb( const HashMap<String,int>& cb, const String& key, int nb_ret = 0, 
                                                                const std::list<var>& args = {} );

        const bool getBoolean(int i = -1);

    }
}
#include "LBase.h"
#include "MyLookAndFeel.h"
#include "LMouseEvent.h"
#include "LComponent.h"
#include "LButton.h"
#include "LDocumentWindow.h"
#include "LMainComponent.h"
#include "LJUCEApplication.h"
#include "LLabel.h"
#include "LNotificationType.h"
#include "LTextButton.h"
#include "LTextEditor.h"
//#include "LValueTree.h"
#include "LTreeView.h"
#include "LTreeViewItem.h"
#include "MainThread.h"
#include "LuaO.h"
}

#endif // __LUCE_H
