#include "modeleOBJ.h"
#include <fstream>
#include <iostream>

bool chargerOBJ(const char * cheminFichier, vector<ofVec3f>& outVertices, vector<GLuint>& elements, std::vector<ofVec3f>& outNormals);

ModeleOBJ::ModeleOBJ(void)
{
}


ModeleOBJ::~ModeleOBJ(void)
{

}

ModeleOBJ::ModeleOBJ(const string& cheminOBJ)
{
	shader = new Shader("Shaders/modelShader.vert", "Shaders/modelShader.frag");
	shader->charger();
	chargerOBJ(cheminOBJ.c_str(), vertices, elements, normals);
	for(int i = 0; i < vertices.size(); i++)
	{
		colors.push_back(ofVec3f(1.0, 0.0, 1.0));
	}
	glGenBuffers(1, &elementBuffer);

	mesh = Mesh(vertices, colors, normals, elements, vertices.size());

	vertices.clear();
	elements.clear();
	normals.clear();
}

void ModeleOBJ::afficher(ofMatrix4x4 projection, ofMatrix4x4 model, ofMatrix4x4 view, const ofVec3f& lightPos)
{
	glUseProgram(shader->getProgramID());

	glUniformMatrix4fv(glGetUniformLocation(shader->getProgramID(), "projection"), 1, GL_FALSE, projection.getPtr());
	glUniformMatrix4fv(glGetUniformLocation(shader->getProgramID(), "model"), 1, GL_FALSE, model.getPtr());
	glUniformMatrix4fv(glGetUniformLocation(shader->getProgramID(), "view"), 1, GL_FALSE, view.getPtr());
	glUniform3f(glGetUniformLocation(shader->getProgramID(), "lightPos"), lightPos.x, lightPos.y, lightPos.z);
	glUniform3f(glGetUniformLocation(shader->getProgramID(), "lightColor"), 0.8, 0.8, 1);
	glUniform3f(glGetUniformLocation(shader->getProgramID(), "objectColor"), 1, 0.1, 0.31);

	mesh.dessiner();

	glUseProgram(0);
}

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
		else if(ligne[0] == '#') { /* ignoré cette ligne */ }
		else { /* ignoré cette ligne */ }
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
}