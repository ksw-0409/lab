#define GLM_ENABLE_EXPERIMENTAL
#define GLM_SWIZZLE 
#include<iostream>
#include<glm/glm.hpp>
#include<glm/gtx/string_cast.hpp>
#include<glm/gtx/matrix_transform_2d.hpp>

glm::mat4 lookAt(glm::vec3 campos, glm::vec3 look, glm::vec3 up);

int main() {
    glm::vec4 m(4.0f, 5.0f, 3.0f, 1.0f);

    //������Ʈ 
    glm::mat4 rx = glm::rotate(glm::mat4(1.0f), glm::radians(40.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    glm::mat4 rz= glm::rotate(glm::mat4(1.0f), glm::radians(0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    glm::mat4 ry = glm::rotate(glm::mat4(1.0f), glm::radians(56.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    glm::mat4 rot = rx * ry * rz;
    //Ʈ����
    glm::vec3 offset(0.0f, 5.0f, 0.0f);
    glm::mat4 trans = glm::translate(glm::mat4(1.0f), offset);
    //������
    glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(1.3f, 1.3f, 1.3f));

    glm::mat4 modle = trans * rot * scale;
    //std::cout << to_string(modle*m) << std::endl;
    //�� ���
    glm::mat4 view = { 
        {0.83f,-0.3f,0.47f,0.0f},
        {0.0f,0.84f,0.54f,0.0f},
        {-0.56f,-0.45f,0.7f,0.0f},
        {0.0f,0.0f,-44.47f,1.0f}
    };
    //�� view ��Ŀ��� ī�޶���ġ, ī�޶� �����ִ����� �˱�
    // view ����� world -> camera �����ϴ� ���
    // inverse(view) �� camera->world ����� �ȴ� 
  
    glm::mat4 inView = glm::inverse(view);
    //inView �� ������ �ݷ��� ī�޶� ��ġ�� �ȴ� 
    
    glm::vec3 camPos=inView[3]; //ī�޶� ��ġ 
    //view ������ 3���� ���� ���ߴµ� ī�޶�� - z ������ �ٶ󺻴� ����
    
    //ī�޶�� -z ���� �ٶ󺸰� ���� 
    glm::vec3 z_axis = glm::normalize(- inView[2]);

    glm::vec3 look = camPos+z_axis*10.0f;
    glm::vec3 up(0, 1, 0);
    glm::mat4 myView = lookAt(camPos, look, up);
    std::cout << "view: " << glm::to_string(view) << std::endl << "my: " << glm::to_string(myView) << std::endl;
    return 0;
}

glm::mat4 lookAt(glm::vec3 campos, glm::vec3 look, glm::vec3 up) {
    glm::vec3 z = glm::normalize(campos - look);
    glm::vec3 x = glm::normalize(glm::cross(up, z));
    glm::vec3 y = glm::normalize(glm::cross(z, x));

    glm::mat4 t(1.0);
    glm::mat4 trans = glm::translate(t, -campos);

    glm::mat4 rota = { glm::vec4(x.x, y.x, z.x, 0.0f),
    glm::vec4(x.y, y.y, z.y, 0.0f),
    glm::vec4(x.z, y.z, z.z, 0.0f),
    glm::vec4(0.0f, 0.0f, 0.0f, 1.0f) };
    return rota * trans;
}