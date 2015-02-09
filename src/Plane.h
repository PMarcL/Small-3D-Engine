#pragma once

#include "Shader.h"
#include "ofMain.h"

class Plane
{
public:
	Plane():shader(NULL) {}
	Plane(int size, Shader* shader);
	~Plane(void);

	void afficher(ofMatrix4x4 projection, ofMatrix4x4 modelView);
	void addTexture(const string& texPath);

private:
	
	Shader* shader;
	vector<GLfloat> vertices;
	vector<GLfloat> colors;
	vector<GLuint> indices;
	vector<GLfloat> texCoords;
	GLuint texture;
	bool useTexture;
};

