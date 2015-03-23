#include "Lumiere.h"


Lumiere::Lumiere(void)
	:position(POSITION_LUMIERE_DEFAUT), couleurDirectionnelle(COUL_LUMIERE_DEFAUT), couleurAmbiante(COUL_AMBIANTE_DEFAUT),
	intensiteLumiereAmbiante(QUANTITE_LUMIERE_DEFAUT), intensiteSpeculaire(INTENSITE_SPEC_DEFAUT)
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

ofVec3f Lumiere::getPosition() const
{
	return position;
}

ofVec3f Lumiere::getCouleurDirectionnelle() const
{
	return couleurDirectionnelle;
}

ofVec3f Lumiere::getCouleurAmbiante() const
{
	return couleurAmbiante;
}

GLfloat Lumiere::getIntensiteLumiereAmbiante() const
{
	return intensiteLumiereAmbiante;
}

GLfloat Lumiere::getIntensiteSpeculaire() const
{
	return intensiteSpeculaire;
}