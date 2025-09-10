#define GLM_ENABLE_EXPERIMENTAL
#define GLM_SWIZZLE 
#include<iostream>
#include<glm/glm.hpp>
#include<glm/gtx/string_cast.hpp>

int main() {
    //Q1
    std::cout << "1. ";
    glm::vec3 p(1.0f, 4.0f, -5.0f);
    glm::vec3 v(5.0f, 1.0f, 4.0f);
    p = p + v;
    std::cout<<glm::to_string(p)<<std::endl;

    //Q2
    std::cout << "2. ";
    glm::vec3 v1(1.0f, 0.0f, 0.0f);
    glm::vec3 v2(0.0f, 1.0f, 0.0f);
    glm::vec3 result2;
    result2 = v1 + v2;
    std::cout << glm::to_string(result2) << std::endl;

    //Q3
    std::cout << "3. ";
    glm::vec3 v3(0.0f, 1.0f, 0.0f);
    v3 *= 2.0f;
    std::cout << glm::to_string(v3) << std::endl;

    //Q4
    std::cout << "4. ";
    glm::vec3 start(8.0f, 2.0f, 5.0f);
    glm::vec3 end(1.0f, -1.0f, 4.0f);   
    glm::vec3 v4 = end - start;
    std::cout << glm::to_string(v4) << std::endl;

    //Q5
    std::cout << "5. ";
    glm::vec3 v5(1.0f, 3.0f, 4.0f);
    glm::vec3 v5_n;
    v5_n = glm::normalize(v5);  
    //v5 /= sqrt((v5.x * v5.x + v5.y * v5.y + v5.z * v5.z));  流立 备泅茄 规过涝聪促 
    std::cout << glm::to_string(v5_n) << std::endl;

    //Q6
    std::cout << "6. ";
    glm::vec3 v6(1.0f, -1.0f, 4.0f);
    glm::vec4 result6(v6, 0.0f);
    std::cout << glm::to_string(result6) << std::endl;

    return 0;
}
