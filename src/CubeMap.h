#ifndef DEF_CUBEMAP
#define DEF_CUBEMAP

// Includes
#include "Shader.h"
#include "ofMain.h"
#include "Texture.h"


class CubeMap
{
    public:
		CubeMap(){};
		CubeMap(float taille, Shader* shader, string texXN, string texXP, string texYN, string texYP, string texZN, string texZP);
		~CubeMap();
		void afficher(ofMatrix4x4 &projection, ofMatrix4x4 &model, ofMatrix4x4 &view);
		CubeMap& operator=(CubeMap const &cubeMapeACopier);

		//Propriétés
		Shader* getShader() const;
		int getTaille() const;
				
		Texture tex[6];
    private:
		Shader* m_shader;
		
		int m_taille;
		float m_vertices[108];
		float m_coordTexture[72];
};

#endif