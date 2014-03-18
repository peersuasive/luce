#if JUCE_MAC
    extern void initialiseNSApplication();
#endif

#if JUCE_IOS
} // end of namespace

@interface LuceAppStartupDelegate : NSObject <UIApplicationDelegate>
{
}

- (void) applicationDidFinishLaunching: (UIApplication*) application;
- (void) applicationWillTerminate: (UIApplication*) application;
- (void) applicationDidEnterBackground: (UIApplication*) application;
- (void) applicationWillEnterForeground: (UIApplication*) application;

+ (void) setThread: (juce::Thread**) thread;

@end

@implementation LuceAppStartupDelegate

juce::Thread** controlThread;
- (void) applicationDidFinishLaunching: (UIApplication*) application
{
    (void) application;
    juce::LUCEApplicationBase::run(**controlThread);
}

- (void) applicationWillTerminate: (UIApplication*) application
{
    (void) application;
    juce::JUCEApplicationBase::appWillTerminateByForce();
}

- (void) applicationDidEnterBackground: (UIApplication*) application
{
    (void) application;
    if (juce::JUCEApplicationBase* const app = juce::JUCEApplicationBase::getInstance())
        app->suspended();
}

- (void) applicationWillEnterForeground: (UIApplication*) application
{
    (void) application;
    if (juce::JUCEApplicationBase* const app = juce::JUCEApplicationBase::getInstance())
        app->resumed();
}

+ (void) setThread: (juce::Thread**) thread
{
    controlThread = thread;
}

@end

namespace juce {
int luce_iOSMain (int argc, const char* argv[], juce::Thread* t) {
    [LuceAppStartupDelegate setThread:&t];
    return UIApplicationMain (argc, const_cast<char**> (argv), nil, @"LuceAppStartupDelegate");
}
#endif

int LUCEApplicationBase::run(juce::Thread& t) {
    #if LUCE_MAC || JUCE_MAC
    initialiseNSApplication();
    #endif

    initialiseJuce_GUI();
    const ScopedPointer<JUCEApplicationBase> app (juce::JUCEApplicationBase::createInstance());

    std::ofstream logx("/tmp/out5.log");
    logx << "gonna run initApp" << std::endl;
    logx.flush();

    if (!app->initialiseApp())
        return 1;
    
    logx << "run" << std::endl;
    logx.flush();
    logx.close();

    #if LUCE_MAC || JUCE_MAC
    [NSApp finishLaunching];
    [NSApp activateIgnoringOtherApps:YES];
    #endif
 
    #if ! JUCE_IOS
    t.run();

    // FIXME: JUCEApplicationBase::shutdownApp is private,
    //        need to find a way to handle multiple instances and shut them down
    app->shutdown();
    #endif

    return 0;
}
