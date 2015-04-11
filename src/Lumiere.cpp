#include "Lumiere.h"
#include <sstream>

Lumiere::Lumiere(void)
{
	lampeDePoche = NULL;
	lumDirectionnelle.direction = DIRECTION_LUMIERE_DEFAUT;
	lumDirectionnelle.ambiante = COUL_AMBIANTE_DEFAUT;
	lumDirectionnelle.diffuse = COUL_DIFFUSE_DEFAUT;
	lumDirectionnelle.speculaire = COUL_REFLECTION_SPEC;
}


Lumiere::~Lumiere(void)
{
}

void Lumiere::setPositionVue(ofVec3f position)
{
	positionVue = position;
}

void Lumiere::chargerValeursIlluminationUniforms(GLuint programId) const
{
	chargerLumiereDirectionnelle(programId);
	chargerProjecteurs(programId);
	chargerPonctuelles(programId);
}

void Lumiere::chargerLumiereDirectionnelle(GLuint programId) const
{
	glUniform3fv(glGetUniformLocation(programId, "lumDirectionnelle.ambiante"), 1, lumDirectionnelle.ambiante.getPtr());
	glUniform3fv(glGetUniformLocation(programId, "lumDirectionnelle.direction"), 1, lumDirectionnelle.direction.getPtr());
	glUniform3fv(glGetUniformLocation(programId, "lumDirectionnelle.diffuse"), 1, lumDirectionnelle.diffuse.getPtr());
	glUniform3fv(glGetUniformLocation(programId, "lumDirectionnelle.speculaire"), 1, lumDirectionnelle.speculaire.getPtr());
	glUniform3fv(glGetUniformLocation(programId, "positionCamera"), 1, positionVue.getPtr());
}

void Lumiere::chargerProjecteurs(GLuint programId) const
{
	glUniform1i(glGetUniformLocation(programId, "nbProjecteurs"), projecteurs.size());
	for(int i = 0; i < projecteurs.size(); i++)
	{
		stringstream projecteurTableau;
		projecteurTableau << "projecteur[" << i << "].";
		string formatedString = projecteurTableau.str();
		formatedString.append("position");
		glUniform3fv(glGetUniformLocation(programId, formatedString.c_str()), 1, projecteurs[i].position.getPtr());
		formatedString = projecteurTableau.str();
		formatedString.append("direction");
		glUniform3fv(glGetUniformLocation(programId, formatedString.c_str()), 1, projecteurs[i].direction.getPtr());
		formatedString = projecteurTableau.str();
		formatedString.append("diffuse");
		glUniform3fv(glGetUniformLocation(programId, formatedString.c_str()), 1, projecteurs[i].diffuse.getPtr());
		formatedString = projecteurTableau.str();
		formatedString.append("speculaire");
		glUniform3fv(glGetUniformLocation(programId, formatedString.c_str()), 1, projecteurs[i].speculaire.getPtr());
		formatedString = projecteurTableau.str();
		formatedString.append("coneInterne");
		glUniform1f(glGetUniformLocation(programId, formatedString.c_str()), projecteurs[i].coneInterne);
		formatedString = projecteurTableau.str();
		formatedString.append("coneExterne");
		glUniform1f(glGetUniformLocation(programId, formatedString.c_str()), projecteurs[i].coneExterne);
	}

}

void Lumiere::chargerPonctuelles(GLuint programId) const
{
	glUniform1i(glGetUniformLocation(programId, "nbPonctuelles"), lumPonctuelles.size());
	for(int i = 0; i < lumPonctuelles.size(); i++)
	{
		stringstream ponctuelleTableau;
		ponctuelleTableau << "ponctuelles[" << i << "].";
		string formatedString = ponctuelleTableau.str();
		formatedString.append("position");
		glUniform3fv(glGetUniformLocation(programId, formatedString.c_str()), 1, lumPonctuelles[i].position.getPtr());
		formatedString = ponctuelleTableau.str();
		formatedString.append("ambiante");
		glUniform3fv(glGetUniformLocation(programId, formatedString.c_str()), 1, lumPonctuelles[i].ambiante.getPtr());
		formatedString = ponctuelleTableau.str();
		formatedString.append("diffuse");
		glUniform3fv(glGetUniformLocation(programId, formatedString.c_str()), 1, lumPonctuelles[i].diffuse.getPtr());
		formatedString = ponctuelleTableau.str();
		formatedString.append("speculaire");
		glUniform3fv(glGetUniformLocation(programId, formatedString.c_str()), 1, lumPonctuelles[i].speculaire.getPtr());
		formatedString = ponctuelleTableau.str();
		formatedString.append("constante");
		glUniform1f(glGetUniformLocation(programId, formatedString.c_str()), lumPonctuelles[i].constante);
		formatedString = ponctuelleTableau.str();
		formatedString.append("lineaire");
		glUniform1f(glGetUniformLocation(programId, formatedString.c_str()), lumPonctuelles[i].lineaire);
		formatedString = ponctuelleTableau.str();
		formatedString.append("quadratique");
		glUniform1f(glGetUniformLocation(programId, formatedString.c_str()), lumPonctuelles[i].quadratique);
	}

}

void Lumiere::ajouterProjecteur(Projecteur proj)
{
	projecteurs.push_back(proj);
}

void Lumiere::ajouterLumierePonctuelle(LumierePonctuelle lumiere)
{
	lumPonctuelles.push_back(lumiere);
}

void Lumiere::ajouterLampeDePoche(ofVec3f position, ofVec3f direction)
{
	if(lampeDePoche == NULL)
	{
		projecteurs.push_back(Projecteur());
		lampeDePoche = &projecteurs[projecteurs.size() - 1];
		lampeDePoche->position = position;
		lampeDePoche->direction = direction;
		lampeDePoche->diffuse = ofVec3f(0.8, 0.8, 0.8);
		lampeDePoche->speculaire = ofVec3f(1.0, 1.0, 1.0);
		lampeDePoche->coneInterne = cos(ofDegToRad(10.5));
		lampeDePoche->coneExterne = cos(ofDegToRad(20.0));
	}
}

void Lumiere::changerValeurCouleurRougeLampeDePoche(float r)
{
	if(lampeDePoche != NULL)
	{
		lampeDePoche->diffuse.x = r;
		lampeDePoche->speculaire.x = r + 0.2;
	}
}

void Lumiere::changerValeurCouleurVertLampeDePoche(float g)
{
	if(lampeDePoche != NULL)
	{
		lampeDePoche->diffuse.y = g;
		lampeDePoche->speculaire.y = g + 0.2;
	}
}

void Lumiere::changerValeurCouleurBleuLampeDePoche(float b)
{
	if(lampeDePoche != NULL)
	{
		lampeDePoche->diffuse.z = b;
		lampeDePoche->speculaire.z = b + 0.2;
	}
}

void Lumiere::changerValeurConeInterneLampeDePoche(float angle)
{
	if(lampeDePoche != NULL)
	{
		lampeDePoche->coneInterne = cos(ofDegToRad(angle));
	}
}

void Lumiere::changerValeurConeExterneLampeDePoche(float angle)
{
	if(lampeDePoche != NULL)
	{
		lampeDePoche->coneExterne = cos(ofDegToRad(angle));
	}
}

void Lumiere::enleverLampeDePoche()
{
	if(lampeDePoche != NULL)
	{
		for(vector<Projecteur>::iterator i = projecteurs.begin();
			i != projecteurs.end(); i++)
		{
			if(&(*i) == lampeDePoche)
			{
				projecteurs.erase(i);
				break;
			}
		}
		lampeDePoche = NULL;
	}
}

void Lumiere::mettreAJourLampeDePoche(ofVec3f position, ofVec3f direction)
{
	if(lampeDePoche != NULL)
	{
		lampeDePoche->position = position;
		lampeDePoche->direction = direction;
	}
}