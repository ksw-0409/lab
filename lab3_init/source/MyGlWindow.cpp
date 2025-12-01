#include "MyGlWindow.h"
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>

MyGlWindow::MyGlWindow(int w, int h)

//==========================================================================
{
	m_width = w;
	m_height = h;
	setupBuffer();
}

void MyGlWindow::initialize()
{
	m_cube = std::make_unique<ColorCube>();
	shaderProgram = std::make_unique<ShaderProgram>();
	shaderProgram->initFromFiles("shaders/simple.vert", "shaders/simple.frag");
}


//vbo vao ibo 만드는 함수 
void MyGlWindow::setupBuffer()
{
	initialize();
	if (m_cube) m_cube->setup();
}


void MyGlWindow::draw(void)
{
	//0. 뷰포트 설정 : 캔버스 크기 및 위치 설정 : 현재는 800 x 800 인데
	glViewport(0, 0, m_width, m_height); //앞 두개 값 : 시작점, 뒤 두개 : 크기 	
	//1. 쉐이더 use 
	shaderProgram->use();
	if (m_cube) m_cube->draw();
	shaderProgram->disable();

	//4. 쉐이더 disable 
	shaderProgram->disable();
}