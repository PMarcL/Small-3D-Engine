#version 430 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 color;
layout (location = 2) in vec2 texCoord;
layout (location = 3) in vec3 normal;

out vec3 fragColor;
out vec2 fragTexCoord;
out vec3 fragNormal;
out vec3 fragPos;

uniform mat4 projection;
uniform mat4 model;
uniform mat4 view;
uniform float time;

void main()
{
	float deplacementY = sin(time + (position.x / 100.0) + (position.z / 100.0)) * 15;
	vec4 Position = projection * view * model* vec4(position, 1.0);
	Position.y += deplacementY;
	gl_Position = Position;

	fragColor = color;
	fragTexCoord = vec2(texCoord.x + sin(time/4), texCoord.y + sin(time/4));
	fragNormal = mat3(transpose(inverse(model))) * normal;
	fragPos = vec3(model * vec4(position, 1.0));
}
