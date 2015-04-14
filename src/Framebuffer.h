#pragma once
#include "ofMain.h"

static const int NUM_SAMPLES = 8;

class Framebuffer
{
public:
	Framebuffer();
	~Framebuffer();

	

	void generateFBO(unsigned int width, unsigned int height);
	GLuint getColorTexture();
	void resize(unsigned int width, unsigned int height);
	void bind();
	void unbind();

private:
	void generateIntermediateMultiSampleFBO();
	void generateColorTexture();
	void destroy();

	GLuint width;
	GLuint height;
	GLuint FBO;
	GLuint intermediateFBO;
	GLuint rbo;
	GLuint texture_color;
	GLuint screenColor;
	std::vector<GLenum> drawbuffer;
};

