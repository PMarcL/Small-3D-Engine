#pragma once

#include "Noeud.h"

class NoeudMateriau : public  Noeud
{
    public:
		NoeudMateriau(MATERIAUX materiau);
		~NoeudMateriau(){};

		virtual void afficher(const ParametresAffichage* paramsAff, GLuint shaderId, MATERIAUX materiau);	

		MATERIAUX materiau;
	protected:
		void appliquerMateriau(MATERIAUX materiau, GLuint shaderId);
};