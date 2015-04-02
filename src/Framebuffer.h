#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "ofMain.h"
class Framebuffer
{
private:
	unsigned int FBO;
	        
	unsigned int texture_depth;	
	std::vector<GLenum> drawbuffer;

	void destroy();
	void generateColorTexture(unsigned int width, unsigned int height);
	void generateDepthTexture(unsigned int width, unsigned int height);

public:
	Framebuffer();
	~Framebuffer();

	unsigned int texture_color; 

	void generateFBO(unsigned int width, unsigned int height);
	unsigned int getColorTexture();
	unsigned int getDepthTexture();
	void resize(unsigned int width, unsigned int height);
	void bind();
	void unbind();
};

