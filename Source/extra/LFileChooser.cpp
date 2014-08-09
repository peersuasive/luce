/************************************************************

 LFileChooser.cpp

    @author Christophe Berbizier (cberbizier@peersuasive.com)
    @license GPLv3
    @copyright 


(c) 2014, Peersuasive Technologies

*************************************************************/

#include "LFileChooser_inh.h"

const char LFileChooser::className[] = "LFileChooser";
const Luna<LFileChooser>::PropertyType LFileChooser::properties[] = {
    {0,0}
};
const Luna<LFileChooser>::FunctionType LFileChooser::methods[] = {
    method( LFileChooser, getResults ),
    method( LFileChooser, getResult ),
    method( LFileChooser, browseForMultipleFilesOrDirectories ),
    method( LFileChooser, browseForFileToOpen ),
    method( LFileChooser, showDialog ),
    method( LFileChooser, browseForFileToSave ),
    method( LFileChooser, browseForDirectory ),
    method( LFileChooser, browseForMultipleFilesToOpen ),
    {0,0}
};

const Luna<LFileChooser>::StaticType LFileChooser::statics[] = {
    {0,0}
};

LFileChooser::LFileChooser(lua_State *L)
    : LBase(L, "LFileChooser", true),
      FileChooser( "FileChooser" ) /* TODO: add args */
{
}

LFileChooser::LFileChooser(lua_State *L, const String &title, 
        const File initDir, const String &filter,
        bool native)
    : LBase(L, "LFileChooser", true),
      FileChooser(title, initDir, filter, native)
{
}

LFileChooser::~LFileChooser() {}

/**
 * Warning: as opposed to anything that was done until now,
 * LFileChooser takes a table to get optional parameters
 
  {
    start = "/home/user/",
    filter = "*.txt",
    native = true,
  }
 **/
int LFileChooser::lnew(lua_State *L) {
    String title = LUA::getString(2);
    File initDir = File::nonexistent;
    String filter = String::empty;
    bool native = false;
    if (lua_istable(L,2)) {
        lua_getfield(L, -1, "start");
        if(!lua_isnil(L,-1))
            initDir = File( lua_tostring(L,-1) );
        lua_pop(L,1);
        lua_getfield(L, -1, "filter");
        if(!lua_isnil(L,-1))
            filter = String( lua_tostring(L,-1) );
        lua_pop(L,1);
        lua_getfield(L, -1, "native");
        if(!lua_isnil(L,-1))
            native = lua_toboolean(L,-1);
        lua_pop(L,1);
    } 
    lua_settop(L,0);
    return LUA::storeAndReturnUserdata<LFileChooser>( new LFileChooser(L, title, initDir, filter, native) );
}

int LFileChooser::browseForFileToOpen( lua_State* ) {
    // TODO: preview
    return LUA::returnBoolean( FileChooser::browseForFileToOpen( nullptr ) );
}

int LFileChooser::browseForMultipleFilesToOpen( lua_State* ) {
    // TODO: preview
    return LUA::returnBoolean( FileChooser::browseForMultipleFilesToOpen( nullptr ) );
}

int LFileChooser::browseForFileToSave( lua_State* ) {
    bool warnAboutOverwritingExistingFiles = LUA::getBoolean(2);
    return LUA::returnBoolean( FileChooser::browseForFileToSave( warnAboutOverwritingExistingFiles ) );
}

int LFileChooser::browseForDirectory( lua_State* ) {
    return LUA::returnBoolean( FileChooser::browseForDirectory() );
}

int LFileChooser::browseForMultipleFilesOrDirectories( lua_State *L ) {
    // TODO: preview
    return LUA::returnBoolean( FileChooser::browseForMultipleFilesOrDirectories( nullptr ) );
}

int LFileChooser::showDialog( lua_State* ) {
    int flags = LUA::getNumber<int>(2);
    // TODO: preview
    return LUA::returnBoolean( FileChooser::showDialog( flags, nullptr ) );
}

int LFileChooser::getResult(lua_State *L) {
    // TODO: return File ?
    lua_settop(L,0);
    return LUA::returnString( FileChooser::getResult().getFullPathName() );
}

int LFileChooser::getResults( lua_State *L ) {
    // TODO: return Files ?
    lua_settop(L,0);
    Array<File> results = FileChooser::getResults();
    lua_createtable(L, 0, results.size());
    int i = 1;
    for ( File r : results ) {
        lua_pushstring( L, r.getFullPathName().toRawUTF8() );
        lua_rawseti( L, -2, i++ );
    }
    return 1;
}
