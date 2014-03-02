/************************************************************

 LOpenGLShaderProgram.h

    @author Christophe Berbizier (cberbizier@peersuasive.com)
    @license GPLv3
    @copyright 


(c) 2014, Peersuasive Technologies

*************************************************************/

#ifndef __LUCE_LOPENGLSHADERPROGRAM_H
#define __LUCE_LOPENGLSHADERPROGRAM_H

class LOpenGLShaderProgram
    : public LBase,
      public OpenGLShaderProgram
{
public:
    LOpenGLShaderProgram(lua_State*);
    LOpenGLShaderProgram(lua_State*, const OpenGLContext&);
    ~LOpenGLShaderProgram();

    //==============================================================================
    static int s_getLanguageVersion(lua_State*);

    //==============================================================================
    int link(lua_State*);
    int addFragmentShader(lua_State*);
    int getLastError(lua_State*);
    int getProgramID(lua_State*);
    int addVertexShader(lua_State*);
    int addShader(lua_State*);

    //==============================================================================
    int release(lua_State*);
    int use(lua_State*);

    //==============================================================================
    static const char className[];
    static const Luna<LOpenGLShaderProgram>::Inheritence inherits[];
    static const Luna<LOpenGLShaderProgram>::InheritenceF inheritsF[];
    static const Luna<LOpenGLShaderProgram>::PropertyType properties[];
    static const Luna<LOpenGLShaderProgram>::FunctionType methods[];
    static const Luna<LOpenGLShaderProgram>::StaticType statics[];
    static const Luna<LOpenGLShaderProgram>::Enum enums[];

private:
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (LOpenGLShaderProgram)
};

#endif // __LUCE_LOPENGLSHADERPROGRAM_H
