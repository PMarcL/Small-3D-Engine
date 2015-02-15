#version 430 core

in vec3 color;
in vec2 TexCoord;

out vec4 outColor;
uniform sampler2D Texture1;
uniform vec3 lumiereAmbiante;

void main()
{
  vec4 oceanColor = vec4(0.0, 0.1, 0.4, 1.0);
  vec4 oceanWithTex = mix(texture(Texture1, TexCoord), oceanColor, 0.2);
  outColor = mix(oceanWithTex, vec4(lumiereAmbiante, 1.0), 0.2);
}
