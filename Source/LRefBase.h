#ifndef __LUCE_REF_BASE_H
#define __LUCE_REF_BASE_H

class LRefBase : public ReferenceCountedObject
{
public:
    LRefBase( const String& type, void* o ) 
       : me(type),
         object(o)
    {}

    const String getType() {
        return me;
    }

    void *getMe() {
        return object;
    }
    typedef ReferenceCountedObjectPtr<LRefBase> Ptr;

private:
    String me;
    
    void *object;
};
#endif // __LUCE_REF_BASE_H
