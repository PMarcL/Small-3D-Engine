#pragma once

// Includes
#include "ofMain.h"
#include "Shader.h"

// Classe Axes
class Axes
{
    public:
		Axes();
		Axes(float taille, Shader* shader);
		~Axes();
		void afficher(ofMatrix4x4 &projection, ofMatrix4x4 &model, ofMatrix4x4& view);
    private:
		Shader* m_shader;
		float m_vertices[18];
		float m_couleurs[18];
};