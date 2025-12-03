//#define  FREEGLUT_LIB_PRAGMAS  0
#define GLM_ENABLE_EXPERIMENTAL 
#include <iostream>
#include <GL/gl3w.h>
#include <string>
#include "Loader.h"
#include"colorCube.h"
#include"Viewer.h"


class MyGlWindow {
public:
	MyGlWindow(int w, int h);
	void draw();
	std::unique_ptr<Viewer>  m_viewer;

	void setSize(int width,int height);
	void setAspect(float aspect);
private:
	std::unique_ptr<ColorCube> m_cube;	
	std::unique_ptr<ShaderProgram> shaderProgram;
	int m_width;
	int m_height;
	float m_aspect;
	
	glm::mat4 lookAt(glm::vec3 campos, glm::vec3 look, glm::vec3 up);
	glm::mat4 MyGlWindow::perspective(float fovY, float aspect, float n, float f);

	void initialize();
	void setupBuffer();
};
