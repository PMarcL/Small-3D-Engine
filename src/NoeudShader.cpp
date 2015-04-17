#include "NoeudShader.h"

NoeudShader::NoeudShader(Shader shader){
	this->type |= typeShader;
	this->shader = shader;
}

void NoeudShader::afficher(const ofMatrix4x4* projection, const ofMatrix4x4* vue, const Lumiere* lumiere, vector<ofMatrix4x4*>* modeles, GLuint shaderId, MATERIAUX materiau){
	this->preparerContextRendu(projection, vue, lumiere, shader.getProgramID());
	Noeud::afficher(projection, vue, lumiere, modeles, shader.getProgramID(), materiau);
	this->preparerContextRendu(projection, vue, lumiere, shaderId);
}

void NoeudShader::preparerContextRendu(const ofMatrix4x4* projection, const ofMatrix4x4* vue, const Lumiere* lumiere, GLuint shaderId){
	glUseProgram(shaderId);
	glUniformMatrix4fv(glGetUniformLocation(shaderId, "projection"), 1, GL_FALSE, projection->getPtr());
	glUniformMatrix4fv(glGetUniformLocation(shaderId, "view"), 1, GL_FALSE, vue->getPtr());
	if(lumiere != NULL)
		lumiere->chargerValeursIlluminationUniforms(shaderId);
}


void NoeudShader::ajouterNoeudAMateriau(Noeud* noeud, MATERIAUX materiau){
	list<Noeud*>::iterator i = this->listeEnfants.begin();
	bool noeudTrouve = false;
	while(i != this->listeEnfants.end() && !noeudTrouve){
		if((*i)->getType() == TypeNoeud::typeMateriau && ((NoeudMateriau*)(*i))->materiau == materiau){
			noeudTrouve = true;
			(*i)->ajouterEnfant(noeud);
		}
		i++;
	}

	if(!noeudTrouve){
		NoeudMateriau* noeudMateriau = new NoeudMateriau(materiau);
		this->ajouterEnfant(noeudMateriau);
		noeudMateriau->ajouterEnfant(noeud);
	}
}