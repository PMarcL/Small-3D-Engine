#include "EffetPleinEcran.h"


EffetPleinEcran::EffetPleinEcran()
{
	shaderBrouillard = Shader("Shaders/ShaderPleinEcran.vert", "Shaders/ShaderBrouillard.frag");
	shaderBrouillard.charger();
}

void EffetPleinEcran::afficher()
{
	GLuint rectanglePleinEcran = creerRectanglePleinEcran();
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glDisable(GL_DEPTH_TEST);
	glDisable(GL_LIGHTING);
	
	glUseProgram(shaderBrouillard.getProgramID());
	glBindVertexArray(rectanglePleinEcran);
    glBindTexture(GL_TEXTURE_2D, textureID);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);

	glUseProgram(0);
}

void EffetPleinEcran::chargerTexture(GLuint texture) 
{
	textureID = texture;
}

GLuint EffetPleinEcran::creerRectanglePleinEcran()
{
	GLfloat verticesPleinEcran[] = { 
        -1.0f,  1.0f,  0.0f, 1.0f,
        -1.0f, -1.0f,  0.0f, 0.0f,
         1.0f, -1.0f,  1.0f, 0.0f,

        -1.0f,  1.0f,  0.0f, 1.0f,
         1.0f, -1.0f,  1.0f, 0.0f,
         1.0f,  1.0f,  1.0f, 1.0f
    };
	GLuint rectangleArrayVertices, quadVBO;
    glGenVertexArrays(1, &rectangleArrayVertices);
    glGenBuffers(1, &quadVBO);
    glBindVertexArray(rectangleArrayVertices);
    glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verticesPleinEcran), &verticesPleinEcran, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)(2 * sizeof(GLfloat)));
    glBindVertexArray(0);

	return rectangleArrayVertices;
}
