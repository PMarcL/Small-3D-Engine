#include "Mesh.h"


Mesh::Mesh(void)
{
}

Mesh::Mesh(const vector<GLfloat>& positions, const vector<GLfloat>& couleurs, 
		   const vector<GLfloat>& texCoords, const vector<GLfloat>& normals,
		   const vector<GLuint>& indices, int nbSommets)
{
	utiliserIndices = false;
	ajouterVertices(nbSommets);
	ajouterPositions( positions);
	
	if(couleurs.size() > 0) 
		ajouterCouleurs(couleurs);
	if(texCoords.size() > 0) 
		ajouterTexCoords(texCoords);
	if(normals.size() > 0)
		ajouterNormals(normals);
	if(indices.size() > 0)
	{
		ajouterIndices(indices);
		utiliserIndices = true;
	}
	if(!normals.empty())
		ajouterTangentes();

	genererBuffer();
}

Mesh::Mesh(const vector<ofVec3f>& positions, const vector<ofVec3f>& colors,
		   const vector<ofVec3f>& normals, const vector<GLuint>& indices, int nbSommets)
{
	utiliserIndices = false;
	ajouterVertices(nbSommets);
	ajouterPositions(positions);

	if(colors.size() > 0)
		ajouterCouleurs(colors);
	if(normals.size() > 0)
		ajouterNormals(normals);
	if(indices.size() > 0)
	{
		ajouterIndices(indices);
		utiliserIndices = true;
	}

	if(!normals.empty())
		ajouterTangentes();

	genererBuffer();
}

Mesh::Mesh(const vector<ofVec3f>& positions, const vector<ofVec3f>& colors, const vector<GLfloat>& texCoords,
		   const vector<ofVec3f>& normals, const vector<GLuint>& indices, int nbSommets)
{
	utiliserIndices = false;
	ajouterVertices(nbSommets);
	ajouterPositions(positions);

	if(colors.size() > 0)
		ajouterCouleurs(colors);
	if(texCoords.size() > 0) 
		ajouterTexCoords(texCoords);
	if(normals.size() > 0)
		ajouterNormals(normals);
	if(indices.size() > 0)
	{
		ajouterIndices(indices);
		utiliserIndices = true;
	}

	if(!normals.empty())
		ajouterTangentes();

	genererBuffer();
}

Mesh::Mesh(const vector<ofVec3f>& positions, const vector<ofVec3f>& colors, const vector<ofVec2f>& texCoords,
		   const vector<ofVec3f>& normals, const vector<GLuint>& indices, int nbSommets)
{
	utiliserIndices = false;
	ajouterVertices(nbSommets);
	ajouterPositions(positions);

	if(colors.size() > 0)
		ajouterCouleurs(colors);
	if(texCoords.size() > 0) 
		ajouterTexCoords(texCoords);
	if(normals.size() > 0)
		ajouterNormals(normals);
	if(indices.size() > 0)
	{
		ajouterIndices(indices);
		utiliserIndices = true;
	}

	if(!normals.empty())
		ajouterTangentes();

	genererBuffer();
}

void Mesh::ajouterVertices(int nbVertices)
{
	for(int i = 0; i < nbVertices; i++)
	{
		vertices.push_back(Vertex());
	}
}

void Mesh::ajouterPositions(const vector<GLfloat>& positions)
{
	vector<GLfloat>::const_iterator it = positions.begin();
	for(int i = 0; i < vertices.size(); i++)
	{
		vertices[i].x = (*it);
		it++;
		vertices[i].y = (*it);
		it++;
		vertices[i].z = (*it);
		it++;
	}
}

void Mesh::ajouterCouleurs(const vector<GLfloat>& couleurs)
{
	vector<GLfloat>::const_iterator it = couleurs.begin();
	for(int i = 0; i < vertices.size(); i++)
	{
		vertices[i].colorR = (*it);
		it++;
		vertices[i].colorG = (*it);
		it++;
		vertices[i].colorB = (*it);
		it++;
	}
}

void Mesh::ajouterNormals(const vector<GLfloat>& normals)
{
	vector<GLfloat>::const_iterator it = normals.begin();
	for(int i = 0; i < vertices.size(); i++)
	{
		vertices[i].normalX = (*it);
		it++;
		vertices[i].normalY = (*it);
		it++;
		vertices[i].normalZ = (*it);
		it++;
	}
}

void Mesh::ajouterTexCoords(const vector<GLfloat>& texCoords)
{
	vector<GLfloat>::const_iterator it = texCoords.begin();
	for(int i = 0; i < vertices.size(); i++)
	{
		vertices[i].texCoordX = (*it);
		it++;
		vertices[i].texCoordY = (*it);
		it++;
	}
}

void Mesh::ajouterIndices(const vector<GLuint>& indices)
{
	vector<GLuint>::const_iterator it = indices.begin();
	while(it != indices.end())
	{
		this->indices.push_back(*it);
		it++;
	}
}

void Mesh::utilisationDesIndices(bool utiliser)
{
	utiliserIndices = utiliser;
}

void Mesh::ajouterPositions(const vector<ofVec3f>& positions)
{
	vector<ofVec3f>::const_iterator it = positions.begin();
	for(int i = 0; i < vertices.size(); i++)
	{
		vertices[i].x = it->x;
		vertices[i].y = it->y;
		vertices[i].z = it->z;
		it++;
	}
}

void Mesh::ajouterCouleurs(const vector<ofVec3f>& colors)
{
	vector<ofVec3f>::const_iterator it = colors.begin();
	for(int i = 0; i < vertices.size(); i++)
	{
		vertices[i].colorR = it->x;
		vertices[i].colorG = it->y;
		vertices[i].colorB = it->z;
		it++;
	}
}

void Mesh::ajouterTexCoords(const vector<ofVec2f>& texCoords)
{
	vector<ofVec2f>::const_iterator it = texCoords.begin();
	for(int i = 0; i < vertices.size(); i++)
	{
		vertices[i].texCoordX = it->x;
		vertices[i].texCoordY = it->y;
		it++;
	}
}

void Mesh::ajouterNormals(const vector<ofVec3f>& normals)
{
	vector<ofVec3f>::const_iterator it = normals.begin();
	for(int i = 0; i < vertices.size(); i++)
	{
		vertices[i].normalX = it->x;
		vertices[i].normalY = it->y;
		vertices[i].normalZ = it->z;
		it++;
	}
}

void Mesh::ajouterTangentes() 
{
	if(!indices.empty())
		ajouterTangentesAvecIndices();
	else
		ajouterTangentesAvecListeSommets();
}

void Mesh::ajouterTangentesAvecListeSommets()
{
	for(int i = 0; i < vertices.size(); i += 3)
	{
		Vertex& v0 = vertices[i];
		Vertex& v1 = vertices[i + 1];
		Vertex& v2 = vertices[i + 2];

		ofVec3f tangente = calculerTangentePourSommets(v0, v1, v2);

		ajouterTangenteAuSommet(v0, tangente);
		ajouterTangenteAuSommet(v1, tangente);
		ajouterTangenteAuSommet(v2, tangente);
	}
}

void Mesh::ajouterTangentesAvecIndices()
{
	for(int i = 0; i < indices.size(); i += 3)
	{
		Vertex& v0 = vertices[indices[i]];
		Vertex& v1 = vertices[indices[i + 1]];
		Vertex& v2 = vertices[indices[i + 2]];

		ofVec3f tangente = calculerTangentePourSommets(v0, v1, v2);

		ajouterTangenteAuSommet(v0, tangente);
		ajouterTangenteAuSommet(v1, tangente);
		ajouterTangenteAuSommet(v2, tangente);
	}
}

ofVec3f Mesh::calculerTangentePourSommets(Vertex& v0, Vertex& v1, Vertex& v2)
{
	ofVec3f arete1 = ofVec3f(v1.x, v1.y, v1.z) - ofVec3f(v0.x, v0.y, v0.z);
	ofVec3f arete2 = ofVec3f(v2.x, v2.y, v2.z) - ofVec3f(v0.x, v0.y, v0.z);

	float deltaU1 = v1.texCoordX - v0.texCoordX;
	float deltaV1 = v1.texCoordY - v0.texCoordY;
	float deltaU2 = v2.texCoordX - v0.texCoordX;
	float deltaV2 = v2.texCoordY - v0.texCoordY;

	float f = 1.0 / (deltaU1 * deltaV2 - deltaU2 * deltaV1);

	ofVec3f tangente;

	tangente.x = f * (deltaV2 * arete1.x - deltaV1 * arete2.x);
	tangente.y = f * (deltaV2 * arete1.y - deltaV1 * arete2.y);
	tangente.z = f * (deltaV2 * arete1.z - deltaV1 * arete2.z);

	return tangente.normalize();
}

void Mesh::ajouterTangenteAuSommet(Vertex& v, ofVec3f& tangente)
{
	v.tangenteX = tangente.x;
	v.tangenteY = tangente.y;
	v.tangenteZ = tangente.z;
}


void Mesh::genererBuffer()
{
	glGenBuffers(1, &elementArrayBuffer);
	glGenBuffers(1, &vertexBufferObject);
	glGenVertexArrays(1, &vertexArrayObject);

	glBindVertexArray(vertexArrayObject);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices[0]) * vertices.size(), vertices.data(), GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementArrayBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices[0]) * indices.size(), indices.data(), GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, NB_VERTEX_ATTRIB * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, NB_VERTEX_ATTRIB * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, NB_VERTEX_ATTRIB * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, NB_VERTEX_ATTRIB * sizeof(GLfloat), (GLvoid*)(8 * sizeof(GLfloat)));
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, NB_VERTEX_ATTRIB * sizeof(GLfloat), (GLvoid*)(11 * sizeof(GLfloat)));
	glEnableVertexAttribArray(4);
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Mesh::dessiner()
{
	glBindVertexArray(vertexArrayObject);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	if (utiliserIndices) {
		glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
	}
	else {
		glDrawArrays(GL_TRIANGLES, 0, vertices.size());
	}

	glBindVertexArray(0);
}
