#include "Octaedre.h"

Octaedre::Octaedre(float taille, Shader* shader) : m_shader(shader)
{

	taille /= 2;
	// Vertices temporaires
	float verticesTmp[] = {
		-taille, 0, -taille,
		0, taille, 0,
		taille, 0, -taille,

		taille, 0, -taille,
		0, taille, 0,
		taille, 0, taille,

		taille, 0, taille,
		0, taille, 0,
		-taille, 0, taille,

		-taille, 0, taille,
		0, taille, 0,
		-taille, 0, -taille,


		-taille, 0, -taille,
		0, -taille, 0,
		taille, 0, -taille,

		taille, 0, -taille,
		0, -taille, 0,
		taille, 0, taille,

		taille, 0, taille,
		0, -taille, 0,
		-taille, 0, taille,

		-taille, 0, taille,
		0, -taille, 0,
		-taille, 0, -taille
	};

	// Couleurs temporaires
	float couleursTmp[] = { 0.0, 0.0, 0.0,	0.0, 1.0, 0.0,	0.0, 0.0, 0.0,
							0.0, 0.0, 0.0,	0.0, 1.0, 0.0,	0.0, 0.0, 0.0,
							0.0, 0.0, 0.0,	0.0, 1.0, 0.0,	0.0, 0.0, 0.0,
							0.0, 0.0, 0.0,	0.0, 1.0, 0.0,	0.0, 0.0, 0.0,
							
							0.0, 0.0, 0.0,	0.0, 0.0, 1.0,	0.0, 0.0, 0.0,
							0.0, 0.0, 0.0,	0.0, 0.0, 1.0,	0.0, 0.0, 0.0,
							0.0, 0.0, 0.0,	0.0, 0.0, 1.0,	0.0, 0.0, 0.0,
							0.0, 0.0, 0.0,	0.0, 0.0, 1.0,	0.0, 0.0, 0.0};
						   
	// Copie des valeurs dans les tableaux finaux
	for(int i(0); i < 72; i++)
	{
		m_vertices[i] = verticesTmp[i];
		m_couleurs[i] = couleursTmp[i];
	}
}

Octaedre::~Octaedre()
{

}

void Octaedre::afficher(ofMatrix4x4 &projection, ofMatrix4x4 &modelview)
{
	// Activation du shader
	glUseProgram(m_shader->getProgramID());
		
		// Envoi des vertices
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, m_vertices);
		glEnableVertexAttribArray(0);
		
		// Envoi de la couleur
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, m_couleurs);
		glEnableVertexAttribArray(1);
		
		// Envoi des matrices
		glUniformMatrix4fv(glGetUniformLocation(m_shader->getProgramID(), "projection"), 1, GL_FALSE, projection.getPtr());
		glUniformMatrix4fv(glGetUniformLocation(m_shader->getProgramID(), "modelview"), 1, GL_FALSE, modelview.getPtr());
		
		// Rendu
		glDrawArrays(GL_TRIANGLES, 0, 24);
		
		// Désactivation des tableaux
		glDisableVertexAttribArray(1);
		glDisableVertexAttribArray(0);
		
	// Désactivation du shader
	glUseProgram(0);
}