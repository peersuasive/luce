namespace LUCE {
namespace {
    typedef const char* NumType;
    template<class T> struct ArrayType:std::vector<T>{}; //vector has no virtual destructor, don't inherit
    
    void Set(lua_State *L_);

    void luce_error(const char *);

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
    const juce::Range<T> luce_torange(int i = -1);


    template<class T, class U>
    int luce_pushtable(const U&);
    template<class T>
    int luce_pushtable(const juce::Range<T>&);
    template<class T>
    int luce_pushtable(const juce::Point<T>&);
    template<class T>
    int luce_pushtable(const juce::Rectangle<T>& r);
    template<class T>
    int luce_pushtable(const juce::Line<T>& r);
    template<class T, class U>
    int luce_pushtable( const OwnedArray<U>& a);
    template<class T>
    int luce_pushtable(const Array<T>& val);
    template<class T>
    int luce_pushtable( const juce::SparseSet<T>& r );

    int luce_pushtable(const juce::AffineTransform&);
    int luce_pushtable(const std::list<var>);
    int luce_pushtable(const juce::RectanglePlacement&);
    int luce_pushtable(const StringArray& sa);
    int luce_pushtable(const StringPairArray& sa);
    int luce_pushtable(const Array<var>& val);

    ComponentBoundsConstrainer *luce_tocomponentboundsconstrainer(int i);

    template<class T>
    const juce::BorderSize<T> luce_tobordersize(int i);
    const juce::BorderSize<int> luce_tobordersize(int i);
    template<class T>
    int luce_pushlightbordersize(const juce::BorderSize<T>& r);
    template<class T>
    int luce_pushtable(const juce::BorderSize<T>& r);

    const juce::Colour luce_tocolour(int i = -1);

    const juce::StringArray luce_tostringarray(int i = -1);
    const juce::StringPairArray luce_tostringpairarray(int i = -1);

    const juce::TextLayout::Glyph luce_toglyph(int i = -1);
    int luce_pushlightglyph(const TextLayout::Glyph&);

    template<class T>
    const ArrayType<T> luce_tonumberarray(int i = -1);

    template<class T>
    const juce::Line<T> luce_toline(int i);
    const juce::Line<int> luce_toline(int i);

    const juce::RectanglePlacement luce_torectangleplacement(int i);

    bool isofnumtype(const char *t, int i);
    bool isoftype(const char *t, int i);
    bool isnumtype(const char* t1, const char *t2);
    #define luce_isoftype(t,i) isoftype(#t, i)
    #define luce_isofnumtype(t,i) isofnumtype(#t, i)
    #define luce_isnumtype(t1, t2) isnumtype(#t1, t2)

    #define luce_isnumtype(t1, t2) isnumtype(#t1, t2)

    template<class T>
    bool isofclass(const char* t, int i);
    #define ct_1(T)   isofclass<T>( #T )
    #define ct_2(T,i) isofclass<T>( #T, i )
    #define ct_sel(x,T,i,FUNC, ...) FUNC
    #define luce_isofclass(...) ct_sel(,##__VA_ARGS__, ct_2(__VA_ARGS__), ct_1(__VA_ARGS__),)

}
}
