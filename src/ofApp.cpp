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
	angleChampDeVision = ANGLE_VISION_NORMAL;
	m_angle = 0.0;
	m_pause = false;
	cameraAvance = false;
	vertigoEnFonction = false;
	m_projection.makePerspectiveMatrix(angleChampDeVision, (double)ofGetWindowWidth()/ofGetWindowHeight(), 1.0, FAR_PLANE_DISTANCE);
	model.makeIdentityMatrix();
	son.jouerMusiqueEtAmbiance();
	glEnable(GL_DEPTH_TEST);

	mouseHandler = new MousePositionHandler();
	m_camera = Camera(ofVec3f(6, 6, 6), ofVec3f(0, 0, 0), ofVec3f(0, 1, 0), 0.4, 1.0, mouseHandler);
	m_shader = Shader("Shaders/shader3D.vert", "Shaders/shader3D.frag");
	m_shader.charger();
	m_axes = Axes(30, &m_shader);
	perso = ModeleOBJ("Models/dude.obj");
	m_cube = Cube(2.0, &m_shader);

	m_shaderTex = Shader("Shaders/shaderTexture.vert", "Shaders/shaderTexture.frag");
	m_shaderTex.charger();
	
	m_cubeMap = CubeMap(100, &m_shaderTex, 
		"Textures/ciel/XN.jpg",
		"Textures/ciel/XP.jpg",
		"Textures/ciel/YN.jpg",
		"Textures/ciel/YP.jpg",
		"Textures/ciel/ZN.jpg",
		"Textures/ciel/ZN.jpg");
}

//--------------------------------------------------------------
void ofApp::update(){
	if(!m_pause){
		mouseHandler->update(mouseX, mouseY);
		m_camera.update();
		m_angle += ROTATION_SPEED;
		if(vertigoEnFonction && cameraAvance)
			zoomIn();
		else if(vertigoEnFonction && angleChampDeVision > ANGLE_VISION_NORMAL)
			zoomOut();
	}
}

//--------------------------------------------------------------
void ofApp::draw(){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	m_camera.lookAt(view);
	//	pushMatrix
	ofMatrix4x4 pushModel = model;
	model.glTranslate(m_camera.getPosition().x, m_camera.getPosition().y, m_camera.getPosition().z);
	m_cubeMap.afficher(m_projection, model, view);
	model = pushModel;
	m_axes.afficher(m_projection, model, view);
	paysage.afficher(m_projection, model, view, DIRECTION_LUMIERE);
	model.glTranslate(50, 0, 0);
	model.glScale(10,10,10);
	perso.afficher(m_projection, model, view, DIRECTION_LUMIERE);
	Cube cube(2.0, &m_shader);
	model = pushModel;
	model.glRotate(m_angle, 0, 1, 0);
	for(int i = 0; i < 4; i++){
		cube.afficher(m_projection, model, view);
		model.glTranslate(3, 0, 0);
	}
	// popMatrix
	model = pushModel;
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	if(key == 'w' || key == 'W')
	{
		m_camera.setMoveForward(true);
		cameraAvance = true;
	}
	else if(key == 's' || key == 'S')
		m_camera.setMoveBackward(true);
	else if(key == 'a' || key == 'A')
		m_camera.setMoveLeft(true);
	else if(key == 'd' || key == 'D')
		m_camera.setMoveRight(true);
	else if(key == OF_KEY_UP)
		zoomIn();
	else if(key == OF_KEY_DOWN)
		zoomOut();
	else if(key == 'v' || key == 'V')
	{
		vertigoEnFonction = !vertigoEnFonction;
		m_camera.setVitesse(0.8);
		if(!vertigoEnFonction)
		{
			angleChampDeVision = ANGLE_VISION_NORMAL;
			m_projection.makePerspectiveMatrix(angleChampDeVision, (double)ofGetWindowWidth()/ofGetWindowHeight(), 1.0, FAR_PLANE_DISTANCE);
			m_camera.setVitesse(1.0);
		}
	}
	else if(key == 'i' || key == 'I')
	{
		ofImage screen;
		screen.grabScreen(0,0, ofGetWindowWidth(), ofGetWindowHeight());
		screen.saveImage("screenShot.png");

	}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
	if(key == 'w' || key == 'W')
	{
		m_camera.setMoveForward(false);
		cameraAvance = false;
	}
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
			son.desactionnerPauseMusiqueEtAmbiance();
		}else{
			m_pause = true;
			ofShowCursor();
			son.actionnerPauseMusiqueEtAmbiance();
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

void ofApp::zoomIn()
{
	if(angleChampDeVision < 170.0)
	{
		angleChampDeVision += VERTIGO_DEGREE_PAR_FRAME;
		m_projection.makePerspectiveMatrix(angleChampDeVision, (double)ofGetWindowWidth()/ofGetWindowHeight(), 1.0, FAR_PLANE_DISTANCE);
	}
}

void ofApp::zoomOut()
{
	if(angleChampDeVision > 1.0)
	{
		angleChampDeVision -= VERTIGO_DEGREE_PAR_FRAME;
		m_projection.makePerspectiveMatrix(angleChampDeVision, (double)ofGetWindowWidth()/ofGetWindowHeight(), 1.0, FAR_PLANE_DISTANCE);
	}
}

ofApp::~ofApp() {
	delete mouseHandler;
}