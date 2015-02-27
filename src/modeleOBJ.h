#pragma once

#include "ofMain.h"
#include "Shader.h"
#include "Mesh.h"

class ModeleOBJ
{
public:
	ModeleOBJ(void);
	ModeleOBJ(const string& cheminOBJ);
	~ModeleOBJ(void);

	void afficher(ofMatrix4x4 projection, ofMatrix4x4 model, ofMatrix4x4 view,
		const ofVec3f& directionLumiere, const ofVec3f& couleurLumiere, const float& intensiteLumiere);

private:
	
	GLuint elementBuffer;
	Shader* shader;
	vector<ofVec3f> vertices;
	vector<GLuint> elements;
	vector<ofVec3f> normals;
	vector<ofVec3f> colors;
	Mesh mesh;
};

