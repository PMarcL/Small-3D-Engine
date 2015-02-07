#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofBackground(0);
	ofSetFrameRate(60);
	ofHideCursor();
	m_largeurFenetre = ofGetWindowWidth();
	m_hauteurFenetre = ofGetWindowHeight();
	glEnable(GL_DEPTH_TEST);
	mouseHandler = new MousePositionHandler(m_largeurFenetre/2 + ofGetWindowPositionX(), m_hauteurFenetre/2 + ofGetWindowPositionY());
	m_projection.makePerspectiveMatrix(70.0, (double)m_largeurFenetre/m_hauteurFenetre, 1.0, 100.0);
	m_modelview.makeIdentityMatrix();
	m_camera = Camera(ofVec3f(6, 6, 6), ofVec3f(0, 0, 0), ofVec3f(0, 1, 0), 0.4, 0.4, mouseHandler);
	m_shader = Shader("Shaders/shader3D.vert", "Shaders/shader3D.frag");
	m_shader.charger();
	m_angle = 0.0;
	m_axes = Axes(10, "Shaders/shader3D.vert", "Shaders/shader3D.frag");
	m_pause = false;
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

	//Afficage des axes
	m_axes.afficher(m_projection, m_modelview);

	//Déclaration d'un objet cube
	Cube cube(2.0, "Shaders/shader3D.vert", "Shaders/shader3D.frag");

	//Affichage de 4 cubes qui tournent autour de l'axe des Y
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
	else if(key == 'p' || key == 'P'){
		if(m_pause){
			m_pause = false;
			ofHideCursor();
			mouseHandler->setCursorPos(m_largeurFenetre/2 + ofGetWindowPositionX(), m_hauteurFenetre/2 + ofGetWindowPositionY());
		}else{
			m_pause = true;
			ofShowCursor();
		}
	}
	else if(key == 'f' || key == 'F'){
		ofToggleFullscreen();
		mouseHandler->setCursorPos(m_largeurFenetre/2 + ofGetWindowPositionX(), m_hauteurFenetre/2 + ofGetWindowPositionY());		
	}
		
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
	//Note: pas encore testé
	m_largeurFenetre = w;
	m_hauteurFenetre = h;
	m_projection.makePerspectiveMatrix(70.0, (double)m_largeurFenetre/m_hauteurFenetre, 1.0, 100.0);
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