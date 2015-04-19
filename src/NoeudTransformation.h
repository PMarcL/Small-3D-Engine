#pragma once

#include "Noeud.h"

class NoeudTransformation : public  Noeud
{
public:
	NoeudTransformation();
	~NoeudTransformation(){};

	ofMatrix4x4 getTransformations();
	void setTransformations(ofMatrix4x4 transformations);

	virtual void afficher(const ParametresAffichage* paramsAff, GLuint shaderId, MATERIAUX materiau);
protected:
	void ajouterModele(vector<ofMatrix4x4*>* modeles);
	void retirerModele(vector<ofMatrix4x4*>* modeles);
	virtual Noeud* chercherMesh(Noeud* meshPlusProche, ofVec3f position, float rayon, float* distanceMinimum, vector<ofMatrix4x4*>* transformations);
	virtual ofMatrix4x4 getTransformationsPrecedentes();
	virtual void miseAJourPositionAbsolueEnfants(ofMatrix4x4 transformations);
private:
	ofMatrix4x4 matriceTransformations;
};