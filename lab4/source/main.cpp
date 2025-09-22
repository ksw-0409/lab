#define GLM_ENABLE_EXPERIMENTAL
#define GLM_SWIZZLE 
#include<iostream>
#include<glm/glm.hpp>
#include<glm/gtx/string_cast.hpp>

int main() {    
    //glm 외적 |a||b|sin() 값 확인  
    glm::vec3 u (1.0f, 0.0f, 0.0f);
    glm::vec3 v(-1.0f, 1.0f, 0.0f);
    glm::vec3 c = glm::cross(u, v);
    float l = glm::length(c); 
    float ang = glm::acos(glm::dot(u, v) / (glm::length(u) * glm::length(v)));
    float l2 = glm::length(u) * glm::length(v) * sin(ang);
    std::cout << "l: " << l << '\n' << "ang: " << glm::degrees(ang) << '\n' << "l2: " << l2 << '\n'<<'\n';
    
    //외적결과벡터의 길이와 평행사변형의 크기는 같다 
    glm::vec3 u2(1.0f, 0.0f, 0.0f);
    glm::vec3 v2(0.0f, 1.0f, 0.0f);
    float area = glm::length(glm::cross(u2, v2));
    std::cout << "area: " << area << '\n' << '\n';

    //평행된 두 벡터 외적
    glm::vec3 u3(1.0f, 0.0f, 0.0f);
    glm::vec3 v3(1.0f, 0.0f, 0.0f);
    float c3 = glm::length(glm::cross(u3, v3));
    std::cout << "cross3: " << c3 << '\n' << '\n';

    //삼각형의 넓이 구하기 평행사변형 활용
    glm::vec3 p4_1(1.0f, 0.0f, 0.0f);
    glm::vec3 p4_2(1.0f, 1.0f, 0.0f);
    glm::vec3 p4_3(-1.0f, 0.0f, 0.0f);
    glm::vec3 v4_1 = p4_3 - p4_2;
    glm::vec3 v4_2 = p4_1 - p4_2;
    float area4 = glm::length(glm::cross(v4_1, v4_2)) *0.5f;
    std::cout << "area4: " << area4 << '\n' << '\n';
    
    //평면 삼각형의 normal vector 구하기 
    glm::vec3 p5_1(3.0f, 0.0f, 0.0f);
    glm::vec3 p5_2(1.5f, 0.86f, 0.0f);
    glm::vec3 p5_3(3.0f, 0.0f, -1.0f);

    glm::vec3 v5_1 = p5_2 - p5_3;
    glm::vec3 v5_2 = p5_1 - p5_3;
  
    glm::vec3 n_v5 = glm::normalize(glm::cross(v5_2, v5_1));
   
    std::cout << "normal vector: " << glm::to_string(n_v5) << '\n' << '\n';

    return 0;
}
