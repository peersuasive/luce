/************************************************************

 LOpenGLShaderProgram.cpp

    @author Christophe Berbizier (cberbizier@peersuasive.com)
    @license GPLv3
    @copyright 


(c) 2014, Peersuasive Technologies

*************************************************************/

#include "LOpenGLShaderProgram_inh.h"

const char LOpenGLShaderProgram::className[] = "LOpenGLShaderProgram";
const Luna<LOpenGLShaderProgram>::PropertyType LOpenGLShaderProgram::properties[] = {
    {0,0}
};
const Luna<LOpenGLShaderProgram>::FunctionType LOpenGLShaderProgram::methods[] = {
    method( LOpenGLShaderProgram, link ),
    method( LOpenGLShaderProgram, addFragmentShader ),
    method( LOpenGLShaderProgram, getLastError ),
    method( LOpenGLShaderProgram, getProgramID ),
    method( LOpenGLShaderProgram, addVertexShader ),
    method( LOpenGLShaderProgram, addShader ),
    method( LOpenGLShaderProgram, release ),
    method( LOpenGLShaderProgram, use ),
    {0,0}
};

const Luna<LOpenGLShaderProgram>::StaticType LOpenGLShaderProgram::statics[] = {
    smethod( LOpenGLShaderProgram, getLanguageVersion ),
    {0,0}
};

LOpenGLShaderProgram::LOpenGLShaderProgram(lua_State *L)
    : LBase(L, "LOpenGLShaderProgram", true),
      OpenGLShaderProgram( OpenGLContext() )
{
    // INVALID
}

LOpenGLShaderProgram::LOpenGLShaderProgram(lua_State *L, const OpenGLContext& context)
    : LBase(L, "LOpenGLShaderProgram", true),
      OpenGLShaderProgram( context )
{
}

LOpenGLShaderProgram::~LOpenGLShaderProgram() {}


/////// statics
int LOpenGLShaderProgram::s_getLanguageVersion ( lua_State* ) {
    return LUA::returnNumber( OpenGLShaderProgram::getLanguageVersion() );
}

/////// getters
int LOpenGLShaderProgram::link ( lua_State* ) {
    return LUA::returnBoolean( OpenGLShaderProgram::link() );
}

int LOpenGLShaderProgram::addFragmentShader ( lua_State* ) {
    StringRef shaderSourceCode ( LUA::getString(2) );
    return LUA::returnBoolean( OpenGLShaderProgram::addFragmentShader( shaderSourceCode ) );
}

int LOpenGLShaderProgram::getLastError ( lua_State* ) {
    return LUA::returnString( OpenGLShaderProgram::getLastError() );
}

int LOpenGLShaderProgram::getProgramID ( lua_State *L ) {
    return LUA::returnNumber( OpenGLShaderProgram::getProgramID() );
}

int LOpenGLShaderProgram::addVertexShader ( lua_State* ) {
    StringRef shaderSourceCode ( LUA::getString(2) );
    return LUA::returnBoolean( OpenGLShaderProgram::addVertexShader( shaderSourceCode ) );
}

int LOpenGLShaderProgram::addShader ( lua_State* ) {
    StringRef shaderSourceCode ( LUA::getString(2) );
    GLenum shaderType = (GLenum)LUA::getNumber<int>(2);
    return LUA::returnBoolean( OpenGLShaderProgram::addShader( shaderSourceCode, shaderType ) );
}

/////// setters
int LOpenGLShaderProgram::release ( lua_State* ) {
    OpenGLShaderProgram::release();
    return 0;
}

int LOpenGLShaderProgram::use ( lua_State* ) {
    OpenGLShaderProgram::use();
    return 0;
}

