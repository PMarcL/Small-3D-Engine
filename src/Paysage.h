#pragma once

#include "ofMain.h"
#include "Plane.h"
#include "Shader.h"
#include "modeleOBJ.h"
#include <stack>

const static int NB_ARBRES = 40;
const static ofVec3f LUMIERE_AMBIANTE = ofVec3f(0.0, 0.0, 0.8);

class Paysage
{
public:
	Paysage(void);
	~Paysage(void) {}

	void afficher(ofMatrix4x4 projection, ofMatrix4x4 model, ofMatrix4x4 view,
		const ofVec3f& directionLumiere, const ofVec3f& couleurLumiere, const float& intensiteLumiere);

private:
	void generationPositionsArbres();
	ofVec3f genererPositionAvecEspacement(int espacement);
	bool positionEstEnConflit(int espacement, ofVec3f position);
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
	Texture texTree;
	ModeleOBJ champignon;
	vector<ofVec3f> positionsArbres;
};

