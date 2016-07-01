namespace rec {
namespace mpg123 {

#include <mpg123.h>

namespace {

    class Initializer {
        public:
            Initializer() { initialize(); }

            Error initialize() {
                if (!running_) {
                    initError_ = mpg123_init();
                    running_ = true;
                }
                return initError_;
            }

            void exit() {
                if (running_) {
                    running_ = false;
                    if (!initError_)
                        mpg123_exit();
                }
            }

            Error initError_;
            bool running_;

            static Initializer& instance() {
                // C guarantees thread-safe construction of this variable, so we're
                // guaranteed that that first mpg123_init() is atomic - but if you turn it
                // off and on, all bets are off!
                static Initializer i;
                return i;
            }
    };

}  // namespace

Error initializeOnce() {
    return Initializer::instance().initError_;
}

void exitOnce() {
    Initializer::instance().exit();
}

StringArray getMp3FileExtensions() {
    static const char* const extensions[] = { ".mp3", ".mp2", ".mp1", 0 };
    return StringArray(extensions);
}

Array<int> getSampleRates() {
    const long* rates;
    size_t ratesCount;
    mpg123_rates(&rates, &ratesCount);

    Array<int> r(rates, ratesCount);
    r.add(0);

    return r;
}

Array<int> getBitDepths() {
    static const int depths[] = {8, 16, 32, 64, 0};
    return Array<int>(depths);
}

int getBitsPerSample(int encoding) {
    return
        (encoding & MPG123_ENC_16) ? 16 :
        (encoding & MPG123_ENC_32) ? 32 :
        (encoding & MPG123_ENC_8) ? 8 :
        (encoding & MPG123_ENC_FLOAT_64) ? 64 :
        0;
}

String getTranslatedName() {
    return TRANS("MP3 Audio file");
}

static AudioFormatManager* getAFMInitialized() {
    AudioFormatManager* afm = new AudioFormatManager();
    afm->registerBasicFormats();
    afm->registerFormat(new Format(), false);

    return afm;
}

// Get the default audio format manager and make sure it knows about mp3s.
AudioFormatManager* getAudioFormatManager() {
    static AudioFormatManager* afm = getAFMInitialized();
    return afm;
}

}  // namespace mpg123
}  // namespace rec
