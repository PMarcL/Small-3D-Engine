#version 430 core											

out vec4 color;

in vec3 ourColor;
in vec2 TexCoord;

uniform sampler2D ourTexture1;

void main()
{
	color = texture(ourTexture1, TexCoord);
}
