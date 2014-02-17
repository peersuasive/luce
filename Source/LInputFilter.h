/************************************************************

 LInputFilter.h

    @author Christophe Berbizier (cberbizier@peersuasive.com)
    @license GPLv3
    @copyright 


(c) 2013, Peersuasive Technologies

*************************************************************/

#ifndef __LUCE_LINPUTFILTER_H
#define __LUCE_LINPUTFILTER_H

class LInputFilter;
class LInputFilter
    : public LBase,
      public TextEditor::InputFilter
{
public:
    LInputFilter(lua_State*);
    ~LInputFilter();

    //==============================================================================
    int filterNewText(lua_State*);

    static const char className[];
    static const Luna<LInputFilter>::Inheritence inherits[];
    static const Luna<LInputFilter>::InheritenceF inheritsF[];
    static const Luna<LInputFilter>::PropertyType properties[];
    static const Luna<LInputFilter>::FunctionType methods[];
    static const Luna<LInputFilter>::StaticType statics[];
    static const Luna<LInputFilter>::Enum enums[];

    friend class LTextEditor;

private:
    //==============================================================================
    virtual String filterNewText(TextEditor&, const String&) override;

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (LInputFilter)
};

#endif // __LUCE_LINPUTFILTER_H
