#ifndef DEF_GENERATEURMESH
#define DEF_GENERATEURMESH

#include "ofMain.h"
#include "PrimitivesData.h"
#include "Mesh.h"

class GenerateurMesh
{
public:
	GenerateurMesh(void){};
	~GenerateurMesh(void){};

	static Mesh genererPrimitive(PRIMITIVES primitive, int taille);
	static Mesh genererObj(const string& cheminOBJ);
private:
	static bool chargerObj(const char * cheminFichier, vector<ofVec3f>& sommets, vector<ofVec2f>& texCoord, std::vector<ofVec3f>& normales);
};

#endif