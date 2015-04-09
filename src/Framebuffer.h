#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "ofMain.h"
class Framebuffer
{
private:
	GLuint FBO;
	GLuint rbo;
	        
	GLuint texture_depth;	
	std::vector<GLenum> drawbuffer;

	void destroy();
	void generateColorTexture(unsigned int width, unsigned int height);
	void generateDepthTexture(unsigned int width, unsigned int height);

public:
	Framebuffer();
	~Framebuffer();

	unsigned int texture_color; 

	void generateFBO(unsigned int width, unsigned int height);
	GLuint getColorTexture();
	GLuint getDepthTexture();
	void resize(unsigned int width, unsigned int height);
	void bind();
	void unbind();
};

