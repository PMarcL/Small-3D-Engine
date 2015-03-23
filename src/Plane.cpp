#include "Plane.h"

Plane::Plane(int size, int numColumn, int numRow)
	:nbColonnes(numColumn), nbLignes(numRow), taille(size), useTexture(false)
{
	ratioTextureParCarre = 1.0;
	this->ajouterSommets();
	this->ajouterIndices();
	this->ajouterCouleurs();
	this->ajouterTexCoordPourChaqueSommet();
	this->calculerNormals();
	this->initialiserMesh();
}

void Plane::ajouterSommets()
{
	int halfSize = taille / 2;
	int columnSize = taille / nbColonnes;
	int rowSize = taille / nbLignes;

	for(int j = 0; j < nbColonnes + 1; j++)
	{
		int x = j * columnSize;
		x = ofMap(x, 0, taille, -halfSize, halfSize);
		for(int i = 0; i < nbLignes + 1; i++)
		{
			int z = i * rowSize;
			z = ofMap(z, 0, taille, -halfSize, halfSize);
			vertices.push_back(ofVec3f(x, 0, z));
		}
	}
}

void Plane::ajouterIndices()
{
	for(int i = 0; i < nbColonnes; i++)
	{
		int relIndice = i * (nbLignes + 1);
		for(int j = 0; j < nbLignes; j++)
		{
			indices.push_back(j + relIndice); indices.push_back(j + relIndice + 1); indices.push_back(j + relIndice + nbLignes + 1); 
			indices.push_back(j + relIndice + nbLignes + 1); indices.push_back(j + relIndice + 1); indices.push_back(j + relIndice + nbLignes + 2);
		}
	}
}

void Plane::ajouterCouleurs()
{
	for(int i = 0; i < nbColonnes; i++)
	{
		for(int j = 0; j < nbLignes; j++)
		{
			colors.push_back(ofVec3f(1.0, 0.0, 0.0));
			colors.push_back(ofVec3f(0.0, 1.0, 0.0));
			colors.push_back(ofVec3f(0.0, 0.0, 1.0));
			colors.push_back(ofVec3f(1.0, 0.0, 1.0));
		}
	}
}

void Plane::calculerNormals()
{
	normals.resize(vertices.size());
	for (int i = 0; i < indices.size(); i+=3)
	{
		GLuint ia = indices[i];
		GLuint ib = indices[i+1];
		GLuint ic = indices[i+2];
		ofVec3f normal = ofVec3f(vertices[ib]) - ofVec3f(vertices[ia]);
		normal.cross(ofVec3f(vertices[ic]) - ofVec3f(vertices[ia]));
		normal.normalize();
		normals[ia] = normals[ib] = normals[ic] = normal;
	}
}

void Plane::initialiserMesh()
{
	mesh = Mesh(vertices, colors, texCoords, normals, indices, (nbColonnes + 1) * (nbLignes + 1));
}

void Plane::afficher()
{
	if(useTexture)
		chargerTextures();
	mesh.dessiner();
}

void Plane::chargerTextures()
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture.getID());
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glGenerateMipmap(GL_TEXTURE_2D);
}

void Plane::ajouterTexture(const string& texPath)
{
	texture.setFichierImage(texPath);
	texture.charger();
}

void Plane::utiliserTextures(bool utiliser)
{
	useTexture = utiliser;
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
	for(int i = 1; i < vertices.size(); i++)
	{
		vertices[i].y = ofRandom(minHeight, maxHeight);
	}

	this->initialiserMesh();
}

void Plane::generePenteProgressive(float minHeight, float maxHeight)
{
	float x = 0;
	for(int i = 1; i < vertices.size(); i++)
	{
		vertices[i].y = ofRandom(minHeight, maxHeight) * x;
		minHeight++;
		maxHeight++;
		x++;
	}

	this->initialiserMesh();
}

void Plane::reinitialiseHauteur()
{
	for(int i = 1; i < vertices.size(); i++)
	{
		vertices[i].y = 0;
	}

	this->initialiserMesh();
}

void Plane::setRatioTextureParCarre(float ratio)
{
	ratioTextureParCarre = ratio;
	texCoords.clear();
	ajouterTexCoordPourChaqueSommet();
	this->initialiserMesh();
}

Plane::~Plane(void)
{
}
