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
	void activerEffetBrouillard();
	void activerEffetNoirEtBlanc();
	void activerEffetLignes();
	void desactiverEffet();
	enum Effet { AUCUN, BROUILLARD, NOIR_ET_BLANC, LIGNES };
	
private:
	Texture image;
	GLuint vao;
	GLuint vbo;
	Shader shaderActif;
	GLfloat verticesPleinEcran[24];
	GLuint textureID;
	GLuint screenTextureID;
	int largeur;
	int hauteur;

	
	Effet effetCourant;

	void creerRectanglePleinEcran();
};

