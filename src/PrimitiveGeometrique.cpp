#include "PrimitiveGeometrique.h"


PrimitiveGeometrique::PrimitiveGeometrique(PRIMITIVES primitive, MATERIAUX materiau, ofVec3f position, int taille)
	:position(position), materiau(materiau)
{
	vector<float> sommets = getSommetsPourPrimitive(primitive, taille);
	vector<float> normals = getNormals(sommets);
	vector<float> texCoords = getTexCoordPourPrimitive(primitive);

	mesh = Mesh(sommets, vector<float>(), texCoords, normals, vector<GLuint>(), sommets.size()/3);

	setMateriau(materiau);
}


PrimitiveGeometrique::~PrimitiveGeometrique(void)
{
}

MATERIAUX PrimitiveGeometrique::getMateriau()
{
	return materiau;
}

void PrimitiveGeometrique::setMateriau(MATERIAUX materiau)
{
	this->materiau = materiau;
	vector<float> materiauInfo = getMateriauData(materiau);
	reflectionAmbiante = ofVec3f(materiauInfo[0], materiauInfo[1], materiauInfo[2]);
	reflectionDiffuse = ofVec3f(materiauInfo[3], materiauInfo[4], materiauInfo[5]);
	reflectionSpeculaire = ofVec3f(materiauInfo[6], materiauInfo[7], materiauInfo[8]);
	brillance = materiauInfo[9] * 128;
}

void PrimitiveGeometrique::afficher()
{
	mesh.dessiner();
}

void PrimitiveGeometrique::chargerMateriauUniforms(GLuint programId) const
{
	glUniform3fv(glGetUniformLocation(programId, "materiau.ambiante"), 1, reflectionAmbiante.getPtr());
	glUniform3fv(glGetUniformLocation(programId, "materiau.diffuse"), 1, reflectionDiffuse.getPtr());
	glUniform3fv(glGetUniformLocation(programId, "materiau.speculaire"), 1, reflectionSpeculaire.getPtr());
	glUniform1f(glGetUniformLocation(programId, "materiau.brillance"), brillance);
}

ofVec3f PrimitiveGeometrique::getPosition()
{
	return position;
}

void PrimitiveGeometrique::setPosition(ofVec3f position)
{
	this->position = position;
}