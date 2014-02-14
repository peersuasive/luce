/************************************************************

 LAttributedString_inh.h

    @author Christophe Berbizier (cberbizier@peersuasive.com)
    @license GPLv3
    @copyright 


(c) 2014, Peersuasive Technologies

*************************************************************/

#ifndef __LUCE_LATTRIBUTEDSTRING_INH_H
#define __LUCE_LATTRIBUTEDSTRING_INH_H

// LBase inheritage
const Luna<LAttributedString>::Inheritence LAttributedString::inherits[] = {
    {0,0}
};

const Luna<LAttributedString>::InheritenceF LAttributedString::inheritsF[] = {
    {0,0}
};

const Luna<LAttributedString>::Enum LAttributedString::enums[] = {
    { "WordWrap" , {
        { "none", AttributedString::none },
        { "byWord", AttributedString::byWord },
        { "byChar", AttributedString::byChar },
    }},

    { "ReadingDirection", {
        { "natural", AttributedString::natural },
        { "leftToRight", AttributedString::leftToRight },
        { "rightToLeft", AttributedString::rightToLeft },
    }},

    {0}
};
#endif // __LUCE_LATTRIBUTEDSTRING_INH_H
