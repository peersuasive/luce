#ifndef __LUCE_INITIALISATION
#define __LUCE_INITIALISATION

#if JUCE_IOS
int luce_iOSMain (int argc, const char* argv[], juce::Thread* t);
#endif

class JUCE_API  LUCEApplicationBase
{
protected:
    //==============================================================================
    LUCEApplicationBase();

public:
    virtual ~LUCEApplicationBase();
    static int run(juce::Thread&);
};

#endif // __LUCE_INITIALISATION
