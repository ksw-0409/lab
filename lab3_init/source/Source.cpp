
//#define GLFW_INCLUDE_GLU

#include <iostream>

#include <GL/gl3w.h>
#include <GLFW/glfw3.h>

#include "MyGlWindow.h"

#include<memory>//스마트포인터 사용 

// shared_ptr / unique_ptr 두가지 사용법 익히기  
std::unique_ptr<MyGlWindow> win;

int main(void)
{
	/* Initialize the library */
	if (!glfwInit()) //glfw 초기화
	{
		// Initialization failed
	}
	//오픈지엘 버전 지정:
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	//오픈지엘 예정 기능은 다빼고 신 기능만 쓸래요 (예전기능 사용하려면 COMPATIBLE_PROFILE)
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//800x800윈도우생성
	int width = 800;
	int height = 800;
	/* Create a windowed mode window and its OpenGL context */
	//파일이름 
	GLFWwindow* window = glfwCreateWindow(width, height, "OpenGL FrameWork", NULL, NULL);
	if (!window) {
		glfwTerminate();
		return-1;
	}
	//윈도우 제대로 생성 ->
	
	//OpenGL context생성(context => 구조체 struct) glm3w 초기화
	glfwMakeContextCurrent(window);
	
	//헬퍼 초기화 : opengl의 함수를 이용하기위한 helper(loader)를 초기화 
	if (gl3wInit()) {
		fprintf(stderr, "failed to initialize OpenGL\n");
		return -1;
	}
	//3.2 서포트 하는지 확인 
	if (!gl3wIsSupported(3, 2)) {
		fprintf(stderr, "OpenGL 3.2 not supported\n");
		return -1;
	}
	//컴퓨터 버전 출력 
	printf("OpenGL %s, GLSL %s\n", glGetString(GL_VERSION),
		glGetString(GL_SHADING_LANGUAGE_VERSION));
	
	//모니터의 refresh rate sync 1넣으면 모니터 주사율과 씽크 맞춰줌 0이면 안맞춤(주석처리하는방법도있음)
	glfwSwapInterval(1);  //enable vsync

	printf("OpenGL %s, GLSL %s\n",
		glGetString(GL_VERSION), glGetString(GL_SHADING_LANGUAGE_VERSION));

	//MyGlWindow 클래스 객체 생성 
	//win = new MyGlWindow(width, height); //cpp 98방식
	//스마트포인터로 
	win = std::make_unique<MyGlWindow>(width,height);

	//윈도우창X누를때까지 보인다는 와일조건문/ 내부는 키보드 마우스 입력을 확인함 
	while (!glfwWindowShouldClose(window))
	{
		//여기에 뭔가를 그려줘야함 
		win->draw();
		// Swap front and back buffers 
		glfwSwapBuffers(window);
		// Poll for and process events 
		glfwPollEvents();
	}

	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}


