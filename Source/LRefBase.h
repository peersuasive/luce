#ifndef __LUCE_REF_BASE_H
#define __LUCE_REF_BASE_H

class LRefBase : public ReferenceCountedObject
{
public:
    LRefBase( const String& type, void* o ) 
       : me(type),
         object(o)
    {}

    LRefBase( const HashMap<String, var>& h )
        : me("HashMap")
    {
        for( HashMap<String, var>::Iterator i(h); i.next(); )
            hash.set( i.getKey(), i.getValue() );
    }

    const String getType() {
        return me;
    }

    void *getMe() {
        return object;
    }

    HashMap<String, var>* getHash() {
        return &hash;
    }

    typedef ReferenceCountedObjectPtr<LRefBase> Ptr;

private:
    String me;
    
    void *object;
    HashMap<String,var> hash;
};
#endif // __LUCE_REF_BASE_H
