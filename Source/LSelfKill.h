/************************************************************

 LSelfKill.h

    @author Christophe Berbizier (cberbizier@peersuasive.com)
    @license GPLv3
    @copyright 


(c) 2014, Peersuasive Technologies

*************************************************************/

#ifndef LSELF_KILL_H
#define LSELF_KILL_H

class LSelfKill 
{
public:
    LSelfKill(const String& n = "(unnamed)", bool p = true);
    virtual ~LSelfKill();
    virtual void selfKill() = 0;

    void myName(const String&);
    const String myName() const;

    const bool pureBase() const;
protected:
    void pureBase(bool);
private:
    String name;
    bool pure;

    WeakReference<LSelfKill>::Master masterReference;
    friend class WeakReference<LSelfKill>;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (LSelfKill)
};

#endif // LSELF_KILL_H
