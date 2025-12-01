#version 450

in vec3 fColor;

//프레그먼트 쉐이더는 반드시 하나이상의 out vec4가 있어야함 
out vec4 fragColor; //픽셀의 색상을 의미 왜 vec4 냐? RGB A 까지 
void main()
{
    fragColor=vec4(fColor,1.0f);
}