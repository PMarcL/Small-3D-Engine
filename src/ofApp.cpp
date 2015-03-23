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
	nbCaptureEcran = 0;
	m_angle = 0.0;
	intensiteLumiere = QUANTITE_LUMIERE_DEFAUT;
	showMenu = true;
	paused = false;
	
	m_projection.makePerspectiveMatrix(angleChampDeVision, (double)ofGetWindowWidth()/ofGetWindowHeight(), 1.0, FAR_PLANE_DISTANCE);
	model.makeIdentityMatrix();
	son.jouerMusiqueEtAmbiance();
	
	mouseHandler = new MousePositionHandler();
	m_camera = Camera(ofVec3f(6, 6, 6), ofVec3f(0, 0, 0), ofVec3f(0, 1, 0), 0.4, 1.50, mouseHandler);
	m_shader = Shader("Shaders/shader3D.vert", "Shaders/shader3D.frag");
	m_shader.charger();
	m_axes = Axes(30, &m_shader);
	m_cube = Cube(2.0, &m_shader);
	m_tretraedre = Tetraedre(8.0, &m_shader);
	m_octaedre = Octaedre(2.0, &m_shader);

	m_shaderTex = Shader("Shaders/shaderTexture.vert", "Shaders/shaderTexture.frag");
	m_shaderTex.charger();
	this->configurerUI();

	m_cubeMap = CubeMap(100, &m_shaderTex, 
		"Textures/ciel/XN.jpg",
		"Textures/ciel/XP.jpg",
		"Textures/ciel/YN.jpg",
		"Textures/ciel/YP.jpg",
		"Textures/ciel/ZN.jpg",
		"Textures/ciel/ZP.jpg");
}

//--------------------------------------------------------------
void ofApp::update(){
	if(!paused){
		mouseHandler->update(mouseX, mouseY);
		m_camera.update();
		if (rotationActive) {
			m_angle += vitesseRotation;
		}
		
		if(vertigoEnFonction && m_camera.isMovingForward())
			zoomIn();
		else if(vertigoEnFonction && angleChampDeVision > ANGLE_VISION_NORMAL)
			zoomOut();
		fps = to_string(ofGetFrameRate());
	}
}

//--------------------------------------------------------------
void ofApp::draw(){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	
	m_camera.lookAt(view);

	pushMatrix();
		model.glTranslate(m_camera.getPosition().x, m_camera.getPosition().y, m_camera.getPosition().z);
		m_cubeMap.afficher(m_projection, model, view);
	popMatrix();
	
	pushMatrix();
		model.glTranslate(30.0f, 0.0f, 100.0f);
		m_tretraedre.afficher(m_projection, model, view);
		for (float i = 0; i < 360; i += 30){
			pushMatrix();
				model.glRotate(i + m_angle, 0.0f, 1.0f, 0.0f);
				model.glTranslate(30.0f, 0.0f, 0.0f);
				m_octaedre.afficher(m_projection, model, view);
			popMatrix();
		}
		m_octaedre.afficher(m_projection, model, view);
	popMatrix();

	pushMatrix();
		m_axes.afficher(m_projection, model, view);
		paysage.afficher(m_projection, model, view, DIRECTION_LUMIERE, COUL_LUMIERE, intensiteLumiere);
	popMatrix();

	pushMatrix();
		Cube cube(2.0, &m_shader);
		model.glRotate(m_angle, 0, 1, 0);
		for (int i = 0; i < 4; i++){
			cube.afficher(m_projection, model, view);
			model.glTranslate(3, 0, 0);
		}
	popMatrix();
	
	glDisable(GL_LIGHTING);
	glDisable(GL_DEPTH_TEST);
	if (showMenu) {
		gui.draw();
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
	else if(key == OF_KEY_UP)
		zoomIn();
	else if(key == OF_KEY_DOWN)
		zoomOut();
	else if(key == 'v' || key == 'V')
		vertigoEnFonction = !vertigoEnFonction;
	else if(key == 'i' || key == 'I')
	{
		ofImage fenetre;
		fenetre.grabScreen(0,0, ofGetWindowWidth(), ofGetWindowHeight());
		string nb = to_string(nbCaptureEcran);
		fenetre.saveImage("Captures/capture" + nb +".png");
		nbCaptureEcran++;
	}
	else if (key == 'm' || key == 'M')
		showMenu = !showMenu;
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
		paused = !paused;
	} else if(key == 'r' || key == 'r'){
		rotationActive = !rotationActive;
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

void ofApp::configurerUI() {
	paused.addListener(this, &ofApp::pauseToggled);
	vertigoEnFonction.addListener(this, &ofApp::vertigoToggled);
	vitesseCamera.addListener(this, &ofApp::speedChanged);
	quantiteIntensiteLumiere.addListener(this, &ofApp::intensiteLumiereChangee);
	
	gui.setup("Parametres");
	gui.add(guiMessage.setup("", "Pour acceder au menu \navec la souris, \nvous devez entrer \nla touche 'p'", 200, 120));
	gui.add(paused.setup("p - Pause", false));
	gui.add(rotationActive.setup("r - Rotation primitives", true));
	gui.add(vertigoEnFonction.setup("v - Effet vertigo", false));
	gui.add(vitesseCamera.setup("vitesse de deplacement", VITESSE_CAMERA_DEFAUT, 0.5, 10));
	gui.add(vitesseRotation.setup("vitesse de rotation", VITESSE_ROTATION_DEFAUT, 0.5, 5));
	gui.add(quantiteIntensiteLumiere.setup("lumiere ambiante", intensiteLumiere, 0.0, 1.0));
	gui.add(fps.setup("fps", ""));
	gui.add(usageMessage.setup("Autres fonctions", "\nw - avancer\ns - reculer\na - bouger a gauche\nd - bouger a droite\ni capture d'ecran\nf - mode plein ecran\nm - afficher menu", 200, 220));
}

void ofApp::pauseToggled(bool &paused) {
	if (paused){
		ofShowCursor();
		son.actionnerPauseMusiqueEtAmbiance();
	}
	else{
		ofHideCursor();
		mouseHandler->resetCusor();
		son.desactionnerPauseMusiqueEtAmbiance();
	}
}

void ofApp::vertigoToggled(bool &enabled) {
	if (enabled){
		vitesseCamera = 0.8;
	}
	else{
		angleChampDeVision = ANGLE_VISION_NORMAL;
		m_projection.makePerspectiveMatrix(angleChampDeVision, (double)ofGetWindowWidth() / ofGetWindowHeight(), 1.0, FAR_PLANE_DISTANCE);
		vitesseCamera = 1;
	}
}

void ofApp::speedChanged(float &speed) {
	m_camera.setVitesse(speed);
}

void ofApp::intensiteLumiereChangee(float & intensite)
{
	intensiteLumiere = intensite;
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

void ofApp::pushMatrix()
{
	matrices.push(model);
}

void ofApp::popMatrix()
{
	model = matrices.top();
	matrices.pop();
}

ofApp::~ofApp() {
	delete mouseHandler;
}