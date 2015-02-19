#version 430 core

in vec3 in_Vertex;
in vec3 in_normal;

uniform mat4 projection;
uniform mat4 modelview;

out vec3 Normal;

void main()
{
    gl_Position = projection * modelview * vec4(in_Vertex, 1.0);
	Normal = in_normal;
}