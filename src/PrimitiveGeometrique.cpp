#include "PrimitiveGeometrique.h"


PrimitiveGeometrique::PrimitiveGeometrique(PRIMITIVES primitive, MATERIAUX materiaux, ofVec3f position, int taille)
	:position(position), materiaux(materiaux)
{
	vector<float> sommets = getSommetsPourPrimitive(primitive, taille);
	vector<float> normals = getNormals(sommets);
	vector<float> texCoords = getTexCoordPourPrimitive(primitive);

	mesh = Mesh(sommets, vector<float>(), texCoords, normals, vector<GLuint>(), sommets.size()/3);

	setMateriaux(materiaux);
}


PrimitiveGeometrique::~PrimitiveGeometrique(void)
{
}

MATERIAUX PrimitiveGeometrique::getMateriaux()
{
	return materiaux;
}

void PrimitiveGeometrique::setMateriaux(MATERIAUX materiaux)
{
	this->materiaux = materiaux;
	vector<float> materiauxInfo = getMateriauxData(materiaux);
	reflectionAmbiante = ofVec3f(materiauxInfo[0], materiauxInfo[1], materiauxInfo[2]);
	reflectionDiffuse = ofVec3f(materiauxInfo[3], materiauxInfo[4], materiauxInfo[5]);
	reflectionSpeculaire = ofVec3f(materiauxInfo[6], materiauxInfo[7], materiauxInfo[8]);
	brillance = materiauxInfo[9] * 128;
}

void PrimitiveGeometrique::afficher()
{
	mesh.dessiner();
}

void PrimitiveGeometrique::chargerMateriauxUniforms(GLuint programId) const
{
	glUniform3fv(glGetUniformLocation(programId, "materiaux.ambiante"), 1, reflectionAmbiante.getPtr());
	glUniform3fv(glGetUniformLocation(programId, "materiaux.diffuse"), 1, reflectionDiffuse.getPtr());
	glUniform3fv(glGetUniformLocation(programId, "materiaux.speculaire"), 1, reflectionSpeculaire.getPtr());
	glUniform1f(glGetUniformLocation(programId, "materiaux.brillance"), brillance);
}

ofVec3f PrimitiveGeometrique::getPosition()
{
	return position;
}

void PrimitiveGeometrique::setPosition(ofVec3f position)
{
	this->position = position;
}