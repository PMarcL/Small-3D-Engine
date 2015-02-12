#version 430 core

in vec3 in_Vertex;
in vec2 texCoord;
out vec2 TexCoord;

uniform mat4 projection;
uniform mat4 modelview;

void main()
{
  position = projection * modelview * vec4(in_Vertex, 1.0);
  gl_Position = position.xyww;
  TexCoord = texCoord;
}
