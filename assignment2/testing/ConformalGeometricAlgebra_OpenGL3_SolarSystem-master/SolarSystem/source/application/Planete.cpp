#include "application/Planete.hpp"


Planete::Planete(const double _radius): radius(_radius){
    /** init sphereC3GA **/
    createSphere();
};

void Planete::createSphere(){
    c3ga::Mvec<double> pt1 = c3ga::point<double>(0,0,radius);
    c3ga::Mvec<double> pt2 = c3ga::point<double>(-radius, 0, 0);
    c3ga::Mvec<double> pt3 = c3ga::point<double>(0, radius, 0);
    c3ga::Mvec<double> pt4 = c3ga::point<double>(0, -radius, 0);
    sphereC3GA = (pt1 ^ pt2 ^ pt3 ^ pt4);
    dualSphereC3GA = sphereC3GA.dual();

    // c3ga::Mvec<double> centerP = c3ga::point<double>(0,0,0);
    // dualSphereC3GA = centerP - (radius * radius * 2) / 2 * c3ga::ei<double>();
    // sphereC3GA = dualSphereC3GA.dual();
};

void Planete::initVBO(){
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    // Données récupérées de la class Cube ( voir fichier cpp + hpp)
    glBufferData(GL_ARRAY_BUFFER, sphere.getVertexCount() * sizeof(ShapeVertex), sphere.getDataPointer(), GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Planete::initVAO(){
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glEnableVertexAttribArray(VERTEX_ATTR_POSITION);
    glEnableVertexAttribArray(VERTEX_ATTR_NORMAL);
    glEnableVertexAttribArray(VERTEX_ATTR_TEXTURE);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
        GLsizei stride = sizeof(ShapeVertex);  // le nombre d'octets séparant l'attribut pour deux sommets consécutifs.
    glVertexAttribPointer(VERTEX_ATTR_POSITION, 3, GL_FLOAT, GL_FALSE, stride , (const GLvoid*)offsetof(ShapeVertex, position));
    glVertexAttribPointer(VERTEX_ATTR_NORMAL, 3, GL_FLOAT, GL_FALSE, stride , (const GLvoid*)offsetof(ShapeVertex, normal));
    glVertexAttribPointer(VERTEX_ATTR_TEXTURE, 2, GL_FLOAT, GL_FALSE, stride , (const GLvoid*)offsetof(ShapeVertex, texCoords));
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);  
};

void Planete::generatePlanete(){
    double radiusC3ga ;
    dualSphereC3GA = sphereC3GA.dual();
    radiusAndCenterFromDualSphere(dualSphereC3GA, radiusC3ga, centerC3GA);
    /** After Scale and all transformation**/
    radius = radiusC3ga / 2.f;
    sphere = Sphere(radius); // rayon = 1, latitude = 32, longitude = 16
    //Creation du VBO
    initVBO();
    //Creation du VAO
    initVAO();
};

void Planete::bindTexture(const std::string PathFile){
    std::unique_ptr<Image> texImg = loadImage(FilePath(PathFile));
    if (texImg == NULL) {
        std::cerr << "Impossible de charger l'image dans le chemin est " << PathFile << " car elle n'a pas été trouvée !! \n" << std::endl;
        exit(0);
    }
    glGenTextures(1, &textureID);

    glBindTexture(GL_TEXTURE_2D, textureID);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texImg->getWidth(), texImg->getHeight(), 0, GL_RGBA, GL_FLOAT, texImg->getPixels());
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glBindTexture(GL_TEXTURE_2D, 0);
};

c3ga::Mvec<double> Planete::getSphere(){
    return sphereC3GA;
};

void Planete::translate(const double distanceX, const double distanceY, const double distanceZ ){
    c3ga::Mvec<double> T = 1 - 0.5 * transformation.translator(distanceX, distanceY, distanceZ) * c3ga::ei<double>();
	sphereC3GA = T * sphereC3GA * T.inv();
    //sphereC3GA.roundZero(1.0e-10);
}

void Planete::rotate(const double angle, const c3ga::Mvec<double> Axe){
    c3ga::Mvec<double> R = transformation.rotator(angle, Axe);
    sphereC3GA = R * sphereC3GA * R.inv();
    //sphereC3GA.roundZero(1.0e-10);
}

void Planete::scale(const double factor){
    c3ga::Mvec<double> D = transformation.dilator(factor);
    sphereC3GA = D * sphereC3GA * D.inv(); 
    //sphereC3GA.roundZero(1.0e-10);
}

void Planete::drawPlanete(const FreeflyCamera Camera, const TexProgram &Program, const glm::mat4 ProjMatrix){
    glBindVertexArray(vao);
    Program.m_Program.use();
    glUniform1i(Program.uTexture, 0);

    dualSphereC3GA = sphereC3GA.dual();
    radiusAndCenterFromDualSphere(dualSphereC3GA, radius, centerC3GA);
    glm::vec3 vecPos = glm::vec3(centerC3GA[c3ga::E1] , centerC3GA[c3ga::E2], centerC3GA[c3ga::E3]);
    glm::mat4 globalMVMatrix = Camera.getViewMatrix();
    glm::mat4 MVMatrix = glm::translate(globalMVMatrix, vecPos);
   
    glUniformMatrix4fv(Program.uMVMatrix, 1, GL_FALSE, glm::value_ptr(MVMatrix));
    glUniformMatrix4fv(Program.uNormalMatrix, 1, GL_FALSE, glm::value_ptr(glm::transpose(glm::inverse(MVMatrix))));
    glUniformMatrix4fv(Program.uMVPMatrix, 1, GL_FALSE, glm::value_ptr(ProjMatrix * MVMatrix));

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textureID);
    glDrawArrays(GL_TRIANGLES, 0, sphere.getVertexCount());
 
    glUniform1i(Program.uTexture, 0);
};
