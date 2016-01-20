/************************************************************

 LURL.h

    @author Christophe Berbizier (cberbizier@peersuasive.com)
    @license GPLv3
    @copyright 


(c) 2014, Peersuasive Technologies

*************************************************************/

#ifndef __LUCE_LURL_H
#define __LUCE_LURL_H

class LURL
    : public LBase,
      public URL
{
public:
    LURL(lua_State*);
    LURL(lua_State*, const String&);
    LURL(lua_State*, const URL&);

    static int lnew(lua_State*);
    ~LURL();

    //==============================================================================
    static int s_removeEscapeChars(lua_State*);
    static int s_isProbablyAnEmailAddress(lua_State*);
    static int s_createWithoutParsing(lua_State*);
    static int s_isProbablyAWebsiteURL(lua_State*);
    static int s_addEscapeChars(lua_State*);

    //==============================================================================
    int isEmpty(lua_State*);
    int getPostDataAsMemoryBlock(lua_State*);
    int getPort(lua_State*);
    int withNewSubPath(lua_State*);
    int getScheme(lua_State*);
    int readEntireTextStream(lua_State*);
    int getParameterValues(lua_State*);
    int isWellFormed(lua_State*);
    int withFileToUpload(lua_State*);
    int readEntireXmlStream(lua_State*);
    int readEntireBinaryStream(lua_State*);
    int launchInDefaultBrowser(lua_State*);
    int withParameters(lua_State*);
    int createInputStream(lua_State*);
    int getPostData(lua_State*);
    int withDataToUpload(lua_State*);
    int getSubPath(lua_State*);
    int getParameterNames(lua_State*);
    int withPOSTData(lua_State*);
    int getChildURL(lua_State*);
    int withParameter(lua_State*);
    int toString(lua_State*);
    int getDomain(lua_State*);

    //== callbacks =================================================================
    static bool progressCallback(void *context, int byteSend, int totalBytes);
    int progress(lua_State*);

    //==============================================================================
    static const char className[];
    static const Luna<LURL>::Inheritence inherits[];
    static const Luna<LURL>::InheritenceF inheritsF[];
    static const Luna<LURL>::PropertyType properties[];
    static const Luna<LURL>::FunctionType methods[];
    static const Luna<LURL>::StaticType statics[];
    static const Luna<LURL>::Enum enums[];

private:
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (LURL)
};

#endif // __LUCE_LURL_H
