#pragma once

#include "ofMain.h"
#include "Shader.h"

class ModeleOBJ
{
public:
	ModeleOBJ(void);
	ModeleOBJ(const string& cheminOBJ);
	~ModeleOBJ(void);

	void afficher(ofMatrix4x4 projection, ofMatrix4x4 modelView,const ofVec3f& lightPos);

private:
	
	GLuint elementBuffer;
	Shader* shader;
	vector<ofVec3f> vertices;
	vector<GLushort> elements;
	vector<ofVec3f> normals;
	vector<ofVec3f> colors;
};

