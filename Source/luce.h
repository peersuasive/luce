#ifndef __LUCE_H
#define __LUCE_H

#define LUCE_VERSION_MAJOR 0
#define LUCE_VERSION_MINOR 1
#define LUCE_VERSION_BUILD 0

#include <list>
#include <map>

#include "JuceHeader.h"
#ifdef LUA52
#define LUA_COMPAT_MODULE
#endif

namespace luce {

#include "LSelfKill.h"

#include <lua.hpp>
#include "LBase.h"
#include "LuaO.h"
#include "MainThread.h"
#include "luna5.h"

#include "LRefBase.h"

#include "MyLookAndFeel.h"
//#include "LBase.h"
#include "LModifierKeys.h"
#include "LMouseEvent.h"
#include "LStretchableLayoutManager.h"
#include "LFont.h"
#include "LSourceDetails.h"

#include "LComponent.h"
#include "LButton.h"
#include "LDocumentWindow.h"
#include "LMainComponent.h"
#include "LJComponent.h"
#include "LJUCEApplication.h"
#include "LLabel.h"
#include "LNotificationType.h"
#include "LTextButton.h"
#include "LTextEditor.h"
//#include "LValueTree.h"
#include "LTreeView.h"
#include "LTreeViewItem.h"
#include "LStretchableLayoutResizerBar.h"

}

#endif // __LUCE_H
