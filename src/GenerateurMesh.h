#pragma once

#include "ofMain.h"
#include "PrimitivesData.h"
#include "Mesh.h"

class GenerateurMesh
{
public:
	GenerateurMesh(void){};
	GenerateurMesh(list<PRIMITIVES> primitives, int taille);
	~GenerateurMesh(void);

	static Mesh genererPrimitive(PRIMITIVES primitive, int taille);
	static Mesh genererObj(const string& cheminOBJ);
	Mesh* selectionnerPrimitive(PRIMITIVES primitive);
	Mesh* ajouterPrimitive(PRIMITIVES primitive, int taille);
private:
	struct MeshPrimitive{
		Mesh* mesh;
		PRIMITIVES primitve;
	};

	static bool chargerObj(const char * cheminFichier, vector<ofVec3f>& sommets, vector<ofVec2f>& texCoord, std::vector<ofVec3f>& normales);
	list<MeshPrimitive> listePrimitives;
};