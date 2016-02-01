/************************************************************

 LConnectionPool_inh.h

    @author Christophe Berbizier (cberbizier@peersuasive.com)
    @license GPLv3
    @copyright 


(c) 2016, Peersuasive Technologies

*************************************************************/

#ifndef __LUCE_LCONNECTIONPOOL_INH_H
#define __LUCE_LCONNECTIONPOOL_INH_H

// LBase inheritage
const Luna<LConnectionPool>::Inheritence LConnectionPool::inherits[] = {
    {0,0}
};

const Luna<LConnectionPool>::InheritenceF LConnectionPool::inheritsF[] = {
    method( LBase, light),
    method( LBase, unlight),
    {0,0}
};

const Luna<LConnectionPool>::Enum LConnectionPool::enums[] = {
    {0}
};

#endif // __LUCE_LCONNECTIONPOOL_INH_H
