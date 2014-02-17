/************************************************************

 LInputFilter.cpp

    @author Christophe Berbizier (cberbizier@peersuasive.com)
    @license GPLv3
    @copyright 


(c) 2014, Peersuasive Technologies

*************************************************************/

#include "LInputFilter_inh.h"

////// static methods
const char LInputFilter::className[] = "LInputFilter";
const Luna<LInputFilter>::PropertyType LInputFilter::properties[] = {
    {0,0}
};
const Luna<LInputFilter>::FunctionType LInputFilter::methods[] = {
    method( LInputFilter, filterNewText ),
    {0,0}
};

const Luna<LInputFilter>::StaticType LInputFilter::statics[] = {
    {0,0}
};

LInputFilter::LInputFilter(lua_State *L)
    : LBase(L, "LInputFilter", true),
      TextEditor::InputFilter()
{
}
LInputFilter::~LInputFilter(){}

String LInputFilter::filterNewText(TextEditor&, const String& s) {
    if(hasCallback("filterNewText")) {
        callback("filterNewText", 1, { s });
        return LUA::checkAndGetString(-1, String::empty);
    }
    return String::empty;
}

int LInputFilter::filterNewText(lua_State*) {
    set("filterNewText");
    return 0;
}
