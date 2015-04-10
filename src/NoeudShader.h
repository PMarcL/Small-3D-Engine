#pragma once

#include "Noeud.h"
#include "Shader.h"

class NoeudShader : public Noeud
{
public:
	NoeudShader(Shader shader);
	~NoeudShader(){};

	virtual void afficher(const ofMatrix4x4* projection, const ofMatrix4x4* vue, const Lumiere* lumiere, vector<ofMatrix4x4*>* modeles, GLuint shaderId, MATERIAUX materiau);

	Shader shader;
protected:
	void preparerContextRendu(const ofMatrix4x4* projection, const ofMatrix4x4* vue, const Lumiere* lumiere, GLuint shaderId);
};