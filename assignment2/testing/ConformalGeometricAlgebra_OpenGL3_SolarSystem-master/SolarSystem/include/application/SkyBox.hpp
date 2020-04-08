#ifndef SKYBOX_APPLICAtION
#define SKYBOX_APPLICAtION

#include <iostream>

#include <GL/glew.h>

#include "glimac/common.hpp"
#include "glimac/Program.hpp"
#include "glimac/FilePath.hpp"

#include "application/Texture.hpp"

using namespace glimac;
using namespace glm;

class SkyBox {
	public :
		// Constructor
        SkyBox(){};
        SkyBox(const GLsizei count_vertex_skybox, const ShapeVertex *verticesSkyBox);

        // Destructor
        ~SkyBox(){};

        /** Load and bind texture for SkyBox **/
        GLuint loadTexture(std::vector<std::string> faces);

        /** Display The SkyBox **/
        void drawSkyBox(const TexSkyBox &skyBoxTexture, const GLuint &cubeMapTexture, float ratio_h_w, glm::mat4 VMatrix);

    private :
        GLuint vao;
    	GLuint vbo;

        /* Methdoes */
        void initVAO();
        void initVBO(const GLsizei count_vertex_skybox, const ShapeVertex *verticesSkyBox);

};

#endif // SKYBOX_APPLICAtION