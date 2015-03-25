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

	void afficher(ofMatrix4x4 projection, ofMatrix4x4 model, ofMatrix4x4 view,
		const Lumiere& lumiere);

private:
	void chargerValeursIlluminationUniforms(const Lumiere& lumiere);
	void chargerMatricesMVPUniforms(GLuint id, const ofMatrix4x4& projection, const ofMatrix4x4& model, const ofMatrix4x4& view);

	Shader* shader;
	Mesh mesh;
};

