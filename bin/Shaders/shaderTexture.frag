#version 430 core

out vec4 color;

in vec3 fragColor;
in vec2 fragTexCoord;

uniform sampler2D Texture1;

void main()
{
    color = texture(Texture1, fragTexCoord);
}
