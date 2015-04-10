#include "modeleOBJ.h"
#include <fstream>
#include <iostream>

ModeleOBJ::ModeleOBJ(void)
{
}


ModeleOBJ::~ModeleOBJ(void)
{

}

ModeleOBJ::ModeleOBJ(const string& cheminOBJ)
{
	vector<ofVec3f> vertices;
	vector<ofVec3f> normals;
	vector<ofVec2f> texCoords;
	chargerOBJ(cheminOBJ.c_str(), vertices, texCoords, normals);

	mesh = Mesh(vertices, vector<ofVec3f>(), texCoords, normals, vector<GLuint>(), vertices.size());

}

void ModeleOBJ::afficher()
{
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	mesh.dessiner();

	glDisable(GL_CULL_FACE);
}

bool ModeleOBJ::chargerOBJ(const char * cheminFichier, vector<ofVec3f>& sommets, vector<ofVec2f>& texCoord, std::vector<ofVec3f>& normales)
{
	vector<unsigned int> vertexIndices, uvIndices, normalIndices;
	vector<ofVec3f> tempVertices;
	vector<ofVec2f> tempTexCoords;
	vector<ofVec3f> tempNormals;

	ifstream fichier(cheminFichier);
	if(!fichier)
	{
		cout << "Fichier: " << cheminFichier << " impossible a ouvrir!" << endl;
		return false;
	}

	string ligne; 
	while(getline(fichier, ligne))
	{
		string enTete = ligne.substr(0,2);
		istringstream s(ligne.substr(2));
		if(enTete == "v ")
		{
			ofVec3f vertex;
			s >> vertex.x;
			s >> vertex.y;
			s >> vertex.z;
			tempVertices.push_back(vertex);
		}
		else if(enTete == "vt") 
		{
			ofVec2f texCoord;
			s >> texCoord.x;
			s >> texCoord.y;
			tempTexCoords.push_back(texCoord);
		}
		else if(enTete == "vn")
		{
			ofVec3f normal;
			s >> normal.x;
			s >> normal.y;
			s >> normal.z;
			tempNormals.push_back(normal);
		}
		else if(enTete == "f ")
		{
			GLuint vertexIndex[3], texCoordIndex[3], normalIndex[3];
			s >> vertexIndex[0];
			s.ignore();
			s >> texCoordIndex[0];
			s.ignore();
			s >> normalIndex[0];
			s.ignore();
			s >> vertexIndex[1];
			s.ignore();
			s >> texCoordIndex[1];
			s.ignore();
			s >> normalIndex[1];
			s.ignore();
			s >> vertexIndex[2];
			s.ignore();
			s >> texCoordIndex[2];
			s.ignore();
			s >> normalIndex[2];
			s.ignore();

			vertexIndices.push_back(vertexIndex[0]);
			vertexIndices.push_back(vertexIndex[1]);
			vertexIndices.push_back(vertexIndex[2]);
			uvIndices.push_back(texCoordIndex[0]);
			uvIndices.push_back(texCoordIndex[1]);
			uvIndices.push_back(texCoordIndex[2]);
			normalIndices.push_back(normalIndex[0]);
			normalIndices.push_back(normalIndex[1]);
			normalIndices.push_back(normalIndex[2]);
		}
		else if(ligne[0] == '#') { /* ignoré cette ligne */ }
		else { /* ignoré cette ligne */ }
	}
	
	for(int i = 0; i < vertexIndices.size(); i++)
	{
		sommets.push_back(tempVertices[vertexIndices[i] - 1]);
		normales.push_back(tempNormals[normalIndices[i] - 1]);
		texCoord.push_back(tempTexCoords[uvIndices[i] - 1]);
	}
	return true;
}