/************************************************************

 LColourSelector.h

    @author Christophe Berbizier (cberbizier@peersuasive.com)
    @license GPLv3
    @copyright 


(c) 2014, Peersuasive Technologies

*************************************************************/

#ifndef __LUCE_LCOLOURSELECTOR_H
#define __LUCE_LCOLOURSELECTOR_H

class LColourSelector
    : public LComponent,
      public ColourSelector,
      private ChangeListener
{
public:
    LColourSelector(lua_State*);
    ~LColourSelector();

    //==============================================================================
    int setCurrentColour(lua_State*);
    int getCurrentColour(lua_State*);
    int setSwatchColour(lua_State*);
    int getSwatchColour(lua_State*);

    //==============================================================================
    int getNumSwatches(lua_State*);

    //== ChangeListener ============================================================
    virtual void changeListenerCallback(ChangeBroadcaster*) override;
    int colourChanged(lua_State*);
    int addChangeListener(lua_State*);
    int removeChangeListener(lua_State*);

    //==============================================================================
    static const char className[];
    static const Luna<LColourSelector>::Inheritence inherits[];
    static const Luna<LColourSelector>::InheritenceF inheritsF[];
    static const Luna<LColourSelector>::PropertyType properties[];
    static const Luna<LColourSelector>::FunctionType methods[];
    static const Luna<LColourSelector>::StaticType statics[];
    static const Luna<LColourSelector>::Enum enums[];

private:
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (LColourSelector)
};

#endif // __LUCE_LCOLOURSELECTOR_H
