#define GLM_ENABLE_EXPERIMENTAL
#define GLM_SWIZZLE 
#include<iostream>
#include<glm/glm.hpp>
#include<glm/gtx/string_cast.hpp>
#include<glm/gtx/matrix_transform_2d.hpp>

int main() {
    //1번 위치이동 
    glm::vec3 v(5.0f, 6.0f, 1.0f);
    glm::mat3 t(1.0f); //단위행렬 만드는 방법(대각선만 1 나머지는 0)
    t = glm::translate(t, glm::vec2(2, 3)); //변환행렬 만드는 함수vec2값만큼 이동시키는 변환행렬
    
    v = t * v;
    std::cout << glm::to_string(t) << '\n';
    std::cout << glm::to_string(v) << '\n';

    //2번 크기조절
    glm::vec3 v2(5.0f, 6.0f, 1.0f);
    glm::mat3 t2(1.0f); 
    t2 = glm::scale(t2, glm::vec2(3, 4)); 
    //변환행렬만드는함수 vec2값만큼 x축으로 n배 y 축으로 n배 
    
    v2 = t2 * v2;
    std::cout << glm::to_string(t2) << '\n';
    std::cout << glm::to_string(v2) << '\n';

    //3번 회전
    glm::vec3 v3(5.0f, 6.0f, 1.0f);
    glm::mat3 t3(1.0f);
    t3 = glm::rotate(t3, glm::radians(45.0f)); 
    //변환행렬 만드는함수 라디안각로 변환해야함그래서 위 함수 사용 45.0f 만큼 반시계로 회전 
    //glm 에서 모든 각도는 라디안으로 한다
    v3 = t3 * v3;
    std::cout << glm::to_string(t3) << '\n';
    std::cout << glm::to_string(v3) << '\n';

    return 0;
}
