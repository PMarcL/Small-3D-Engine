#version 430 core

in vec3 Color;
in vec2 TexCoord;
in vec3 Normal;
in vec3 FragPos;

uniform sampler2D Texture1;
uniform vec3 lumiereAmbiante;
uniform vec3 positionLumiere;
uniform vec3 couleurLumiere;

out vec4 color;

void main()
{
		// Lumière ambiante
    float ambientStrength = 0.2f;
    vec3 ambient = ambientStrength * lumiereAmbiante;

		// Lumière diffuse
    vec3 norm = normalize(Normal);
    vec3 directionLumiere = normalize(positionLumiere - FragPos);
    float diff = max(dot(norm, directionLumiere), 0.0);
    vec3 diffuse = diff * couleurLumiere;

	 	vec4 couleurObjet = texture(Texture1, TexCoord);

    vec3 result = (ambient + diffuse) * couleurObjet.xyz;
    color = vec4(result, 0.5f);
}
