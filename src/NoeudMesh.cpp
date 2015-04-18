#include "NoeudMesh.h"

NoeudMesh::NoeudMesh(Mesh* mesh){
	this->type |= typeMesh;
	this->mesh = mesh;
	this->positionAbsolue = ofVec3f(0, 0, 0);
}

void NoeudMesh::afficher(const ParametresAffichage* paramsAff, GLuint shaderId, MATERIAUX materiau){
	this->ajouterModele(paramsAff->modeles);

	if(positionneDevantPlan(*paramsAff->normalPlan, *paramsAff->positionPlan)){
		this->afficherMesh(paramsAff->modeles->back(), shaderId);
	}

	this->afficherEnfants(paramsAff, shaderId, materiau);
	
	this->retirerModele(paramsAff->modeles);
}

bool NoeudMesh::positionneDevantPlan(ofVec3f normalPlan, ofVec3f positionPlan){
	ofVec3f temp = this->positionAbsolue - positionPlan;
	float res = temp.dot(normalPlan);
	if(res > 0){
		return true;
	}
	return false;
}

void NoeudMesh::afficherMesh(const ofMatrix4x4* modele, const GLuint shaderId){
	glUniformMatrix4fv(glGetUniformLocation(shaderId, "model"), 1, GL_FALSE, modele->getPtr());
	this->mesh->dessiner();
}

void NoeudMesh::changerParent(Noeud* parent){
	Noeud::changerParent(parent);
	this->positionAbsolue = this->getTransformationsPrecedentes().getTranslation();
}

void NoeudMesh::ajouterModele(vector<ofMatrix4x4*>* modeles){
	if(modeles->size() == 0){
		modeles->push_back(new ofMatrix4x4(this->getTransformations()));
	}else
		modeles->push_back(new ofMatrix4x4(*modeles->back() * this->getTransformations()));
}

Noeud* NoeudMesh::chercherMesh(Noeud* meshPlusProche, ofVec3f position, float rayon, float* distanceMinimum, vector<ofMatrix4x4*>* transformations){
	this->ajouterModele(transformations);
	
	float distance = transformations->back()->getTranslation().distance(position);
	if(distance <= rayon && distance < *distanceMinimum){
		*distanceMinimum = distance;
		meshPlusProche = this;
	}

	meshPlusProche = Noeud::chercherMesh(meshPlusProche, position, rayon, distanceMinimum, transformations);

	this->retirerModele(transformations);

	return meshPlusProche;
}

void NoeudMesh::setPositionAbsolue(ofVec3f nouvellePosition){
	ofVec3f positionRelativeActuelle = this->getTransformations().getTranslation();
	ofMatrix4x4 transformations = this->getTransformations();
	
	transformations.setTranslation(
		positionRelativeActuelle.x + (nouvellePosition.x - this->positionAbsolue.x),
		positionRelativeActuelle.y + (nouvellePosition.y - this->positionAbsolue.y),
		positionRelativeActuelle.z + (nouvellePosition.z - this->positionAbsolue.z));

	this->setTransformations(transformations);
}

void NoeudMesh::setPositionAbsolue(float nouvellePositionX, float nouvellePositionY, float nouvellePositionZ){
	this->setPositionAbsolue(ofVec3f(nouvellePositionX, nouvellePositionY, nouvellePositionZ));
}

void NoeudMesh::miseAJourPositionAbsolueEnfants(ofMatrix4x4 transformations){
	this->positionAbsolue = transformations.getTranslation();
	Noeud::miseAJourPositionAbsolueEnfants(transformations);
}

void NoeudMesh::setTransformations(ofMatrix4x4 transformations){
	NoeudTransformation::setTransformations(transformations);
	this->positionAbsolue = this->getTransformationsPrecedentes().getTranslation();
}