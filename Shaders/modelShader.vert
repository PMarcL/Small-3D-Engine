#version 430 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 color;
layout (location = 2) in vec2 texCoord;
layout (location = 3) in vec3 normal;

out vec3 Normal;

uniform mat4 projection;
uniform mat4 modelview;



void main()
{
    gl_Position = projection * modelview * vec4(position, 1.0);
	Normal = normal;
}