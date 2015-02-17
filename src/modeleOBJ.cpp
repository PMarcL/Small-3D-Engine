#include "modeleOBJ.h"
#include <fstream>
#include <iostream>

bool chargerOBJ(const char * cheminFichier, vector<ofVec3f>& outVertices, vector<GLushort>& elements, std::vector<ofVec3f>& outNormals);

ModeleOBJ::ModeleOBJ(void)
{
}


ModeleOBJ::~ModeleOBJ(void)
{
	//delete shader;
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
}

void ModeleOBJ::afficher(ofMatrix4x4 projection, ofMatrix4x4 modelView, const ofVec3f& lightPos)
{
	glUseProgram(shader->getProgramID());
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, vertices.data());
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, normals.data());
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elements[0]) * elements.size(), elements.data(), GL_STATIC_DRAW);
	glUniformMatrix4fv(glGetUniformLocation(shader->getProgramID(), "projection"), 1, GL_FALSE, projection.getPtr());
	glUniformMatrix4fv(glGetUniformLocation(shader->getProgramID(), "modelview"), 1, GL_FALSE, modelView.getPtr());
	glUniform3f(glGetUniformLocation(shader->getProgramID(), "lightPos"), lightPos.x, lightPos.y, lightPos.z);
	glUniform3f(glGetUniformLocation(shader->getProgramID(), "lightColor"), 0.8, 0.8, 1);
	glUniform3f(glGetUniformLocation(shader->getProgramID(), "objectColor"), 1, 0.1, 0.31);

	glDrawElements(GL_TRIANGLES, elements.size(), GL_UNSIGNED_SHORT, 0);

	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(0);

	glUseProgram(0);
}

bool chargerOBJ(const char * cheminFichier, vector<ofVec3f>& outVertices, vector<GLushort>& elements, std::vector<ofVec3f>& outNormals)
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
		string header = ligne.substr(0,2);
		if(header == "v ")
		{
			istringstream s(ligne.substr(2));
			ofVec3f vertex;
			s >> vertex.x;
			s >> vertex.y;
			s >> vertex.z;
			outVertices.push_back(vertex);
		}
		else if(header == "f ")
		{
			istringstream s(ligne.substr(2));
			GLushort a, b, c;
			s >> a; s >> b, s >> c;
			a--; b--; c--;
			elements.push_back(a); elements.push_back(b); elements.push_back(c);
		}
		else if(ligne[0] == '#') { /* ignoré cette ligne */ }
		else { /* ignoré cette ligne */ }
	}
	outNormals.resize(outVertices.size(), ofVec3f(0.0, 0.0, 0.0));
	for (int i = 0; i < elements.size(); i+=3) {
		GLushort ia = elements[i];
		GLushort ib = elements[i+1];
		GLushort ic = elements[i+2];
		ofVec3f normal = ofVec3f(outVertices[ib]) - ofVec3f(outVertices[ia]);
		normal.cross(ofVec3f(outVertices[ic]) - ofVec3f(outVertices[ia]));
		normal.normalize();
		outNormals[ia] = outNormals[ib] = outNormals[ic] = normal;
  }
}