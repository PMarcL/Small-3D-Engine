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

private:
	void chargerMatricesMVPUniforms(const ofMatrix4x4& projection, const ofMatrix4x4& model, const ofMatrix4x4& view);

	Shader shader;
	vector<PrimitiveGeometrique> primitives;
};

