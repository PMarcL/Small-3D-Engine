#pragma once

#include "ofMain.h"
#include "Shader.h"
#include "Mesh.h"
#include "Lumiere.h"

class ModeleOBJ
{
public:
	ModeleOBJ(void);
	ModeleOBJ(const string& cheminOBJ);
	~ModeleOBJ(void);

	void afficher();

private:
	bool chargerOBJ(const char * cheminFichier, vector<ofVec3f>& sommets, vector<ofVec2f>& texCoord, std::vector<ofVec3f>& normales);
	Mesh mesh;
};

