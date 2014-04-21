/************************************************************

 LTextLayout_inh.h

    @author Christophe Berbizier (cberbizier@peersuasive.com)
    @license GPLv3
    @copyright 


(c) 2014, Peersuasive Technologies

*************************************************************/

#ifndef __LUCE_LTEXTLAYOUT_INH_H
#define __LUCE_LTEXTLAYOUT_INH_H

// LBase inheritage
const Luna<LTextLayout>::Inheritence LTextLayout::inherits[] = {
    {0,0}
};

const Luna<LTextLayout>::InheritenceF LTextLayout::inheritsF[] = {
    method( LBase, light),
    method( LBase, unlight),
    {0,0}
};

const Luna<LTextLayout>::Enum LTextLayout::enums[] = {
    {0}
};
#endif // __LUCE_LTEXTLAYOUT_INH_H
