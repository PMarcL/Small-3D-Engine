#include "Texture.h"

Texture::Texture(string fichierImage) : m_id(0), m_fichierImage(fichierImage)
{

}

Texture::~Texture()
{
	glDeleteTextures(1, &m_id);
}


bool Texture::charger()
{
	ofImage image;
	GLenum formatInterne(0);

	if (!image.loadImage(m_fichierImage)){
		cout << "Erreur: la texture \"" << m_fichierImage << "\" n'a pu être chargé" << endl;
		return false;
	}

	//Inversion de l'image
	image.setFromPixels(inverserPixels(&image));

	if(image.type == OF_IMAGE_COLOR){
		formatInterne = GL_RGB;
	}else if (image.type == OF_IMAGE_COLOR_ALPHA){
		formatInterne = GL_RGBA;
	}else //OF_IMAGE_GRAYSCALE
		formatInterne = GL_RED;//à voir: Ajouter gestion d'erreur ici????<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<


	// Destruction d'une éventuelle ancienne texture
	if(glIsTexture(m_id) == GL_TRUE)
		glDeleteTextures(1, &m_id);

	glGenTextures(1, &m_id);
	glBindTexture(GL_TEXTURE_2D, m_id);

	glTexImage2D(GL_TEXTURE_2D, 0, formatInterne, image.width, image.height, 0, formatInterne, GL_UNSIGNED_BYTE, image.getPixels());

	//Les filtres
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	
	glBindTexture(GL_TEXTURE_2D, 0);

	image.clear();
	return true;
}

GLuint Texture::getID() const
{
    return m_id;
}

void Texture::setFichierImage(const string &fichierImage)
{
    m_fichierImage = fichierImage;
}


ofImage Texture::inverserPixels(ofImage *imageSource)
{
    ofImage imageInversee;
	int typeSource = imageSource->type;
	int wSource = imageSource->width;
	int hSource = imageSource->height;
	int bpp = imageSource->bpp / 8;

	// Copie conforme de l'image source sans les pixels
	imageInversee.allocate(wSource, hSource, (ofImageType)typeSource);

    // Tableau intermédiaires permettant de manipuler les pixels
	unsigned char* pixelsSources = imageSource->getPixels();
    unsigned char* pixelsInverses = imageInversee.getPixels();

    // Inversion des pixels
    for(int i = 0; i < hSource; i++)
    {
        for(int j = 0; j < wSource * bpp; j++)
            pixelsInverses[(wSource * bpp * (hSource - 1 - i)) + j] = pixelsSources[(wSource * bpp * i) + j];
    }


    // Retour de l'image inversée
    return imageInversee;
}

Texture::Texture(Texture const &textureACopier)
{
    // Copie de la texture

    m_fichierImage = textureACopier.m_fichierImage;
    charger();
}

Texture& Texture::operator=(Texture const &textureACopier)
{
	// Copie de la texture
	m_fichierImage = textureACopier.m_fichierImage;
	charger();
	
	// Retour du pointeur *this
	return *this;
}