/************************************************************

 LAudioSampleBuffer_inh.h

    @author Christophe Berbizier (cberbizier@peersuasive.com)
    @license GPLv3
    @copyright 


(c) 2014, Peersuasive Technologies

*************************************************************/

#ifndef __LUCE_LAUDIOSAMPLEBUFFER_INH_H
#define __LUCE_LAUDIOSAMPLEBUFFER_INH_H

// LBase inheritage
const Luna<LAudioSampleBuffer>::Inheritence LAudioSampleBuffer::inherits[] = {
    {0,0}
};

const Luna<LAudioSampleBuffer>::InheritenceF LAudioSampleBuffer::inheritsF[] = {
    method( LBase, light),
    method( LBase, unlight),
    {0,0}
};

const Luna<LAudioSampleBuffer>::Enum LAudioSampleBuffer::enums[] = {
    {0}
};
#endif // __LUCE_LAUDIOSAMPLEBUFFER_INH_H