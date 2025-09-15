#define GLM_ENABLE_EXPERIMENTAL
#define GLM_SWIZZLE 
#include<iostream>
#include<glm/glm.hpp>
#include<glm/gtx/string_cast.hpp>

int main() {
    glm::vec3 v(7.0f, 3.0f, -2.0f);
    glm::vec3 u(10.0f, 4.0f, 2.0f);
    float d = glm::dot(v, u);

    std::cout << "v dot u : " << d << std::endl;

    return 0;
}
