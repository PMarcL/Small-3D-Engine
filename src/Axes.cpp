#include "Axes.h"

Axes::Axes(){}

Axes::Axes(float taille, Shader* shader) : m_shader(shader)
{
	// Vertices temporaires
	float verticesTmp[] = {0.0, 0.0, 0.0,		//X
							taille, 0.0, 0.0,

							0.0, 0.0, 0.0,		//Y
							0.0, taille, 0.0,

							0.0, 0.0, 0.0,		//Z
							0.0, 0.0, taille};
	
	// Couleurs temporaires
	float couleursTmp[] = {255.0, 0.0, 0.0,		//X
							255.0, 0.0, 0.0,

							0.0, 255.0, 0.0,	//Y
							0.0, 255.0, 0.0,

							0.0, 0.0, 255.0,	//Z
							0.0, 0.0, 255.0};

	// Copie des valeurs dans les tableaux finaux
	for(int i(0); i < 18; i++)
	{
		m_vertices[i] = verticesTmp[i];
		m_couleurs[i] = couleursTmp[i];
	}
}

Axes::~Axes()
{

}

void Axes::afficher(ofMatrix4x4 &projection, ofMatrix4x4 &modelview)
{
	//Activation du shader
	glUseProgram(m_shader->getProgramID());

		//Axes
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, m_vertices);
		glEnableVertexAttribArray(0);

		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, m_couleurs);
		glEnableVertexAttribArray(1);

		// Envoi des matrices
		glUniformMatrix4fv(glGetUniformLocation(m_shader->getProgramID(), "projection"), 1, GL_FALSE, projection.getPtr());
		glUniformMatrix4fv(glGetUniformLocation(m_shader->getProgramID(), "modelview"), 1, GL_FALSE, modelview.getPtr());

		// Rendu
		glDrawArrays(GL_LINES, 0, 6);

		// Désactivation des tableaux
		glDisableVertexAttribArray(1);
		glDisableVertexAttribArray(0);

	// Désactivation du shader
	glUseProgram(0);
}