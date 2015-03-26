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

const float offset = 1.0 / 300;  

void main()
{
	// Lumière ambiante
    vec3 ambient = intensiteLumiere * lumiereAmbiante;

    // Reflection diffuse
    vec3 normal = normalize(fragNormal);
    vec3 directionLumiere = normalize(positionLumiere - fragPos);
    float diff = max(dot(normal, directionLumiere), 0.0);
    vec3 diffuse = diff * couleurLumiere;

	// Reflection spéculaire
	vec3 directionCamera = normalize(positionCamera - fragPos);
	vec3 directionReflection = reflect(-directionLumiere, normal);
	float spec = pow(max(dot(directionCamera, directionReflection), 0.0), 2);
	vec3 specular = intensiteSpeculaire * spec * couleurLumiere;
	
	// combinaison de la couleur de l'objet et de son illumination
	
	
	 vec2 offsets[9] = vec2[](
        vec2(-offset, offset),  // top-left
        vec2(0.0f,    offset),  // top-center
        vec2(offset,  offset),  // top-right
        vec2(-offset, 0.0f),    // center-left
        vec2(0.0f,    0.0f),    // center-center
        vec2(offset,  0.0f),    // center-right
        vec2(-offset, -offset), // bottom-left
        vec2(0.0f,    -offset), // bottom-center
        vec2(offset,  -offset)  // bottom-right    
    );

    float kernel[9] = float[](
		1.0 / 16, 2.0 / 16, 1.0 / 16,
		2.0 / 16, 4.0 / 16, 2.0 / 16,
		1.0 / 16, 2.0 / 16, 1.0 / 16  
	);
    
    vec3 samples[9];
    for(int i = 0; i < 9; i++)
    {
        samples[i] = vec3(texture(Texture1, fragTexCoord.st + offsets[i]));
    }
    vec3 col;
    for(int i = 0; i < 9; i++)
        col += samples[i] * kernel[i];
    
	
	vec4 couleurObjet = vec4(col, 1.0);	
	
	
	
	
    vec3 result = (ambient + diffuse + specular) * couleurObjet.xyz;
	
	
    color = vec4(result, 1.0f);
}
