#define GLM_ENABLE_EXPERIMENTAL
#define GLM_SWIZZLE 
#include<iostream>
#include<glm/glm.hpp>
#include<glm/gtx/string_cast.hpp>
#include<glm/mat4x4.hpp>
#include<glm/mat2x2.hpp>
#include<glm/mat3x2.hpp>

int main() {
    //행렬 초기화 방법 
    glm::vec4 v1 = { 1,0,1,-1 };
    glm::vec4 v2 = { 1,0,1,-1 };
    glm::vec4 v3 = { 1,0,1,-1 };
    glm::vec4 v4 = { 1,0,1,-1 };
    glm::mat4 m;
    m[0] = v1; m[1] = v2; m[2] = v3; m[3] = v4;
    std::cout << glm::to_string(m) << '\n';

    glm::mat2 m2 = { 1,0,1,-1 }; //2x2 
    std::cout << glm::to_string(m2) << '\n';

    glm::mat3x2 m3 = { {1,0},{1,-1},{0,1} }; //수학적으로보면 2x3행렬이다 
    std::cout << glm::to_string(m3) << '\n';

    glm::mat2 m4_1 = { 1,0,1,-1 };
    glm::mat2 m4_2 = { 0,1,1,-1 };
    glm::mat2 m4_3 = m4_1 * m4_2;
    std::cout << glm::to_string(m4_3) << '\n';
    
    //행렬곱 순서에따른 결과가 다르다 AB != BA
    glm::mat3 A = { {1,1,-1 },{0,2,0},{2,3,1} };
    glm::mat3 B = { {1,0,0},{0,-1,1},{0,1,2} };
    glm::mat3 AB = A * B;
    glm::mat3 BA = B * A;
    std::cout << "AB: " << glm::to_string(AB) << '\n' << "BA: " << glm::to_string(BA) << '\n';
    
    //역행렬
    glm::mat2 A2 = { {4,1},{8,3} };
    glm::mat2 A2i = glm::inverse(A2);
    std::cout << "A inverse: " << glm::to_string(A2i) << '\n';
    glm::mat2 I = A2 * A2i;
    std::cout << "I: " << glm::to_string(I) << '\n';

    //행렬과 백터의 곱 
    glm::vec3 a(1, 2, 3);
    glm::mat3 m5 = { {1,0,0},{2,-1,0},{3,0,1} };
    std::cout << "A * M: " << glm::to_string(a * m5) << '\n' << "M * A: " << glm::to_string(m5 * a) << '\n';
    return 0;
}
