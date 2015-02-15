#include "Paysage.h"


Paysage::Paysage()
{
	shaderPassThru = Shader("Shaders/shader3D.vert", "Shaders/shader3D.frag");
	shaderPassThru.charger();
	
	shaderOscillation =  Shader("Shaders/waveShader.vert", "Shaders/waveShader.frag");
	shaderOscillation.charger();

	shaderUneTexture = Shader("Shaders/shaderTexture.vert", "Shaders/shaderTexture.frag");
	shaderUneTexture.charger();

	surfaceCentrale = Plane(1000, &shaderUneTexture, 20, 20);
	surfaceCentrale.genereHauteursAleatoire(-20.0, -5.0);
	surfaceCentrale.ajouterTexture("Textures/rock.jpg");
	surfaceCentrale.utiliserTextures(true);

	ocean = Plane(1000, &shaderOscillation, 100, 100);
	ocean.ajouterTexture("Textures/water1.jpg");
	ocean.utiliserTextures(true);
	ocean.setRatioTextureParCarre(0.1);
}


void Paysage::afficher(ofMatrix4x4 projection, ofMatrix4x4 modelView)
{
	ofMatrix4x4 pushMatrix = modelView;
	surfaceCentrale.afficher(projection, modelView);
	modelView.glTranslate(1000.0, -10.0, 0.0);
	ocean.afficher(projection, modelView);
}
