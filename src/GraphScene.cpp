#include "GraphScene.h"

GraphScene::GraphScene(){
	this->type |= typeGraphScene;
}

void GraphScene::afficher(const ofMatrix4x4* projection, const ofMatrix4x4* vue, const Lumiere* lumiere, ofVec3f orientationCamera, ofVec3f positionCamera){
	GLint precedentGlProgram;
	glGetIntegerv(GL_CURRENT_PROGRAM, &precedentGlProgram);

	preparerContextRendu(projection, vue, lumiere, this->shaderIdOrigine);

	ParametresAffichage* paramsAff = new ParametresAffichage();
	paramsAff->projection = projection;
	paramsAff->vue = vue;
	paramsAff->lumiere = lumiere;
	paramsAff->modeles = new vector<ofMatrix4x4*>;
	paramsAff->normalPlan = new ofVec3f(orientationCamera.getNormalized());
	paramsAff->positionPlan = new ofVec3f(positionCamera);

	this->afficherEnfants(paramsAff, this->shaderIdOrigine, MATERIAUX::AUCUN);

	glUseProgram(precedentGlProgram);
}

void GraphScene::preparerContextRendu(const ofMatrix4x4* projection, const ofMatrix4x4* vue, const Lumiere* lumiere, GLuint shaderId){
	glUseProgram(shaderId);
	glUniformMatrix4fv(glGetUniformLocation(shaderId, "projection"), 1, GL_FALSE, projection->getPtr());
	glUniformMatrix4fv(glGetUniformLocation(shaderId, "view"), 1, GL_FALSE, vue->getPtr());
	if(lumiere != NULL)
		lumiere->chargerValeursIlluminationUniforms(shaderId);
}