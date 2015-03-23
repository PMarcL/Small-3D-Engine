#include "Courbe.h"


Courbe::Courbe(void)
{
}


Courbe::~Courbe(void)
{
}


ofVec3f Courbe::calculerBezier(float t)
{
	float u = 1 - t;
	float tt = t * t;
	float uu = u * u;
	float ttt = t * t * t;
	float uuu = u * u * u;
	ofVec3f sommet = uuu * origine;
	sommet += 3 * uu * t * controle1;
	sommet += 3 * u * tt * controle2;
	sommet += ttt * destination;
	return sommet;
}