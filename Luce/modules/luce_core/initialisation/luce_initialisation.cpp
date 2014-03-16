#if JUCE_MAC
    extern void initialiseNSApplication();
#endif

int LUCEApplicationBase::run(juce::Thread &t) {
    #if LUCE_MAC || JUCE_MAC
    initialiseNSApplication();
    #endif

    initialiseJuce_GUI();
    const ScopedPointer<JUCEApplicationBase> app (juce::JUCEApplicationBase::createInstance());

    if (!app->initialiseApp())
        return 1;
    
    #if LUCE_MAC || JUCE_MAC
    [NSApp finishLaunching];
    [NSApp activateIgnoringOtherApps:YES];  // TODO(deanm): Do we want this?
    #endif
    
    t.run();

    return 0;
}
