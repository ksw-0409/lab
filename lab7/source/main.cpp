#define GLM_ENABLE_EXPERIMENTAL
#define GLM_SWIZZLE 
#include<iostream>
#include<glm/glm.hpp>
#include<glm/gtx/string_cast.hpp>
#include<glm/gtx/matrix_transform_2d.hpp>

glm::mat4 lookAt(glm::vec3 campos, glm::vec3 look, glm::vec3 up);

int main() {
    glm::vec3 campos = { 5.0f,5.0f,5.0f };
    glm::vec3 look = { 0.0f,0.0f,0.0f };
    glm::vec3 up = { 0.0f,1.0f,0.0f };

    glm::mat4 lookatm = lookAt(campos, look, up);

    std::cout << glm::to_string(lookatm) << std::endl;
    return 0;
}

glm::mat4 lookAt(glm::vec3 campos, glm::vec3 look, glm::vec3 up) {
    glm::vec3 z = glm::normalize(campos - look);
    glm::vec3 x = glm::normalize(glm::cross(up, z));
    glm::vec3 y = glm::normalize(glm::cross(z, x));

    glm::mat4 t(1.0);
    glm::vec3 offset = glm::vec3(-campos.x, -campos.y, -campos.z);
    glm::mat4 trans = glm::translate(t, offset);

    glm::mat4 rota = { glm::vec4(x.x, y.x, z.x, 0.0f),
    glm::vec4(x.y, y.y, z.y, 0.0f),
    glm::vec4(x.z, y.z, z.z, 0.0f), 
    glm::vec4(0.0f, 0.0f, 0.0f, 1.0f)};
    return rota * trans;
}
