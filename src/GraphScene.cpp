#include "GraphScene.h"

GraphScene::GraphScene(){
	this->type |= typeGraphScene;
}

void GraphScene::afficher(const ofMatrix4x4* projection, const ofMatrix4x4* vue, const Lumiere* lumiere){
	GLint precedentGlProgram;
	glGetIntegerv(GL_CURRENT_PROGRAM, &precedentGlProgram);

	vector<ofMatrix4x4*>* modeles = new vector<ofMatrix4x4*>;
	preparerContextRendu(projection, vue, lumiere, this->shaderIdOrigine);

	this->afficherEnfants(projection, vue, lumiere, modeles, this->shaderIdOrigine, MATERIAUX::AUCUN);

	glUseProgram(precedentGlProgram);
}

void GraphScene::preparerContextRendu(const ofMatrix4x4* projection, const ofMatrix4x4* vue, const Lumiere* lumiere, GLuint shaderId){
	glUseProgram(shaderId);
	glUniformMatrix4fv(glGetUniformLocation(shaderId, "projection"), 1, GL_FALSE, projection->getPtr());
	glUniformMatrix4fv(glGetUniformLocation(shaderId, "view"), 1, GL_FALSE, vue->getPtr());
	if(lumiere != NULL)
		lumiere->chargerValeursIlluminationUniforms(shaderId);
}