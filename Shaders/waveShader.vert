#version 430 core

in vec3 in_Vertex;
in vec3 in_Color;
in vec2 texCoord;

uniform mat4 projection;
uniform mat4 modelview;
uniform float time;

out vec3 color;
out vec2 TexCoord;

void main()
{
	float deplacementY = sin(time + (in_Vertex.x / 100.0) + (in_Vertex.z / 100.0)) * 15;
	vec4 position = projection * modelview * vec4(in_Vertex, 1.0);
	position.y += deplacementY;
	gl_Position = position;

	color = in_Color;
	TexCoord = texCoord;

}
