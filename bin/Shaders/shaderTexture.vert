#version 430 core

in vec3 in_Vertex;
in vec3 in_Color;
in vec2 texCoord;

out vec3 ourColor;
out vec2 TexCoord;

uniform mat4 projection;
uniform mat4 modelview;

void main()
{
	gl_Position = projection * modelview * vec4(in_Vertex, 1.0);
	ourColor = in_Color;
	TexCoord = texCoord;
}
