#include "Lumiere.h"


Lumiere::Lumiere(void)
	:direction(DIRECTION_LUMIERE_DEFAUT), position(POSITION_LUMIERE_DEFAUT), couleurDirectionnelle(COUL_LUMIERE_DEFAUT), couleurAmbiante(COUL_AMBIANTE_DEFAUT),
	couleurSpeculaire(REFLECTiON_SPEC_COUL), intensiteLumiereAmbiante(QUANTITE_LUMIERE_DEFAUT), intensiteSpeculaire(INTENSITE_SPEC_DEFAUT)
{
}


Lumiere::~Lumiere(void)
{
}

void Lumiere::deplacerLumiere(ofVec3f nouvellePosition)
{
	position = nouvellePosition;
}

void Lumiere::setIntensiteLumiereAmbiante(GLfloat intensite)
{
	intensiteLumiereAmbiante = intensite;
}

void Lumiere::setPositionVue(ofVec3f position)
{
	positionVue = position;
}

void Lumiere::chargerValeursIlluminationUniforms(GLuint programId) const
{
	glUniform1f(glGetUniformLocation(programId, "intensiteLumiere"), intensiteLumiereAmbiante);
	glUniform3fv(glGetUniformLocation(programId, "lumiereAmbiante"), 1, couleurAmbiante.getPtr());
	//glUniform3fv(glGetUniformLocation(programId, "positionLumiere"), 1, position.getPtr());
	glUniform3fv(glGetUniformLocation(programId, "directionLumiere"), 1, direction.getPtr());
	glUniform3fv(glGetUniformLocation(programId, "couleurLumiere"), 1, couleurDirectionnelle.getPtr());
	glUniform1f(glGetUniformLocation(programId, "intensiteSpeculaire"), intensiteSpeculaire);
	glUniform3fv(glGetUniformLocation(programId, "positionCamera"), 1, positionVue.getPtr());
}

void Lumiere::chargerValeursIlluminationStruct(GLuint programId) const
{
	glUniform3fv(glGetUniformLocation(programId, "lumiere.ambiante"), 1, couleurAmbiante.getPtr());
	//glUniform3fv(glGetUniformLocation(programId, "lumiere.position"), 1, position.getPtr());
	glUniform3fv(glGetUniformLocation(programId, "lumiere.direction"), 1, direction.getPtr());
	glUniform3fv(glGetUniformLocation(programId, "lumiere.diffuse"), 1, couleurDirectionnelle.getPtr());
	glUniform3fv(glGetUniformLocation(programId, "lumiere.speculaire"), 1, couleurSpeculaire.getPtr());
	glUniform3fv(glGetUniformLocation(programId, "positionCamera"), 1, positionVue.getPtr());
}

GLfloat Lumiere::getIntensiteLumiereAmbiante()
{
	return intensiteLumiereAmbiante;
}