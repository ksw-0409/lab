#define GLM_ENABLE_EXPERIMENTAL
#define GLM_SWIZZLE 
#include<iostream>
#include<glm/glm.hpp>
#include<glm/gtx/string_cast.hpp>
#include<glm/gtx/matrix_transform_2d.hpp>

int main() {
    //1�� ��ġ�̵� 
    glm::vec3 v(5.0f, 6.0f, 1.0f);
    glm::mat3 t(1.0f); //������� ����� ���(�밢���� 1 �������� 0)
    t = glm::translate(t, glm::vec2(2, 3)); //��ȯ��� ����� �Լ�vec2����ŭ �̵���Ű�� ��ȯ���
    
    v = t * v;
    std::cout << glm::to_string(t) << '\n';
    std::cout << glm::to_string(v) << '\n';

    //2�� ũ������
    glm::vec3 v2(5.0f, 6.0f, 1.0f);
    glm::mat3 t2(1.0f); 
    t2 = glm::scale(t2, glm::vec2(3, 4)); 
    //��ȯ��ĸ�����Լ� vec2����ŭ x������ n�� y ������ n�� 
    
    v2 = t2 * v2;
    std::cout << glm::to_string(t2) << '\n';
    std::cout << glm::to_string(v2) << '\n';

    //3�� ȸ��
    glm::vec3 v3(5.0f, 6.0f, 1.0f);
    glm::mat3 t3(1.0f);
    t3 = glm::rotate(t3, glm::radians(45.0f)); 
    //��ȯ��� ������Լ� ���Ȱ��� ��ȯ�ؾ��Ա׷��� �� �Լ� ��� 45.0f ��ŭ �ݽð�� ȸ�� 
    //glm ���� ��� ������ �������� �Ѵ�
    v3 = t3 * v3;
    std::cout << glm::to_string(t3) << '\n';
    std::cout << glm::to_string(v3) << '\n';

    return 0;
}
