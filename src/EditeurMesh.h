#pragma once

#include "ofMain.h"
#include "NoeudMesh.h"
#include "PrimitivesData.h"

class EditeurMesh
{
public:
	EditeurMesh();
	~EditeurMesh(){};

	void relacherSelection();
	void selectionnerMesh(NoeudMesh* selection);
	void supprimerSelection();
	void deplacerSelection(ofVec3f position);

	void setEchelle(float echelle);
	float getEchelle();

	ofVec3f positionAEchelle(ofVec3f position);
private:
	NoeudMesh* objetSelectionne;
	float echellePosition;	
};