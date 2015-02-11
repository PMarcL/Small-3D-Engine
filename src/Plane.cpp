#include "Plane.h"


Plane::Plane(int size, Shader* shader, int numColumn, int numRow)
	: shader(shader), texture(0), nbColonnes(numColumn), nbLignes(numRow), taille(size), useTexture(false)
{
	int halfSize = taille /2;

	int columnSize = taille / nbColonnes;
	int rowSize = taille / nbLignes;
	for(int j = 0; j < nbColonnes + 1; j++)
	{
		int z = j * columnSize;
		z = ofMap(z, 0, taille, -halfSize, halfSize);
		for(int i = 0; i < nbLignes + 1; i++)
		{
			int x = i * rowSize;
			x = ofMap(x, 0, taille, -halfSize, halfSize);
			vertices.push_back(x); vertices.push_back(0); vertices.push_back(z);
		}
	}

	this->ajouterIndices();
}

void Plane::ajouterIndices()
{
	for(int i = 0; i < nbColonnes; i++)
	{
		int relIndice = i * (nbLignes + 1);
		for(int j = 0; j < nbLignes; j++)
		{
			colors.push_back(1.0); colors.push_back(0.0); colors.push_back(0.0);
			colors.push_back(0.0); colors.push_back(1.0); colors.push_back(0.0);
			colors.push_back(0.0); colors.push_back(0.0); colors.push_back(1.0);
			colors.push_back(1.0); colors.push_back(0.0); colors.push_back(1.0);
			indices.push_back(j + relIndice); indices.push_back(j + relIndice + 1); indices.push_back(j + relIndice + nbLignes + 1); 
			indices.push_back(j + relIndice + nbLignes + 1); indices.push_back(j + relIndice + 1); indices.push_back(j + relIndice + nbLignes + 2);
		}
	}
}

void Plane::afficher(ofMatrix4x4 projection, ofMatrix4x4 modelView)
{
	if(useTexture)
		{
			Shader texShade("Shaders/shaderTexture.vert", "Shaders/shaderTexture.frag");
			texShade.charger();
			glUseProgram(texShade.getProgramID());

			chargerSommets();
			chargerCouleurs();
			chargerElementBuffer();
			chargerMatrices(projection, modelView, &texShade);
			chargerTexCoord();

			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, texture);
			glUniform1i(glGetUniformLocation(texShade.getProgramID(), "ourTexture1"), 0);

			glPolygonMode(GL_FRONT, GL_FILL);
			glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);

			libererRessources();
		}
	else
	{
		glUseProgram(shader->getProgramID());
		chargerSommets();
		chargerCouleurs();
		chargerElementBuffer();
		chargerMatrices(projection, modelView, shader);
		glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
		libererRessources();
	}
}

void Plane::libererRessources()
{
	glDisableVertexAttribArray(2);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(0);
	glUseProgram(0);
}

void Plane::chargerElementBuffer()
{
	GLuint buffer;
	glGenBuffers(1, &buffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices[0]) * indices.size(), indices.data(), GL_STATIC_DRAW);
}

void Plane::chargerMatrices(ofMatrix4x4 projection, ofMatrix4x4 modelView, Shader* sh)
{
	glUniformMatrix4fv(glGetUniformLocation(sh->getProgramID(), "projection"), 1, GL_FALSE, projection.getPtr());
	glUniformMatrix4fv(glGetUniformLocation(sh->getProgramID(), "modelview"), 1, GL_FALSE, modelView.getPtr());
}

void Plane::chargerSommets()
{
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, vertices.data());
	glEnableVertexAttribArray(0);
}

void Plane::chargerCouleurs()
{
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, colors.data());
	glEnableVertexAttribArray(1);
}

void Plane::chargerTexCoord()
{
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, texCoords.data());
	glEnableVertexAttribArray(2);
}

void Plane::addTexture(const string& texPath)
{
	ofImage image;
	image.loadImage(texPath);
	image.draw(0.0, 0.0);

	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image.width, image.height, 0, GL_RGB, GL_UNSIGNED_BYTE, image.getPixels());
	glGenerateMipmap(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, 0);

	useTexture = true;
	texCoords.push_back(1.0f); texCoords.push_back(1.0f);
	texCoords.push_back(1.0f); texCoords.push_back(0.0f);
	texCoords.push_back(0.0f); texCoords.push_back(0.0f);
	texCoords.push_back(0.0f); texCoords.push_back(1.0f);
}

void Plane::genereHauteursAleatoire()
{
	for(int i = 1; i < vertices.size(); i += 3)
	{
		vertices.assign(i + 1, ofRandom(30));
	}
}

Plane::~Plane(void)
{
}
