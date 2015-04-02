#pragma once

#include "Shader.h"
#include "ofMain.h"
#include "Mesh.h"

const static float TEX_REPETITION_PAR_CARRE = 1;

class Plane
{
public:
	Plane() {}
	Plane(int size, int numColumn, int numRow);
	~Plane();

	void afficher();
	void genereHauteursAleatoire(float minHeight, float maxHeight);
	void generePenteProgressive(float minHeight, float maxHeight);
	void reinitialiseHauteur();
	void setRatioTextureParCarre(float ratio);


private:
	void initialiserMesh();
	void ajouterIndices();
	void ajouterSommets();
	void calculerNormals();
	void ajouterNormals(const vector<ofVec3f>& normalsCalcule);
	void ajouterTexCoordPourChaqueSommet();
	
	vector<ofVec3f> vertices;
	vector<GLuint> indices;
	vector<GLfloat> texCoords;
	vector<ofVec3f> normals;
	int nbColonnes;
	int nbLignes;
	int taille;
	float ratioTextureParCarre;
	Mesh mesh;
};

