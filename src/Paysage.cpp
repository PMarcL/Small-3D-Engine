#include "Paysage.h"


Paysage::Paysage()
{
	shaderOscillation =  Shader("Shaders/waveShader.vert", "Shaders/waveShader.frag");
	shaderOscillation.charger();

	shaderUneTexture = Shader("Shaders/shaderTextureLight.vert", "Shaders/shaderTextureLight.frag");
	shaderUneTexture.charger();

	surfaceCentrale = Plane(1000, 20, 60);
	surfaceCentrale.genereHauteursAleatoire(-30.0, -5.0);
	texRoche = Texture("Textures/rock.jpg");
	texRoche.charger();
	texRocheSpeculaire = Texture("Textures/rock_specular.jpg");
	texRocheSpeculaire.charger();

	ocean = Plane(1000, 100, 300);
	ocean.setRatioTextureParCarre(0.5);
	texEau = Texture("Textures/water1.jpg");
	texEau.charger();
	texEauSpeculaire = Texture("Textures/water1_specular.jpg");
	texEauSpeculaire.charger();

	montagne = Plane(1000, 5, 10);
	montagne.generePenteProgressive(0.0, 5.0);

	arbre = ModeleOBJ("Models/tree.obj");
	generationPositionsArbres();
	texTree = Texture("Textures/wood.jpg");
	texTree.charger();
	texTreeSpeculaire = Texture("Textures/wood_specular.jpg");
	texTreeSpeculaire.charger();
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
		position = ofVec3f(ofRandom(-500.0, 500.0), -20.0, ofRandom(-1400.0, 1400.0));
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
					   const Lumiere& lumiere)
{
	this->model = modelIn;
	// Affichage de la surface de base
	pushMatrix();
		glUseProgram(shaderUneTexture.getProgramID());
		lumiere.chargerValeursIlluminationUniforms(shaderUneTexture.getProgramID());
		glUniform1i(glGetUniformLocation(shaderUneTexture.getProgramID(), "diffuseMap"), 0);
		glUniform1i(glGetUniformLocation(shaderUneTexture.getProgramID(), "specularMap"), 1);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texRoche.getID());
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, texRocheSpeculaire.getID());
		model.glScale(1.5, 1.0, 4.0);
		chargerMatricesMVPUniforms(shaderUneTexture.getProgramID(), projection, model, view);
		surfaceCentrale.afficher();
	popMatrix();

	// Affichage de la montagne
	pushMatrix();
		model.glTranslate(-1200.0, -80.0, 0.0);
		model.glRotate(180.0f, -0.01, 1.0, 0);
		model.glScale(1.0, 1.0, 3.0);
		glUniformMatrix4fv(glGetUniformLocation(shaderUneTexture.getProgramID(), "model"), 1, GL_FALSE, model.getPtr());
		montagne.afficher();
	popMatrix();

	// affichage des arbres
	glUniform1i(glGetUniformLocation(shaderUneTexture.getProgramID(), "diffuseMap"), 0);
	glUniform1i(glGetUniformLocation(shaderUneTexture.getProgramID(), "specularMap"), 1);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texTree.getID());
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, texTreeSpeculaire.getID());
	for(int i = 0; i < NB_ARBRES; i++)
	{
		pushMatrix();
			model.glTranslate(positionsArbres[i]);
			model.glScale(50, 50, 50);
			glUniformMatrix4fv(glGetUniformLocation(shaderUneTexture.getProgramID(), "model"), 1, GL_FALSE, model.getPtr());
			arbre.afficher();		
		popMatrix();
	}
	
	// Affichage de l'océan
	pushMatrix();
		glUseProgram(shaderOscillation.getProgramID());
		model.glTranslate(980.0, -40.0, 0.0);
		model.glScale(10, 10, 30);
		lumiere.chargerValeursIlluminationUniforms(shaderOscillation.getProgramID());
		glUniform1i(glGetUniformLocation(shaderOscillation.getProgramID(), "diffuseMap"), 0);
		glUniform1i(glGetUniformLocation(shaderOscillation.getProgramID(), "specularMap"), 1);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texEau.getID());
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, texEauSpeculaire.getID());
		chargerMatricesMVPUniforms(shaderOscillation.getProgramID(), projection, model, view);
		glUniform1f(glGetUniformLocation(shaderOscillation.getProgramID(), "time"), ofGetElapsedTimef());
		ocean.afficher();
	popMatrix();
	
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, 0);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, 0);
	glUseProgram(0);
}

void Paysage::chargerMatricesMVPUniforms(GLuint id, const ofMatrix4x4& projection, const ofMatrix4x4& model, const ofMatrix4x4& view)
{
	glUniformMatrix4fv(glGetUniformLocation(id, "projection"), 1, GL_FALSE, projection.getPtr());
	glUniformMatrix4fv(glGetUniformLocation(id, "view"), 1, GL_FALSE, view.getPtr());
	glUniformMatrix4fv(glGetUniformLocation(id, "model"), 1, GL_FALSE, model.getPtr());
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
