/************************************************************

 LPathStrokeType_inh.h

    @author Christophe Berbizier (cberbizier@peersuasive.com)
    @license GPLv3
    @copyright 


(c) 2014, Peersuasive Technologies

*************************************************************/

#ifndef __LUCE_LPATHSTROKETYPE_INH_H
#define __LUCE_LPATHSTROKETYPE_INH_H

// LBase inheritage
const Luna<LPathStrokeType>::Inheritence LPathStrokeType::inherits[] = {
    {0,0}
};

const Luna<LPathStrokeType>::InheritenceF LPathStrokeType::inheritsF[] = {
    {0,0}
};

const Luna<LPathStrokeType>::Enum LPathStrokeType::enums[] = {
    { "JoinStyle", {
        { "mitered", PathStrokeType::mitered },
        { "curved", PathStrokeType::curved },
        { "beveled", PathStrokeType::beveled },
        
    }},

    { "EndCapStyle", {
        { "butt", PathStrokeType::beveled },
        { "square", PathStrokeType::square },
        { "rounded", PathStrokeType::rounded },
    }},

    {0}
};
#endif // __LUCE_LPATHSTROKETYPE_INH_H
