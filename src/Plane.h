#pragma once

#include "Shader.h"
#include "ofMain.h"
#include "Mesh.h"
#include "Texture.h"

const static float TEX_REPETITION_PAR_CARRE = 1;

class Plane
{
public:
	Plane() {}
	Plane(int size, int numColumn, int numRow);
	~Plane();

	void afficher();
	void ajouterTexture(const string& texPath);
	void genereHauteursAleatoire(float minHeight, float maxHeight);
	void generePenteProgressive(float minHeight, float maxHeight);
	void reinitialiseHauteur();
	void setRatioTextureParCarre(float ratio);
	void utiliserTextures(bool utiliser);


private:
	void initialiserMesh();
	void ajouterIndices();
	void ajouterCouleurs();
	void ajouterSommets();
	void calculerNormals();
	void ajouterNormals(const vector<ofVec3f>& normalsCalcule);
	void chargerTextures();
	void ajouterTexCoordPourChaqueSommet();
	
	vector<ofVec3f> vertices;
	vector<ofVec3f> colors;
	vector<GLuint> indices;
	vector<GLfloat> texCoords;
	vector<ofVec3f> normals;
	Texture texture;
	int nbColonnes;
	int nbLignes;
	int taille;
	bool useTexture;
	float ratioTextureParCarre;
	Mesh mesh;
};

