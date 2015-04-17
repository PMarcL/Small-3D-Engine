#include "EditeurMesh.h"

EditeurMesh::EditeurMesh(){
	echellePosition = 0;
	objetSelectionne = NULL;
	ancienParent = NULL;
	materiauSelection = new NoeudMateriau(MATERIAUX::SELECTION);
}

void EditeurMesh::relacherSelection(){
	if(objetSelectionne != NULL){
		objetSelectionne->changerParent(ancienParent);
		materiauSelection->changerParent(NULL);
		objetSelectionne = NULL;
	}
}

void EditeurMesh::selectionnerMesh(NoeudMesh* selection){
	objetSelectionne = selection;
	if(selection != NULL){
		ancienParent = selection->getParent();
		ancienParent->ajouterEnfant(materiauSelection);
		selection->changerParent(materiauSelection);
	}
}

void EditeurMesh::supprimerSelection(){
	delete objetSelectionne;
	this->relacherSelection();
}

void EditeurMesh::deplacerSelection(ofVec3f position){
	if(objetSelectionne != NULL)
		((NoeudMesh*)objetSelectionne)->setPositionAbsolue(positionAEchelle(position));
}

void EditeurMesh::setEchelle(float echelle){
	if(echelle < 0){
		this->echellePosition = 0.0f;
	}else
		this->echellePosition = echelle;
}

float EditeurMesh::getEchelle(){
	return this->echellePosition;
}

ofVec3f EditeurMesh::positionAEchelle(ofVec3f position){
	if(this->echellePosition > 0){
		float positionX = fmodf(position.x, this->echellePosition),
			positionY = fmodf(position.y, this->echellePosition),
			positionZ = fmodf(position.z, this->echellePosition);

		float demiEchelle = this->echellePosition * 0.5f;

		if(positionX < demiEchelle){
			positionX = position.x - positionX;
		}else
			positionX = position.x - positionX + this->echellePosition;

		if(positionY < demiEchelle){
			positionY = position.y - positionY;
		}else
			positionY = position.y - positionY + this->echellePosition;

		if(positionZ < demiEchelle){
			positionZ = position.z - positionZ;
		}else
			positionZ = position.z - positionZ + this->echellePosition;

		position = ofVec3f(positionX, positionY, positionZ);
	}
	
	return position;
}