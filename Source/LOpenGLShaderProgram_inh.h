/************************************************************

 LOpenGLShaderProgram_inh.h

    @author Christophe Berbizier (cberbizier@peersuasive.com)
    @license GPLv3
    @copyright 


(c) 2014, Peersuasive Technologies

*************************************************************/

#ifndef __LUCE_LOPENGLSHADERPROGRAM_INH_H
#define __LUCE_LOPENGLSHADERPROGRAM_INH_H

// LBase inheritage
const Luna<LOpenGLShaderProgram>::Inheritence LOpenGLShaderProgram::inherits[] = {
    {0,0}
};

const Luna<LOpenGLShaderProgram>::InheritenceF LOpenGLShaderProgram::inheritsF[] = {
    method( LBase, light),
    method( LBase, unlight),
    {0,0}
};

const Luna<LOpenGLShaderProgram>::Enum LOpenGLShaderProgram::enums[] = {
    {0}
};
#endif // __LUCE_LOPENGLSHADERPROGRAM_INH_H
