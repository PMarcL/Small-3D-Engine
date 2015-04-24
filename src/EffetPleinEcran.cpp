#include "EffetPleinEcran.h"


EffetPleinEcran::EffetPleinEcran()
{
	shaderActif = Shader("Shaders/shaderPleinEcran.vert", "Shaders/shaderEffetAucun.frag");
	shaderActif.charger();
	effetCourant = AUCUN;

	creerRectanglePleinEcran();
}

void EffetPleinEcran::afficher(GLuint texture)
{	
	glUseProgram(shaderActif.getProgramID());

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

void EffetPleinEcran::activerEffetBrouillard()
{
	if(effetCourant != BROUILLARD) {
		shaderActif = Shader("Shaders/shaderPleinEcran.vert", "Shaders/shaderEffetBrouillard.frag");
		shaderActif.charger();
		effetCourant = BROUILLARD;
	}
}

void EffetPleinEcran::activerEffetNoirEtBlanc()
{
	if(effetCourant != NOIR_ET_BLANC) {
		shaderActif = Shader("Shaders/shaderPleinEcran.vert", "Shaders/shaderEffetNoirEtBlanc.frag");
		shaderActif.charger();
		effetCourant = NOIR_ET_BLANC;
	}
}

void EffetPleinEcran::activerEffetLignes()
{
	if(effetCourant != LIGNES) {
		shaderActif = Shader("Shaders/shaderPleinEcran.vert", "Shaders/shaderEffetLignes.frag");
		shaderActif.charger();
		effetCourant = LIGNES;
	}
}

void EffetPleinEcran::desactiverEffet()
{
	if(effetCourant != AUCUN) {
		shaderActif = Shader("Shaders/shaderPleinEcran.vert", "Shaders/shaderEffetAucun.frag");
		shaderActif.charger();
		effetCourant = AUCUN;
	}
}