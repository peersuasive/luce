namespace LUA {
    namespace {
        void Set(lua_State *L_);
        void throwError(const String& err);
        lua_State *Get();
        const var getNumber(int i= -1);
        const var checkAndGetNumber(int i=-1, var def = 0);

        const bool getBoolean(int i = -1);
        const bool checkAndGetBoolean(int i=-1, int def = false);

        const String getString(int i = -1);
        const String checkAndGetString(int i = -1, String def = String::empty);

        const Array<var> getList(int i=-1);
        const juce::Rectangle<int> getRectangle(int i=-1);
        const juce::Point<int> getPoint(int i=-1);
        const juce::Range<int> getRange(int i=-1);
        const std::list<var> getStdList(int i=-1);

            template<class T>
        T* toUserdata(int i=-1);

            template<class T>
        T* to_juce(int i=-1);

            template<class T>
        T* raw_cast(int i=-1);

            template<class T>
        T* from_luce(int i=-1);

            template<class T, class U = T>
        int returnUserdata(const U* udata);

        int returnUserdata(MouseEvent* e);

        int returnBoolean(bool val);

            template<class T>
        int returnNumber(const T& val);

        const int returnString(const String& val);
        int returnString(const std::string& val);

        int returnTable(const std::list<var>& val);
        int returnTable(const Array<var>& val);
        int returnTable( const juce::Rectangle<int>& r );
        int returnTable( const juce::RectangleList<int>& r );
        int returnTable( const juce::Point<int>& r );
        int returnTable( const juce::Range<int>& r );

        int TODO_OBJECT(const String& tmpl, const String& msg = "Not yet implemented: ");

        const int call_cb(int ref, int nb_ret = 0, const std::list<var>& args = {} );
        const int call_cb( const HashMap<String,int>& cb, const String& key, int nb_ret = 0, 
                                                                const std::list<var>& args = {} );

        void unreg( const HashMap<String, int>& cb, const String& key);
        void unregAll( const HashMap<String,int>& cb );
        const String getError();
    }
}
