#pragma once

#include "ofMain.h"
#include "Noeud.h"

class GraphScene : public Noeud
{
public:
	GraphScene();
	~GraphScene(){};

	virtual void afficher(const ofMatrix4x4* projection, const ofMatrix4x4* vue, const Lumiere* lumiere);

	GLuint shaderIdOrigine;
private:
	void preparerContextRendu(const ofMatrix4x4* projection, const ofMatrix4x4* vue, const Lumiere* lumiere, GLuint shaderId);
};
