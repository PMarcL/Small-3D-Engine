#include "SurfaceCoons.h"


SurfaceCoons::SurfaceCoons(void)
{
}

SurfaceCoons::SurfaceCoons(int precision, float ratioTextureParCarre, Courbe c1, Courbe c2, Courbe c3, Courbe c4)
	:ratioTextureParCarre(ratioTextureParCarre/precision)
{
	courbes.push_back(c1);
	courbes.push_back(c2);
	courbes.push_back(c3);
	courbes.push_back(c4);

	triangularisationSurface(precision);
	calculerNormales();

	mesh = Mesh(vertices, vector<ofVec3f>(), texCoords, normals, vector<GLuint>(), vertices.size());
}

void SurfaceCoons::triangularisationSurface(int precision)
{
	float du = 1.0/(float)precision;
	float dv = 1.0/(float)precision;

	for(int j = 1; j < precision; j++)
	{
		for(int i = 1; i < precision; i++)
		{
			// Triangle 1, position et coordonnées de texture
			ofVec3f vertex1 = positionSurface((float)(i - 1) * du, (float)(j - 1) * dv);
			ofVec3f vertex2 = positionSurface((float)(i - 1) * du, (float)(j) * dv);
			ofVec3f vertex3 = positionSurface((float)(i) * du, (float)(j - 1) * dv);
			vertices.push_back(vertex1); texCoords.push_back(i * ratioTextureParCarre); texCoords.push_back(j * ratioTextureParCarre);
			vertices.push_back(vertex2); texCoords.push_back(i * ratioTextureParCarre); texCoords.push_back((j + 1) * ratioTextureParCarre);
			vertices.push_back(vertex3); texCoords.push_back((i + 1) * ratioTextureParCarre); texCoords.push_back(j * ratioTextureParCarre);

			// Triangle 2, position et coordonnées de texture
			vertices.push_back(vertex3); texCoords.push_back((i + 1) * ratioTextureParCarre); texCoords.push_back(j * ratioTextureParCarre);
			vertices.push_back(vertex2); texCoords.push_back(i * ratioTextureParCarre); texCoords.push_back((j + 1) * ratioTextureParCarre);
			ofVec3f vertex4 = positionSurface((float)(i) * du, (float)(j) * dv);
			vertices.push_back(vertex4); texCoords.push_back((i + 1) * ratioTextureParCarre); texCoords.push_back((j + 1) * ratioTextureParCarre);
		}
	}
}

ofVec3f SurfaceCoons::positionSurface(float u, float v)
{
	return lerp_u(u, v) + lerp_v(u, v) - blerp(u, v);
}

ofVec3f SurfaceCoons::blerp(float u, float v)
{
	return ((1.0 - u)*(1.0 - v) * courbes[0].calculerBezier(u)) + (u*(1.0 - v) * courbes[1].calculerBezier(u)) + 
		((1.0 - u)*v * courbes[2].calculerBezier(v)) + (u*v * courbes[3].calculerBezier(v));
}

ofVec3f SurfaceCoons::lerp_u(float u, float v)
{
	return (1.0 - v) * courbes[0].calculerBezier(u) + v * courbes[1].calculerBezier(u);
}

ofVec3f SurfaceCoons::lerp_v(float u, float v)
{
	return (1.0 - u) * courbes[2].calculerBezier(v) + u * courbes[3].calculerBezier(v);
}

void SurfaceCoons::calculerNormales()
{
	normals.resize(vertices.size());
	for(int i = 0; i < vertices.size() / 3; i++)
	{
		GLuint ia = i*3;
		GLuint ib = i*3 + 1;
		GLuint ic = i*3 + 2;
		ofVec3f normal = ofVec3f(vertices[ib]) - ofVec3f(vertices[ia]);
		normal.cross(ofVec3f(vertices[ic]) - ofVec3f(vertices[ia]));
		normal.normalize();
		normals[ia] = normals[ib] = normals[ic] = normal;
	}
}

void SurfaceCoons::afficher()
{
	//glEnable(GL_CULL_FACE);
	//glCullFace(GL_BACK);

	mesh.dessiner();

	//glDisable(GL_CULL_FACE);
}