#include "Framebuffer.h"


Framebuffer::Framebuffer()
{
}


Framebuffer::~Framebuffer()
{
	destroy();
}

void Framebuffer::destroy(){
	glDeleteFramebuffers(1, &FBO);
	glDeleteTextures(1, &texture_color);
	glDeleteTextures(1, &screenColor);
}

void Framebuffer::generateColorTexture(){
	glGenTextures(1, &texture_color);
	glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, texture_color);
	glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, NUM_SAMPLES, GL_RGB, width, height, GL_TRUE);
	glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, 0);
}

void Framebuffer::generateFBO(unsigned int width, unsigned int height){

	this->width = width;
	this->height = height;

	glGenFramebuffers(1, &FBO);
	glBindFramebuffer(GL_FRAMEBUFFER, FBO);

	generateColorTexture();
	
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D_MULTISAMPLE, texture_color, 0);
	
	glGenRenderbuffers(1, &rbo);
	glBindRenderbuffer(GL_RENDERBUFFER, rbo);
	glRenderbufferStorageMultisample(GL_RENDERBUFFER, NUM_SAMPLES, GL_DEPTH24_STENCIL8, width, height);
	glBindRenderbuffer(GL_RENDERBUFFER, 0);

	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo);

	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE){
		std::cout << "Erreur: Le framebuffer n'est pas complete." << std::endl;
		std::cin.get();
		std::terminate();
	}
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	generateIntermediateMultiSampleFBO();
}

void Framebuffer::generateIntermediateMultiSampleFBO(){
	glGenTextures(1, &screenColor);
	glBindTexture(GL_TEXTURE_2D, screenColor);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
    glBindTexture(GL_TEXTURE_2D, 0);

	glGenFramebuffers(1, &intermediateFBO);
	glBindFramebuffer(GL_FRAMEBUFFER, intermediateFBO);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, screenColor, 0);
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE){
		std::cout << "Erreur: Le framebuffer n'est pas complete." << std::endl;
		std::cin.get();
		std::terminate();
	}
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

unsigned int Framebuffer::getColorTexture(){
	return screenColor;
}

void Framebuffer::resize(unsigned int width, unsigned int height){
	destroy();
	this->width = width;
	this->height = height;
	generateFBO(width, height);
}

		
void Framebuffer::bind(){
	glBindFramebuffer(GL_FRAMEBUFFER, FBO);
}
				
void Framebuffer::unbind(){
	glBindFramebuffer(GL_READ_FRAMEBUFFER, FBO);
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, intermediateFBO);
	glBlitFramebuffer(0, 0, width, height, 0, 0, width, height, GL_COLOR_BUFFER_BIT, GL_NEAREST);

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}