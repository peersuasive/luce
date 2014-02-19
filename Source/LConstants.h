/************************************************************

 LColours.h

    @author Christophe Berbizier (cberbizier@peersuasive.com)
    @license GPLv3
    @copyright 


(c) 2014] = Peersuasive Technologies

*************************************************************/

#ifndef LCONSTANTS_H
#define LCONSTANTS_H

#include "JuceHeader.h"

namespace LConstants {
namespace {
    std::list<const char*> lColours = {
        "transparentBlack",
        "transparentWhite",
        "black",
        "white",
        "blue",
        "grey",
        "green",
        "red",
        "yellow",
        "aliceblue",
        "antiquewhite",
        "aqua",
        "aquamarine",
        "azure",
        "beige",
        "bisque",
        "blanchedalmond",
        "blueviolet",
        "brown",
        "burlywood",
        "cadetblue",
        "chartreuse",
        "chocolate",
        "coral",
        "cornflowerblue",
        "cornsilk",
        "crimson",
        "cyan",
        "darkblue",
        "darkcyan",
        "darkgoldenrod",
        "darkgrey",
        "darkgreen",
        "darkkhaki",
        "darkmagenta",
        "darkolivegreen",
        "darkorange",
        "darkorchid",
        "darkred",
        "darksalmon",
        "darkseagreen",
        "darkslateblue",
        "darkslategrey",
        "darkturquoise",
        "darkviolet",
        "deeppink",
        "deepskyblue",
        "dimgrey",
        "dodgerblue",
        "firebrick",
        "floralwhite",
        "forestgreen",
        "fuchsia",
        "gainsboro",
        "gold",
        "goldenrod",
        "greenyellow",
        "honeydew",
        "hotpink",
        "indianred",
        "indigo",
        "ivory",
        "khaki",
        "lavender",
        "lavenderblush",
        "lemonchiffon",
        "lightblue",
        "lightcoral",
        "lightcyan",
        "lightgoldenrodyellow",
        "lightgreen",
        "lightgrey",
        "lightpink",
        "lightsalmon",
        "lightseagreen",
        "lightskyblue",
        "lightslategrey",
        "lightsteelblue",
        "lightyellow",
        "lime",
        "limegreen",
        "linen",
        "magenta",
        "maroon",
        "mediumaquamarine",
        "mediumblue",
        "mediumorchid",
        "mediumpurple",
        "mediumseagreen",
        "mediumslateblue",
        "mediumspringgreen",
        "mediumturquoise",
        "mediumvioletred",
        "midnightblue",
        "mintcream",
        "mistyrose",
        "navajowhite",
        "navy",
        "oldlace",
        "olive",
        "olivedrab",
        "orange",
        "orangered",
        "orchid",
        "palegoldenrod",
        "palegreen",
        "paleturquoise",
        "palevioletred",
        "papayawhip",
        "peachpuff",
        "peru",
        "pink",
        "plum",
        "powderblue",
        "purple",
        "rosybrown",
        "royalblue",
        "saddlebrown",
        "salmon",
        "sandybrown",
        "seagreen",
        "seashell",
        "sienna",
        "silver",
        "skyblue",
        "slateblue",
        "slategrey",
        "snow",
        "springgreen",
        "steelblue",
        "tan",
        "teal",
        "thistle",
        "tomato",
        "turquoise",
        "violet",
        "wheat",
        "whitesmoke",
        "yellowgreen"
    };
    
    std::map<const char*, int> lJustificationType = {
        { "left", juce::Justification::left },
        { "right", juce::Justification::right },
        { "horizontallyCentred", juce::Justification::horizontallyCentred },
        { "top", juce::Justification::top }, 
        { "bottom", juce::Justification::bottom }, 
        { "verticallyCentred", juce::Justification::verticallyCentred },
        { "horizontallyJustified", juce::Justification::horizontallyJustified },
        { "centred", juce::Justification::centred },
        { "centredLeft", juce::Justification::centredLeft },
        { "centredRight", juce::Justification::centredRight },
        { "centredTop", juce::Justification::centredTop },
        { "centredBottom", juce::Justification::centredBottom },
        { "topLeft", juce::Justification::topLeft },
        { "topRight", juce::Justification::topRight },
        { "bottomLeft", juce::Justification::bottomLeft },
        { "bottomRight", juce::Justification::bottomRight },
    };

    std::map<const char *, int> lNotificationType = {
        { "dontSendNotification"  , NotificationType::dontSendNotification },
        { "sendNotification"      , NotificationType::sendNotification },
        { "sendNotificationSync"  , NotificationType::sendNotificationAsync },
        { "sendNotificationAsync" , NotificationType::sendNotificationSync }
    };

    std::map<const char *, int> lFocusChangeType = {
        { "focusChangedByMouseClick", Component::focusChangedByMouseClick },
        { "focusChangedByTabKey", Component::focusChangedByTabKey },
        { "focusChangedDirectly", Component::focusChangedDirectly },
    };

    /* not yet -- maybe never
    std::map<const char *, int> lSpecialLocationType = {
        { "userHomeDirectory", File::userHomeDirectory },
        { "userDocumentsDirectory", File::userDocumentsDirectory },
        { "userDesktopDirectory", File::userDesktopDirectory },
        { "userMusicDirectory", File::userMusicDirectory },
        { "userMoviesDirectory", File::userMoviesDirectory },
        { "userPicturesDirectory", File::userPicturesDirectory },
        { "userApplicationDataDirectory", File::userApplicationDataDirectory },
        { "commonApplicationDataDirectory", File::commonApplicationDataDirectory },
        { "commonDocumentsDirectory", File::commonDocumentsDirectory },
        { "tempDirectory", File::tempDirectory },
        { "currentExecutableFile", File::currentExecutableFile },
        { "currentApplicationFile", File::currentApplicationFile },
        { "invokedExecutableFile", File::invokedExecutableFile },
        { "hostApplicationPath", File::hostApplicationPath },
        { "globalApplicationsDirectory", File::globalApplicationsDirectory }
    };
    */


#define is_set(macro) is_set_(macro)
#define macrotest_1 ,
#define is_set_(value) is_set__(macrotest_##value)
#define is_set__(comma) is_set___(comma 1, 0)
#define is_set___(_, v, ...) v
    std::map<const char*, int> lCurrentOS = {
        { "android", is_set(JUCE_ANDROID) },
        { "ios",     is_set(JUCE_IOS)     },
        { "windows", is_set(JUCE_WINDOWS) },
        { "linux",   is_set(JUCE_LINUX)   },
        { "macosx",  is_set(JUCE_MAC)     },
        { "ppc",     is_set(JUCE_PPC)     },
        { "bsd",     is_set(JUCE_BSD)     },
    };
}
};

#endif // LCONSTANTS_H

