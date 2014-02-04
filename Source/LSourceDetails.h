/************************************************************

 LSourceDetails.h

    @author Christophe Berbizier (cberbizier@peersuasive.com)
    @license GPLv3
    @copyright 


(c) 2013, Peersuasive Technologies

*************************************************************/

#ifndef __LUCE_LSOURCEDETAILS_H
#define __LUCE_LSOURCEDETAILS_H

class LSourceDetails
    : public LBase
{
public:
    LSourceDetails(lua_State*);
    LSourceDetails(lua_State*, const juce::DragAndDropTarget::SourceDetails&);
    ~LSourceDetails();
    int getDescription(lua_State*);
    int setDescription(lua_State*);
    int getSourceComponent(lua_State*);
    int setSourceComponent(lua_State*);
    int getLocalPosition(lua_State*);
    int setLocalPosition(lua_State*);

    operator juce::DragAndDropTarget::SourceDetails () const;

    static const char className[];
    static const Luna<LSourceDetails>::Inheritence inherits[];
    static const Luna<LSourceDetails>::InheritenceF inheritsF[];
    static const Luna<LSourceDetails>::PropertyType properties[];
    static const Luna<LSourceDetails>::FunctionType methods[];
    static const Luna<LSourceDetails>::StaticType statics[];
    static const Luna<LSourceDetails>::Enum enums[];

private:
    var description;
    WeakReference<Component> sourceComponent;
    Point<int> localPosition;
    
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (LSourceDetails)
};

#endif // __LUCE_LSOURCEDETAILS_H
