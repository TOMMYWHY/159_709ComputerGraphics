//
// Created by Tommy on 2020-03-09.
//

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

using namespace std;

int main(){
    cout <<"testing...."<<endl;
    glm::vec4 vec(1.0f, 0.0f, 0.0f, 1.0f);

    glm::mat4 trans;
    trans = glm::translate(trans, glm::vec3(1.0f, 1.0f, 0.0f));
    vec = trans * vec;
    std::cout << "X:"<<vec.x<<" Y:" << vec.y << " Z:"<< vec.z << std::endl;

    return 0;

}