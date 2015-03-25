#include "PrimitivesData.h"
#include "ofMain.h"

void ajusterTailleSommets(vector<float>& sommets, float taille);

vector<float> getSommetsPourPrimitive(PRIMITIVES primitive, int taille) {
	vector<float> sommets;
	switch(primitive) {
	case(CUBE):
		sommets = vector<float>(CUBE_SOMMETS, CUBE_SOMMETS + sizeof(CUBE_SOMMETS) / sizeof(CUBE_SOMMETS[0]));
		break;
	case(OCTAEDRE):
		sommets = vector<float>(OCTAEDRE_SOMMETS, OCTAEDRE_SOMMETS + sizeof(OCTAEDRE_SOMMETS) / sizeof(OCTAEDRE_SOMMETS[0]));
		break;
	case(TETRAEDRE):
		sommets = vector<float>(TETRAEDRE_SOMMETS, TETRAEDRE_SOMMETS + sizeof(TETRAEDRE_SOMMETS) / sizeof(TETRAEDRE_SOMMETS[0]));
		break;
	default:
		break;
	}

	ajusterTailleSommets(sommets, taille*0.5);
	return sommets;
}

void ajusterTailleSommets(vector<float>& sommets, float taille) {
	for(int i = 0; i < sommets.size(); i++)
		sommets[i] *= taille; 
}

vector<float> getNormals(vector<float> sommets) {
	vector<float> normals;
	for(int i = 0; i < sommets.size(); i += 9) {
		ofVec3f sommet1(sommets[i], sommets[i+1], sommets[i+2]);
		ofVec3f sommet2(sommets[i+3], sommets[i+4], sommets[i+5]);
		ofVec3f sommet3(sommets[i+6], sommets[i+7], sommets[i+8]);
		
		ofVec3f normal = sommet2 - sommet1;
		normal.cross(sommet3 - sommet1);
		normal.normalize();
		
		normals.push_back(normal.x); normals.push_back(normal.y); normals.push_back(normal.z);
		normals.push_back(normal.x); normals.push_back(normal.y); normals.push_back(normal.z);
		normals.push_back(normal.x); normals.push_back(normal.y); normals.push_back(normal.z);
	}
	return normals;
}

vector<float> getTexCoordPourPrimitive(PRIMITIVES primitive) {
	switch(primitive) {
	case(CUBE):
		return vector<float>(CUBE_TEXCOORD, CUBE_TEXCOORD + sizeof(CUBE_TEXCOORD) / sizeof(CUBE_TEXCOORD[0]));
		break;
	case(OCTAEDRE):
		return vector<float>(OCTAEDRE_TEXCOORDS, OCTAEDRE_TEXCOORDS + sizeof(OCTAEDRE_TEXCOORDS) / sizeof(OCTAEDRE_TEXCOORDS[0]));
		break;
	case(TETRAEDRE):
		return vector<float>(TETRAEDRE_TEXCOORD, TETRAEDRE_TEXCOORD + sizeof(TETRAEDRE_TEXCOORD) / sizeof(TETRAEDRE_TEXCOORD[0]));
		break;
	}
}