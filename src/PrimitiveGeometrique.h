#pragma once

#include "PrimitivesData.h"
#include "Mesh.h"
#include "ofMain.h"

class PrimitiveGeometrique
{
public:
	PrimitiveGeometrique(void);
	PrimitiveGeometrique(PRIMITIVES primitive, int taille);
	~PrimitiveGeometrique(void);

	void afficher();

private:
	Mesh mesh;
};

