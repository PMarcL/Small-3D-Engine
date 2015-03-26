#pragma once

#include "PrimitivesData.h"
#include "Mesh.h"
#include "ofMain.h"

class PrimitiveGeometrique
{
public:
	PrimitiveGeometrique(void);
	PrimitiveGeometrique(PRIMITIVES primitive, MATERIAUX materiaux, ofVec3f position, int taille);
	~PrimitiveGeometrique(void);

	void setMateriaux(MATERIAUX materiaux);
	void afficher();
	void chargerMateriauxUniforms(GLuint programId) const;
	ofVec3f getPosition();
	MATERIAUX getMateriaux();
	void setPosition(ofVec3f position);

private:

	Mesh mesh;
	MATERIAUX materiaux;
	ofVec3f position;
	ofVec3f reflectionAmbiante;
	ofVec3f reflectionDiffuse;
	ofVec3f reflectionSpeculaire;
	GLfloat brillance;
};

