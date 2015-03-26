#include "EffetPleinEcran.h"


EffetPleinEcran::EffetPleinEcran()
{
	shaderBrouillard = Shader("Shaders/quadPleinEcran.vert", "Shaders/ShaderBrouillard.frag");
	shaderBrouillard.charger();

	 GLfloat verticesTemporaires[] = { 
        -1.0f,  1.0f,  0.0f, 1.0f,
        -1.0f, -1.0f,  0.0f, 0.0f,
         1.0f, -1.0f,  1.0f, 0.0f,

        -1.0f,  1.0f,  0.0f, 1.0f,
         1.0f, -1.0f,  1.0f, 0.0f,
         1.0f,  1.0f,  1.0f, 1.0f
    };
	
	 for(int i=0; i < 24; i++) {
		verticesPleinEcran[i] = verticesTemporaires[i];
	}
}

void EffetPleinEcran::afficher()
{
	GLuint quadVAO, quadVBO;
    glGenVertexArrays(1, &quadVAO);
    glGenBuffers(1, &quadVBO);
    glBindVertexArray(quadVAO);
    glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verticesPleinEcran), &verticesPleinEcran, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)(2 * sizeof(GLfloat)));
    glBindVertexArray(0);
	
	
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
    // Clear all relevant buffers
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f); // Set clear color to white (not really necessery actually, since we won't be able to see behind the quad anyways)
    glClear(GL_COLOR_BUFFER_BIT);
    glDisable(GL_DEPTH_TEST);
	
	glUseProgram(shaderBrouillard.getProgramID());
	glBindVertexArray(quadVAO);
    glBindTexture(GL_TEXTURE_2D, textureID);	// Use the color attachment texture as the texture of the quad plane
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);

	glUseProgram(0);
}

void EffetPleinEcran::chargerTexture(GLuint texture) 
{
	textureID = texture;
}

