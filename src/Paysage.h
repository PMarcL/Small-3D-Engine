#pragma once

#include "ofMain.h"
#include "Plane.h"
#include "Shader.h"
#include <stack>


class Paysage
{
public:
	Paysage(void);
	~Paysage(void) {}

	void afficher(ofMatrix4x4 projection, ofMatrix4x4 model, ofMatrix4x4 view, const ofVec3f& lightPos);

private:
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
};

