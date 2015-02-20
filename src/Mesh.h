#pragma once

#include "ofMain.h"

const static int NB_VERTEX_ATTRIB = 11;

struct Vertex {
	Vertex()
		:x(0), y(0), z(0), 
		colorR(0), colorG(0), colorB(0), 
		texCoordX(0), texCoordY(0), 
		normalX(0), normalY(0), normalZ(0)
	{}

	GLfloat x;
	GLfloat y;
	GLfloat z;

	GLfloat colorR;
	GLfloat colorG;
	GLfloat colorB;

	GLfloat texCoordX;
	GLfloat texCoordY;

	GLfloat normalX;
	GLfloat normalY;
	GLfloat normalZ;
};


class Mesh
{
public:
	Mesh();
	Mesh(const vector<GLfloat>& positions, const vector<GLfloat>& colors, 
		const vector<GLfloat>& texCoords, const vector<GLfloat>& normals, 
		const vector<GLuint>& indices, int nbSommets);
	Mesh(const vector<ofVec3f>& positions, const vector<ofVec3f>& colors,
		const vector<ofVec3f>& normals, const vector<GLuint>& indices, int nbSommets);
	~Mesh(void) {}
	
	void utilisationDesIndices(bool utiliser);
	void dessiner();

private:
	void ajouterVertices(int nbVertices);
	void ajouterPositions(const vector<GLfloat>& positions);
	void ajouterCouleurs(const vector<GLfloat>& couleurs);
	void ajouterTexCoords(const vector<GLfloat>& texCoords);
	void ajouterNormals(const vector<GLfloat>& normals);
	void ajouterIndices(const vector<GLuint>& indices);
	void ajouterPositions(const vector<ofVec3f>& positions);
	void ajouterCouleurs(const vector<ofVec3f>& positions);
	void ajouterNormals(const vector<ofVec3f>& positions);
	void genererBuffer();

	bool utiliserIndices;
	vector<Vertex> vertices;
	vector<GLuint> indices;
	GLuint vertexBufferObject;
	GLuint vertexArrayObject;
	GLuint elementArrayBuffer;
};

