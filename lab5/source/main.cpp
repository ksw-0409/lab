#define GLM_ENABLE_EXPERIMENTAL
#define GLM_SWIZZLE 
#include<iostream>
#include<glm/glm.hpp>
#include<glm/gtx/string_cast.hpp>
#include<glm/mat4x4.hpp>
#include<glm/mat2x2.hpp>
#include<glm/mat3x2.hpp>

int main() {
    //��� �ʱ�ȭ ��� 
    glm::vec4 v1 = { 1,0,1,-1 };
    glm::vec4 v2 = { 1,0,1,-1 };
    glm::vec4 v3 = { 1,0,1,-1 };
    glm::vec4 v4 = { 1,0,1,-1 };
    glm::mat4 m;
    m[0] = v1; m[1] = v2; m[2] = v3; m[3] = v4;
    std::cout << glm::to_string(m) << '\n';

    glm::mat2 m2 = { 1,0,1,-1 }; //2x2 
    std::cout << glm::to_string(m2) << '\n';

    glm::mat3x2 m3 = { {1,0},{1,-1},{0,1} }; //���������κ��� 2x3����̴� 
    std::cout << glm::to_string(m3) << '\n';

    glm::mat2 m4_1 = { 1,0,1,-1 };
    glm::mat2 m4_2 = { 0,1,1,-1 };
    glm::mat2 m4_3 = m4_1 * m4_2;
    std::cout << glm::to_string(m4_3) << '\n';
    
    //��İ� ���������� ����� �ٸ��� AB != BA
    glm::mat3 A = { {1,1,-1 },{0,2,0},{2,3,1} };
    glm::mat3 B = { {1,0,0},{0,-1,1},{0,1,2} };
    glm::mat3 AB = A * B;
    glm::mat3 BA = B * A;
    std::cout << "AB: " << glm::to_string(AB) << '\n' << "BA: " << glm::to_string(BA) << '\n';
    
    //�����
    glm::mat2 A2 = { {4,1},{8,3} };
    glm::mat2 A2i = glm::inverse(A2);
    std::cout << "A inverse: " << glm::to_string(A2i) << '\n';
    glm::mat2 I = A2 * A2i;
    std::cout << "I: " << glm::to_string(I) << '\n';

    //��İ� ������ �� 
    glm::vec3 a(1, 2, 3);
    glm::mat3 m5 = { {1,0,0},{2,-1,0},{3,0,1} };
    std::cout << "A * M: " << glm::to_string(a * m5) << '\n' << "M * A: " << glm::to_string(m5 * a) << '\n';
    return 0;
}
