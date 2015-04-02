#include "Framebuffer.h"


Framebuffer::Framebuffer()
{
}


Framebuffer::~Framebuffer()
{
	destroy();
}

void Framebuffer:: destroy(){
	glDeleteFramebuffers(1, &FBO);
	glDeleteTextures(1, &texture_color);
	glDeleteTextures(1, &texture_depth);
}

void Framebuffer::generateColorTexture(unsigned int width, unsigned int height){
	glGenTextures(1, &texture_color);
	glBindTexture(GL_TEXTURE_2D, texture_color);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0);
}

	

void Framebuffer::generateDepthTexture(unsigned int width, unsigned int height){
	glGenTextures(1, &texture_depth);
	glBindTexture(GL_TEXTURE_2D, texture_depth);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT24, width, height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, 0);
}

void Framebuffer::generateFBO(unsigned int width, unsigned int height){

	//Generate a framebuffer object(FBO) and bind it to the pipeline
	glGenFramebuffers(1, &FBO);
	glBindFramebuffer(GL_FRAMEBUFFER, FBO);

	generateColorTexture(width, height);//generate empty texture
	generateDepthTexture(width, height);//generate empty texture

	//to keep track of our textures
	unsigned int attachment_index_color_texture = 0;

	//bind textures to pipeline. texture_depth is optional
	//0 is the mipmap level. 0 is the heightest
			
	glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + attachment_index_color_texture, texture_color, 0);
	glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, texture_depth, 0);//optional

	//add attachements
	drawbuffer.push_back(GL_COLOR_ATTACHMENT0 + attachment_index_color_texture);
	glDrawBuffers(drawbuffer.size(), &drawbuffer[0]);
	//Check for FBO completeness
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE){
		std::cout << "Error! FrameBuffer is not complete" << std::endl;
		std::cin.get();
		std::terminate();
	}

	//unbind framebuffer
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

unsigned int Framebuffer::getColorTexture(){
	return texture_color;
}

unsigned int Framebuffer::getDepthTexture(){
	return texture_depth;
}

void Framebuffer::resize(unsigned int width, unsigned int height){
	destroy();
	generateFBO(width, height);
}

		
void Framebuffer::bind(){
	glBindFramebuffer(GL_FRAMEBUFFER, FBO);
}
				
void Framebuffer::unbind(){
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}