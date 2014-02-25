#if JUCE_MAC
    extern void initialiseNSApplication();
    extern void juce_initialiseMacMainMenu();
#endif

int LUCEApplicationBase::altmain ()
{
    //JUCE_AUTORELEASEPOOL
    //{
       #if JUCE_MAC
        initialiseNSApplication();
       #endif
    //}
    return 0;
}

void LUCEApplicationBase::initialiseApp() {
    #if JUCE_MAC
    juce_initialiseMacMainMenu(); // (needs to get the app's name)
    #endif
}

//extern const char* const* juce_argv;
//extern int juce_argc;
//int LUCEApplicationBase::altmain(int argc, const char* argv[])
//{
//    juce_argc = argc;
//    juce_argv = argv;
//
//    #if JUCE_MAC
//    initialiseNSApplication();
//    #endif
//
//    initialiseJuce_GUI();
//    jassert( JUCEApplicationBase::createInstance != nullptr );
//}
