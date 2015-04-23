#pragma once

#include "ofMain.h"
#include "Plane.h"
#include "Shader.h"
#include "modeleOBJ.h"
#include "Lumiere.h"
#include "Texture.h"
#include <stack>

const static int NB_ARBRES = 30;
const static ofVec3f LUMIERE_AMBIANTE = ofVec3f(0.0, 0.0, 0.8);

class Paysage
{
public:
	Paysage(void);
	~Paysage(void) {}

	void afficher(ofMatrix4x4 projection, ofMatrix4x4 model, ofMatrix4x4 view,
		const Lumiere& lumiere);

private:
	void generationPositionsArbres();
	ofVec3f genererPositionAvecEspacement(int espacement);
	bool positionEstEnConflit(int espacement, ofVec3f position);
	void chargerMatricesMVPUniforms(GLuint id, const ofMatrix4x4& projection, const ofMatrix4x4& model, const ofMatrix4x4& view);
	void pushMatrix();
	void popMatrix();

	ofVec3f lumiereAmbiante;
	Shader shaderUneTexture;
	Shader shaderOscillation;
	stack<ofMatrix4x4> matrices;
	ofMatrix4x4 model;
	Plane surfaceCentrale;
	Plane ocean;
	Plane montagne;
	ModeleOBJ arbre;
	Texture texTree;
	Texture texTreeSpeculaire;
	Texture texTreeNormal;
	Texture texRoche;
	Texture texRocheSpeculaire;
	Texture texRocheNormal;
	Texture texEau;
	Texture texEauSpeculaire;
	Texture texEauNormal;
	ModeleOBJ champignon;
	Texture texChampignon;
	Texture texChampignonSpeculaire;
	Texture texChampignonNormal;
	vector<ofVec3f> positionsArbres;
	vector<ofVec3f> positionsChampignon;
};

