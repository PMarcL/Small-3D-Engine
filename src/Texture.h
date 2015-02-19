#ifndef DEF_TEXTURE
#define DEF_TEXTURE

#include "ofMain.h"

class Texture
{
    public:
		Texture(){};
		Texture(string fichierImage);
		~Texture();
		bool charger();
		GLuint getID() const;
		void setFichierImage(const string &fichierImage);

		Texture(Texture const &textureACopier);
		Texture& operator=(Texture const &textureACopier);
    private:
		GLuint m_id;
		string m_fichierImage;

		ofImage inverserPixels(ofImage *imageSource);
};

#endif