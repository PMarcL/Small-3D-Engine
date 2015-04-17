#pragma once

#include "Noeud.h"
#include "Shader.h"
#include "NoeudMateriau.h"

class NoeudShader : public Noeud
{
public:
	NoeudShader(Shader shader);
	~NoeudShader(){};

	virtual void afficher(const ParametresAffichage* paramsAff, GLuint shaderId, MATERIAUX materiau);
	void ajouterNoeudAMateriau(Noeud* noeud, MATERIAUX materiau);

	Shader shader;
protected:
	void preparerContextRendu(const ofMatrix4x4* projection, const ofMatrix4x4* vue, const Lumiere* lumiere, GLuint shaderId);
};