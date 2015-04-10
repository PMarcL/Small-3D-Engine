#include "NoeudMateriau.h"

NoeudMateriau::NoeudMateriau(MATERIAUX materiau){
	this->type |= typeMateriau;
	this->materiau = materiau;
}

void NoeudMateriau::afficher(const ofMatrix4x4* projection, const ofMatrix4x4* vue, const Lumiere* lumiere, vector<ofMatrix4x4*>* modeles, GLuint shaderId, MATERIAUX materiau){
	this->appliquerMateriau(this->materiau, shaderId);

	this->afficherEnfants(projection, vue, lumiere, modeles, shaderId, this->materiau);
	
	this->appliquerMateriau(materiau, shaderId);
}

void NoeudMateriau::appliquerMateriau(MATERIAUX materiau, GLuint shaderId){
	ofVec3f reflectionAmbiante;
	ofVec3f reflectionDiffuse;
	ofVec3f reflectionSpeculaire;
	GLfloat brillance;
	vector<float> materiauInfo = getMateriauData(materiau);
	reflectionAmbiante = ofVec3f(materiauInfo[0], materiauInfo[1], materiauInfo[2]);
	reflectionDiffuse = ofVec3f(materiauInfo[3], materiauInfo[4], materiauInfo[5]);
	reflectionSpeculaire = ofVec3f(materiauInfo[6], materiauInfo[7], materiauInfo[8]);
	brillance = materiauInfo[9] * 128;

	glUniform3fv(glGetUniformLocation(shaderId, "materiau.ambiante"), 1, reflectionAmbiante.getPtr());
	glUniform3fv(glGetUniformLocation(shaderId, "materiau.diffuse"), 1, reflectionDiffuse.getPtr());
	glUniform3fv(glGetUniformLocation(shaderId, "materiau.speculaire"), 1, reflectionSpeculaire.getPtr());
	glUniform1f(glGetUniformLocation(shaderId, "materiau.brillance"), brillance);
}