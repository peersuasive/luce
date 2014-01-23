/************************************************************

 LSelfKill.cpp

    @author Christophe Berbizier (cberbizier@peersuasive.com)
    @license GPLv3
    @copyright 


(c) 2014, Peersuasive Technologies

*************************************************************/

LSelfKill::LSelfKill(const String& n, bool p) 
    : name(n),
      pure(p)
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

const bool LSelfKill::pureBase() const {
    return pure;
}

void LSelfKill::pureBase(bool p) {
    pure = p;
}
