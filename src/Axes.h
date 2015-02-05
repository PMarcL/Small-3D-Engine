#ifndef DEF_AXES
#define DEF_AXES

// Includes
#include "ofMain.h"
#include "Shader.h"

// Classe Axes
class Axes
{
    public:
		Axes();
		Axes(float taille, string const vertexShader, string const fragmentShader);
		~Axes();
		void afficher(ofMatrix4x4 &projection, ofMatrix4x4 &modelview);
    private:
		Shader m_shader;
		float m_vertices[18];
		float m_couleurs[18];
};

#endif