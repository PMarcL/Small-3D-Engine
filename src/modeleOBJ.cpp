#include "modeleOBJ.h"
#include <fstream>
#include <iostream>

bool chargerOBJ(const char * cheminFichier, vector<ofVec3f>& sommets, vector<ofVec2f>& texCoord, std::vector<ofVec3f>& normales);

ModeleOBJ::ModeleOBJ(void)
{
}


ModeleOBJ::~ModeleOBJ(void)
{

}

ModeleOBJ::ModeleOBJ(const string& cheminOBJ)
{
	shader = new Shader("Shaders/shaderTextureLight.vert", "Shaders/shaderTextureLight.frag");
	shader->charger();
	vector<ofVec3f> vertices;
	vector<ofVec3f> normals;
	vector<ofVec2f> texCoords;
	chargerOBJ(cheminOBJ.c_str(), vertices, texCoords, normals);

	mesh = Mesh(vertices, vector<ofVec3f>(), texCoords, normals, vector<GLuint>(), vertices.size());

}

void ModeleOBJ::afficher(ofMatrix4x4 projection, ofMatrix4x4 model, ofMatrix4x4 view,
						 const ofVec3f& directionLumiere, const ofVec3f& couleurLumiere, const float& intensiteLumiere)
{
	glUseProgram(shader->getProgramID());

	glUniform1f(glGetUniformLocation(shader->getProgramID(), "intensiteLumiere"), intensiteLumiere);
	glUniform3f(glGetUniformLocation(shader->getProgramID(), "lumiereAmbiante"), 0.0, 0.0, 0.8);
	glUniformMatrix4fv(glGetUniformLocation(shader->getProgramID(), "projection"), 1, GL_FALSE, projection.getPtr());
	glUniformMatrix4fv(glGetUniformLocation(shader->getProgramID(), "model"), 1, GL_FALSE, model.getPtr());
	glUniformMatrix4fv(glGetUniformLocation(shader->getProgramID(), "view"), 1, GL_FALSE, view.getPtr());
	glUniform3fv(glGetUniformLocation(shader->getProgramID(), "positionLumiere"), 1, directionLumiere.getPtr());
	glUniform3fv(glGetUniformLocation(shader->getProgramID(), "couleurLumiere"), 1, couleurLumiere.getPtr());
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	mesh.dessiner();

	glDisable(GL_CULL_FACE);
	glBindTexture(GL_TEXTURE_2D, 0);
	glUseProgram(0);
}


bool chargerOBJ(const char * cheminFichier, vector<ofVec3f>& sommets, vector<ofVec2f>& texCoord, std::vector<ofVec3f>& normales)
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
}


/*
bool chargerOBJ(const char * cheminFichier, vector<ofVec3f>& sommets, vector<GLuint>& indices, std::vector<ofVec3f>& normales)
{
	vector<unsigned int> vertexIndices, uvIndices, normalIndices;

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
		if(enTete == "v ")
		{
			istringstream s(ligne.substr(2));
			ofVec3f vertex;
			s >> vertex.x;
			s >> vertex.y;
			s >> vertex.z;
			sommets.push_back(vertex);
		}
		else if(enTete == "f ")
		{
			istringstream s(ligne.substr(2));
			GLushort a, b, c;
			s >> a; s >> b, s >> c;
			a--; b--; c--;
			indices.push_back(a); indices.push_back(b); indices.push_back(c);
		}
		else if(ligne[0] == '#') {  }
		else {  }
	}
	normales.resize(sommets.size(), ofVec3f(0.0, 0.0, 0.0));
	for (int i = 0; i < indices.size(); i+=3) {
		GLuint ia = indices[i];
		GLuint ib = indices[i+1];
		GLuint ic = indices[i+2];
		ofVec3f normal = ofVec3f(sommets[ib]) - ofVec3f(sommets[ia]);
		normal.cross(ofVec3f(sommets[ic]) - ofVec3f(sommets[ia]));
		normal.normalize();
		normales[ia] = normales[ib] = normales[ic] = normal;
  }
}*/