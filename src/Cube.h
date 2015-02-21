#ifndef DEF_CUBE
#define DEF_CUBE

// Includes
#include "Shader.h"
#include "ofMain.h"


// Classe Cube
class Cube
{
    public:
		Cube(){}
		Cube(float taille, Shader* shader);
		~Cube();
		void afficher(ofMatrix4x4 &projection, ofMatrix4x4 &model, ofMatrix4x4 &view);
    private:
		Shader* m_shader;
		float m_vertices[108];
		float m_couleurs[108];
};

#endif