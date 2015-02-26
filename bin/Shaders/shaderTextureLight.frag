#version 430 core

out vec4 color;

in vec3 ourColor;
in vec2 TexCoord;
in vec3 Normal;
in vec3 FragPos;

uniform sampler2D Texture1;
uniform vec3 lumiereAmbiante;
uniform vec3 positionLumiere;
uniform vec3 couleurLumiere;

void main()
{
		// Lumière ambiante
    float intensiteLumiereAmbiante = 0.2f;
    vec3 ambient = intensiteLumiereAmbiante * lumiereAmbiante;

    // Lumière diffuse
    vec3 norm = normalize(Normal);
    vec3 directionLumiere = normalize(positionLumiere - FragPos);
    float diff = max(dot(norm, directionLumiere), 0.0);
    vec3 diffuse = diff * couleurLumiere;

		vec4 couleurObjet = texture(Texture1, TexCoord);

    vec3 result = (ambient + diffuse) * couleurObjet.xyz;
    color = vec4(result, 1.0f);
}
