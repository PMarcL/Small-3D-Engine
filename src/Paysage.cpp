#include "Paysage.h"


Paysage::Paysage()
{
	lumiereAmbiante = ofVec3f(0.0, 0.0, 0.3);

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


void Paysage::afficher(ofMatrix4x4 projection, ofMatrix4x4 model, ofMatrix4x4 view,  const ofVec3f& lightPos)
{
	// Affichage de la surface de base
	ofMatrix4x4 pushMatrix = model;
	glUseProgram(shaderUneTexture.getProgramID());
	glUniform3fv(glGetUniformLocation(shaderUneTexture.getProgramID(), "lumiereAmbiante"), 1, lumiereAmbiante.getPtr());
	glUniform3fv(glGetUniformLocation(shaderUneTexture.getProgramID(), "positionLumiere"), 1, lightPos.getPtr());
	glUniform3f(glGetUniformLocation(shaderUneTexture.getProgramID(), "couleurLumiere"), 1.0, 1.0, 1.0);
	glUniformMatrix4fv(glGetUniformLocation(shaderUneTexture.getProgramID(), "projection"), 1, GL_FALSE, projection.getPtr());
	glUniformMatrix4fv(glGetUniformLocation(shaderUneTexture.getProgramID(), "view"), 1, GL_FALSE, view.getPtr());
	glUniformMatrix4fv(glGetUniformLocation(shaderUneTexture.getProgramID(), "model"), 1, GL_FALSE, model.getPtr());
	surfaceCentrale.afficher();
	model.glTranslate(0.0, -10.0, 1000.0);
	glUniformMatrix4fv(glGetUniformLocation(shaderUneTexture.getProgramID(), "model"), 1, GL_FALSE, model.getPtr());
	surfaceCentrale.afficher();
	model = pushMatrix;
	model.glTranslate(0.0, -10.0, -1000.0);
	glUniformMatrix4fv(glGetUniformLocation(shaderUneTexture.getProgramID(), "model"), 1, GL_FALSE, model.getPtr());
	surfaceCentrale.afficher();
	
	// Affichage de la montagne
	model = pushMatrix;
	model.glTranslate(-1000.0, -40.0, 0.0);
	model.glRotate(-90.0f, 0.0, 1.0, 0.0);
	glUniformMatrix4fv(glGetUniformLocation(shaderUneTexture.getProgramID(), "model"), 1, GL_FALSE, model.getPtr());
	montagne.afficher();
	ofMatrix4x4 pushMatrix2 = model;
	model.glTranslate(1000.0, 0.0, 0.0);
	glUniformMatrix4fv(glGetUniformLocation(shaderUneTexture.getProgramID(), "model"), 1, GL_FALSE, model.getPtr());
	montagne.afficher();
	model = pushMatrix2;
	model.glTranslate(-1000.0, 0.0, 200.0);
	glUniformMatrix4fv(glGetUniformLocation(shaderUneTexture.getProgramID(), "model"), 1, GL_FALSE, model.getPtr());
	montagne.afficher();
	
	// Affichage de l'océan
	model = pushMatrix;
	model.glTranslate(1000.0, -10.0, 0.0);
	glUseProgram(shaderOscillation.getProgramID());
	glUniform1f(glGetUniformLocation(shaderOscillation.getProgramID(), "time"), ofGetElapsedTimef());
	glUniformMatrix4fv(glGetUniformLocation(shaderOscillation.getProgramID(), "projection"), 1, GL_FALSE, projection.getPtr());
	glUniformMatrix4fv(glGetUniformLocation(shaderOscillation.getProgramID(), "view"), 1, GL_FALSE, view.getPtr());
	glUniformMatrix4fv(glGetUniformLocation(shaderOscillation.getProgramID(), "model"), 1, GL_FALSE, model.getPtr());
	ocean.afficher();
	pushMatrix2 = model;
	model.glTranslate(0.0, 0.0, -1000.0);
	model.glRotate(90.0, 0.0, 1.0, 0.0);
	glUniformMatrix4fv(glGetUniformLocation(shaderOscillation.getProgramID(), "model"), 1, GL_FALSE, model.getPtr());
	ocean.afficher();
	model = pushMatrix2;
	model.glTranslate(0.0, 0.0, 1000.0);
	model.glRotate(90.0, 0.0, 1.0, 0.0);
	glUniformMatrix4fv(glGetUniformLocation(shaderOscillation.getProgramID(), "model"), 1, GL_FALSE, model.getPtr());
	ocean.afficher();

	glUseProgram(0);
}
