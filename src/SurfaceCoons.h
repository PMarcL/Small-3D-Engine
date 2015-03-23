#pragma once

#include "ofMain.h"
#include "Mesh.h"
#include "Courbe.h"
#include "Shader.h"

class SurfaceCoons
{
public:
	SurfaceCoons();
	SurfaceCoons(int precision, float ratioTextureParCarre, Courbe c1, Courbe c2, Courbe c3, Courbe c4);
	~SurfaceCoons(void){}

	void afficher();

private:
	void triangularisationSurface(int Precision);
	void calculerNormales();
	ofVec3f positionSurface(float u, float v);
	ofVec3f blerp(float u, float v);
	ofVec3f lerp_u(float u, float v);
	ofVec3f lerp_v(float u, float v);

	vector<ofVec3f> vertices;
	vector<ofVec3f> normals;
	vector<GLfloat> texCoords;
	vector<Courbe> courbes;
	float ratioTextureParCarre;
	Mesh mesh;
};

