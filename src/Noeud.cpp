#include "Noeud.h"

int Noeud::nouveauId = 0;

Noeud::Noeud():id(nouveauId++), type(typeNoeud){
	this->parent = NULL;
}

Noeud::~Noeud(){
	this->supprimerEnfants();
	if(parent != NULL)
		parent->retirerEnfantListe(this->id);
}

void Noeud::afficher(const ofMatrix4x4* projection, const ofMatrix4x4* vue, const Lumiere* lumiere, vector<ofMatrix4x4*>* modeles, GLuint shaderId, MATERIAUX materiau){
	this->afficherEnfants(projection, vue, lumiere, modeles, shaderId, materiau);
}

void Noeud::supprimerEnfants(){
	list<Noeud*> temp;
	for(list<Noeud*>::iterator i = this->listeEnfants.begin(); i != this->listeEnfants.end(); i++)
			temp.push_back((*i));
	for(list<Noeud*>::iterator i = temp.begin(); i != temp.end(); i++)
		delete (*i);
	//En fesant un delete sur les enfants, la liste va se vider automatiquement
    //this->listeEnfants.clear();
}

void Noeud::ajouterEnfant(Noeud* enfant){
	enfant->changerParent(this);
}

void Noeud::ajouterEnfantListe(Noeud* enfant){
	this->listeEnfants.push_back(enfant);
}

void Noeud::retirerEnfantListe(int idEnfant){
	bool enfantTrouve = false;
	list<Noeud*>::iterator i = this->listeEnfants.begin();

	while(!enfantTrouve && i != this->listeEnfants.end()){
		if((*i)->getId() == idEnfant){
			enfantTrouve = true;
			this->listeEnfants.erase(i);
		}else
			i++;
	}
}

int Noeud::getId(){
	return this->id;
}

void Noeud::changerParent(Noeud* parent){
	if(this->parent != NULL)
		this->parent->retirerEnfantListe(this->id);
	if(parent != NULL)
		parent->ajouterEnfantListe(this);
	this->parent = parent;
}

Noeud* Noeud::trouverNoeud(int id){
	list<Noeud*>::iterator i = this->listeEnfants.begin();
	Noeud* noeudTrouve = NULL;
	while(i != this->listeEnfants.end() && noeudTrouve == NULL){
		if((*i)->getId() == id)
			noeudTrouve = (*i);
		else
			noeudTrouve = (*i)->trouverNoeud(id);
		i++;			
	}
	return noeudTrouve;
}

Noeud* Noeud::trouverMesh(ofVec3f position, float rayon){
	float d = FLT_MAX;
	float* distanceMinimum = &d;

	return this->chercherMesh(NULL, position, rayon, distanceMinimum, new vector<ofMatrix4x4*>);
}

Noeud* Noeud::chercherMesh(Noeud* meshPlusProche, ofVec3f position, float rayon, float* distanceMinimum, vector<ofMatrix4x4*>* transformations){
	for(list<Noeud*>::iterator i = this->listeEnfants.begin(); i != this->listeEnfants.end(); i++)
		meshPlusProche = (*i)->chercherMesh(meshPlusProche, position, rayon, distanceMinimum, transformations);
	return meshPlusProche;
}

void Noeud::afficherEnfants(const ofMatrix4x4* projection, const ofMatrix4x4* vue, const Lumiere* lumiere, vector<ofMatrix4x4*>* modeles, GLuint shaderId, MATERIAUX materiau){
	for(list<Noeud*>::iterator i = this->listeEnfants.begin(); i != this->listeEnfants.end(); i++)
		(*i)->afficher(projection, vue, lumiere, modeles, shaderId, materiau);
}

uint8_t Noeud::getType(){
	return this->type;
}

ofMatrix4x4 Noeud::getTransformationsPrecedentes(){
	if(this->parent == NULL)
		return ofMatrix4x4::newIdentityMatrix();
	return this->parent->getTransformationsPrecedentes();
}

Noeud* Noeud::getParent(){
	return this->parent;
}