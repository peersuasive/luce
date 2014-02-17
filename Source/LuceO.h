namespace LUCE {
namespace {
    typedef const char* NumType;
    template<class T> struct ArrayType:std::vector<T>{}; //vector has no virtual destructor, don't inherit
    
    void Set(lua_State *L_);

    void throw_error(const char *);

    const char* luce_typename(int i = -1);
    const char* luce_numtype(int i = -1);
 
    template<class T>
    const T luce_tonumber(int i = -1);
    const int luce_tonumber(int i);

    template<class T>
    const juce::Rectangle<T> luce_torectangle(int i = -1);
    const juce::Rectangle<int> luce_torectangle(int i);

    template<class T>
    const juce::RectangleList<T> luce_torectanglelist(int i = -1);
    const juce::RectangleList<int> luce_torectanglelist(int i);

    const juce::AffineTransform luce_toaffinetransform(int i);

    template<class T>
    const juce::Point<T> luce_topoint(int i = -1);

    template<class T>
    const juce::Rectangle<T> luce_torectangle(int i = -1);

    template<class T>
    const juce::Range<T> luce_torange(int i = -1);


    template<class T, class U>
    int luce_pushtable(const U&);

    const juce::StringArray luce_tostringarray(int i = -1);

    const juce::TextLayout::Glyph luce_toglyph(int i = -1);
    int luce_pushlightglyph(const TextLayout::Glyph&);

    template<class T>
    const ArrayType<T> luce_tonumberarray(int i = -1);
}
}
