#ifndef __LUCE_REF_BASE_H
#define __LUCE_REF_BASE_H

class LRefBase : public ReferenceCountedObject
{
public:
    LRefBase( const String& type, const void* o ) 
       : me(type),
         object(o)
    {}

    LRefBase( const HashMap<String, var>& h )
        : me("Properties")
    {
        for( HashMap<String, var>::Iterator i(h); i.next(); )
            hash.set( i.getKey(), i.getValue() );
    }

    const String getType() {
        return me;
    }

    const void* getMe() {
        return object;
    }

    HashMap<String, var>* getHash() {
        return &hash;
    }

    typedef ReferenceCountedObjectPtr<LRefBase> Ptr;

private:
    const void* object;
    String me;
    HashMap<String,var> hash;
};
#endif // __LUCE_REF_BASE_H
