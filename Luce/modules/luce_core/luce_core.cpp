#include "LAppConfig.h"
#include "luce_core.h"

#include "../../../JuceLibraryCode/modules/juce_core/native/juce_BasicNativeHeaders.h"

#if JUCE_MAC
 #import <IOKit/IOKitLib.h>
 #import <IOKit/IOCFPlugIn.h>
 #import <IOKit/hid/IOHIDLib.h>
 #import <IOKit/hid/IOHIDKeys.h>
 #import <IOKit/pwr_mgt/IOPMLib.h>
#endif

namespace juce
{
#if JUCE_MAC
 #include "../../../JuceLibraryCode/modules/juce_core/native/juce_osx_ObjCHelpers.h"
 #include "../../../JuceLibraryCode/modules/juce_events/native/juce_osx_MessageQueue.h"
#endif

 #include "initialisation/luce_initialisation.cpp"
}

