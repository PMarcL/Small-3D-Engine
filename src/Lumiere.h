#pragma once

#include "ofMain.h"

const static ofVec3f COUL_DIFFUSE_DEFAUT = ofVec3f(0.5, 0.5, 0.5);
const static ofVec3f COUL_AMBIANTE_DEFAUT = ofVec3f(0.1, 0.07, 0.01);
const static ofVec3f COUL_REFLECTION_SPEC = ofVec3f(1.0, 0.9, 0.7);
const static ofVec3f DIRECTION_LUMIERE_DEFAUT = ofVec3f(0.5, 0.1, 0.35);

struct LumiereDirectionnelle {
	ofVec3f direction;
	ofVec3f ambiante;
	ofVec3f diffuse;
	ofVec3f speculaire;
};

struct LumierePonctuelle {
	ofVec3f position;
	ofVec3f ambiante;
	ofVec3f diffuse;
	ofVec3f speculaire;

	float constante;
	float lineaire;
	float quadratique;
};

struct Projecteur {
	ofVec3f direction;
	ofVec3f position;
	ofVec3f diffuse;
	ofVec3f speculaire;

	float coneInterne;
	float coneExterne;
};

class Lumiere
{
public:
	Lumiere(void);
	~Lumiere(void);

	void setPositionVue(ofVec3f position);
	void chargerValeursIlluminationUniforms(GLuint programId) const;
	void ajouterProjecteur(Projecteur proj);
	void ajouterLumierePonctuelle(LumierePonctuelle lumiere);
	void ajouterLampeDePoche(ofVec3f position, ofVec3f direction);
	void changerValeurCouleurRougeLampeDePoche(float r);
	void changerValeurCouleurVertLampeDePoche(float g);
	void changerValeurCouleurBleuLampeDePoche(float b);
	void changerValeurConeInterneLampeDePoche(float angle);
	void changerValeurConeExterneLampeDePoche(float angle);
	void enleverLampeDePoche();
	void mettreAJourLampeDePoche(ofVec3f position, ofVec3f direction);

private:
	void chargerLumiereDirectionnelle(GLuint programId) const;
	void chargerProjecteurs(GLuint programId) const;
	void chargerPonctuelles(GLuint programId) const;

	LumiereDirectionnelle lumDirectionnelle;
	vector<LumierePonctuelle> lumPonctuelles;
	vector<Projecteur> projecteurs;

	Projecteur* lampeDePoche;
	ofVec3f positionVue;
};

