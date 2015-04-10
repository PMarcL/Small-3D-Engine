#pragma once

#include "Noeud.h"

class NoeudTransformation : public  Noeud
{
public:
	NoeudTransformation();
	~NoeudTransformation(){};

	ofMatrix4x4 matriceTransformations;

	virtual void afficher(const ofMatrix4x4* projection, const ofMatrix4x4* vue, const Lumiere* lumiere, vector<ofMatrix4x4*>* modeles, GLuint shaderId, MATERIAUX materiau);	
protected:
	void ajouterModele(vector<ofMatrix4x4*>* modeles);
	void retirerModele(vector<ofMatrix4x4*>* modeles);
	virtual Noeud* chercherMesh(Noeud* meshPlusProche, ofVec3f position, float rayon, float* distanceMinimum, vector<ofMatrix4x4*>* transformations);
	virtual ofMatrix4x4 getTransformationsPrecedentes();
};