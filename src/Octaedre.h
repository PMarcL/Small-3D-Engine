#ifndef DEF_OCTAEDRE
#define DEF_OCTAEDRE

// Includes
#include "Shader.h"
#include "ofMain.h"

//Otaèdre régulier
class Octaedre
{
    public:
		Octaedre(){}
		Octaedre(float taille, Shader* shader);
		~Octaedre();
		void afficher(ofMatrix4x4 &projection, ofMatrix4x4 &model, ofMatrix4x4 &view);
    private:
		Shader* m_shader;
		float m_vertices[72];
		float m_couleurs[72];
};

#endif