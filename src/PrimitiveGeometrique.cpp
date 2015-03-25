#include "PrimitiveGeometrique.h"


PrimitiveGeometrique::PrimitiveGeometrique(PRIMITIVES primitive, int taille)
{
	vector<float> sommets = getSommetsPourPrimitive(primitive, taille);
	vector<float> normals = getNormals(sommets);
	vector<float> texCoords = getTexCoordPourPrimitive(primitive);

	mesh = Mesh(sommets, vector<float>(), texCoords, normals, vector<GLuint>(), sommets.size()/3);
}


PrimitiveGeometrique::~PrimitiveGeometrique(void)
{
}


void PrimitiveGeometrique::afficher()
{
	mesh.dessiner();
}