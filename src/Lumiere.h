#pragma once

#include "ofMain.h"

const static float QUANTITE_LUMIERE_DEFAUT = 0.2;
const static float INTENSITE_SPEC_DEFAUT = 0.5;
const static ofVec3f POSITION_LUMIERE_DEFAUT = ofVec3f(1500, 2500, 500);
const static ofVec3f COUL_LUMIERE_DEFAUT = ofVec3f(1.0, 1.0, 1.0);
const static ofVec3f COUL_AMBIANTE_DEFAUT = ofVec3f(0.3, 0.0, 0.8);

class Lumiere
{
public:
	Lumiere(void);
	~Lumiere(void);

	void deplacerLumiere(ofVec3f nouvellePosition);
	void setIntensiteLumiereAmbiante(GLfloat intensite);
	void setPositionVue(ofVec3f position);
	ofVec3f getPosition() const;
	ofVec3f getCouleurDirectionnelle() const;
	ofVec3f getCouleurAmbiante() const;
	ofVec3f getPositionVue() const;
	GLfloat getIntensiteLumiereAmbiante() const;
	GLfloat getIntensiteSpeculaire() const;

private:

	ofVec3f position;
	ofVec3f positionVue;
	ofVec3f couleurDirectionnelle;
	ofVec3f couleurAmbiante;
	GLfloat intensiteLumiereAmbiante;
	GLfloat intensiteSpeculaire;
};

