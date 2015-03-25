#include "ConteneurPrimitives.h"


ConteneurPrimitives::ConteneurPrimitives(void)
{
	shader = Shader("Shaders/shaderMateriaux.vert", "Shaders/shaderMateriaux.frag");
	shader.charger();
}


ConteneurPrimitives::~ConteneurPrimitives(void)
{
}

void ConteneurPrimitives::ajouterPrimitive(PrimitiveGeometrique primitive)
{
	primitives.push_back(primitive);
}

void ConteneurPrimitives::afficher(ofMatrix4x4 projection, ofMatrix4x4 model, ofMatrix4x4 view, Lumiere lumiere)
{
	glUseProgram(shader.getProgramID());

		lumiere.chargerValeursIlluminationStruct(shader.getProgramID());
		chargerMatricesMVPUniforms(projection, model, view);
		ofMatrix4x4 modelSave = model;
		for(int i = 0; i < primitives.size(); i++)
		{
			model.glTranslate(primitives[i].getPosition());
			glUniformMatrix4fv(glGetUniformLocation(shader.getProgramID(), "model"), 1, GL_FALSE, model.getPtr());
			primitives[i].chargerMateriauxUniforms(shader.getProgramID());
			primitives[i].afficher();
			model = modelSave;
		}

	glUseProgram(0);
}

void ConteneurPrimitives::chargerMatricesMVPUniforms(const ofMatrix4x4& projection, const ofMatrix4x4& model, const ofMatrix4x4& view)
{
	glUniformMatrix4fv(glGetUniformLocation(shader.getProgramID(), "projection"), 1, GL_FALSE, projection.getPtr());
	glUniformMatrix4fv(glGetUniformLocation(shader.getProgramID(), "view"), 1, GL_FALSE, view.getPtr());
	glUniformMatrix4fv(glGetUniformLocation(shader.getProgramID(), "model"), 1, GL_FALSE, model.getPtr());
}