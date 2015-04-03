#pragma once

#include "ofMain.h"
#include "Shader.h"
#include "Texture.h"

class EffetPleinEcran
{
public:
	EffetPleinEcran();
	~EffetPleinEcran(void) {}

	void afficher(GLuint);
	void chargerTexture(GLuint);
	void redimensionner(int, int);
	
private:
	Texture image;
	GLuint vao;
	GLuint vbo;
	Shader shaderBrouillard;
	GLfloat verticesPleinEcran[24];
	GLuint textureID;
	GLuint screenTextureID;
	int largeur;
	int hauteur;

	void creerRectanglePleinEcran();
};

