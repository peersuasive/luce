/************************************************************

 LTimer_inh.h

    @author Christophe Berbizier (cberbizier@peersuasive.com)
    @license GPLv3
    @copyright 


(c) 2014, Peersuasive Technologies

*************************************************************/

#ifndef __LUCE_LTIMER_INH_H
#define __LUCE_LTIMER_INH_H

// LBase inheritage
const Luna<LTimer>::Inheritence LTimer::inherits[] = {
    {0,0}
};

const Luna<LTimer>::InheritenceF LTimer::inheritsF[] = {
    method( LBase, light),
    method( LBase, unlight),
    {0,0}
};

const Luna<LTimer>::Enum LTimer::enums[] = {
    {0}
};
#endif // __LUCE_LTIMER_INH_H
