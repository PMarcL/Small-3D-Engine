#version 430 core

layout (location = 0) out vec4 color;
uniform sampler2D screenTexture;

in vec2 texcoords;

void main()
{ 
    color = texture(screenTexture, texcoords);
	float average = 0.2126 * color.r + 0.7152 * color.g + 0.0722 * color.b;
    color = vec4(average, average, average, 1.0);
}
