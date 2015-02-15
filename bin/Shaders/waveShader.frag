#version 430 core

in vec3 color;
in vec2 TexCoord;

out vec4 outColor;
uniform sampler2D Texture1;
uniform sampler2D Texture2;

void main()
{
  vec4 oceanColor = vec4(0.0, 0.1, 0.4, 1.0);
  vec4 textureOcean = mix(texture(Texture1, TexCoord), texture(Texture2, TexCoord), 0.4);
  outColor = mix(texture(Texture2, TexCoord), oceanColor, 0.2);
}
