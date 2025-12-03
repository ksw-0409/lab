#include"colorCube.h"

void ColorCube::setup() {
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
	//glCreat-> DSA 방법
	glCreateVertexArrays(1, &vaoHandle);
	glCreateBuffers(1, &vbo_cube_vertices);
	glCreateBuffers(1, &vbo_cube_colors);
	//2. vbo 생성
	//position 처리
	//GPU 메모리 할당
	glNamedBufferData(vbo_cube_vertices, sizeof(cube_vertices), cube_vertices, GL_STATIC_DRAW);
	//GPU 해석 방법 알려줌
	glVertexArrayVertexBuffer(
		vaoHandle,		//vao
		0,				//binding index 번호
		vbo_cube_vertices,	//vbo
		0,				//offset
		sizeof(GLfloat) * 3 //stride 
	);

	//color 처리
	//GPU 메모리 할당
	glNamedBufferData(vbo_cube_colors, sizeof(cube_colors), cube_colors, GL_STATIC_DRAW);
	//GPU 해석 방법 알려줌
	glVertexArrayVertexBuffer(
		vaoHandle,		//vao
		1,				//binding index 번호
		vbo_cube_colors,		//vbo
		0,				//offset
		sizeof(GLfloat) * 3 //stride
	);

	//포지션 
	glVertexArrayAttribFormat(
		vaoHandle, //vao
		0, //속성(attribute) 번호 바인딩 인덱스와 다를수있다 
		3, //vertex당 데이터수
		GL_FLOAT,
		GL_FALSE,
		0 //offset
	);

	glVertexArrayAttribBinding(vaoHandle,
		0, //속성번호 
		0 //바인딩 인덱스 0 연결
	);

	glEnableVertexArrayAttrib(vaoHandle, 0);//0번 속성 enable

	//컬러
	glVertexArrayAttribFormat(
		vaoHandle, //vao
		1, //속성(attribute) 번호 바인딩 인덱스와 다를수있다 
		3, //vertex당 데이터수
		GL_FLOAT,
		GL_FALSE,
		0 //offset
	);

	glVertexArrayAttribBinding(vaoHandle,
		1, //속성번호 
		1 //바인딩 인덱스 1 연결
	);

	glEnableVertexArrayAttrib(vaoHandle, 1);//1번 속성 enable

	//인덱스 처리 
	GLuint ibo_cube_elements;
	glGenBuffers(1, &ibo_cube_elements);
	glNamedBufferData(ibo_cube_elements, sizeof(cube_elements), cube_elements, GL_STATIC_DRAW);
	glVertexArrayElementBuffer(vaoHandle, ibo_cube_elements);

	glBindVertexArray(0);//unbinding
}

void ColorCube::draw() {
	glClearColor(0.2, 0.2, 0.2, 1); // 백그라운드 색상 지정 R G B A
	//2. vao binding
	glBindVertexArray(vaoHandle);
	//3. cal draw function   
	//인덱스가 있을때 그리기  glDrawElements()
	int size;
	glGetBufferParameteriv(GL_ELEMENT_ARRAY_BUFFER, GL_BUFFER_SIZE, &size);
	glDrawElements(GL_TRIANGLES, size / sizeof(GLushort), GL_UNSIGNED_SHORT, 0);
}