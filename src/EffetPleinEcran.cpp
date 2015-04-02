#include "EffetPleinEcran.h"


EffetPleinEcran::EffetPleinEcran()
{
	shaderBrouillard = Shader("Shaders/shaderPleinEcran.vert", "Shaders/shaderBrouillard.frag");
	shaderBrouillard.charger();
}

void EffetPleinEcran::afficher(GLuint texture)
{
	
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //glDisable(GL_DEPTH_TEST);
	glDisable(GL_LIGHTING);
	
	glUseProgram(shaderBrouillard.getProgramID());
	
	GLuint rectangle = creerRectanglePleinEcran();

	glActiveTexture(GL_TEXTURE0 + 1);
	glBindTexture(GL_TEXTURE_2D, texture);

	glUniform1i(glGetUniformLocation(shaderBrouillard.getProgramID(), "screenTexture"), 1);
	glBindVertexArray(rectangle);
	glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
	
	glUseProgram(0);
}

void EffetPleinEcran::chargerTexture(GLuint texture) 
{
	textureID = texture;
	std::cout << "nouvelle texture:" << textureID<< std::endl;
}

GLuint EffetPleinEcran::creerRectanglePleinEcran()
{
	
	GLfloat quadVertices[] = {

        -1.0f,  1.0f,  0.0f, 1.0f,
        -1.0f, -1.0f,  0.0f, 0.0f,
         1.0f, -1.0f,  1.0f, 0.0f,

        -1.0f,  1.0f,  0.0f, 1.0f,
         1.0f, -1.0f,  1.0f, 0.0f,
         1.0f,  1.0f,  1.0f, 1.0f
    };	
	
	GLuint quadVAO, quadVBO;
    glGenVertexArrays(1, &quadVAO);
    glGenBuffers(1, &quadVBO);
    glBindVertexArray(quadVAO);
    glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)(2 * sizeof(GLfloat)));
    glBindVertexArray(0);

	return quadVAO;
}
