#define GLM_ENABLE_EXPERIMENTAL
#include"cowdata.h"
#include<iostream>
#include <GL/gl3w.h>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>
#include<vector>

class cow {
public:
    cow();
    void setup();
    void draw();
    void calculateNormal();
    GLuint vaoHandle;
    GLuint vbo_cow_vertices, ibo_cow_elements;
    GLuint vbo_cow_normals;
    std::vector<glm::vec3> normals;
};
