/************************************************************

 LColourGradient_inh.h

    @author Christophe Berbizier (cberbizier@peersuasive.com)
    @license GPLv3
    @copyright 


(c) 2014, Peersuasive Technologies

*************************************************************/

#ifndef __LUCE_LCOLOURGRADIENT_INH_H
#define __LUCE_LCOLOURGRADIENT_INH_H

// LBase inheritage
const Luna<LColourGradient>::Inheritence LColourGradient::inherits[] = {
    {0,0}
};

const Luna<LColourGradient>::InheritenceF LColourGradient::inheritsF[] = {
    method( LBase, light),
    method( LBase, unlight),
    {0,0}
};

const Luna<LColourGradient>::Enum LColourGradient::enums[] = {
    {0}
};
#endif // __LUCE_LCOLOURGRADIENT_INH_H
