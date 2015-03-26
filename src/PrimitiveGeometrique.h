#pragma once

#include "PrimitivesData.h"
#include "Mesh.h"
#include "ofMain.h"

class PrimitiveGeometrique
{
public:
	PrimitiveGeometrique(void);
	PrimitiveGeometrique(PRIMITIVES primitive, MATERIAUX materiau, ofVec3f position, int taille);
	~PrimitiveGeometrique(void);

	void setMateriau(MATERIAUX materiau);
	void afficher();
	void chargerMateriauUniforms(GLuint programId) const;
	ofVec3f getPosition();
	MATERIAUX getMateriau();
	void setPosition(ofVec3f position);

private:

	Mesh mesh;
	MATERIAUX materiau;
	ofVec3f position;
	ofVec3f reflectionAmbiante;
	ofVec3f reflectionDiffuse;
	ofVec3f reflectionSpeculaire;
	GLfloat brillance;
};

