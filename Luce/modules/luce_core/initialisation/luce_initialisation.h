#ifndef __LUCE_INITIALISATION
#define __LUCE_INITIALISATION

class JUCE_API  LUCEApplicationBase
{
protected:
    //==============================================================================
    LUCEApplicationBase();

public:
    /** Destructor. */
    virtual ~LUCEApplicationBase();
    static int altmain();
    static void initialiseApp();
};

#endif // __LUCE_INITIALISATION
