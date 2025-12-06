#define _USE_MATH_DEFINES 
#define GLM_ENABLE_EXPERIMENTAL

#include <iostream>
#include<vector> //stl vector

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/string_cast.hpp>

#include <fstream> //파일 읽기
#include <chrono> //시간 체크

#include "cow.h" // [!!!] cow.h에 num_vertices, ntris, vertices, nvertices가 정의되어 있음
#include "ppm_io.h"


//원점 기준인 점들(-1~1사이)을 모두 0~1 사이 값으로 이동시켜주는과정 == 모두 더하기1-> 0~2사이값-> 나누기2 -> 모두0~1사이값
void convertNDCtoImage(const glm::vec4 vertexNDC, glm::vec4 vertexView, const uint32_t& imageWidth, const uint32_t& imageHeight, glm::vec3& vertexRaster)
{
    // [!!!] 참고: 원본 함수를 유지했지만, vertexView.z가 음수이므로
    // vertexRaster.z = -vertexView.z; 가 맞습니다.
    vertexRaster.x = (vertexNDC.x + 1.0f) / 2.0f * imageWidth;
    vertexRaster.y = (1.0f - vertexNDC.y) / 2.0f * imageHeight;
    vertexRaster.z = -vertexView.z; // 카메라(View) 공간의 Z값 (양수)
}



float min3(const float& a, const float& b, const float& c)
{
    return std::min(a, std::min(b, c));
}

float max3(const float& a, const float& b, const float& c)
{
    return std::max(a, std::max(b, c));
}

//삼각형 내부 외부 판별 
bool edge(const glm::vec3& a, const glm::vec3& b, const glm::vec3& c)
{
    return ((c.x - a.x) * (b.y - a.y) - (c.y - a.y) * (b.x - a.x) >= 0);
}

//삼각형 넓이 구하는 함수
float area(const glm::vec3 a, const glm::vec3 b, const glm::vec3 c)
{
    return fabs((c[0] - a[0]) * (b[1] - a[1]) - (c[1] - a[1]) * (b[0] - a[0]));
}

glm::mat4 lookAt(glm::vec3 pos, glm::vec3 look, glm::vec3 up)
{
    glm::mat4 viewMatrix(1.0f);
    glm::vec3 z = glm::normalize(pos - look);
    glm::vec3 x = glm::normalize(glm::cross(up, z));
    glm::vec3 y = glm::normalize(glm::cross(z, x));

    viewMatrix = glm::translate(viewMatrix, -pos);

    glm::mat4 rota = { glm::vec4(x.x, y.x, z.x, 0.0f),
    glm::vec4(x.y, y.y, z.y, 0.0f),
    glm::vec4(x.z, y.z, z.z, 0.0f),
    glm::vec4(0.0f, 0.0f, 0.0f, 1.0f) };

    viewMatrix = rota * viewMatrix;
    return viewMatrix;
}

glm::mat4 perspective(float fovy, float aspect, float near, float far)
{
    glm::mat4 projection(0.0f);
    projection[0][0] = 1.0f / (aspect * glm::tan(glm::radians(fovy) / 2.0f));
    projection[1][1] = 1.0f / (glm::tan(glm::radians(fovy) / 2.0f));
    projection[2][2] = -(far + near) / (far - near);
    projection[2][3] = -1.0f;
    projection[3][2] = -(2.0f * far * near) / (far - near);
    return projection;

}

const uint32_t imageWidth = 640;
const uint32_t imageHeight = 480;


const float nearClippingPlane = 1;
const float farClippingPLane = 1000;
const uint32_t ntris = 3156;

//노말값 저장 배열 
glm::vec3 vertices_normal[1732] = {};


int main(int argc, char** argv)
{
    glm::mat4 worldToCamera = glm::lookAt(glm::vec3(20, 10, 20), glm::vec3(0, 5, 0), glm::vec3(0, 1, 0));

    float t, b, l, r;

    PPM ppmOut;
    ppmOut.setBinary(true);



    struct rgb
    {
        uint8_t r, g, b;
    };

    //이미지를 저장하기위한 프레임버퍼 frameBuffer
    std::vector <rgb>  frameBuffer;
    frameBuffer.resize(imageWidth * imageHeight);


    for (uint32_t i = 0; i < imageWidth * imageHeight; ++i) {
        frameBuffer[i].r = 0;
        frameBuffer[i].g = 0;
        frameBuffer[i].b = 0;
    }

    //깊이버퍼(겹칠경우 사용)
    float* depthBuffer = new float[imageWidth * imageHeight];

    for (uint32_t i = 0; i < imageWidth * imageHeight; ++i) {
        depthBuffer[i] = farClippingPLane;
    }

    // 면 노멀 누적
    for (uint32_t i = 0; i < ntris; ++i)
    {
        // 실제 정점 인덱스
        int i0 = nvertices[i * 3 + 0];
        int i1 = nvertices[i * 3 + 1];
        int i2 = nvertices[i * 3 + 2];

        // 정점 위치
        const glm::vec3& v0 = vertices[i0];
        const glm::vec3& v1 = vertices[i1];
        const glm::vec3& v2 = vertices[i2];

        // 면 노멀 계산
        glm::vec3 faceNormal = glm::normalize(glm::cross(v1 - v0, v2 - v0));

        // 각 면에 노멀을 더함
        vertices_normal[i0] += faceNormal;
        vertices_normal[i1] += faceNormal;
        vertices_normal[i2] += faceNormal;
    }

    // 정규화 => 평균 
    for (uint32_t i = 0; i < 1732; ++i)
    {
        vertices_normal[i] = glm::normalize(vertices_normal[i]);
    }

    auto t_start = std::chrono::high_resolution_clock::now();

    //삼각형 꼭짓점 1 2 3 번째 뽑기 반복문 여기서부터 시작 
    for (uint32_t i = 0; i < ntris; ++i) {
        //로컬(모델)좌표 
        const glm::vec3& v0 = vertices[nvertices[i * 3]];
        const glm::vec3& v1 = vertices[nvertices[i * 3 + 1]];
        const glm::vec3& v2 = vertices[nvertices[i * 3 + 2]];

        //모델행렬 (위치 옮기는걸 그냥 가정 하고 그래서 그냥 단위행렬) 로컬->글로벌
        glm::mat4 modelMatrix(1.0f);
        //뷰행렬 글로벌->카메라 lookAt 구현한걸로 만듦
        // 20 , 10 , 20 이 원래 좌표 
        glm::mat4 viewMatrix = lookAt(glm::vec3(20, 10, 20), glm::vec3(0, 5, 0), glm::vec3(0, 1, 0));
        //모델뷰행렬 로컬->카메라 (모델 뷰 행렬 곱해서 만듦)
        glm::mat4 modelViewMatrix = viewMatrix * modelMatrix;

        //Camera(view) coordinates 선언 
        glm::vec4 v0e;
        glm::vec4 v1e;
        glm::vec4 v2e;

        //모델 뷰 행렬 * 로컬좌표계 계산하면서 값을 넣어줌 (로컬좌표계 v0~v2 vec 3에서 동차좌표계로 만들어주는 과정) 
        v0e = modelViewMatrix * glm::vec4(v0, 1.0f);
        v1e = modelViewMatrix * glm::vec4(v1, 1.0f);
        v2e = modelViewMatrix * glm::vec4(v2, 1.0f);

        //perspective 함수로 구함 
        glm::mat4 projection = perspective((45.0f), imageWidth / (float)imageHeight, nearClippingPlane, farClippingPLane);

        //Clip coodinates 선언 
        glm::vec4 v0c, v1c, v2c;

        //클립= 프로젝션행렬 * 뷰좌표계 구해줌  
        v0c = projection * v0e;
        v1c = projection * v1e;
        v2c = projection * v2e;

        //Perspective division (divide v0c.x, v0c.y, v0c.z by v0c.w   (same to v1c, v2c)
        //x y z 를 w 로 나누어줌 Perspective division 과정
        // 모든 좌표값을 [-1, 1] 로 바꾸기 위해 : NDC 

        v0c.x /= v0c.w; v0c.y /= v0c.w; v0c.z /= v0c.w;
        v1c.x /= v1c.w; v1c.y /= v1c.w; v1c.z /= v1c.w;
        v2c.x /= v2c.w; v2c.y /= v2c.w; v2c.z /= v2c.w;
        //NDC 좌표계로 변경 완료 : v0c, v1c, v2c 

        glm::vec3 v0Raster, v1Raster, v2Raster;
        convertNDCtoImage(v0c, v0e, imageWidth, imageHeight, v0Raster);
        convertNDCtoImage(v1c, v1e, imageWidth, imageHeight, v1Raster);
        convertNDCtoImage(v2c, v2e, imageWidth, imageHeight, v2Raster);
           
        //레스터라이제이션 
        //bounding box
        float xmin = min3(v0Raster.x, v1Raster.x, v2Raster.x);
        float ymin = min3(v0Raster.y, v1Raster.y, v2Raster.y);
        float xmax = max3(v0Raster.x, v1Raster.x, v2Raster.x);
        float ymax = max3(v0Raster.y, v1Raster.y, v2Raster.y);

        if (xmin > imageWidth - 1 || xmax < 0 || ymin > imageHeight - 1 || ymax < 0) continue;

        uint32_t x0 = std::max(int32_t(0), (int32_t)(std::floor(xmin)));
        uint32_t x1 = std::min(int32_t(imageWidth) - 1, (int32_t)(std::floor(xmax)));
        uint32_t y0 = std::max(int32_t(0), (int32_t)(std::floor(ymin)));
        uint32_t y1 = std::min(int32_t(imageHeight) - 1, (int32_t)(std::floor(ymax)));


        //calculat the area of triangle  (area)
        float total = area(v0Raster, v1Raster, v2Raster);
        //딥스 버퍼 값 
        v0Raster.z = 1.0f / v0Raster.z;
        v1Raster.z = 1.0f / v1Raster.z;
        v2Raster.z = 1.0f / v2Raster.z;

        //노말값 가져옴 
        glm::vec3 n0 = vertices_normal[nvertices[i * 3 + 0]];
        glm::vec3 n1 = vertices_normal[nvertices[i * 3 + 1]];
        glm::vec3 n2 = vertices_normal[nvertices[i * 3 + 2]];

        //삼각형 민 맥스값 바운더리 반복문  
        for (uint32_t y = y0; y <= y1; ++y) {
            for (uint32_t x = x0; x <= x1; ++x) {

                //픽셀의 정가운대를 테스트하기위해 0.5 더해줌 
                glm::vec3 pixelSample(x + 0.5, y + 0.5, 0);

                //calculate the areas of  three suvdivided triangles

                //엣지 함수 벡터의 왼 오 판별 다트루 -> 삼각형내부 
                bool w0 = edge(v1Raster, v2Raster, pixelSample); //w0
                bool w1 = edge(v2Raster, v0Raster, pixelSample); //w1
                bool w2 = edge(v0Raster, v1Raster, pixelSample); //w2

                //삼각형 내부 외부 판별 if
                if (w0 == true && w1 == true && w2 == true) { //inside

                    // 무게중심 좌표 (Barycentric)
                    float a0 = area(v1Raster, v2Raster, pixelSample); // v0 가중치
                    float a1 = area(v2Raster, v0Raster, pixelSample); // v1 가중치
                    float a2 = area(v0Raster, v1Raster, pixelSample); // v2 가중치

                    //면적비 구하는것 
                    a0 /= total;
                    a1 /= total;
                    a2 /= total;

                    //calculate the z of pixelSample (원근 보정)
                    float oneOverZ = v0Raster.z * a0 + v1Raster.z * a1 + v2Raster.z * a2;
                    float z = 1.0f / oneOverZ;

                    //깊이 비교 뎁스 버퍼의 값과 비교 
                    // depth버퍼에는 해당 픽셀의 가장 가까운 거리값(카메라까지의)이 들어있음 
                    if (z < depthBuffer[y * imageWidth + x]) {
                        //더 가깝다면 -> 즉 앞이라면 뎁스버퍼 값 새로 할당, 해당 픽셀에 새로운 색 추가  
                        depthBuffer[y * imageWidth + x] = z;

                        //n / z * 넓이 가중치 -> n/z 
                        glm::vec3 n_over_z = (n0 * v0Raster.z * a0) +
                            (n1 * v1Raster.z * a1) +
                            (n2 * v2Raster.z * a2);
                        //n/z 에 z 곱해서 n 값만 남기기
                        glm::vec3 n = glm::normalize(n*n_over_z);

                        // n-> x y z 가 모두 -1~1 사이 -> 0~1 사이로 바꿔야함
                        n.x = (n.x + 1.0f) / 2.0f;
                        n.y = (n.y + 1.0f) / 2.0f;
                        n.z = (n.z + 1.0f) / 2.0f;

                        frameBuffer[y * imageWidth + x].r = n.x * 255;
                        frameBuffer[y * imageWidth + x].g = n.y * 255;
                        frameBuffer[y * imageWidth + x].b = n.z * 255;
                    }
                }
            } //안쪽 for loop
        } //바깥쪽 for loop
    }
    auto t_end = std::chrono::high_resolution_clock::now();
    auto passedTime = std::chrono::duration<double, std::milli>(t_end - t_start).count();
    std::cerr << "Wall passed time: " << passedTime << "ms" << std::endl;


    rgb* p = frameBuffer.data();

    ppmOut.load(&p[0].r, imageHeight, imageWidth, 255, "P6");
    ppmOut.write("../../output.ppm");

    delete[] depthBuffer;

    return 0;
}