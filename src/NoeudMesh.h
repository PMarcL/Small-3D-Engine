#pragma once

#include "NoeudTransformation.h"
#include "Mesh.h"

class NoeudMesh : public NoeudTransformation
{
public:
	NoeudMesh(Mesh* mesh);
	~NoeudMesh(){};

	Mesh* mesh;

	virtual void afficher(const ParametresAffichage* paramsAff, GLuint shaderId, MATERIAUX materiau);
	virtual void changerParent(Noeud* parent);

	void setPositionAbsolue(ofVec3f nouvellePosition);
	void setPositionAbsolue(float nouvellePositionX, float nouvellePositionY, float nouvellePositionZ);
protected:
	void afficherMesh(const ofMatrix4x4* modele, const GLuint shaderId);
	virtual void ajouterModele(vector<ofMatrix4x4*>* modeles);
	virtual Noeud* chercherMesh(Noeud* meshPlusProche, ofVec3f position, float rayon, float* distanceMinimum, vector<ofMatrix4x4*>* transformations);
	virtual void miseAJourPositionAbsolueEnfants(ofMatrix4x4 transformations);

private:
	ofVec3f positionAbsolue;

	bool positionneDevantPlan(ofVec3f normalPlan, ofVec3f positionPlan);
	void majPositionRelative();
};