#ifndef __LUCE_INITIALISATION
#define __LUCE_INITIALISATION

class JUCE_API  LUCEApplicationBase
{
protected:
    //==============================================================================
    LUCEApplicationBase();

public:
    virtual ~LUCEApplicationBase();
    static int run(juce::Thread &t);
};

#endif // __LUCE_INITIALISATION
