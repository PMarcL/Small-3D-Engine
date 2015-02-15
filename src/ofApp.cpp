#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofBackground(0);
	ofSetFrameRate(60);
	ofHideCursor();
	m_centreXFenetre = ofGetWindowWidth() * 0.5;
	m_centreYFenetre = ofGetWindowHeight() * 0.5;
	mouseX = m_centreXFenetre;
	mouseY = m_centreYFenetre;
	angleChampDeVision = 70.0;
	m_angle = 0.0;
	m_pause = false;
	m_projection.makePerspectiveMatrix(angleChampDeVision, (double)ofGetWindowWidth()/ofGetWindowHeight(), 1.0, FAR_PLANE_DISTANCE);
	m_modelview.makeIdentityMatrix();
	musiqueAmbiance.loadSound("Musique/november.mp3");
	musiqueAmbiance.setLoop(true);
	musiqueAmbiance.play();
	sfxAmbiance.loadSound("SFX/wind.wav");
	sfxAmbiance.setLoop(true);
	sfxAmbiance.setVolume(0.5);
	sfxAmbiance.play();
	glEnable(GL_DEPTH_TEST);

	mouseHandler = new MousePositionHandler();
	m_camera = Camera(ofVec3f(6, 6, 6), ofVec3f(0, 0, 0), ofVec3f(0, 1, 0), 0.4, 1.0, mouseHandler);
	m_shader = Shader("Shaders/shader3D.vert", "Shaders/shader3D.frag");
	m_shader.charger();
	floor = Plane(1000, &m_shader, 20, 20);
	roof = Plane(1000, &m_shader, 100, 100);
	m_axes = Axes(30, &m_shader);
	wave = new Shader("Shaders/waveShader.vert", "Shaders/waveShader.frag");
	wave->charger();
	ocean = Plane(1000, wave, 100, 100);
	ocean.ajouterTexture("Textures/water1.jpg");
	ocean.ajouterTexture("Textures/water2.jpg");
	ocean.utiliserTextures(true);
	ocean.setShader(wave);
	ocean.setRatioTextureParCarre(0.2);
	
	floor.ajouterTexture("Textures/rock.jpg");
	floor.genereHauteursAleatoire(-20.0, -5.0);
	floor.utiliserTextures(true);
	floor.setShader(new Shader("Shaders/shaderTexture.vert", "Shaders/shaderTexture.frag"));
	roof.ajouterTexture("Textures/rock.jpg");
	roof.genereHauteursAleatoire(100, 200);
	roof.utiliserTextures(true);
	roof.setShader(new Shader("Shaders/shaderTexture.vert", "Shaders/shaderTexture.frag"));
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
	m_camera.lookAt(m_modelview);
	//Sauvegarde de la matrice modelview
	ofMatrix4x4 sauvegardeModelview = m_modelview;
	m_axes.afficher(m_projection, m_modelview);
	floor.afficher(m_projection, m_modelview);
	roof.afficher(m_projection, m_modelview);
	m_modelview.glTranslate(1000, -10, 0);
	ocean.afficher(m_projection, m_modelview);
	Cube cube(2.0, &m_shader);
	m_modelview = sauvegardeModelview;
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
			musiqueAmbiance.setPaused(!(musiqueAmbiance.getIsPlaying()));
			sfxAmbiance.setPaused(!(sfxAmbiance.getIsPlaying()));
		}else{
			m_pause = true;
			ofShowCursor();
			musiqueAmbiance.setPaused(musiqueAmbiance.getIsPlaying());
			sfxAmbiance.setPaused(sfxAmbiance.getIsPlaying());
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
	m_projection.makePerspectiveMatrix(angleChampDeVision, (double)ofGetWindowWidth()/ofGetWindowHeight(), 1.0, FAR_PLANE_DISTANCE);
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