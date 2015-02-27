#include "Paysage.h"


Paysage::Paysage()
{
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

	arbre = ModeleOBJ("Models/tree.obj");
	generationPositionArbres();
}

void Paysage::generationPositionArbres()
{
	for(int i = 0; i < NB_ARBRES; i++)
	{
		positionsArbres.push_back(ofVec3f(ofRandom(-500.0, 500.0), -10.0, ofRandom(-1500.0, 1500.0)));
	}
}

void Paysage::afficher(ofMatrix4x4 projection, ofMatrix4x4 modelIn, ofMatrix4x4 view, 
					   const ofVec3f& directionLumiere, const ofVec3f& couleurLumiere)
{
	this->model = modelIn;
	// Affichage de la surface de base
	pushMatrix();
		glUseProgram(shaderUneTexture.getProgramID());
		glUniform3fv(glGetUniformLocation(shaderUneTexture.getProgramID(), "lumiereAmbiante"), 1, LUMIERE_AMBIANTE.getPtr());
		glUniform3fv(glGetUniformLocation(shaderUneTexture.getProgramID(), "positionLumiere"), 1, directionLumiere.getPtr());
		glUniform3fv(glGetUniformLocation(shaderUneTexture.getProgramID(), "couleurLumiere"), 1, couleurLumiere.getPtr());
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
		glUniform3fv(glGetUniformLocation(shaderOscillation.getProgramID(), "lumiereAmbiante"), 1, LUMIERE_AMBIANTE.getPtr());
		glUniform3fv(glGetUniformLocation(shaderOscillation.getProgramID(), "positionLumiere"), 1, directionLumiere.getPtr());
		glUniform3fv(glGetUniformLocation(shaderOscillation.getProgramID(), "couleurLumiere"), 1, couleurLumiere.getPtr());
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
	
	for(int i = 0; i < NB_ARBRES; i++)
	{
		pushMatrix();
			model.glTranslate(positionsArbres[i]);
			model.glScale(50, 50, 50);
			arbre.afficher(projection, model, view, directionLumiere, couleurLumiere);
		popMatrix();
	}

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
