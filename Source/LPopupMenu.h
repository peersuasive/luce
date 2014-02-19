/************************************************************

 LPopupMenu.h

    @author Christophe Berbizier (cberbizier@peersuasive.com)
    @license GPLv3
    @copyright 


(c) 2014, Peersuasive Technologies

*************************************************************/

#ifndef __LUCE_LPOPUPMENU_H
#define __LUCE_LPOPUPMENU_H

class LPopupMenu
    : public LBase,
      public PopupMenu
{
public:
    LPopupMenu(lua_State*);
    LPopupMenu(lua_State*, const PopupMenu&);
    ~LPopupMenu();

    //==============================================================================
    int menuInvocationCallback(lua_State *L);
    void menuInvocationCallback(int);

    //==============================================================================
    static int s_dismissAllActiveMenus(lua_State*);

    static int s_Options(lua_State*);

    //==============================================================================
    int containsCommandItem(lua_State*);
    int getNumItems(lua_State*);
    int containsAnyActiveItems(lua_State*);

    //==============================================================================
    int addColouredItem(lua_State*);
    int addSubMenu(lua_State*);
    int addSectionHeader(lua_State*);
    int addItem(lua_State*);
    int addCommandItem(lua_State*);
    int setLookAndFeel(lua_State*);
    int addSeparator(lua_State*);
    int clear(lua_State*);
    int addCustomItem(lua_State*);

    int showMenuAsync(lua_State*);
    int show(lua_State*);

    //==============================================================================
    static const char className[];
    static const Luna<LPopupMenu>::Inheritence inherits[];
    static const Luna<LPopupMenu>::InheritenceF inheritsF[];
    static const Luna<LPopupMenu>::PropertyType properties[];
    static const Luna<LPopupMenu>::FunctionType methods[];
    static const Luna<LPopupMenu>::StaticType statics[];
    static const Luna<LPopupMenu>::Enum enums[];

private:
    //==============================================================================
    class LCallbackComponent : public Component 
    {
    public:
        LCallbackComponent(LPopupMenu *p) { this->parent = p; }
        ~LCallbackComponent() {}
        static void menuInvocationCallback(int modalResult, LCallbackComponent *c) {
            if(c)
                c->parent->menuInvocationCallback(modalResult);
        }
    private:
        //==============================================================================
        LPopupMenu *parent;

        //==============================================================================
        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (LCallbackComponent)
    };
    ScopedPointer<LCallbackComponent> cbComp;

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (LPopupMenu)
};

#endif // __LUCE_LPOPUPMENU_H
