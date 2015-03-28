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

struct Projecteur {
	vec3 position;
	vec3 direction;
	vec3 diffuse;
	vec3 speculaire;
	
	float coneExterne;
	float coneInterne;
};

uniform LumiereDirectionnelle lumDirectionnelle;
uniform Projecteur projecteur;

uniform sampler2D diffuseMap;
uniform sampler2D specularMap;
uniform vec3 positionCamera;

vec3 calculerIlluminationDirectionnelle(LumiereDirectionnelle lumiere, vec3 normal, vec3 directionCamera);
vec3 calculerProjecteur(Projecteur proj, vec3 normal, vec3 directionCamera);

void main()
{

	vec3 normal = normalize(fragNormal);
	vec3 directionCamera = normalize(positionCamera - fragPos);
	
	vec3 resultatDir = calculerIlluminationDirectionnelle(lumDirectionnelle, normal, directionCamera);
	vec3 resultatProj = calculerProjecteur(projecteur, normal, directionCamera);
	
    color = vec4(resultatDir + resultatProj, 1.0f);
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
	float spec = pow(max(dot(directionCamera, directionReflection), 0.0), 2);
	vec3 specular = lumiere.speculaire * spec * vec3(texture(specularMap, fragTexCoord));
	
	return (ambient + diffuse + specular);
}

vec3 calculerProjecteur(Projecteur proj, vec3 normal, vec3 directionCamera)
{
	vec3 directionLumiere = normalize(proj.position - fragPos);
	float theta = dot(directionLumiere, normalize(-proj.direction));
	float epsilon = proj.coneInterne - proj.coneExterne;
	float intensite = clamp((theta - proj.coneExterne) / epsilon, 0.0, 1.0);
	
	float diff = max(dot(normal, directionLumiere), 0.0f);
	vec3 diffuse = proj.diffuse * diff * vec3(texture(diffuseMap, fragTexCoord));
	
	vec3 directionVue = normalize(positionCamera - fragPos);
	vec3 directionReflection = reflect(-directionLumiere, normal);
	float spec = pow(max(dot(directionVue, directionReflection), 0.0), 2);
	vec3 specular = proj.speculaire * (spec * vec3(texture(specularMap, fragTexCoord)));
		
	diffuse *= intensite;
	specular *= intensite;
		
	return (diffuse + specular);
}









