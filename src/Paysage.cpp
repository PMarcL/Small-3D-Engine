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
	generationPositionsArbres();
	texTree = Texture("Textures/wood.jpg");
	texTree.charger();
}

void Paysage::generationPositionsArbres()
{
	for(int i = 0; i < NB_ARBRES; i++)
	{
		ofVec3f position = genererPositionAvecEspacement(150);
		positionsArbres.push_back(position);
	}
}

ofVec3f Paysage::genererPositionAvecEspacement(int espacement)
{
	ofVec3f position;
	bool positionTrouvee = false;
	while(!positionTrouvee) {
		position = ofVec3f(ofRandom(-500.0, 500.0), -10.0, ofRandom(-1400.0, 1400.0));
		positionTrouvee = positionEstEnConflit(espacement, position);
	}
	return position;
}

bool Paysage::positionEstEnConflit(int espacement, ofVec3f position)
{
	for(int j = 0; j < positionsArbres.size(); j++) {
		ofVec3f difference = position - positionsArbres[j];
		if(difference.x <= espacement && difference.x >= -espacement && difference.z <= espacement && difference.z >= -espacement) {
			return false;
		}
	}
	return true;
}

void Paysage::afficher(ofMatrix4x4 projection, ofMatrix4x4 modelIn, ofMatrix4x4 view, 
					   const ofVec3f& directionLumiere, const ofVec3f& couleurLumiere, const float& intensiteLumiere)
{
	this->model = modelIn;
	// Affichage de la surface de base
	pushMatrix();
		glUseProgram(shaderUneTexture.getProgramID());
		glUniform1f(glGetUniformLocation(shaderUneTexture.getProgramID(), "intensiteLumiere"), intensiteLumiere);
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
		glUniform1f(glGetUniformLocation(shaderOscillation.getProgramID(), "intensiteLumiere"), intensiteLumiere);
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
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, texTree.getID());
			model.glTranslate(positionsArbres[i]);
			model.glScale(50, 50, 50);
			arbre.afficher(projection, model, view, directionLumiere, couleurLumiere, intensiteLumiere);		
		popMatrix();
	}
	glBindTexture(GL_TEXTURE_2D, 0);
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
