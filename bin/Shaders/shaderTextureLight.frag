#version 430 core

out vec4 color;

in vec3 fragColor;
in vec2 fragTexCoord;
in vec3 fragNormal;
in vec3 fragPos;
in vec3 fragTangente;

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

struct Ponctuelle {
	vec3 position;
	vec3 ambiante;
	vec3 diffuse;
	vec3 speculaire;
	
	float constante;
	float lineaire;
	float quadratique;
};

#define NB_PROJECTEURS_MAX 10
#define NB_LUMIERES_PONCTUELLES_MAX 10

uniform LumiereDirectionnelle lumDirectionnelle;
uniform int nbProjecteurs;
uniform Projecteur projecteur[NB_PROJECTEURS_MAX];
uniform int nbPonctuelles;
uniform Ponctuelle ponctuelles[NB_LUMIERES_PONCTUELLES_MAX];
uniform sampler2D diffuseMap;
uniform sampler2D specularMap;
uniform sampler2D normalMap;
uniform vec3 positionCamera;

vec3 calculerIlluminationDirectionnelle(LumiereDirectionnelle lumiere, vec3 normal, vec3 directionCamera);
vec3 calculerProjecteur(Projecteur proj, vec3 normal, vec3 directionCamera);
vec3 calculerPonctuelle(Ponctuelle lumiere, vec3 normal, vec3 directionCamera);
vec3 calculerNormal();

void main()
{

	vec3 normal = calculerNormal();
	vec3 directionCamera = normalize(positionCamera - fragPos);
	
	vec3 resultatDir = calculerIlluminationDirectionnelle(lumDirectionnelle, normal, directionCamera);
	vec3 resultatProj;
	for(int i = 0; i < nbProjecteurs; i++) {
		resultatProj += calculerProjecteur(projecteur[i], normal, directionCamera);
	}
	vec3 resultatPonctuelles;
	for(int i = 0; i < nbPonctuelles; i++) {
		resultatPonctuelles += calculerPonctuelle(ponctuelles[i], normal, directionCamera);
	}
	
    color = vec4(resultatDir + resultatProj + resultatPonctuelles, 1.0f);
}

vec3 calculerNormal()
{
	vec3 normal = normalize(fragNormal);
	vec3 tangente = normalize(fragTangente);
	tangente = normalize(tangente - dot(tangente, normal) * normal);
	vec3 biTangente = cross(tangente, normal);
	
	vec3 normalTexture = vec3(texture(normalMap, fragTexCoord));
	normalTexture = 2.0 * normalTexture - vec3(1.0);
	
	mat3 espaceTangent = mat3(tangente, biTangente, normal);
	vec3 normalAjustee = espaceTangent * normalTexture;
	
	return normalize(normalAjustee);
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

vec3 calculerPonctuelle(Ponctuelle lumiere, vec3 normal, vec3 directionCamera)
{
    vec3 directionLumiere = normalize(lumiere.position - fragPos);
    
    float diff = max(dot(normal, directionLumiere), 0.0);
    
    vec3 directionReflection = reflect(-directionLumiere, normal);
    float spec = pow(max(dot(directionCamera, directionReflection), 0.0), 2);
    
	// Attenuation
    float distance    = length(lumiere.position - fragPos);
    float attenuation = 1.0f / (lumiere.constante + lumiere.lineaire * distance + 
  			     lumiere.quadratique * (distance * distance));
    
	// Resultat combiné
    vec3 ambiante  = lumiere.ambiante  * vec3(texture(diffuseMap, fragTexCoord));
    vec3 diffuse  = lumiere.diffuse  * diff * vec3(texture(diffuseMap, fragTexCoord));
    vec3 speculaire = lumiere.speculaire * spec * vec3(texture(specularMap, fragTexCoord));
    ambiante  *= attenuation;
    diffuse  *= attenuation;
    speculaire *= attenuation;
    return (ambiante + diffuse + speculaire);
} 







