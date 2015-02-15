#include "Paysage.h"


Paysage::Paysage()
{
	lumiereAmbiante = ofVec3f(0.0,0.0,0.3);

	shaderPassThru = Shader("Shaders/shader3D.vert", "Shaders/shader3D.frag");
	shaderPassThru.charger();
	
	shaderOscillation =  Shader("Shaders/waveShader.vert", "Shaders/waveShader.frag");
	shaderOscillation.charger();

	shaderUneTexture = Shader("Shaders/shaderTexture.vert", "Shaders/shaderTexture.frag");
	shaderUneTexture.charger();

	surfaceCentrale = Plane(1000, 20, 20);
	surfaceCentrale.genereHauteursAleatoire(-20.0, -5.0);
	surfaceCentrale.ajouterTexture("Textures/rock.jpg");
	surfaceCentrale.utiliserTextures(true);

	ocean = Plane(1000, 100, 100);
	ocean.ajouterTexture("Textures/water1.jpg");
	ocean.utiliserTextures(true);
	ocean.setRatioTextureParCarre(0.1);

	montagne = Plane(1000, 5, 5);
	montagne.generePenteProgressive(0.0, 5.0);
	montagne.ajouterTexture("Textures/rock.jpg");
	montagne.utiliserTextures(true);
}


void Paysage::afficher(ofMatrix4x4 projection, ofMatrix4x4 modelView)
{
	// Affichage de la surface de base
	ofMatrix4x4 pushMatrix = modelView;
	glUseProgram(shaderUneTexture.getProgramID());
	glUniform3fv(glGetUniformLocation(shaderUneTexture.getProgramID(), "lumiereAmbiante"), 1, lumiereAmbiante.getPtr());
	glUniformMatrix4fv(glGetUniformLocation(shaderUneTexture.getProgramID(), "projection"), 1, GL_FALSE, projection.getPtr());
	glUniformMatrix4fv(glGetUniformLocation(shaderUneTexture.getProgramID(), "modelview"), 1, GL_FALSE, modelView.getPtr());
	surfaceCentrale.afficher();
	modelView.glTranslate(0.0, -10.0, 1000.0);
	glUniformMatrix4fv(glGetUniformLocation(shaderUneTexture.getProgramID(), "modelview"), 1, GL_FALSE, modelView.getPtr());
	surfaceCentrale.afficher();
	modelView = pushMatrix;
	modelView.glTranslate(0.0, -10.0, -1000.0);
	glUniformMatrix4fv(glGetUniformLocation(shaderUneTexture.getProgramID(), "modelview"), 1, GL_FALSE, modelView.getPtr());
	surfaceCentrale.afficher();

	// Affichage de la montagne
	modelView = pushMatrix;
	modelView.glTranslate(-1000.0, -40.0, 0.0);
	modelView.glRotate(-90.0f, 0.0, 1.0, 0.0);
	glUniformMatrix4fv(glGetUniformLocation(shaderUneTexture.getProgramID(), "modelview"), 1, GL_FALSE, modelView.getPtr());
	montagne.afficher();
	ofMatrix4x4 pushMatrix2 = modelView;
	modelView.glTranslate(1000.0, 0.0, 0.0);
	glUniformMatrix4fv(glGetUniformLocation(shaderUneTexture.getProgramID(), "modelview"), 1, GL_FALSE, modelView.getPtr());
	montagne.afficher();
	modelView = pushMatrix2;
	modelView.glTranslate(-1000.0, 0.0, 200.0);
	glUniformMatrix4fv(glGetUniformLocation(shaderUneTexture.getProgramID(), "modelview"), 1, GL_FALSE, modelView.getPtr());
	montagne.afficher();
	
	// Affichage de l'océan
	modelView = pushMatrix;
	modelView.glTranslate(1000.0, -10.0, 0.0);
	glUseProgram(shaderOscillation.getProgramID());
	glUniform1f(glGetUniformLocation(shaderOscillation.getProgramID(), "time"), ofGetElapsedTimef());
	glUniformMatrix4fv(glGetUniformLocation(shaderOscillation.getProgramID(), "projection"), 1, GL_FALSE, projection.getPtr());
	glUniformMatrix4fv(glGetUniformLocation(shaderOscillation.getProgramID(), "modelview"), 1, GL_FALSE, modelView.getPtr());
	ocean.afficher();
	pushMatrix2 = modelView;
	modelView.glTranslate(0.0, 0.0, -1000.0);
	modelView.glRotate(90.0, 0.0, 1.0, 0.0);
	glUniformMatrix4fv(glGetUniformLocation(shaderOscillation.getProgramID(), "modelview"), 1, GL_FALSE, modelView.getPtr());
	ocean.afficher();
	modelView = pushMatrix2;
	modelView.glTranslate(0.0, 0.0, 1000.0);
	modelView.glRotate(90.0, 0.0, 1.0, 0.0);
	glUniformMatrix4fv(glGetUniformLocation(shaderOscillation.getProgramID(), "modelview"), 1, GL_FALSE, modelView.getPtr());
	ocean.afficher();

	glUseProgram(0);
}
