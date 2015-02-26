#version 430 core

in vec3 Normal;
in vec3 FragPos;

out vec4 out_Color;

uniform vec3 lightPos;
uniform vec3 lightColor;
uniform vec3 objectColor;

void main()
{
		// Lumière ambiante
    float ambientStrength = 0.1f;
    vec3 ambient = ambientStrength * lightColor;

		// Lumière diffuse
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;

    vec3 result = (ambient + diffuse) * objectColor;
    out_Color = vec4(result, 1.0f);
}
