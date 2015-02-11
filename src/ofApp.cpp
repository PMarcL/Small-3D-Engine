#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofBackground(0);
	ofSetFrameRate(60);
	ofHideCursor();
	m_centreXFenetre = ofGetWindowWidth() * 0.5;
	m_centreYFenetre = ofGetWindowHeight() * 0.5;
	glEnable(GL_DEPTH_TEST);
	mouseHandler = new MousePositionHandler();
	m_projection.makePerspectiveMatrix(70.0, (double)ofGetWindowWidth()/ofGetWindowHeight(), 1.0, 1000.0);
	m_modelview.makeIdentityMatrix();
	m_camera = Camera(ofVec3f(6, 6, 6), ofVec3f(0, 0, 0), ofVec3f(0, 1, 0), 0.4, 1.0, mouseHandler);
	m_shader = Shader("Shaders/shader3D.vert", "Shaders/shader3D.frag");
	m_shader.charger();
	m_angle = 0.0;
	floor = Plane(500, &m_shader, 10, 10);
	//floor.addTexture("Textures/grass2.jpg");
	m_axes = Axes(10, &m_shader);
	m_pause = false;

	//Pour corriger notre problème d'affichage au démarrage
	mouseX = m_centreXFenetre;
	mouseY = m_centreYFenetre;

	//floor.genereHauteursAleatoire();
}

//--------------------------------------------------------------
void ofApp::update(){
	if(!m_pause){
		mouseHandler->update(mouseX, mouseY);
		m_camera.update();
		m_angle += ROTATION_SPEED;
	}
}

//--------------------------------------------------------------
void ofApp::draw(){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//Placement de la caméra
	m_camera.lookAt(m_modelview);
	//Sauvegarde de la matrice modelview
	ofMatrix4x4 sauvegardeModelview = m_modelview;
	
	m_axes.afficher(m_projection, m_modelview);
	floor.afficher(m_projection, m_modelview);
	Cube cube(2.0, &m_shader);
	m_modelview.glRotate(m_angle, 0, 1, 0);
	for(int i = 0; i < 4; i++){
		cube.afficher(m_projection, m_modelview);
		m_modelview.glTranslate(3, 0, 0);
	}
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	if(key == 'w' || key == 'W')
		m_camera.setMoveForward(true);
	else if(key == 's' || key == 'S')
		m_camera.setMoveBackward(true);
	else if(key == 'a' || key == 'A')
		m_camera.setMoveLeft(true);
	else if(key == 'd' || key == 'D')
		m_camera.setMoveRight(true);
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
	if(key == 'w' || key == 'W')
		m_camera.setMoveForward(false);
	else if(key == 's' || key == 'S')
		m_camera.setMoveBackward(false);
	else if(key == 'a' || key == 'A')
		m_camera.setMoveLeft(false);
	else if(key == 'd' || key == 'D')
		m_camera.setMoveRight(false);
	else if(key == 'p' || key == 'P'){
		if(m_pause){
			m_pause = false;
			ofHideCursor();
			mouseHandler->resetCusor();
		}else{
			m_pause = true;
			ofShowCursor();
		}
	}
	else if(key == 'f' || key == 'F'){
		ofToggleFullscreen();
		mouseHandler->resetCusor();	
	}
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){
	m_centreXFenetre = w * 0.5;
	m_centreYFenetre = h * 0.5;
	m_projection.makePerspectiveMatrix(70.0, (double)w/h, 1.0, 100.0);
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}


ofApp::~ofApp() {
	delete mouseHandler;
}