#version 430 core

out vec4 color;

in vec3 ourColor;
in vec2 TexCoord;

uniform sampler2D Texture1;
uniform vec3 ambientColor;

void main()
{
	color = mix(texture(Texture1, TexCoord), vec4(ambientColor, 1.0), 0.2);
}
