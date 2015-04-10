#pragma once

#include "Noeud.h"

class NoeudMateriau : public  Noeud
{
    public:
		NoeudMateriau(MATERIAUX materiau);
		~NoeudMateriau(){};

		virtual void afficher(const ofMatrix4x4* projection, const ofMatrix4x4* vue, const Lumiere* lumiere, vector<ofMatrix4x4*>* modeles, GLuint shaderId, MATERIAUX materiau);	

		MATERIAUX materiau;
	protected:
		void appliquerMateriau(MATERIAUX materiau, GLuint shaderId);
};