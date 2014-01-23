namespace LUA {
    namespace {
        std::map<int, WeakReference<LSelfKill>> objects;
        void store(int addr, WeakReference<LSelfKill> o);

        void reg(const LBase* key);
        void unreg(const LBase* key);
        bool set(const LBase* key, const char* name, int n_ = -1);
        void unset(const LBase* key, const char* name);
        bool hasCallback(const LBase* key, const char* name);

        void Set(lua_State *L_);
        void throwError(const String& err);
        lua_State *Get();

        const var getNumber(int i= -1);
        const var checkAndGetNumber(int i=2, var def = 0);

        const bool getBoolean(int i = -1);
        const bool checkAndGetBoolean(int i=2, int def = false);

        const String getString(int i = -1);
        const String checkAndGetString(int i=2, String def = String::empty);

        const Array<var> getList(int i=-1);
            template<class T>
        const Array<T> getList(int i=-1);
        const Array<Component*> getComponentList(int n, int i=-1);
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

            template<class T, class U = T>
        U* from_luce(int i=-1);

            template<class T, class U = T>
        int returnUserdata(const U* udata);
            template<class T, class U = T>
        int storeAndReturnUserdata(const U* udata);

        int returnBoolean(bool val);
        
        int returnNil();

            template<class T>
        int returnNumber(const T& val);

        const int returnString(const String& val);
        int returnString(const std::string& val);

        int returnTable(const std::list<var>& val);
        int returnTable(const Array<var>& val);
        int returnTable( const juce::StringArray& );
        int returnTable( const juce::Rectangle<int>& r );
        int returnTable( const juce::RectangleList<int>& r );
        int returnTable( const juce::Point<int>& r );
        int returnTable( const juce::Range<int>& r );

        int TODO_OBJECT(const String& tmpl, const String& msg = "Not yet implemented: ");

        const int call_cb(int ref, int nb_ret = 0, const std::list<var>& args = {} );

        const int call_cb( const LBase* key, const char *name, int nb_ret = 0,
                                                                const std::list<var>& args = {} );

        const String getError();
    }
}
