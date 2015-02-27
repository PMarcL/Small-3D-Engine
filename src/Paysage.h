#pragma once

#include "ofMain.h"
#include "Plane.h"
#include "Shader.h"
#include "modeleOBJ.h"
#include <stack>

const static int NB_ARBRES = 30;
const static ofVec3f LUMIERE_AMBIANTE = ofVec3f(0.0, 0.0, 0.8);

class Paysage
{
public:
	Paysage(void);
	~Paysage(void) {}

	void afficher(ofMatrix4x4 projection, ofMatrix4x4 model, ofMatrix4x4 view,
		const ofVec3f& directionLumiere, const ofVec3f& couleurLumiere, const float& intensiteLumiere);

private:
	void generationPositionArbres();
	void pushMatrix();
	void popMatrix();

	ofVec3f lumiereAmbiante;
	Shader shaderUneTexture;
	Shader shaderPassThru;
	Shader shaderOscillation;
	stack<ofMatrix4x4> matrices;
	ofMatrix4x4 model;
	Plane surfaceCentrale;
	Plane ocean;
	Plane montagne;
	ModeleOBJ arbre;
	vector<ofVec3f> positionsArbres;
};

