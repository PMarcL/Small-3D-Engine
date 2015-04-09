#version 430 core

layout (location = 0) out vec4 color;
uniform sampler2D screenTexture;

in vec2 texcoords;

void main()
{ 
    color = texture(screenTexture, texcoords);
}
