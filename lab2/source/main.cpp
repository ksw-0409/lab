#define GLM_ENABLE_EXPERIMENTAL
#define GLM_SWIZZLE 
#include<iostream>
#include<glm/glm.hpp>
#include<glm/gtx/string_cast.hpp>

int main() {
    //gml ����
    glm::vec3 v(7, 3, -2);
    glm::vec3 u(10, 4, 2);
    float d = glm::dot(v, u);
    std::cout << "d: " << d << std::endl;

    //�������� cos ������ ��Ÿ�� ���ϱ�
    const double DEGREES_TO_RADIANS = glm::pi<float>() / 180.0;
    const double RADIANS_TO_DEGREES = 180.0 / glm::pi<float>();
    glm::vec3 v2(2.0f, -1.0f, 1.0f);
    glm::vec3 u2(1.0f, 1.0f, 2.0f);
    float d2 = glm::dot(v2, u2);
    float c = d2 / (glm::length(u2) * glm::length(v2));
    //float deg = glm::acos(c) * RADIANS_TO_DEGREES;
    float deg = glm::degrees(glm::acos(c));
    // glm::radians();     glm::degrees(); �Լ��� ��ü ���� ���� ��׸� ��ȯ �Լ� 
    std::cout << "v2 u2 deg: " << deg << std::endl;

    //�������� ������ ���������� ���� �����ϱ� a b=1 / 0<a b <1/a b =0 / -1< a b<0/ a b= -1
    glm::vec3 v3(2.0f, 0.0f, 0.0f);
    glm::vec3 u3(-1.0f, 1.0f, 0.0f);
    float d3 = glm::dot(glm::normalize(v3), glm::normalize(u3));
    std::cout << "v3 u3 dot: " << d3 << std::endl;
    
    //���ͺ��Ұ� ���� ���������� Ȱ�� 
    glm::vec3 v4(1.0f, 2.0f, -1.0f);
    glm::vec3 c4(0.0f, 1.0f, 0.0f);
    glm::vec3 b4= c4*glm::dot(c4, v4);
    glm::vec3 a4 = v4 - b4;
    std::cout << "a: " << glm::to_string(a4) << std::endl << "b: " << glm::to_string(b4) << std::endl;

    //���� ���������� Ȱ��2 ������ �Ÿ� 
    glm::vec3 n5(0.0f, 1.0f, 0.0f);
    glm::vec3 p5(1.0f, 0.0f, 1.0f);
    glm::vec3 x5(-3.0f, 3.0f, 2.0f);
    glm::vec3 v5 = x5 - p5;
    n5 = glm::normalize(n5);
    float d5 = glm::dot(v5, n5);
    std::cout << "d: " << d5 << std::endl;

    return 0;
}
