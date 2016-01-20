/************************************************************

 LURL_inh.h

    @author Christophe Berbizier (cberbizier@peersuasive.com)
    @license GPLv3
    @copyright 


(c) 2014, Peersuasive Technologies

*************************************************************/

#ifndef __LUCE_LURL_INH_H
#define __LUCE_LURL_INH_H

// LBase inheritage
const Luna<LURL>::Inheritence LURL::inherits[] = {
    {0,0}
};

const Luna<LURL>::InheritenceF LURL::inheritsF[] = {
    method( LBase, light),
    method( LBase, unlight),
    {0,0}
};

const Luna<LURL>::Enum LURL::enums[] = {
    {0}
};
#endif // __LUCE_LURL_INH_H
