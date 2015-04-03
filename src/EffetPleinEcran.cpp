#include "EffetPleinEcran.h"


EffetPleinEcran::EffetPleinEcran()
{
	shaderBrouillard = Shader("Shaders/shaderPleinEcran.vert", "Shaders/shaderBrouillard.frag");
	shaderBrouillard.charger();

	creerRectanglePleinEcran();
}

void EffetPleinEcran::afficher(GLuint texture)
{	
	glUseProgram(shaderBrouillard.getProgramID());

    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
	
	glDisable(GL_DEPTH_TEST);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);

	glBindVertexArray(vao);
	glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
	
	glUseProgram(0);
}

void EffetPleinEcran::chargerTexture(GLuint texture) 
{
	textureID = texture;
	std::cout << "nouvelle texture:" << textureID<< std::endl;
}

void EffetPleinEcran::creerRectanglePleinEcran()
{
	
	GLfloat quadVertices[] = {

        -1.0f,  1.0f,  0.0f, 1.0f,
        -1.0f, -1.0f,  0.0f, 0.0f,
         1.0f, -1.0f,  1.0f, 0.0f,

        -1.0f,  1.0f,  0.0f, 1.0f,
         1.0f, -1.0f,  1.0f, 0.0f,
         1.0f,  1.0f,  1.0f, 1.0f
    };	
	
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)(2 * sizeof(GLfloat)));
    glBindVertexArray(0);
}
