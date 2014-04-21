/************************************************************

 LFillType_inh.h

    @author Christophe Berbizier (cberbizier@peersuasive.com)
    @license GPLv3
    @copyright 


(c) 2014, Peersuasive Technologies

*************************************************************/

#ifndef __LUCE_LFILLTYPE_INH_H
#define __LUCE_LFILLTYPE_INH_H

// LBase inheritage
const Luna<LFillType>::Inheritence LFillType::inherits[] = {
    {0,0}
};

const Luna<LFillType>::InheritenceF LFillType::inheritsF[] = {
    method( LBase, light),
    method( LBase, unlight),
    {0,0}
};

const Luna<LFillType>::Enum LFillType::enums[] = {
    {0}
};
#endif // __LUCE_LFILLTYPE_INH_H
