/************************************************************

 LHighResolutionTimer_inh.h

    @author Christophe Berbizier (cberbizier@peersuasive.com)
    @license GPLv3
    @copyright 


(c) 2014, Peersuasive Technologies

*************************************************************/

#ifndef __LUCE_LHIGHRESOLUTIONTIMER_INH_H
#define __LUCE_LHIGHRESOLUTIONTIMER_INH_H

// LBase inheritage
const Luna<LHighResolutionTimer>::Inheritence LHighResolutionTimer::inherits[] = {
    {0,0}
};

const Luna<LHighResolutionTimer>::InheritenceF LHighResolutionTimer::inheritsF[] = {
    method( LBase, light),
    method( LBase, unlight),
    {0,0}
};

const Luna<LHighResolutionTimer>::Enum LHighResolutionTimer::enums[] = {
    {0}
};
#endif // __LUCE_LHIGHRESOLUTIONTIMER_INH_H
