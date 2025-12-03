#define GLM_ENABLE_EXPERIMENTAL
#include<iostream>
#include <GL/gl3w.h>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>

class ColorCube {
private:
    GLuint vaoHandle;
    GLuint vbo_cube_vertices, vbo_cube_colors;
    GLuint ibo_cube_elements;
public:
	void setup();
    void draw();
};