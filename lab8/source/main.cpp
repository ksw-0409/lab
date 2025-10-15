#define GLM_ENABLE_EXPERIMENTAL
#define GLM_SWIZZLE 
#include<iostream>
#include<glm/glm.hpp>
#include<glm/gtx/string_cast.hpp>
#include<glm/gtx/matrix_transform_2d.hpp>

glm::mat4 perspective(float fovY, float aspect, float near, float far);

int main() {
    float width = 780.0f;
    float height = 750.0f;
    float fovY = 45.0f;
    fovY = glm::radians(fovY);
    float nearZ = 0.1f;
    float farZ = 500.0f;
    float aspect = width / height;
    
    glm::mat4 ppmat = perspective(fovY, aspect, nearZ, farZ);
    
    std::cout << glm::to_string(ppmat) << std::endl;

    return 0;
}

glm::mat4 perspective(float fovY, float aspect, float near, float far) {
    glm::mat4 projection_matrix(0.0f);
    projection_matrix[0][0] = 1.0f / (aspect * glm::tan(fovY / 2.0f));
    projection_matrix[1][1] = 1.0f / (glm::tan(fovY / 2.0f));
    projection_matrix[2][2] = -(far + near) / (far - near);
    projection_matrix[2][3] = -1.0f;
    projection_matrix[3][2] = -(2.0f * far * near) / (far - near);
    return projection_matrix;
}
