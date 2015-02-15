#include "Plane.h"

Plane::Plane(int size, int numColumn, int numRow)
	:nbColonnes(numColumn), nbLignes(numRow), taille(size), useTexture(false)
{
	ratioTextureParCarre = 1.0;
	glGenBuffers(1, &elemBuffer);
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

void Plane::afficher()
{
	chargerSommets();
	chargerCouleurs();
	chargerElementBuffer();
	if(useTexture)
	{
		chargerTexCoord();
		chargerTextures();
		glPolygonMode(GL_FRONT, GL_FILL);
		glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
	}
	else
	{
		glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
	}
	libererRessources();
}

void Plane::libererRessources()
{
	glDisableVertexAttribArray(2);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Plane::chargerElementBuffer()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elemBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices[0]) * indices.size(), indices.data(), GL_STATIC_DRAW);
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

void Plane::chargerTextures()
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textures[0]);
	
}

void Plane::ajouterTexture(const string& texPath)
{
	ofImage image;
	image.loadImage(texPath);
	
	textures.push_back(GLuint());
	glGenTextures(1, &textures[textures.size() - 1]);
	glBindTexture(GL_TEXTURE_2D, textures[textures.size() - 1]);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image.width, image.height, 0, GL_RGB, GL_UNSIGNED_BYTE, image.getPixels());
	glGenerateMipmap(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, 0);
	image.clear();
}

void Plane::utiliserTextures(bool utiliser)
{
	useTexture = utiliser;
	ajouterTexCoordPourChaqueSommet();
}

void Plane::ajouterTexCoordPourChaqueSommet()
{
	for(int i = 0; i < nbColonnes + 1; i++)
	{
		for(int j = 0; j < nbLignes + 1; j++)
		{
			texCoords.push_back(j * ratioTextureParCarre);
			texCoords.push_back(i * ratioTextureParCarre);
		}
	}
}

void Plane::genereHauteursAleatoire(float minHeight, float maxHeight)
{
	for(int i = 1; i < vertices.size(); i += 3)
	{
		vertices[i] = ofRandom(minHeight, maxHeight);
	}
}

void Plane::setRatioTextureParCarre(float ratio)
{
	ratioTextureParCarre = ratio;
	texCoords.clear();
	ajouterTexCoordPourChaqueSommet();
}

Plane::~Plane(void)
{
}
