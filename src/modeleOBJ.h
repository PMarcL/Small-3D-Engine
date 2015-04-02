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
	Mesh mesh;
};

