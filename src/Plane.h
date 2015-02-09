#pragma once

#include "Shader.h"
#include "ofMain.h"

class Plane
{
public:
	Plane():shader(NULL) {}
	Plane(int size, Shader* shader, int numColumn, int numRow);
	~Plane(void);

	void afficher(ofMatrix4x4 projection, ofMatrix4x4 modelView);
	void addTexture(const string& texPath);


private:
	void ajouterIndices();
	
	Shader* shader;
	vector<GLfloat> vertices;
	vector<GLfloat> colors;
	vector<GLuint> indices;
	vector<GLfloat> texCoords;
	int nbColonnes;
	int nbLignes;
	GLuint texture;
	bool useTexture;
};

