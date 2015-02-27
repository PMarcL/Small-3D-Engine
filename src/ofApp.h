#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "Shader.h"
#include "camera.h"
#include "Cube.h"
#include "Axes.h"
#include "MousePositionHandler.h"
#include "Paysage.h"
#include "MusiqueSFX.h"
#include "modeleOBJ.h"
#include "CubeMap.h"
#include <stack>
#include "Tetraedre.h"
#include "Octaedre.h"

const static float DEFAULT_ROTATION_SPEED = 2.0;
const static float DEFAULT_CAMERA_SPEED = 1.0;
const static float FAR_PLANE_DISTANCE = 3000.0;
const static float VERTIGO_DEGREE_PAR_FRAME = 1.0;
const static float ANGLE_VISION_NORMAL = 70.0;
const static ofVec3f DIRECTION_LUMIERE = ofVec3f(500, 1500, 300);
const static ofVec3f COUL_LUMIERE = ofVec3f(1.0, 1.0, 1.0);

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
		void zoomIn();
		void zoomOut();

		~ofApp();

	private:
		void pushMatrix();
		void popMatrix();

		stack<ofMatrix4x4> matrices;
		Shader m_shader;
		Shader m_shaderTex;
		Camera m_camera;
		Axes m_axes;
		ofMatrix4x4 m_projection;
		ofMatrix4x4 model;
		ofMatrix4x4 view;
		MusiqueSFX son;
		Paysage paysage;
		ModeleOBJ perso;
		CubeMap m_cubeMap;
		Cube m_cube;
		Tetraedre m_tretraedre;
		Octaedre m_octaedre;

		int m_centreXFenetre;
		int m_centreYFenetre;
		int nbCaptureEcran;
		float m_angle;
		float angleChampDeVision;
		float intensiteLumiere;
		MousePositionHandler* mouseHandler;
		
		void pauseToggled(bool & paused);
		void vertigoToggled(bool & enabled);
		void speedChanged(float & speed);

		bool showMenu;
		ofxFloatSlider cameraSpeed;
		ofxFloatSlider rotationSpeed;
		ofxFloatSlider quantiteIntensiteLumiere;
		ofxToggle rotationActivated;
		ofxToggle vertigoEnFonction;
		ofxToggle paused;
		ofxLabel guiMessage;
		ofxLabel fps;
		ofxLabel usageMessage;

		ofxPanel gui;
};
