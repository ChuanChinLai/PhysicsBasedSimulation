#version 330

layout(location = 0) in vec3 i_position;
layout(location = 1) in vec3 i_color;
layout(location = 2) in vec3 i_offset;

uniform mat4 modelMat;
uniform mat4 viewMat;
uniform mat4 projectedMat;


out vec2 vertexColor;
 
void main()
{
  //gl_Position = projectedMat * viewMat * vec4(i_position + i_offset, 1.0);
  gl_Position = i_position;
  vertexColor = i_color;
}