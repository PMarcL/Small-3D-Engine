#pragma once

#include "ofMain.h"
#include "Lumiere.h"
#include "PrimitivesData.h"//Changer pour un materiau data<<<<<<<<<<

class Noeud
{
    public:
		enum TypeNoeud : uint8_t{//� retirer si au final �a ne sert pas.<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
			typeNoeud = 0,
			typeShader = 1,
			typeTransformation = 2,
			typeMesh = 4,
			typeGraphScene = 8,
			typeMateriau = 16
		};

		Noeud();
		~Noeud();

		virtual void afficher(const ofMatrix4x4* projection, const ofMatrix4x4* vue, const Lumiere* lumiere, vector<ofMatrix4x4*>* modeles, GLuint shaderId, MATERIAUX materiau);

		void ajouterEnfant(Noeud* enfant);
		void supprimerEnfants();
		void changerParent(Noeud* parent);
		Noeud* trouverNoeud(int id);
		Noeud* trouverMesh(ofVec3f position, float rayon);

		int getId();
		uint8_t getType();
	protected:
		static int nouveauId;
		Noeud* parent;
		list<Noeud*> listeEnfants;
		uint8_t type;

		void ajouterEnfantListe(Noeud* enfant);
		void retirerEnfantListe(int idEnfant);

		virtual Noeud* chercherMesh(Noeud* meshPlusProche, ofVec3f position, float rayon, float* distanceMinimum, vector<ofMatrix4x4*>* transformations);
		virtual ofMatrix4x4 getTransformationsPrecedentes();

		void afficherEnfants(const ofMatrix4x4* projection, const ofMatrix4x4* vue, const Lumiere* lumiere, vector<ofMatrix4x4*>* modeles, GLuint shaderId, MATERIAUX materiau);
	private:
		const int id;
};