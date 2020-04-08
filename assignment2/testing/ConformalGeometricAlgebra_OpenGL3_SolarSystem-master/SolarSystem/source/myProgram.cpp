#include <iostream>
#include <cstddef>
#include <vector>
#include <cstdlib>
#include <cmath>

#include <GL/glew.h>

#include "c3ga/c3gaTools.hpp"
#include <c3ga/Mvec.hpp>

#include <glimac/SDLWindowManager.hpp>
#include "glimac/Sphere.hpp"
#include "glimac/common.hpp"
#include "glimac/Program.hpp"
#include "glimac/FilePath.hpp"
#include "glimac/glm.hpp"
#include "glimac/Cube.hpp"
#include "glimac/FreeFlyCamera.hpp"

#include "application/SkyBox.hpp"
#include "application/Planete.hpp"

using namespace glimac;
using namespace glm;
      

/** Global varibles **/
const int width_windows = 1920;
const int height_windows = 1280; 
const double ratio_h_w = double (height_windows) / double(width_windows);

SkyBox skyBox;
GLuint texSkyBoxID;
FreeflyCamera Camera;

const std::string PathTexture = "assets/Textures/";
                            /**   Soleil  , Mercure, Venus   , Terre   , Mars    , Jupiter  , Saturne  , Uranus    , Neptune    **/
                    enum planete {Soleil= 0 , Mercure=1, Venus= 2  , Terre= 3  , Mars= 4   , Jupiter= 5 , Saturne= 6 , Uranus= 7   , Neptune= 8  };  /** Used **/
const double DistSoleil[9]    = {0         , 2        , 3         , 4         , 5.5       , 7          , 10         , 13          , 17          };  /** used **/
const double Rotation[9]      = {0         , 5097600  , 20995200  , 86400     , 88596     , 35388      , 36828      , 25320       , 65520       };
const double RotationS[9]     = {2332800.f , 7603200.f, 19353600.f, 31536000.f, 59356800.f, 374328000.f, 929597472.f, 2651218560.f, 5206982400.f}; /** used **/
const double Radius[9]        = {1       , 0.15     , 0.18      , 0.2       , 0.15      , 0.5        , 0.15       , 0.35        , 0.35        };  /** Used **/
        double AngleS[9]      = {0         , 0        , 0         , 0         , 0         , 0          , 0          , 0           , 0           };  /** Used **/
        double AngleLM[9]     = {0         , 0        , 0         , 0         , 0         , 0          , 0          , 0           , 0           };  /** Used **/
Planete planetes[9]          = {Planete() , Planete(), Planete() , Planete() , Planete() , Planete()  , Planete()  , Planete()   , Planete()   };
const std::string textures[9]= {"Sun", "Mercure", "Venus"   , "Earth"   , "Mars"    , "Jupiter"  , "Saturne"  , "Uranus"    , "Neptune"};
const double DistanceMoonFromEarth  = 0.3f;
const double speedTime = 1000;

const c3ga::Mvec<double> AxeX= c3ga::e23<double>();
const c3ga::Mvec<double> AxeY= c3ga::e13<double>();
const c3ga::Mvec<double> AxeZ= c3ga::e12<double>();

/** Methodes **/
void initSkyBox(SkyBox &SkyBox, GLuint &texSkyBoxID);
void drawSkyBox(const SkyBox &SkyBox, const TexSkyBox &skyBoxProgram);

/** Generation d'une comete et sa trajectoire aleatoirement**/
void generateComete(std::vector<Planete*> &vectCometes);


int main(int argc, char** argv) {
    // Initialize SDL and open a window
    SDLWindowManager windowManager(width_windows, height_windows, "MyApplication");

    // Initialize glew for OpenGL3+ support
    GLenum glewInitError = glewInit();
    if(GLEW_OK != glewInitError) {
        std::cerr << glewGetErrorString(glewInitError) << std::endl;
        return EXIT_FAILURE;
    }

    std::cout << "OpenGL Version : " << glGetString(GL_VERSION) << std::endl;
    std::cout << "GLEW Version : " << glewGetString(GLEW_VERSION) << std::endl;

    /*********************************
     * HERE SHOULD COME THE INITIALIZATION CODE
     *********************************/
    FilePath applicationPath(argv[0]);
    /** SkyBox Univers **/
    TexSkyBox skyBoxProgram(applicationPath);
    initSkyBox(skyBox, texSkyBoxID);

    std::vector<Planete*> vectCometes;

     /**   Soleil  , Mercure, Venus   , Terre   , Mars    , Jupiter  , Saturne  , Uranus    , Neptune    **/
    TexProgram planetProgram(applicationPath);
    for(int i = 0; i < 9; i++){
        planetes[i].bindTexture("assets/Textures/"+textures[i]+"Texture.jpg");
        planetes[i].scale(Radius[i]);
        planetes[i].translate(DistSoleil[i], 0.f, 0.f);
        planetes[i].generatePlanete();
    }

    /** moon **/
    TexProgram moonProgram(applicationPath);
    Planete moon(1);
    moon.bindTexture("assets/Textures/MoonTexture.jpg");
     /** earth.rotateZ(90); Rotation de la terre autour d'elle emme a revoir **/
    moon.scale(0.02);//Radius[Terre]);
    moon.translate(DistanceMoonFromEarth, 0.f, 0.f);    // La distace entre la lune et la terre
    moon.generatePlanete();

    TexProgram cometeProgram(applicationPath);
    generateComete(vectCometes);

    glEnable(GL_DEPTH_TEST);
    glm::mat4 ProjMatrix = glm::perspective(glm::radians(70.f), 800.f/600.f, 0.1f, 100.f);
    
    glm::ivec2 lastmousePos;
    bool flag = false;

    double speedcam = 0.25;
    // Application loop:
    bool done = false;

    while (!done) {
        /** Debut de Gestion des evenements souris et clavier **/
        SDL_Event e;
        while (windowManager.pollEvent(e)) {
            if (e.type == SDL_QUIT || windowManager.isKeyPressed(SDLK_ESCAPE)) {
                done = true;
            }
            /** Generation d'une comete Aleatoire ainsi que sa trajectoire **/
            if (windowManager.isKeyPressed(SDLK_c) == true) {
                generateComete(vectCometes);
            }
        }
        //** Gestion de la souris **/
        if (windowManager.isMouseButtonPressed(SDL_BUTTON_LEFT) == true) {
            SDL_GetRelativeMouseState(&lastmousePos.x, &lastmousePos.y);
            if (flag == true) {
                Camera.rotateLeft(lastmousePos.x / 5);
                Camera.rotateUp(lastmousePos.y / 5);
            }
            flag = true;
        }
        else {
            flag = false;
        }
        /** Gestion des touches de clavier **/

        if (windowManager.isKeyPressed(SDLK_z) == true) {
            Camera.moveFront(speedcam);
        }
        if (windowManager.isKeyPressed(SDLK_q) == true) {
            Camera.moveLeft(speedcam);
        }

        if (windowManager.isKeyPressed(SDLK_s) == true) {
            Camera.moveFront(-speedcam);
        }

        if (windowManager.isKeyPressed(SDLK_d) == true) {
            Camera.moveLeft(-speedcam);
        }
        /** Fin de Gestion des evenements souris et clavier **/

        /*************************************
        * HERE SHOULD COME THE RENDERING CODE*
        **************************************/
        /** Réinitialiser la fenetre **/
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        /** Afficher la SkyBox **/
        drawSkyBox(skyBox, skyBoxProgram);


         /** Afficher les planetes **/
        for (int i = 0; i<9; i++){
            planetes[i].rotate((360.f/RotationS[i]) * speedTime, AxeZ);
            planetes[i].drawPlanete(Camera, planetProgram, ProjMatrix);
        }

        /** Afficher la Lune **/
        moon.rotate((360.f/(28.5 * 24 * 3600)) * speedTime, AxeZ);  /** Rotation de la lune autour de la terre ( a revoir coté affichge)**/ 
        moon.rotate(5.145f, AxeY);
        c3ga::Mvec<double> centerOfEarth;
        double radiusOfEarth;
        radiusAndCenterFromDualSphere((planetes[3].getSphere()).dual(), radiusOfEarth, centerOfEarth);
        moon.translate(centerOfEarth[c3ga::E1], centerOfEarth[c3ga::E2], centerOfEarth[c3ga::E3]);    // La distace du soleil
        // moon.generatePlanete();
        moon.drawPlanete(Camera, moonProgram, ProjMatrix);
        moon.translate(-centerOfEarth[c3ga::E1], -centerOfEarth[c3ga::E2], -centerOfEarth[c3ga::E3]);
        moon.rotate(-5.149f, AxeY);

        /** Afficher les cometes **/
        for(auto comete:vectCometes){
            comete->translate(comete->getPasTranslation().x, 0, 0);
            comete->translate(0, comete->getPasTranslation().y, 0);
            comete->translate(0, 0, comete->getPasTranslation().z);
            comete->drawPlanete(Camera, cometeProgram, ProjMatrix);
            for(auto planet:planetes){
                c3ga::Mvec<double> inter = !(!planet.getSphere() ^ !comete->getSphere());
                if (whoAmI(inter) == "circle (imaginary dual pair point)"){
                    /** remove comete if intersection **/
                    vectCometes.erase(std::remove(vectCometes.begin(), vectCometes.end(), comete), vectCometes.end());
                }
            }     
        }
        
        // Update the display
        windowManager.swapBuffers();
    }
    return EXIT_SUCCESS;
}

void initSkyBox(SkyBox &skyBox, GLuint &texSkyBoxID){
    double size_cube = 1;
    Cube cubeSkybox(size_cube);
    GLsizei count_vertex_skybox = cubeSkybox.getVertexCount();
    const ShapeVertex*  Datapointeur_skybox = cubeSkybox.getDataPointer();
    ShapeVertex verticesSkybox[count_vertex_skybox];
    for (auto i = 0; i < count_vertex_skybox; i++) { // Skybox
        verticesSkybox[i] = *Datapointeur_skybox;
        verticesSkybox[i].position.x -= 0.5;
        verticesSkybox[i].position.y -= 0.5;
        verticesSkybox[i].position.z += 0.5;
        Datapointeur_skybox++;
    }
    skyBox = SkyBox(count_vertex_skybox, verticesSkybox);
    std::vector<std::string> skyBoxTextures {
        "assets/Textures/skyBox/skyBox_1.png",   //R
        "assets/Textures/skyBox/skyBox_2.png",   //l
        "assets/Textures/skyBox/skyBox_3.png",   //top   
        "assets/Textures/skyBox/skyBox_4.png",   //Butt
        "assets/Textures/skyBox/skyBox_5.png",   //front
        "assets/Textures/skyBox/skyBox_6.png"    //back
    };
    texSkyBoxID = skyBox.loadTexture(skyBoxTextures);
};

void drawSkyBox(const SkyBox &SkyBox, const TexSkyBox &skyBoxProgram){
    glm::mat4  VMatrix = Camera.getViewMatrix();
    skyBox.drawSkyBox(skyBoxProgram, texSkyBoxID, ratio_h_w, VMatrix);
};

void generateComete(std::vector<Planete*> &vectCometes){
    Planete *comete = new Planete(1);
    comete->bindTexture("assets/Textures/CometeTexture.jpg");
    int tab[2] = {-1,1};
    bool found =  false;
    glm::vec3 posComete;
    while(!found){
        int cometeX = (rand() % 25) * (tab[rand()%2]);
        int cometeY = (rand() % 25) * (tab[rand()%2]);
        int cometeZ = (rand() % 25) * (tab[rand()%2]);
        if ((std::pow(cometeX, 2) + std::pow(cometeY, 2) + std::pow(cometeZ, 2) > std::pow(17, 2)) && (std::pow(cometeX, 2) + std::pow(cometeY, 2) + std::pow(cometeZ, 2) < std::pow(25, 2)))
        found = true;
        posComete = glm::vec3(cometeX, cometeY, cometeZ);
    }
    
    comete->scale(0.3);
    comete->translate(posComete.x, posComete.y, posComete.z);
    comete->generatePlanete();

    {
        int directionX = (rand() % 2) * (tab[rand()%2]);
        int directionY = (rand() % 2) * (tab[rand()%2]);
        int directionZ = (rand() % 2) * (tab[rand()%2]);
        glm::vec3 directionComete(directionX, directionY, directionZ);
        glm::vec3 Trajectoire = posComete - directionComete;
    
        double trajectoireLenght = glm::length(Trajectoire);

        double speed = -0.1;
        float pasX = speed * Trajectoire.x / trajectoireLenght;
        float pasY = speed * Trajectoire.y / trajectoireLenght;
        float pasZ = speed * Trajectoire.z / trajectoireLenght;
        glm::vec3 pasTranslation(pasX, pasY, pasZ);
        comete->setPasTranslation(pasTranslation);
    }

    vectCometes.push_back(comete);
};