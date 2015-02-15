#pragma once

#include "Shader.h"
#include "ofMain.h"

const static float TEX_REPETITION_PAR_CARRE = 1;

class Plane
{
public:
	Plane():shader(NULL) {}
	Plane(int size, Shader* shader, int numColumn, int numRow);
	~Plane();

	void afficher(ofMatrix4x4 projection, ofMatrix4x4 modelView);
	void ajouterTexture(const string& texPath);
	void genereHauteursAleatoire(float minHeight, float maxHeight);
	void setShader(Shader* nouveauShader);
	void setRatioTextureParCarre(float ratio);
	void utiliserTextures(bool utiliser);


private:
	void ajouterIndices();
	void libererRessources();
	void chargerElementBuffer();
	void chargerMatrices(ofMatrix4x4 projection, ofMatrix4x4 modelView, Shader* shader);
	void chargerSommets();
	void chargerCouleurs();
	void chargerTexCoord();
	void chargerTextures();
	void ajouterTexCoordPourChaqueSommet();
	
	Shader* shader;
	vector<GLfloat> vertices;
	vector<GLfloat> colors;
	vector<GLuint> indices;
	vector<GLfloat> texCoords;
	vector<GLuint> textures;
	int nbColonnes;
	int nbLignes;
	int taille;
	GLuint elemBuffer;
	bool useTexture;
	float ratioTextureParCarre;
};

