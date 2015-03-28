#version 430 core

out vec4 color;

in vec3 fragColor;
in vec2 fragTexCoord;
in vec3 fragNormal;
in vec3 fragPos;

struct LumiereDirectionnelle {
	vec3 direction;
	vec3 ambiante;
	vec3 diffuse;
	vec3 speculaire;
};

uniform LumiereDirectionnelle lumDirectionnelle;

uniform sampler2D diffuseMap;
uniform sampler2D specularMap;
uniform vec3 positionCamera;

vec3 calculerIlluminationDirectionnelle(LumiereDirectionnelle lumiere, vec3 normal, vec3 directionCamera);

void main()
{

	vec3 normal = normalize(fragNormal);
	vec3 directionCamera = normalize(positionCamera - fragPos);
	
	vec3 resultatDir = calculerIlluminationDirectionnelle(lumDirectionnelle, normal, directionCamera);
	
    color = vec4(resultatDir, 0.7f);
}

vec3 calculerIlluminationDirectionnelle(LumiereDirectionnelle lumiere, vec3 normal, vec3 directionCamera)
{
	vec3 directionLumiere = normalize(lumiere.direction);
	
	// Lumière ambiante
    vec3 ambient = lumiere.ambiante * vec3(texture(diffuseMap, fragTexCoord));

    // Reflection diffuse
    float diff = max(dot(normal, directionLumiere), 0.0);
    vec3 diffuse = lumiere.diffuse * diff * vec3(texture(diffuseMap, fragTexCoord));

	// Reflection spéculaire
	vec3 directionReflection = reflect(-directionLumiere, normal);
	float spec = pow(max(dot(directionCamera, directionReflection), 0.0), 32);
	vec3 specular = lumiere.speculaire * spec * vec3(texture(specularMap, fragTexCoord));
	
	return (ambient + diffuse + specular);
}