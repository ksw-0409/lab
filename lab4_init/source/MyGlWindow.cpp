#include "MyGlWindow.h"
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>

static float DEFAULT_VIEW_POINT[3] = { 5, 5, 5 };
static float DEFAULT_VIEW_CENTER[3] = { 0, 0, 0 };
static float DEFAULT_UP_VECTOR[3] = { 0, 1, 0 };

MyGlWindow::MyGlWindow(int w, int h)

//==========================================================================
{
	m_width = w;
	m_height = h;

	glm::vec3 viewPoint(DEFAULT_VIEW_POINT[0], DEFAULT_VIEW_POINT[1], DEFAULT_VIEW_POINT[2]);
	glm::vec3 viewCenter(DEFAULT_VIEW_CENTER[0], DEFAULT_VIEW_CENTER[1], DEFAULT_VIEW_CENTER[2]);
	glm::vec3 upVector(DEFAULT_UP_VECTOR[0], DEFAULT_UP_VECTOR[1], DEFAULT_UP_VECTOR[2]);
	m_aspect = (w / (float)h);
	m_viewer = std::make_unique<Viewer>(viewPoint, viewCenter, upVector, 60.0, m_aspect);
	initialize();
	setupBuffer();
}

void MyGlWindow::setSize(int width, int height) {
	m_width = width;
	m_height = height;
}
void MyGlWindow::setAspect(float aspect) {
	m_aspect = aspect;
}
void MyGlWindow::initialize()
{
	m_cow = std::make_unique<cow>();
}


//vbo vao ibo 만드는 함수 
void MyGlWindow::setupBuffer()
{
	glEnable(GL_DEPTH_TEST);
	shaderProgram = std::make_unique<ShaderProgram>();
	shaderProgram->initFromFiles("shaders/simple.vert", "shaders/simple.frag");
	if (m_cow) m_cow->setup();
	//shaderProgram->addUniform("model");
	//shaderProgram->addUniform("view");
	//shaderProgram->addUniform("projection");
	shaderProgram->addUniform("mvp");
}


void MyGlWindow::draw(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//0. 뷰포트 설정 : 캔버스 크기 및 위치 설정 : 현재는 800 x 800 인데
	glViewport(0, 0, m_width, m_height); //앞 두개 값 : 시작점, 뒤 두개 : 크기 	
	//1. 쉐이더 use 
	shaderProgram->use();

	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
	//glUniformMatrix4fv(shaderProgram->uniform("model"), 1, GL_FALSE, glm::value_ptr(model));

	glm::vec3 eye = m_viewer->getViewPoint();
	glm::vec3 look = m_viewer->getViewCenter();
	glm::vec3 up = m_viewer->getUpVector();
	glm::mat4 view = lookAt(eye, look, up);
	//glUniformMatrix4fv(shaderProgram->uniform("view"), 1, GL_FALSE, glm::value_ptr(view));

	glm::mat4 projection = perspective(45.0f, m_width / m_height, 0.1f, 500.0f);
	//glUniformMatrix4fv(shaderProgram->uniform("projection"), 1, GL_FALSE, glm::value_ptr(projection));

	glm::mat4 mview = view * model;
	glm::mat4 mvp = projection * view * model;
	glUniformMatrix4fv(shaderProgram->uniform("mvp"), 1, GL_FALSE, glm::value_ptr(mvp));

	if (m_cow) m_cow->draw();
	shaderProgram->disable();

	//4. 쉐이더 disable 
	shaderProgram->disable();
}

glm::mat4 MyGlWindow::lookAt(glm::vec3 campos, glm::vec3 look, glm::vec3 up) {
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

glm::mat4 MyGlWindow::perspective(float fovY, float aspect, float n, float f) {
	glm::mat4 projection_matrix(0.0f);
	projection_matrix[0][0] = 1.0f / (aspect * glm::tan(fovY / 2.0f));
	projection_matrix[1][1] = 1.0f / (glm::tan(fovY / 2.0f));
	projection_matrix[2][2] = -(f + n) / (f - n);
	projection_matrix[2][3] = -1.0f;
	projection_matrix[3][2] = -(2.0f * f * n) / (f - n);
	return projection_matrix;
}