#ifndef PLANET_APPLICATION
#define PLANET_APPLICATION

#include <iostream>

#include <GL/glew.h>

#include "glimac/glm.hpp"
#include <glimac/SDLWindowManager.hpp>
#include "glimac/Sphere.hpp"
#include "glimac/FreeflyCamera.hpp"

#include "application/Versor.hpp"
#include "application/Texture.hpp"

#include "c3ga/c3gaTools.hpp"
#include "c3ga/Entry.hpp"

class Planete{
    private:
        /* data */
        GLuint vao;
        GLuint vbo;
        GLuint textureID;
        
        Sphere sphere;
        c3ga::Mvec<double> sphereC3GA;
        c3ga::Mvec<double> dualSphereC3GA;
        Versor<double> transformation;
        c3ga::Mvec<double> centerC3GA;
        double radius;

        // Juste pour les cometes
        glm::vec3 pasTranslation;

        /* Methdoes */
        void initVAO();
        void initVBO();

       
    public:
        /** Constructor **/
        Planete(const double _radius=1);

         /** Destructor **/
        ~Planete(){};

        /** position sphere in coordinate (x,y,z) after All trasformation with c3ga to dispaly **/
        void generatePlanete();

         /** generate Sphere c3ga and sphere OpenGL **/ // --> Use in Constructor
        void createSphere();

        /** Bind texture of sphere **/
        void bindTexture(const std::string PathFile);

        /** Get sphere of c3ga **/ // --> used particularu for Moon, he need position of Earth
        c3ga::Mvec<double> getSphere();

        /** Apply Rotation with c3ga **/
        void rotate(const double angle, const c3ga::Mvec<double> Axe);

        /** Apply translaion with c3ga **/
        void translate(const double distanceX = 0.f, const double distanceY = 0.f, const double distanceZ = 0.f);

        /** Apply scale with c3ga **/
        void scale(const double factor);

        /** Display planet in OpenGL **/
        void drawPlanete(const FreeflyCamera Camera, const TexProgram &Program, const glm::mat4 ProjMatrix);
        
        void setPasTranslation(glm::vec3 vec){
            pasTranslation = vec;
        };

        glm::vec3 getPasTranslation(){
            return pasTranslation;
        };
};

#endif // PLANET_APPLICAtION