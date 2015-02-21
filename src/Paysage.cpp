#include "Paysage.h"


Paysage::Paysage()
{
	lumiereAmbiante = ofVec3f(0.0, 0.0, 0.3);

	shaderPassThru = Shader("Shaders/shader3D.vert", "Shaders/shader3D.frag");
	shaderPassThru.charger();
	
	shaderOscillation =  Shader("Shaders/waveShader.vert", "Shaders/waveShader.frag");
	shaderOscillation.charger();

	shaderUneTexture = Shader("Shaders/shaderTextureLight.vert", "Shaders/shaderTextureLight.frag");
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


void Paysage::afficher(ofMatrix4x4 projection, ofMatrix4x4 modelIn, ofMatrix4x4 view,  const ofVec3f& lightPos)
{
	this->model = modelIn;
	// Affichage de la surface de base
	pushMatrix();
		glUseProgram(shaderUneTexture.getProgramID());
		glUniform3fv(glGetUniformLocation(shaderUneTexture.getProgramID(), "lumiereAmbiante"), 1, lumiereAmbiante.getPtr());
		glUniform3fv(glGetUniformLocation(shaderUneTexture.getProgramID(), "positionLumiere"), 1, lightPos.getPtr());
		glUniform3f(glGetUniformLocation(shaderUneTexture.getProgramID(), "couleurLumiere"), 1.0, 1.0, 1.0);
		glUniformMatrix4fv(glGetUniformLocation(shaderUneTexture.getProgramID(), "projection"), 1, GL_FALSE, projection.getPtr());
		glUniformMatrix4fv(glGetUniformLocation(shaderUneTexture.getProgramID(), "view"), 1, GL_FALSE, view.getPtr());
		glUniformMatrix4fv(glGetUniformLocation(shaderUneTexture.getProgramID(), "model"), 1, GL_FALSE, model.getPtr());
		surfaceCentrale.afficher();
		model.glTranslate(0.0, 0.0, 1000.0);
		glUniformMatrix4fv(glGetUniformLocation(shaderUneTexture.getProgramID(), "model"), 1, GL_FALSE, model.getPtr());
		surfaceCentrale.afficher();
	popMatrix();
	pushMatrix();
		model.glTranslate(0.0, 0.0, -1000.0);
		glUniformMatrix4fv(glGetUniformLocation(shaderUneTexture.getProgramID(), "model"), 1, GL_FALSE, model.getPtr());
		surfaceCentrale.afficher();
	popMatrix();
	
	// Affichage de la montagne
	pushMatrix();
		model.glTranslate(-1000.0, -40.0, 0.0);
		model.glRotate(180.0f, 0.0, 1.0, 0.0);
		glUniformMatrix4fv(glGetUniformLocation(shaderUneTexture.getProgramID(), "model"), 1, GL_FALSE, model.getPtr());
		montagne.afficher();
		
		pushMatrix();
			model.glTranslate(0.0, 0.0, 1000.0);
			glUniformMatrix4fv(glGetUniformLocation(shaderUneTexture.getProgramID(), "model"), 1, GL_FALSE, model.getPtr());
			montagne.afficher();
		popMatrix();
	
		model.glTranslate(-150.0, -40.0, -900.0);
		model.glRotate(20.0f, 0.0, 1.0, 0.0);
		glUniformMatrix4fv(glGetUniformLocation(shaderUneTexture.getProgramID(), "model"), 1, GL_FALSE, model.getPtr());
		montagne.afficher();
	popMatrix();
	
	// Affichage de l'océan
	pushMatrix();
		model.glTranslate(980.0, -40.0, 0.0);
		glUseProgram(shaderOscillation.getProgramID());
		glUniform3fv(glGetUniformLocation(shaderOscillation.getProgramID(), "lumiereAmbiante"), 1, lumiereAmbiante.getPtr());
		glUniform3fv(glGetUniformLocation(shaderOscillation.getProgramID(), "positionLumiere"), 1, lightPos.getPtr());
		glUniform3f(glGetUniformLocation(shaderOscillation.getProgramID(), "couleurLumiere"), 1.0, 1.0, 1.0);
		glUniform1f(glGetUniformLocation(shaderOscillation.getProgramID(), "time"), ofGetElapsedTimef());
		glUniformMatrix4fv(glGetUniformLocation(shaderOscillation.getProgramID(), "projection"), 1, GL_FALSE, projection.getPtr());
		glUniformMatrix4fv(glGetUniformLocation(shaderOscillation.getProgramID(), "view"), 1, GL_FALSE, view.getPtr());
		glUniformMatrix4fv(glGetUniformLocation(shaderOscillation.getProgramID(), "model"), 1, GL_FALSE, model.getPtr());
		ocean.afficher();
	
		pushMatrix();
			model.glTranslate(0.0, 0.0, -1000.0);
			model.glRotate(90.0, 0.0, 1.0, 0.0);
			glUniformMatrix4fv(glGetUniformLocation(shaderOscillation.getProgramID(), "model"), 1, GL_FALSE, model.getPtr());
			ocean.afficher();
		popMatrix();

		pushMatrix();
			model.glTranslate(0.0, 0.0, 1000.0);
			model.glRotate(90.0, 0.0, 1.0, 0.0);
			glUniformMatrix4fv(glGetUniformLocation(shaderOscillation.getProgramID(), "model"), 1, GL_FALSE, model.getPtr());
			ocean.afficher();
		popMatrix();

	popMatrix();

	glUseProgram(0);
}

void Paysage::pushMatrix()
{
	matrices.push(model);
}

void Paysage::popMatrix()
{
	model = matrices.top();
	matrices.pop();
}
