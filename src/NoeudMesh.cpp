#include "NoeudMesh.h"

NoeudMesh::NoeudMesh(Mesh* mesh){
	this->type |= typeMesh;
	this->mesh = mesh;
}

void NoeudMesh::afficher(const ofMatrix4x4* projection, const ofMatrix4x4* vue, const Lumiere* lumiere, vector<ofMatrix4x4*>* modeles, GLuint shaderId, MATERIAUX materiau){
	this->ajouterModele(modeles);

	this->afficherMesh(modeles->back(), shaderId);

	this->afficherEnfants(projection, vue, lumiere, modeles, shaderId, materiau);
	
	this->retirerModele(modeles);
}

void NoeudMesh::afficherMesh(const ofMatrix4x4* modele, const GLuint shaderId){
	glUniformMatrix4fv(glGetUniformLocation(shaderId, "model"), 1, GL_FALSE, modele->getPtr());
	this->mesh->dessiner();
}

void NoeudMesh::ajouterModele(vector<ofMatrix4x4*>* modeles){
	if(modeles->size() == 0){
		modeles->push_back(new ofMatrix4x4(this->matriceTransformations));
	}else
		modeles->push_back(new ofMatrix4x4(*modeles->back() * this->matriceTransformations));
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
	this->setPositionAbsolue(nouvellePosition.x, nouvellePosition.y, nouvellePosition.z);
}

void NoeudMesh::setPositionAbsolue(float nouvellePositionX, float nouvellePositionY, float nouvellePositionZ){
	ofVec3f positionAbsolueActuelle = this->getTransformationsPrecedentes().getTranslation();
	ofVec3f positionRelativeActuelle = this->matriceTransformations.getTranslation();
	this->matriceTransformations.setTranslation(
		positionRelativeActuelle.x + (nouvellePositionX - positionAbsolueActuelle.x),
		positionRelativeActuelle.y + (nouvellePositionY - positionAbsolueActuelle.y),
		positionRelativeActuelle.z + (nouvellePositionZ - positionAbsolueActuelle.z));
}