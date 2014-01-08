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
#include "LuaO.h"

#include "LRefBase.h"

#include "MyLookAndFeel.h"
#include "LBase.h"
#include "LModifierKeys.h"
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
}

#endif // __LUCE_H
