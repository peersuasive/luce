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
    std::list<const char*> lcolours = {
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
    
    std::map<const char*, int> ljustification = {
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

    std::map<const char *, int> lnotification = {
        { "dontSendNotification"  , NotificationType::dontSendNotification },
        { "sendNotification"      , NotificationType::sendNotification },
        { "sendNotificationSync"  , NotificationType::sendNotificationAsync },
        { "sendNotificationAsync" , NotificationType::sendNotificationSync }
    };

    }
};

#endif // LCONSTANTS_H
