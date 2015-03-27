#pragma once

#include "ofMain.h"

const static float QUANTITE_LUMIERE_DEFAUT = 0.2;
const static float INTENSITE_SPEC_DEFAUT = 0.5;
const static ofVec3f POSITION_LUMIERE_DEFAUT = ofVec3f(1500, 1000, 1200);
const static ofVec3f COUL_LUMIERE_DEFAUT = ofVec3f(0.5, 0.5, 0.5);
const static ofVec3f COUL_AMBIANTE_DEFAUT = ofVec3f(0.11, 0.3, 0.8);
const static ofVec3f REFLECTiON_SPEC_COUL = ofVec3f(1.0, 1.0, 1.0);
const static ofVec3f DIRECTION_LUMIERE_DEFAUT = ofVec3f(0.5, 0.3, 0.5);

class Lumiere
{
public:
	Lumiere(void);
	~Lumiere(void);

	void deplacerLumiere(ofVec3f nouvellePosition);
	void setIntensiteLumiereAmbiante(GLfloat intensite);
	void setPositionVue(ofVec3f position);
	void chargerValeursIlluminationUniforms(GLuint programId) const;
	void chargerValeursIlluminationStruct(GLuint programId) const;
	GLfloat getIntensiteLumiereAmbiante();

private:

	ofVec3f direction;
	ofVec3f position;
	ofVec3f positionVue;
	ofVec3f couleurDirectionnelle;
	ofVec3f couleurAmbiante;
	ofVec3f couleurSpeculaire;
	GLfloat intensiteLumiereAmbiante;
	GLfloat intensiteSpeculaire;
};

