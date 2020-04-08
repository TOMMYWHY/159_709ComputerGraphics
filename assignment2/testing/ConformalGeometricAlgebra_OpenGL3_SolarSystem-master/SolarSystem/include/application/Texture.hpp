#ifndef TEXTURE_APPLICATION
#define TEXTURE_APPLICATION

#include <iostream>

#include <GL/glew.h>

#include "glimac/common.hpp"
#include "glimac/Program.hpp"
#include "glimac/FilePath.hpp"
#include "glimac/Image.hpp"

using namespace glimac;
using namespace glm;

struct TexProgram {
    Program m_Program;
    GLint uMVPMatrix;
    GLint uMVMatrix;
    GLint uNormalMatrix;
    GLint uTexture;

    TexProgram(const FilePath& applicationPath):
        m_Program(loadProgram(applicationPath.dirPath() + "shaders/3D.vs.glsl",
                              applicationPath.dirPath() + "shaders/tex3D.fs.glsl")) {
        uMVPMatrix      = glGetUniformLocation(m_Program.getGLId(), "uMVPMatrix"    );
        uMVMatrix       = glGetUniformLocation(m_Program.getGLId(), "uMVMatrix"     );
        uNormalMatrix   = glGetUniformLocation(m_Program.getGLId(), "uNormalMatrix" );
        uTexture        = glGetUniformLocation(m_Program.getGLId(), "uTexture"      );
    }
};

struct TexSkyBox {
    glimac::Program m_Program;
    GLint uCubemap;
    GLint uMVP;
    TexSkyBox(const glimac::FilePath& applicationPath): m_Program(loadProgram(applicationPath.dirPath() + "shaders/skybox.vs.glsl",
                                                                            applicationPath.dirPath() + "shaders/skybox.fs.glsl")) {
        uCubemap = glGetUniformLocation(m_Program.getGLId(), "uCubemap");
        uMVP = glGetUniformLocation(m_Program.getGLId(), "uMVP");
    }
};

#endif // TEXTURE_APPLICATION