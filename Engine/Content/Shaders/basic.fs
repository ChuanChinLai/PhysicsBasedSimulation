#version 330

in vec3 vertexColor;
out vec4 o_color;

void main()
{
	o_color = vec4(vertexColor, 1.0f);
}