#pragma once

#include "ofMain.h"

class Courbe
{
public:
	Courbe(void);
	Courbe(ofVec3f o, ofVec3f c1, ofVec3f c2, ofVec3f d)
		:origine(o), destination(d), controle1(c1), controle2(c2)
	{}
	~Courbe(void);

	ofVec3f calculerBezier(float t);

private:

	ofVec3f origine;
	ofVec3f destination;
	ofVec3f controle1;
	ofVec3f controle2;

};

