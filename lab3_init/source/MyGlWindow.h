//#define  FREEGLUT_LIB_PRAGMAS  0
#define GLM_ENABLE_EXPERIMENTAL 
#include <iostream>
#include <GL/gl3w.h>
#include <string>
#include "Loader.h"
#include"colorCube.h"


class MyGlWindow {
public:
	MyGlWindow(int w, int h);
	void draw();
private:
	std::unique_ptr<ColorCube> m_cube;	
	std::unique_ptr<ShaderProgram> shaderProgram;

	int m_width;
	int m_height;
	
	void initialize();
	void setupBuffer();

};
