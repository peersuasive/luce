/************************************************************

 LPopupMenu_inh.h

    @author Christophe Berbizier (cberbizier@peersuasive.com)
    @license GPLv3
    @copyright 


(c) 2014, Peersuasive Technologies

*************************************************************/

#ifndef __LUCE_LPOPUPMENU_INH_H
#define __LUCE_LPOPUPMENU_INH_H

// LBase inheritage
const Luna<LPopupMenu>::Inheritence LPopupMenu::inherits[] = {
    {0,0}
};

const Luna<LPopupMenu>::InheritenceF LPopupMenu::inheritsF[] = {
    method( LBase, light),
    method( LBase, unlight),
    {0,0}
};

const Luna<LPopupMenu>::Enum LPopupMenu::enums[] = {
    { "ColourIds", {
        { "backgroundColourId"              , PopupMenu::backgroundColourId },
        { "textColourId"                    , PopupMenu::textColourId },
        { "headerTextColourId"              , PopupMenu::headerTextColourId },
        { "highlightedBackgroundColourId"   , PopupMenu::highlightedBackgroundColourId },
        { "highlightedTextColourId"         , PopupMenu::highlightedTextColourId },
    }},
    {0}
};
#endif // __LUCE_LPOPUPMENU_INH_H
