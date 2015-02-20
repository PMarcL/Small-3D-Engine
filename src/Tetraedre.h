#ifndef DEF_TETRAEDRE
#define DEF_TETRAEDRE

// Includes
#include "Shader.h"
#include "ofMain.h"

//Tétraèdre régulier
class Tetraedre
{
    public:
		Tetraedre(){}
		Tetraedre(float taille, Shader* shader);
		~Tetraedre();
		void afficher(ofMatrix4x4 &projection, ofMatrix4x4 &modelview);
    private:
		Shader* m_shader;
		float m_vertices[36];
		float m_couleurs[36];
};

#endif