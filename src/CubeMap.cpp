#include "CubeMap.h"

CubeMap::CubeMap(float taille, Shader* shader, string texXN, string texXP, string texYN, string texYP, string texZN, string texZP):
	m_taille(taille), m_shader(shader)
{

	tex[0] = Texture(texXN);//Avant
	tex[1] = Texture(texYP);//Droit
	tex[2] = Texture(texZP);//Dessous
	tex[3] = Texture(texXP);//Derriere
	tex[4] = Texture(texYN);//Gauche
	tex[5] = Texture(texZN);//Haut

	for(int i = 0; i < 6; i++){
		tex[i].charger();
		glBindTexture(GL_TEXTURE_2D, tex[i].getID());
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	taille /= 2;
	// Vertices temporaires
	float verticesTmp[] = {-taille, -taille, -taille,   taille, -taille, -taille,   taille, taille, -taille,     // Face 1
						   -taille, -taille, -taille,   -taille, taille, -taille,   taille, taille, -taille,

						   taille, -taille, taille,   taille, -taille, -taille,   taille, taille, -taille,       // Face 2
						   taille, -taille, taille,   taille, taille, taille,   taille, taille, -taille,

						   -taille, -taille, taille,   taille, -taille, taille,   taille, -taille, -taille,      // Face 3
						   -taille, -taille, taille,   -taille, -taille, -taille,   taille, -taille, -taille,

						   -taille, -taille, taille,   taille, -taille, taille,   taille, taille, taille,        // Face 4
						   -taille, -taille, taille,   -taille, taille, taille,   taille, taille, taille,

						   -taille, -taille, -taille,   -taille, -taille, taille,   -taille, taille, taille,     // Face 5
						   -taille, -taille, -taille,   -taille, taille, -taille,   -taille, taille, taille,

						   -taille, taille, taille,   taille, taille, taille,   taille, taille, -taille,         // Face 6
						   -taille, taille, taille,   -taille, taille, -taille,   taille, taille, -taille};

	// Copie des valeurs dans les tableaux finaux
	for(int i(0); i < 108; i++)
		m_vertices[i] = verticesTmp[i];

	// Coordonn�es de texture temporaires
	float coordTextureTmp[] = {
		0, 0,	1, 0,	1, 1,	// Face 1
		0, 0,	0, 1,	1, 1,
		
		0, 0,	1, 0,	1, 1,	// Face 2
		0, 0,	0, 1,	1, 1,
		
		0, 0,	1, 0,	1, 1,	// Face 3
		0, 0,	0, 1,	1, 1,
		
		0, 0,	1, 0,	1, 1,	// Face 4
		0, 0,	0, 1,	1, 1,
		
		0, 0,	1, 0,	1, 1,	// Face 5
		0, 0,	0, 1,	1, 1,
		
		0, 0,	1, 0,	1, 1,	// Face 6
		0, 0,	0, 1,	1, 1};

	for(int i (0); i < 72; i++)
		m_coordTexture[i] = coordTextureTmp[i];
}

CubeMap::~CubeMap()
{

}

void CubeMap::afficher(ofMatrix4x4 &projection, ofMatrix4x4 &modelview)
{
	glDisable(GL_LIGHTING);

	// D�sactivation de l'�criture dans le DepthBuffer
	glDepthMask(GL_FALSE);

	// Activation du shader
	glUseProgram(m_shader->getProgramID());
		// Envoi des vertices
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, m_vertices);
		glEnableVertexAttribArray(0);
		
		// Envoi des textures
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, m_coordTexture);
        glEnableVertexAttribArray(2);
		
		// Envoi des matrices
		glUniformMatrix4fv(glGetUniformLocation(m_shader->getProgramID(), "projection"), 1, GL_FALSE, projection.getPtr());
		glUniformMatrix4fv(glGetUniformLocation(m_shader->getProgramID(), "modelview"), 1, GL_FALSE, modelview.getPtr());
		
		for(int i = 0; i < 6; i++){
			glBindTexture(GL_TEXTURE_2D, tex[i].getID());
			//glBindTexture(GL_TEXTURE_2D, textu.getID());
			//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			glDrawArrays(GL_TRIANGLES, i * 6, 6);
			glBindTexture(GL_TEXTURE_2D, 0);
		}
		// D�sactivation des tableaux
		glDisableVertexAttribArray(2);
		glDisableVertexAttribArray(0);
		
	// D�sactivation du shader
	glUseProgram(0);

	// R�activation de l'�criture dans le DepthBuffer
	glDepthMask(GL_TRUE);

	glEnable(GL_LIGHTING);
}

CubeMap& CubeMap::operator=(CubeMap const &cubeMapACopier)
{
	for(int i = 0; i < 6; i++){
		tex[i] = cubeMapACopier.tex[i];
	}

	for(int i = 0; i < 6; i++){
		glBindTexture(GL_TEXTURE_2D, tex[i].getID());
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	m_shader = cubeMapACopier.getShader();

	int taille = cubeMapACopier.getTaille();
	taille /= 2;
	// Vertices temporaires
	float verticesTmp[] = {-taille, -taille, -taille,   taille, -taille, -taille,   taille, taille, -taille,     // Face 1
							-taille, -taille, -taille,   -taille, taille, -taille,   taille, taille, -taille,

							taille, -taille, taille,   taille, -taille, -taille,   taille, taille, -taille,       // Face 2
							taille, -taille, taille,   taille, taille, taille,   taille, taille, -taille,

							-taille, -taille, taille,   taille, -taille, taille,   taille, -taille, -taille,      // Face 3
							-taille, -taille, taille,   -taille, -taille, -taille,   taille, -taille, -taille,

							-taille, -taille, taille,   taille, -taille, taille,   taille, taille, taille,        // Face 4
							-taille, -taille, taille,   -taille, taille, taille,   taille, taille, taille,

							-taille, -taille, -taille,   -taille, -taille, taille,   -taille, taille, taille,     // Face 5
							-taille, -taille, -taille,   -taille, taille, -taille,   -taille, taille, taille,

							-taille, taille, taille,   taille, taille, taille,   taille, taille, -taille,         // Face 6
							-taille, taille, taille,   -taille, taille, -taille,   taille, taille, -taille};

	// Copie des valeurs dans les tableaux finaux
	for(int i(0); i < 108; i++)
		m_vertices[i] = verticesTmp[i];

	// Coordonn�es de texture temporaires
	float coordTextureTmp[] = {
		0, 0,	1, 0,	1, 1,	// Face 1
		0, 0,	0, 1,	1, 1,
		
		0, 0,	1, 0,	1, 1,	// Face 2
		0, 0,	0, 1,	1, 1,
		
		0, 0,	1, 0,	1, 1,	// Face 3
		0, 0,	0, 1,	1, 1,
		
		0, 0,	1, 0,	1, 1,	// Face 4
		0, 0,	0, 1,	1, 1,
		
		0, 0,	1, 0,	1, 1,	// Face 5
		0, 0,	0, 1,	1, 1,
		
		0, 0,	1, 0,	1, 1,	// Face 6
		0, 0,	0, 1,	1, 1};

	for(int i (0); i < 72; i++)
		m_coordTexture[i] = coordTextureTmp[i];

	return *this;
}

Shader* CubeMap::getShader() const
{
	return m_shader;
}

int CubeMap::getTaille() const
{
	return m_taille;
}