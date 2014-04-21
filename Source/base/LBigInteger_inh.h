/************************************************************

 LBigInteger_inh.h

    @author Christophe Berbizier (cberbizier@peersuasive.com)
    @license GPLv3
    @copyright 


(c) 2014, Peersuasive Technologies

*************************************************************/

#ifndef __LUCE_LBIGINTEGER_INH_H
#define __LUCE_LBIGINTEGER_INH_H

// LBase inheritage
const Luna<LBigInteger>::Inheritence LBigInteger::inherits[] = {
    {0,0}
};

const Luna<LBigInteger>::InheritenceF LBigInteger::inheritsF[] = {
    method( LBase, light),
    method( LBase, unlight),
    {0,0}
};

const Luna<LBigInteger>::Enum LBigInteger::enums[] = {
    {0}
};
#endif // __LUCE_LBIGINTEGER_INH_H
