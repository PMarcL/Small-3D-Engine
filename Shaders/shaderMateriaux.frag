#version 430 core

out vec4 color;

in vec3 fragColor;
in vec2 fragTexCoord;
in vec3 fragNormal;
in vec3 fragPos;

struct Lumiere {
	//vec3 position;
	vec3 direction;
	vec3 ambiante;
	vec3 diffuse;
	vec3 speculaire;
};

struct Materiau {
	vec3 ambiante;
	vec3 diffuse;
	vec3 speculaire;
	float brillance;
};

uniform Lumiere lumiere;
uniform Materiau materiau;
uniform vec3 positionCamera;

void main()
{
	vec3 ambiante = lumiere.ambiante * materiau.ambiante;
	
	vec3 normal = normalize(fragNormal);
	vec3 lumiereDirection = normalize(lumiere.direction);
	float diff = max(dot(normal, lumiereDirection), 0.0f);
	vec3 diffuse = lumiere.diffuse * (diff * materiau.diffuse);
	
	vec3 vueDirection = normalize(positionCamera - fragPos);
	vec3 reflectionDirection = reflect(-lumiereDirection, normal);
	float spec = pow(max(dot(vueDirection, reflectionDirection), 0.0), materiau.brillance);
	vec3 speculaire = lumiere.speculaire * (spec * materiau.speculaire);
	
	vec3 resultat = ambiante + diffuse + speculaire;
	color = vec4(resultat, 1.0f);
}
