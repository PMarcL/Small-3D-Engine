#pragma once

#include "ofMain.h"
#include "Shader.h"

class EffetPleinEcran
{
public:
	EffetPleinEcran();
	~EffetPleinEcran(void) {}

	void afficher();
	void chargerTexture(GLuint);
	
private:

	Shader shaderBrouillard;
	GLfloat verticesPleinEcran[24];
	GLuint textureID;

	int largeur;
	int hauteur;

};

