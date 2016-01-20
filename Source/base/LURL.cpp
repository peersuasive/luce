/************************************************************

 LURL.cpp

    @author Christophe Berbizier (cberbizier@peersuasive.com)
    @license GPLv3
    @copyright 


(c) 2016, Peersuasive Technologies

*************************************************************/

#include "LURL_inh.h"

const char LURL::className[] = "LURL";
const Luna<LURL>::PropertyType LURL::properties[] = {
    {0,0}
};
const Luna<LURL>::FunctionType LURL::methods[] = {
    method( LURL, isEmpty ),
    method( LURL, getPostDataAsMemoryBlock ),
    method( LURL, getPort ),
    method( LURL, withNewSubPath ),
    method( LURL, getScheme ),
    method( LURL, readEntireTextStream ),
    method( LURL, getParameterValues ),
    method( LURL, isWellFormed ),
    method( LURL, withFileToUpload ),
    method( LURL, readEntireXmlStream ),
    method( LURL, readEntireBinaryStream ),
    method( LURL, launchInDefaultBrowser ),
    method( LURL, withParameters ),
    method( LURL, createInputStream ),
    method( LURL, getPostData ),
    method( LURL, withDataToUpload ),
    method( LURL, getSubPath ),
    method( LURL, getParameterNames ),
    method( LURL, withPOSTData ),
    method( LURL, getChildURL ),
    method( LURL, withParameter ),
    method( LURL, toString ),
    method( LURL, getDomain ),
    // callbacks
    method( LURL, progress ),
    {0,0}
};

const Luna<LURL>::StaticType LURL::statics[] = {
    smethod( LURL, removeEscapeChars ),
    smethod( LURL, isProbablyAnEmailAddress ),
    smethod( LURL, createWithoutParsing ),
    smethod( LURL, isProbablyAWebsiteURL ),
    smethod( LURL, addEscapeChars ),
    {0,0}
};

LURL::LURL(lua_State *L)
    : LBase(L, "LURL", true),
      URL()
{
}

LURL::LURL(lua_State *L, const String& url_)
    : LBase(L, "LURL", true),
      URL( url_ )
{
}

LURL::LURL(lua_State *L, const URL& class_)
    : LBase(L, "LURL", true),
      URL( class_ )
{
}

LURL::~LURL() {}

int LURL::lnew(lua_State *L) {
    if(lua_isnoneornil(L, 2)) {
        return LUA::storeAndReturnUserdata<LURL>( new LURL(L) );
    } else if(!lua_isnumber(L,2) && lua_isstring(L, 2)) {
        return LUA::storeAndReturnUserdata<LURL>( new LURL(L, String(LUA::getString())) );
    } else if(LUCE::luce_isofclass(LURL, 2)) {
        return LUA::storeAndReturnUserdata<LURL>(
            new LURL(L, *LUA::from_luce<LURL>(2))
        );
    }
}

/////// statics
int LURL::s_removeEscapeChars ( lua_State* ) {
    String stringToRemoveEscapeCharsFrom = LUA::getString(2);
    return LUA::returnString( URL::removeEscapeChars( stringToRemoveEscapeCharsFrom ) );
}

int LURL::s_isProbablyAnEmailAddress ( lua_State* ) {
    String possibleEmailAddress = LUA::getString(2);
    return LUA::returnBoolean( URL::isProbablyAnEmailAddress( possibleEmailAddress ) );
}

int LURL::s_createWithoutParsing ( lua_State *L ) {
    String url = LUA::getString(2);
    return LUA::storeAndReturnUserdata<LURL>( new LURL(L,
        URL::createWithoutParsing( url )
    ));
}

int LURL::s_isProbablyAWebsiteURL ( lua_State* ) {
    String possibleURL = LUA::getString(2);
    return LUA::returnBoolean( URL::isProbablyAWebsiteURL( possibleURL ) );
}

int LURL::s_addEscapeChars ( lua_State* ) {
    String stringToAddEscapeCharsTo = LUA::getString(2);
    bool isParameter = LUA::getBoolean(2);
    return LUA::returnString( URL::addEscapeChars( stringToAddEscapeCharsTo, isParameter ) );
}

/////// getters
int LURL::isEmpty ( lua_State* ) {
    return LUA::returnBoolean( URL::isEmpty() );
}

int LURL::getPostDataAsMemoryBlock ( lua_State *L ) {
    MemoryBlock data( URL::getPostDataAsMemoryBlock() );
    size_t len = data.getSize();
    lua_pushlstring(L, (char*)data.getData(), len);
    return 1;
}

int LURL::getPort ( lua_State* ) {
    return LUA::returnNumber( URL::getPort() );
}

int LURL::withNewSubPath ( lua_State *L ) {
    String newPath = LUA::getString(2);
    return LUA::storeAndReturnUserdata<LURL>( new LURL(L,
        URL::withNewSubPath( newPath )
    ));
}

int LURL::getScheme ( lua_State* ) {
    return LUA::returnString( URL::getScheme() );
}

int LURL::readEntireTextStream ( lua_State* ) {
    bool usePostCommand = LUA::checkAndGetBoolean(2, false);
    return LUA::returnString( URL::readEntireTextStream( usePostCommand ) );
}

int LURL::getParameterValues ( lua_State *L ) {
    return LUCE::luce_pushtable( URL::getParameterValues() );
}

int LURL::isWellFormed ( lua_State* ) {
    return LUA::returnBoolean( URL::isWellFormed() );
}

int LURL::withFileToUpload ( lua_State *L ) {
    String parameterName = LUA::getString(2);
    String file_path = LUA::getString(2);
    String mimeType = LUA::getString(2);
    File file(file_path);
    return LUA::storeAndReturnUserdata<LURL>( new LURL(L,
        URL::withFileToUpload( parameterName, file, mimeType )
    ));
}

int LURL::readEntireXmlStream ( lua_State *L ) {
    bool usePostCommand = LUA::checkAndGetBoolean(2, false);
    // CHECK
    // return LUA::storeAndReturnUserdata<LXmlElement>( new LXmlElement(L,
    //     URL::readEntireXmlStream( usePostCommand )
    // ));
    lua_settop(LUA::Get(), 1); // added by TODO
    return LUA::TODO_OBJECT( "XmlElement readEntireXmlStream( usePostCommand )" );
}

int LURL::readEntireBinaryStream ( lua_State *L ) {
    bool usePostCommand = LUA::checkAndGetBoolean(2, false);
    MemoryBlock destData;
    if ( URL::readEntireBinaryStream( destData, usePostCommand ) ) {
        size_t len = destData.getSize();
        lua_pushlstring(L, (char*)destData.getData(), len);
    }else{
        lua_pushboolean(L, false);
    }
    return 1;
}

int LURL::launchInDefaultBrowser ( lua_State* ) {
    return LUA::returnBoolean( URL::launchInDefaultBrowser() );
}

int LURL::withParameter ( lua_State *L ) {
    String parameterName = LUA::getString(2);
    String parameterValue = LUA::getString(2);
    return LUA::storeAndReturnUserdata<LURL>( new LURL(L,
        URL::withParameter( parameterName, parameterValue )
    ));
}

int LURL::withParameters ( lua_State *L ) {
    StringPairArray parametersToAdd( LUCE::luce_tostringpairarray() );
    return LUA::storeAndReturnUserdata<LURL>( new LURL(L,
        URL::withParameters( parametersToAdd )
    ));
}

bool LURL::progressCallback(void *context, int byteSend, int totalBytes) {
    LURL *me = (LURL*)context;
    if(me->hasCallback("progress")) {
        me->callback("progress", 1);
        return LUA::checkAndGetBoolean(-1, true);
    }else return true;
}
int LURL::progress(lua_State*) {
    if(!hasCallback("progress"))
        set("progress");
    return 0;
}

int LURL::createInputStream ( lua_State *L ) {
    bool doPostLikeRequest = false;
    OpenStreamProgressCallback *progress_cb = nullptr;
    void *progressCallbackContext = nullptr;
    String extraHeaders = String();
    int connectionTimeOutMs = 0;
    int numRedirectsToFollow = 5;
    String httpRequestCmd = String();
    if(lua_gettop(L)>1) {
        doPostLikeRequest = LUA::checkAndGetBoolean(2,false);
        if(lua_type(L,2)==LUA_TFUNCTION && !hasCallback("progress")) {
            set("progress", LUA_TFUNCTION, 2);
            lua_remove(L,2);
        }
        extraHeaders = LUA::checkAndGetString(2, String());
        numRedirectsToFollow = LUA::checkAndGetNumber(2, 5);
        httpRequestCmd = LUA::checkAndGetString(2, String());
    }
    if(hasCallback("progress")) {
        progress_cb = &progressCallback;
        progressCallbackContext = this;
    }
    
    StringPairArray responseHeaders;
    int statusCode;
    InputStream *is = URL::createInputStream( doPostLikeRequest, progress_cb, progressCallbackContext,
            extraHeaders, connectionTimeOutMs, &responseHeaders, &statusCode, numRedirectsToFollow, httpRequestCmd);
    if(statusCode)
        LUA::storeAndReturnUserdata<LInputStream>( new LInputStream(L, is) );
    else
        lua_pushnil(L);
    LUCE::luce_pushtable(responseHeaders);
    lua_pushnumber(L, statusCode);
    return 3;
}

int LURL::getPostData ( lua_State* ) {
    return LUA::returnString( URL::getPostData() );
}

int LURL::withDataToUpload ( lua_State *L ) {
    String parameterName = LUA::getString(2);
    String filename = LUA::getString(2);
    size_t len;
    const void *raw = (const void*)lua_tolstring(L, 2, &len);
    lua_remove(L,2);
    MemoryBlock data(raw, len);
    String mimeType = LUA::getString(2);
    return LUA::storeAndReturnUserdata<LURL>( new LURL(L,
        URL::withDataToUpload( parameterName, filename, data, mimeType )
    ));
}

int LURL::getSubPath ( lua_State* ) {
    return LUA::returnString( URL::getSubPath() );
}

int LURL::getParameterNames ( lua_State *L ) {
    return LUCE::luce_pushtable( URL::getParameterNames() );
}

int LURL::withPOSTData ( lua_State *L ) {
    bool is_binary = LUA::checkAndGetBoolean(3, false);
    if(is_binary) {
        size_t len;
        const void *raw = (const void*)lua_tolstring(L, 2, &len);
        MemoryBlock postData(raw, len);
        return LUA::storeAndReturnUserdata<LURL>( new LURL(L,
            URL::withPOSTData( postData )
        ));
    }else{
        String postData = LUA::getString(2);
        return LUA::storeAndReturnUserdata<LURL>( new LURL(L,
            URL::withPOSTData( postData )
        ));
    }
}

int LURL::getChildURL ( lua_State *L ) {
    String subPath = LUA::getString(2);
    return LUA::storeAndReturnUserdata<LURL>( new LURL(L,
        URL::getChildURL( subPath )
    ));
}

int LURL::toString ( lua_State* ) {
    bool includeGetParameters = LUA::checkAndGetBoolean(2,true);
    return LUA::returnString( URL::toString( includeGetParameters ) );
}

int LURL::getDomain ( lua_State* ) {
    return LUA::returnString( URL::getDomain() );
}
