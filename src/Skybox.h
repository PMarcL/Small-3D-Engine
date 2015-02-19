#pragma once

#include "Plane.h"
#include "ofMain.h"
#include "Shader.h"
#include "camera.h"
#include "Cube.h"

const static int NB_SURFACES_SKYBOX = 6;

class Skybox
{
public:
	Skybox() {}
	Skybox(const string& emplacementTex, Shader* shader);
	~Skybox() { glDeleteTextures(1, &texCube);}

	void afficher(ofMatrix4x4 projection, ofMatrix4x4 modelView, Camera cam);

private:
	Shader* shader;
	GLuint texCube;

};

