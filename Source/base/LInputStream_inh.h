/************************************************************

 LInputStream_inh.h

    @author Christophe Berbizier (cberbizier@peersuasive.com)
    @license GPLv3
    @copyright 


(c) 2014, Peersuasive Technologies

*************************************************************/

#ifndef __LUCE_LINPUTSTREAM_INH_H
#define __LUCE_LINPUTSTREAM_INH_H

// LBase inheritage
const Luna<LInputStream>::Inheritence LInputStream::inherits[] = {
    {0,0}
};

const Luna<LInputStream>::InheritenceF LInputStream::inheritsF[] = {
    method( LBase, light),
    method( LBase, unlight),
    {0,0}
};

const Luna<LInputStream>::Enum LInputStream::enums[] = {
    {0}
};
#endif // __LUCE_LINPUTSTREAM_INH_H
