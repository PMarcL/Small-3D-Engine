#pragma once

#include "ofMain.h"
#include "PrimitiveGeometrique.h"
#include "Shader.h"
#include "Lumiere.h"

class ConteneurPrimitives
{
public:
	ConteneurPrimitives(void);
	~ConteneurPrimitives(void);

	void ajouterPrimitive(PrimitiveGeometrique primitive);
	void afficher(ofMatrix4x4 projection, ofMatrix4x4 model, ofMatrix4x4 view, Lumiere lumiere);
	void selectionnerPrimitive(ofVec3f position, float rayon);
	void supprimerSelection();
	void relacherPrimitiveSelectionnee();
	void deplacerPrimitiveSelectionnee(ofVec3f position);

private:
	void chargerMatricesMVPUniforms(const ofMatrix4x4& projection, const ofMatrix4x4& model, const ofMatrix4x4& view);
	bool positionDansRayon(const ofVec3f& positionRef, const ofVec3f& position, float rayon);
	float getDistanceEntreVecteur(const ofVec3f& positionRef, const ofVec3f& positionCible);

	Shader shader;
	vector<PrimitiveGeometrique> primitives;
	PrimitiveGeometrique* primitiveSelectionnee;
	MATERIAUX materiauPrimitiveSelectionnee;
};

