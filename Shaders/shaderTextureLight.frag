#version 430 core

out vec4 color;

in vec3 fragColor;
in vec2 fragTexCoord;
in vec3 fragNormal;
in vec3 fragPos;

uniform sampler2D Texture1;
uniform vec3 lumiereAmbiante;
uniform vec3 positionLumiere;
uniform vec3 couleurLumiere;
uniform float intensiteLumiere;
uniform vec3 positionCamera;
uniform float intensiteSpeculaire;

void main()
{
	// Lumière ambiante
    vec3 ambient = intensiteLumiere * lumiereAmbiante;

    // Lumière diffuse
    vec3 normal = normalize(fragNormal);
    vec3 directionLumiere = normalize(positionLumiere - fragPos);
    float diff = max(dot(normal, directionLumiere), 0.0);
    vec3 diffuse = diff * couleurLumiere;

	// Illumination spéculaire
	vec3 directionCamera = normalize(positionCamera - fragPos);
	vec3 directionReflection = reflect(-directionLumiere, normal);
	float spec = pow(max(dot(directionCamera, directionReflection), 0.0), 2);
	vec3 specular = intensiteSpeculaire * spec * couleurLumiere;
	
	// combinaison de la couleur de l'objet et de son illumination
	vec4 couleurObjet = texture(Texture1, fragTexCoord);
    vec3 result = (ambient + diffuse + specular) * couleurObjet.xyz;
    color = vec4(result, 1.0f);
}
