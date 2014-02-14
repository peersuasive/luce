namespace LUCE {
namespace {
    typedef const char* NumType;
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
    const juce::Point<int> luce_topoint(int i);
    template<class T>
    int luce_pushlightpoint(const juce::Point<T>&);

    const juce::StringArray luce_tostringarray(int i = -1);

    template<class T>
    const T* luce_getnumarray(int i = -1);
    const int* luce_getnumarray(int i);

    //#define luce_isoftype(t,i) isoftype(#t, i)
    //#define luce_isofnumtype(t,i) isofnumtype(#t, i)

}
}
