/************************************************************

 LSelfKill.cpp

    @author Christophe Berbizier (cberbizier@peersuasive.com)
    @license GPLv3
    @copyright 


(c) 2014, Peersuasive Technologies

*************************************************************/

LSelfKill::LSelfKill(const String& n) 
    : name(n)
{
}

LSelfKill::~LSelfKill() {
    masterReference.clear();
}

void LSelfKill::myName(const String& n) {
    name = n;
}
const String LSelfKill::myName() const {
    return name;
}
