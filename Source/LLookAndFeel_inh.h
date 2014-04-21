/************************************************************

 LLookAndFeel_inh.h

    @author Christophe Berbizier (cberbizier@peersuasive.com)
    @license GPLv3
    @copyright 


(c) 2014, Peersuasive Technologies

*************************************************************/

#ifndef __LUCE_LLOOKANDFEEL_INH_H
#define __LUCE_LLOOKANDFEEL_INH_H

// LBase inheritage
const Luna<LLookAndFeel>::Inheritence LLookAndFeel::inherits[] = {
    {0,0}
};

const Luna<LLookAndFeel>::InheritenceF LLookAndFeel::inheritsF[] = {
    method( LBase, light),
    method( LBase, unlight),
    {0,0}
};

const Luna<LLookAndFeel>::Enum LLookAndFeel::enums[] = {
    {0}
};
#endif // __LUCE_LLOOKANDFEEL_INH_H
