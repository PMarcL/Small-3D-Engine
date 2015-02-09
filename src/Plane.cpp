#include "Plane.h"


Plane::Plane(int size, Shader* shader)
	: shader(shader), texture(0), useTexture(false)
{
	int halfSize = size /2;

	vertices.push_back(-halfSize); vertices.push_back(0); vertices.push_back(-halfSize); // coin sup gauche
	vertices.push_back(-halfSize); vertices.push_back(0); vertices.push_back(halfSize); // coin inf gauche
	vertices.push_back(halfSize); vertices.push_back(0); vertices.push_back(-halfSize); // coin sup droit
	vertices.push_back(halfSize); vertices.push_back(0); vertices.push_back(halfSize); // coin inf droit

	colors.push_back(1.0); colors.push_back(0.0); colors.push_back(0.0);
	colors.push_back(0.0); colors.push_back(1.0); colors.push_back(0.0);
	colors.push_back(0.0); colors.push_back(0.0); colors.push_back(1.0);
	colors.push_back(1.0); colors.push_back(0.0); colors.push_back(1.0);

	indices.push_back(0); indices.push_back(1); indices.push_back(2);
	indices.push_back(2); indices.push_back(3); indices.push_back(1);
}

void Plane::afficher(ofMatrix4x4 projection, ofMatrix4x4 modelView)
{
	if(useTexture)
		{
			Shader texShade("Shaders/shaderTexture.vert", "Shaders/shaderTexture.frag");
			texShade.charger();
			glUseProgram(texShade.getProgramID());

			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, vertices.data());
			glEnableVertexAttribArray(0);

			glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, colors.data());
			glEnableVertexAttribArray(1);

			GLuint elementArrayBuffer;
			glGenBuffers(1, &elementArrayBuffer);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementArrayBuffer);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices[0]) * indices.size(), indices.data(), GL_STATIC_DRAW);
		
			glUniformMatrix4fv(glGetUniformLocation(texShade.getProgramID(), "projection"), 1, GL_FALSE, projection.getPtr());
			glUniformMatrix4fv(glGetUniformLocation(texShade.getProgramID(), "modelview"), 1, GL_FALSE, modelView.getPtr());
		

			glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, texCoords.data());
			glEnableVertexAttribArray(2);

			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, texture);
			glUniform1i(glGetUniformLocation(texShade.getProgramID(), "ourTexture1"), 0);

			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
			glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);

			glDisableVertexAttribArray(2);
			glDisableVertexAttribArray(1);
			glDisableVertexAttribArray(0);
			glUseProgram(0);
		}
	else
	{
		glUseProgram(shader->getProgramID());
		
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, vertices.data());
			glEnableVertexAttribArray(0);

			glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, colors.data());
			glEnableVertexAttribArray(1);

			GLuint elementArrayBuffer;
			glGenBuffers(1, &elementArrayBuffer);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementArrayBuffer);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices[0]) * indices.size(), indices.data(), GL_STATIC_DRAW);
		
			glUniformMatrix4fv(glGetUniformLocation(shader->getProgramID(), "projection"), 1, GL_FALSE, projection.getPtr());
			glUniformMatrix4fv(glGetUniformLocation(shader->getProgramID(), "modelview"), 1, GL_FALSE, modelView.getPtr());
		
		
			glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);

			glDisableVertexAttribArray(1);
			glDisableVertexAttribArray(0);
		glUseProgram(0);
	}
}

void Plane::addTexture(const string& texPath)
{
	ofImage image;
	image.loadImage(texPath);
	image.draw(0.0, 0.0);

	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image.width, image.height, 0, GL_RGB, GL_UNSIGNED_BYTE, image.getPixels());
	glGenerateMipmap(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, 0);

	useTexture = true;
	texCoords.push_back(1.0f); texCoords.push_back(1.0f);
	texCoords.push_back(1.0f); texCoords.push_back(0.0f);
	texCoords.push_back(0.0f); texCoords.push_back(0.0f);
	texCoords.push_back(0.0f); texCoords.push_back(1.0f);
}

Plane::~Plane(void)
{
}
