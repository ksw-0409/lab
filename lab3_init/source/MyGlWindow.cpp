
#define GLM_ENABLE_EXPERIMENTAL 
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



//vbo vao ibo 만드는 함수 
void MyGlWindow::setupBuffer()
{
	//쉐이더 객체 생성 : modern C++ 
	shaderProgram = std::make_unique<ShaderProgram>();
	
	//load shaders : vertex shader 랑 fragment shader 지정 
	shaderProgram->initFromFiles("shaders/simple.vert", "shaders/simple.frag");
	//따로처리용 배열
	//삼각형 위치 저장 : 0
	const float vertexPosition[] = {
		-0.2f, 0.0f, 0.0f,1.0f,
		-0.2f, 0.4f, 0.0f,1.0f,
		 0.2f, 0.0f, 0.0f,1.0f,
		 0.2f, 0.4f, 0.0f,1.0f
	};
	//삼각형 색상 저장 : 1
	const float vertexColor[] = {
		 1.0f, 0.0f, 0.0f,
		 0.0f, 1.0f, 0.0f,
		 0.0f, 0.0f, 1.0f,
		 1.0f, 0.0f, 0.0f
	};
	//같이처리용 배열
	const float vertices[] = { //interleave 방식 ( 포지션, 칼라 같이 쓰는 방식) 
		-0.2f, 0.0f, 0.0f, 1.0f,   1.0f,0.0f,0.0f, // position , color v0
		 0.0f, 0.4f, 0.0f, 1.0f,   0.0f,1.0f,0.0f, // position , color v1
		 0.2f, 0.0f, 0.0f, 1.0f,   0.0f,0.0f,1.0f  // position , color v2
	};

	//큐브 
	const GLfloat cube_vertices[] = {
		// front
		-1.0, -1.0, 1.0,
		1.0, -1.0, 1.0,
		1.0, 1.0, 1.0,
		-1.0, 1.0, 1.0,
		// back
		-1.0, -1.0, -1.0,
		1.0, -1.0, -1.0,
		1.0, 1.0, -1.0,
		-1.0, 1.0, -1.0
	};
	const GLfloat cube_colors[] = {
		// front colors
		1.0, 0.0, 0.0,
		0.0, 1.0, 0.0,
		0.0, 0.0, 1.0,
		1.0, 1.0, 1.0,
		// back colors
		1.0, 0.0, 0.0,
		0.0, 1.0, 0.0,
		0.0, 0.0, 1.0,
		1.0, 1.0, 1.0,
	};
	//큐브인덱스버퍼
	const GLushort cube_elements[] = {
	0, 1, 2,	2, 3, 0,	1, 5, 6,
	6, 2, 1,	7, 6, 5,	5, 4, 7,
	4, 0, 3,	3, 7, 4,	4, 5, 1,
	1, 0, 4,	3, 2, 6,	6, 7, 3,
	};

	//삼각형 정보 배열에 저장 (포지션, 칼라 따로 처리)
	/*
	// 이제 삼각형에 대한 정보를 CPU가 아닌 GPU에 보냄
	// 삼각형이 가진 속성정보 : 위치, 색상 
	//1. VAO 생성 (Vertex Array Object : 컨테이너이고 실제 속성정보는 없다-> 안에 넣어줘야함 )
	//VAO컨테이너 안에 -> VBO - Vertex Buffer Object 위치, 색상
		glGenVertexArrays(1, &vaohandle); //컨테이너 생성 여기만 & 사용
		glBindVertexArray(vaohandle); //바인드 여러개의 vao중에(만일 여러개가 있다면) 어떤거 사용할지
		//바인드  : activate의미 : 난 앞으로 여기에 뭔가 작업을 할래 지정, 선언 
		//2. VBO 생성 (Vectex Buffer Object) : vertex의 속성정보 저장 
		GLuint vbo_position;
		glGenBuffers(1, &vbo_position); //vertex 위치 정보를 저장하기 위한 vbo 
		glBindBuffer(GL_ARRAY_BUFFER, vbo_position); //vbo 바인딩 : activate 
	
		//데이터를 메인 메모리 -> GPU 메모리로 보낸 후 할당 : 마지막 usage /STATIC << 바꿀 필요가없어서 
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertexPosition), vertexPosition, GL_STATIC_DRAW);
		glVertexAttribPointer( //GPU 한테, 메모리에 올라온 데이타 해석 방법을 알려줌 
			0, // 속성 번호 -> 버텍스의 속성 ( 포지션 or 컬러 번호 ) 
			4, //데이터 수 -> 버텍스 당 데이터의 수 
			GL_FLOAT, //데이터 타입
			GL_FALSE, //normalize 여부
			0, //stride 값이 끝나고 다음 값이 시작할때까지의 간격을 뜻함
			0 // offset
		);
		//속성 enable 하기
		glEnableVertexAttribArray(0); //속성번호 0번 enable 요까지 세트 

	//컬러 
		GLuint vbo_color;
		glGenBuffers(1, &vbo_color);  //여기서만 사용 &
		glBindBuffer(GL_ARRAY_BUFFER, vbo_color); 
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertexColor), vertexColor, GL_STATIC_DRAW);
		glVertexAttribPointer( 
			1, // 속성 번호 -> 버텍스의 속성 ( 포지션 or 컬러 번호 ) 
			3, //데이터 수 -> 버텍스 당 데이터의 수 
			GL_FLOAT, //데이터 타입
			GL_FALSE, //normalize 여부
			0, //stride
			0 // offset
		);
		glEnableVertexAttribArray(1); //속성번호 1번

	//vao unbound 
	glBindVertexArray(0);// 현재 사용중인 VAO 언바운드 (0번을 넣으면됨)*/

	//NON-DSA (Direct State Access) 방법(포지션, 칼라 같이 처리)
	/*
	

	//1. vao 바인딩 방법 까먹지 말기 
	glGenVertexArrays(1, &vaohandle); //컨테이너생성
	glBindVertexArray(vaohandle); // binding
		GLuint vbo_vertex;
		glGenBuffers(1, &vbo_vertex);
		glBindBuffer(GL_ARRAY_BUFFER,vbo_vertex);//vbo binging-> activate
		//copy data from CPU to GPU
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices,GL_STATIC_DRAW);
		//GPU에게 해석방법 알려줘야 함
		//위치처리
		glVertexAttribPointer(
			0, //속성번호 번호: 0
			4, //vertex당 데이터 수 
			GL_FLOAT, //데이터타입
			GL_FALSE, //노멀라이즈 여부
			sizeof(float)*7, //위치정보가 시작한 후에 얼마 데이터 후에 다시 위치가 시작하나 : stride(보폭)
			(void*)0  //offset: 얼마 후에 데이터가 시작하는지 시작점 void 타입만 받아서 케스팅을 해줘야함
		);
		glEnableVertexAttribArray(0);

		//색상처리
		glVertexAttribPointer(
			1, //속성번호 번호: 1
			3, //vertex당 데이터 수 
			GL_FLOAT, //데이터타입
			GL_FALSE, //노멀라이즈 여부
			sizeof(float) * 7, //컬러정보가 시작한 후에 얼마 데이터 후에 다시 컬러가 시작하나 : stride(보폭)
			(void*)(sizeof(float)*4)  //offset: 얼마 후에 데이터가 시작하는지 시작점 void 타입만 받아서 케스팅을 해줘야함*
		);
		glEnableVertexAttribArray(1);

	glBindVertexArray(0);//unbinding
	*/

	//DSA 방법 : 함수 명이 다르다 (바인딩 없이 사용하는)  
	//새로운 개념 binding index: vao 컨테이너 안에 vbo를 넣을수있는 슬롯 인덱스 어디에 넣을지 지정해주는것 밑 코드에 사용 
	/*
	// 1. vao 생성
	GLuint vbo_position;
	GLuint vbo_color;
	//glCreat-> DSA 방법
	glCreateVertexArrays(1, &vaohandle);
	glCreateBuffers(1, &vbo_position);
	glCreateBuffers(1, &vbo_color);

	//2. vbo 생성
	//position 처리
	//GPU 메모리 할당
	glNamedBufferData(vbo_position, sizeof(vertexPosition), vertexPosition, GL_STATIC_DRAW);
	//GPU 해석 방법 알려줌
	glVertexArrayVertexBuffer(
		vaohandle,		//vao
		0,				//binding index 번호
		vbo_position,	//vbo
		0,				//offset
		sizeof(float)*4 //stride 첫번째값부터 다음첫번째 값까지의 간격
	);

	//color 처리
	//GPU 메모리 할당
	glNamedBufferData(vbo_color, sizeof(vertexColor), vertexColor, GL_STATIC_DRAW);
	//GPU 해석 방법 알려줌
	glVertexArrayVertexBuffer(
		vaohandle,		//vao
		1,				//binding index 번호
		vbo_color,		//vbo
		0,				//offset
		sizeof(float) * 3 //stride
	);

	//포지션 
	glVertexArrayAttribFormat(
		vaohandle, //vao
		0, //속성(attribute) 번호 바인딩 인덱스와 다를수있다 
		4, //vertex당 데이터수
		GL_FLOAT,
		GL_FALSE,
		0 //offset
	);

	glVertexArrayAttribBinding(vaohandle, 
		0, //속성번호 
		0 //바인딩 인덱스 0 연결
	);
	glEnableVertexArrayAttrib(vaohandle, 0);//0번 속성 enable

	//컬러
	glVertexArrayAttribFormat(
		vaohandle, //vao
		1, //속성(attribute) 번호 바인딩 인덱스와 다를수있다 
		3, //vertex당 데이터수
		GL_FLOAT,
		GL_FALSE,
		0 //offset
	);

	glVertexArrayAttribBinding(vaohandle,
		1, //속성번호 
		1 //바인딩 인덱스 1 연결
	);
	glEnableVertexArrayAttrib(vaohandle, 1);//1번 속성 enable
	*/

	//DSA 방법: interleave 방식으로 
	/*
	GLuint vbo_vertex;
	glCreateVertexArrays(1, &vaohandle);	
	glCreateBuffers(1, &vbo_vertex);

	glNamedBufferData(vbo_vertex, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glVertexArrayVertexBuffer(vaohandle, 0, vbo_vertex,0,sizeof(float)*7);
	
	glVertexArrayAttribFormat(vaohandle, 0, 4, GL_FLOAT, GL_FALSE, 0); //마지막 0 : offset
	glVertexArrayAttribBinding(vaohandle, 0, 0); //속성번호: 0 binding index :0
	glEnableVertexArrayAttrib(vaohandle, 0); //속성번호 0 enable 

	glVertexArrayAttribFormat(vaohandle, 1, 3, GL_FLOAT, GL_FALSE, sizeof(float)*4); //마지막 offset 
	glVertexArrayAttribBinding(vaohandle, 1, 0); //속성번호: 1 binding index :0 <- 왜? 하나만 쓰기때문 interleave 방식
	glEnableVertexArrayAttrib(vaohandle, 1); //속성번호 1 enable
	*/

	//큐브 NON-DSA 방식
	/*
	glGenVertexArrays(1, &vaohandle); //컨테이너생성
	glBindVertexArray(vaohandle); // binding
		GLuint cube_position;
		glGenBuffers(1, &cube_position);
		glBindBuffer(GL_ARRAY_BUFFER, cube_position);//vbo binging-> activate
		//copy data from CPU to GPU
		glBufferData(GL_ARRAY_BUFFER, sizeof(cube_vertices), cube_vertices,GL_STATIC_DRAW);
		//GPU에게 해석방법 알려줘야 함
		//위치처리
		glVertexAttribPointer(
			0, //속성번호 번호: 0
			3, //vertex당 데이터 수 
			GL_FLOAT, //데이터타입
			GL_FALSE, //노멀라이즈 여부
			0, //위치정보가 시작한 후에 얼마 데이터 후에 다시 위치가 시작하나 : stride(보폭)
			(void*)0  //offset: 얼마 후에 데이터가 시작하는지 시작점 void 타입만 받아서 케스팅을 해줘야함
		);
		glEnableVertexAttribArray(0);

		//색상처리
		GLuint cube_color;
		glGenBuffers(1, &cube_color);
		glBindBuffer(GL_ARRAY_BUFFER, cube_color);
		glBufferData(GL_ARRAY_BUFFER, sizeof(cube_colors), cube_colors, GL_STATIC_DRAW);
		glVertexAttribPointer(
			1, // 속성 번호 -> 버텍스의 속성 ( 포지션 or 컬러 번호 ) 
			3, //데이터 수 -> 버텍스 당 데이터의 수 
			GL_FLOAT, //데이터 타입
			GL_FALSE, //normalize 여부
			0, //stride
			(void*)0 // offset
		);
		glEnableVertexAttribArray(1); 
		
		//인덱스 처리 
		GLuint ibo_cube_elements;
		glGenBuffers(1, &ibo_cube_elements);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo_cube_elements);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(cube_elements), cube_elements, GL_STATIC_DRAW);

	glBindVertexArray(0);//unbinding
	*/
	
	//큐브 DSA 방식
	// 1. vao 생성
	GLuint vbo_cube_position;
	GLuint vbo_cube_color;
	//glCreat-> DSA 방법
	glCreateVertexArrays(1, &vaohandle);
	glCreateBuffers(1, &vbo_cube_position);
	glCreateBuffers(1, &vbo_cube_color);
	//2. vbo 생성
	//position 처리
	//GPU 메모리 할당
	glNamedBufferData(vbo_cube_position, sizeof(cube_vertices), cube_vertices, GL_STATIC_DRAW);
	//GPU 해석 방법 알려줌
	glVertexArrayVertexBuffer(
		vaohandle,		//vao
		0,				//binding index 번호
		vbo_cube_position,	//vbo
		0,				//offset
		sizeof(GLfloat)*3 //stride 
	);	

	//color 처리
	//GPU 메모리 할당
	glNamedBufferData(vbo_cube_color, sizeof(cube_colors), cube_colors, GL_STATIC_DRAW);
	//GPU 해석 방법 알려줌
	glVertexArrayVertexBuffer(
		vaohandle,		//vao
		1,				//binding index 번호
		vbo_cube_color,		//vbo
		0,				//offset
		sizeof(GLfloat) * 3 //stride
	);

	//포지션 
	glVertexArrayAttribFormat(
		vaohandle, //vao
		0, //속성(attribute) 번호 바인딩 인덱스와 다를수있다 
		3, //vertex당 데이터수
		GL_FLOAT,
		GL_FALSE,
		0 //offset
	);

	glVertexArrayAttribBinding(vaohandle,
		0, //속성번호 
		0 //바인딩 인덱스 0 연결
	);

	glEnableVertexArrayAttrib(vaohandle, 0);//0번 속성 enable

	//컬러
	glVertexArrayAttribFormat(
		vaohandle, //vao
		1, //속성(attribute) 번호 바인딩 인덱스와 다를수있다 
		3, //vertex당 데이터수
		GL_FLOAT,
		GL_FALSE,
		0 //offset
	);

	glVertexArrayAttribBinding(vaohandle,
		1, //속성번호 
		1 //바인딩 인덱스 1 연결
	);

	glEnableVertexArrayAttrib(vaohandle, 1);//1번 속성 enable

	//인덱스 처리 
	GLuint ibo_cube_elements;
	glGenBuffers(1, &ibo_cube_elements);
	glNamedBufferData(ibo_cube_elements, sizeof(cube_elements), cube_elements, GL_STATIC_DRAW);
	glVertexArrayElementBuffer(vaohandle, ibo_cube_elements);

	glBindVertexArray(0);//unbinding
}


void MyGlWindow::draw(void)
{
	glClearColor(0.2, 0.2, 0.2, 1); // 백그라운드 색상 지정 R G B A
	//어떤 버퍼를 지울지 지정: 라스터 라이제이션 할때 두개의 버퍼 : color, depth 
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT); // | , || 차이 
	
	//0. 뷰포트 설정 : 캔버스 크기 및 위치 설정 : 현재는 800 x 800 인데
	// 이걸 다쓸건지 일부만 쓸건지 결정 
	glViewport(0, 0, m_width, m_height); //앞 두개 값 : 시작점, 뒤 두개 : 크기 	
	//1. 쉐이더 use 
	shaderProgram->use();
	//2. vao binding
	glBindVertexArray(vaohandle);
	//3. cal draw function   
	// 인덱스가 있을때 그리기 glDrawArrays()
							                         //GL_TRAINGLE_STRIP < 새로운 버텍스를 하나씩 추가해주면 자동으로 묶어줌  
	//glDrawArrays(GL_TRIANGLE_STRIP, 0, 4); //어떻게 그릴래?(GL_TRIANGLES < 3개씩 점을 묶어 만듬) 삼각형으로, 시작 인덱스, 버텍스수 

	//인덱스가 있을때 그리기  glDrawElements()
	int size;
	glGetBufferParameteriv(GL_ELEMENT_ARRAY_BUFFER, GL_BUFFER_SIZE, &size);
	glDrawElements(GL_TRIANGLES, size / sizeof(GLushort), GL_UNSIGNED_SHORT, 0);

	//4. 쉐이더 disable 
	shaderProgram->disable();
}
