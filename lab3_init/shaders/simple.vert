#version 450 

//cpu로 부터 받은 속성 0번의 입력을 vec4로 받음
layout(location = 0) in vec4 vertexPosition;
//cpu로 부터 받은 속성 1번의 입력을 vec3로 받음
layout(location = 1) in vec3 vertexColor;

out vec3 fColor; //fragment shader 로 보낼 데이터 
void main()
{
    //gl_Position은 빌트인 키워드로서, 클립좌표계를 받아 들인다
    //나중에 자동으로 gl_Position 값을 perspective division 을 해줌 

    //그런데 왜 좌포계 변환을 안하지? 이유는 지금 받은 vertexPosition이 클립좌표계로 가정했기때문 
    //그렇기때문에 지금은 곧바로 넣을수있음 
    //원래는 로컬->월드->뷰->클립 으로 변환 과정을 거침

    //중요!: vertex shader에는 반드시 gl_Position값을 설정해야 함 
    gl_Position=vertexPosition;
    fColor=vertexColor;

}
