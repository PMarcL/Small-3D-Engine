#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "Shader.h"
#include "camera.h"
#include "Axes.h"
#include "MousePositionHandler.h"
#include "Paysage.h"
#include "MusiqueSFX.h"
#include "CubeMap.h"
#include "Lumiere.h"
#include "GraphScene.h"
#include "NoeudMesh.h"
#include "NoeudShader.h"
#include "NoeudMateriau.h"
#include "GenerateurMesh.h"
#include "EditeurMesh.h"
#include "EffetPleinEcran.h"
#include "Framebuffer.h"
#include "PrimitiveGeometrique.h"

#include <stack>

const static float VITESSE_ROTATION_DEFAUT = 2.0;
const static float VITESSE_CAMERA_DEFAUT = 3.0;
const static float FAR_PLANE_DISTANCE = 10000.0;
const static float VERTIGO_DEGREE_PAR_FRAME = 1.0;
const static float ANGLE_VISION_NORMAL = 70.0;
const static float RAYON_DE_SELECTION = 50.0;
const static float DIMENSION_PAR_DEFAUT = 20.0f;
const static int NB_MAX_PRIMITIVE = 5;
const static int NB_MAX_MATERIAU = 21;

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
		

		~ofApp();

	private:
		void configurerUI();
		void zoomIn();
		void zoomOut();
		void pushMatrix();
		void popMatrix();
		void pauseToggled(bool & paused);
		void vertigoToggled(bool & enabled);
		void effetBrouillardToggled(bool & enabled);
		void effetNoirEtBlancToggled(bool & enabled);
		void effetLignesToggled(bool & enabled);
		void lampeDePocheToggled(bool & enabled);
		void vitesseCameraChanged(float& vitesse);
		void primitiveChanged(int& primitive);
		void ofApp::materiauChanged(int& materiau);
		ofVec3f getPositionDevantCamera();

		stack<ofMatrix4x4> matrices;
		Shader shaderOrigine;
		Shader shaderTex;
		Camera camera;
		Axes origineDuMonde;
		ofMatrix4x4 projection;
		ofMatrix4x4 model;
		ofMatrix4x4 view;
		MusiqueSFX son;
		Paysage paysage;
		CubeMap cubeMap;
		Lumiere lumiere;
		EffetPleinEcran effetPleinEcran;

		PRIMITIVES primitiveSelectionnee;
		MATERIAUX materiauSelectionne;
		GraphScene* graphScene;
		NoeudShader* shaderPrimitives;
		EditeurMesh editeurMesh;
		NoeudMateriau* noeudMateriau;
		Framebuffer fbo;

		int centreXFenetre;
		int centreYFenetre;
		int nbCaptureEcran;
		float angleChampDeVision;
		MousePositionHandler* mouseHandler;

		bool showMenu;
		ofxFloatSlider vitesseCamera;
		ofxIntSlider typePrimitive;
		ofxIntSlider typeMateriau;
		ofxToggle vertigoEnFonction;
		ofxToggle paused;
		ofxToggle lampeDePoche;
		ofxToggle effetBrouillard;
		ofxToggle effetNoirEtBlanc;
		ofxToggle effetLignes;
		ofxLabel guiMessage;
		ofxLabel fps;
		ofxLabel usageMessage;
		ofxLabel usageMessage2;
		ofxLabel usageMessage3;
		ofxLabel usageMessage4;
		ofxLabel usageMessage5;
		ofxLabel usageMessage6;
		ofxLabel usageMessage7;
		ofxLabel usageMessage8;
		ofxLabel usageMessage9;
		ofxLabel usageMessage10;
		ofxLabel usageMessage11;
		ofxPanel gui;
		ofxLabel primitivesMessage;

		Shader shaderLampe;
		PrimitiveGeometrique positionLampe;
		PrimitiveGeometrique positionPonctuelle;
};
