#pragma once

#include "ofMain.h"
#include "Shader.h"
#include "ShaderTmp.h"

class EffetPleinEcran
{
public:
	EffetPleinEcran();
	~EffetPleinEcran(void) {}

	void afficher(GLuint);
	void chargerTexture(GLuint);
	void redimensionner(int, int);
	
private:
	Shader shaderBrouillard;
	GLfloat verticesPleinEcran[24];
	GLuint textureID;
	GLuint screenTextureID;
	int largeur;
	int hauteur;

	GLuint creerRectanglePleinEcran();
};

