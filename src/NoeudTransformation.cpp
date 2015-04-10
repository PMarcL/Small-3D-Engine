#include "NoeudTransformation.h"

NoeudTransformation::NoeudTransformation(){
	this->type |= typeTransformation;
	this->matriceTransformations.makeIdentityMatrix();
}

void NoeudTransformation::afficher(const ofMatrix4x4* projection, const ofMatrix4x4* vue, const Lumiere* lumiere, vector<ofMatrix4x4*>* modeles, GLuint shaderId, MATERIAUX materiau){
	this->ajouterModele(modeles);

	this->afficherEnfants(projection, vue, lumiere, modeles, shaderId, materiau);
	
	this->retirerModele(modeles);
}

void NoeudTransformation::ajouterModele(vector<ofMatrix4x4*>* modeles){
	if(modeles->size() == 0){
		modeles->push_back(new ofMatrix4x4(this->matriceTransformations));
	}else
		modeles->push_back(new ofMatrix4x4(*modeles->back() * this->matriceTransformations));
}

void NoeudTransformation::retirerModele(vector<ofMatrix4x4*>* modeles){
	delete modeles->back();
	modeles->pop_back();
}

Noeud* NoeudTransformation::chercherMesh(Noeud* meshPlusProche, ofVec3f position, float rayon, float* distanceMinimum, vector<ofMatrix4x4*>* transformations){
	this->ajouterModele(transformations);
	
	meshPlusProche = Noeud::chercherMesh(meshPlusProche, position, rayon, distanceMinimum, transformations);

	this->retirerModele(transformations);

	return meshPlusProche;
}

ofMatrix4x4 NoeudTransformation::getTransformationsPrecedentes(){
	return Noeud::getTransformationsPrecedentes() * this->matriceTransformations;
}