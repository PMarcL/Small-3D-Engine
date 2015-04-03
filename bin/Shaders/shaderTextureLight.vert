#version 430 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 color;
layout (location = 2) in vec2 texCoord;
layout (location = 3) in vec3 normal;
layout (location = 4) in vec3 tangente;

out vec3 fragColor;
out vec2 fragTexCoord;
out vec3 fragNormal;
out vec3 fragPos;
out vec3 fragTangente;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

void main()
{
	gl_Position = projection * view * model * vec4(position, 1.0);
	fragColor = color;
	fragTexCoord = texCoord;
	fragNormal = mat3(transpose(inverse(model))) * normal;
	fragPos = vec3(model * vec4(position, 1.0));
	fragTangente = vec3(model * vec4(tangente, 1.0));
}
