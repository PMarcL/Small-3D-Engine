#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	
	ofBackground(0);
	ofSetFrameRate(60);
	ofHideCursor();
	
	centreXFenetre = ofGetWindowWidth() * 0.5;
	centreYFenetre = ofGetWindowHeight() * 0.5;
	mouseX = centreXFenetre;
	mouseY = centreYFenetre;
	angleChampDeVision = ANGLE_VISION_NORMAL;
	nbCaptureEcran = 0;
	showMenu = true;
	paused = false;
	
	projection.makePerspectiveMatrix(angleChampDeVision, (double)ofGetWindowWidth()/ofGetWindowHeight(), 1.0, FAR_PLANE_DISTANCE);
	model.makeIdentityMatrix();
	son.jouerMusiqueEtAmbiance();
	
	mouseHandler = new MousePositionHandler();
	camera = Camera(ofVec3f(6, 6, 6), ofVec3f(0, 0, 0), ofVec3f(0, 1, 0), 0.4, 1.50, mouseHandler);
	shaderOrigine = Shader("Shaders/shader3D.vert", "Shaders/shader3D.frag");
	shaderOrigine.charger();
	origineDuMonde = Axes(30, &shaderOrigine);

	shaderTex = Shader("Shaders/shaderTexture.vert", "Shaders/shaderTexture.frag");
	shaderTex.charger();
	this->configurerUI();

	cubeMap = CubeMap(100, &shaderTex, 
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
		camera.update();

		if(vertigoEnFonction && camera.isMovingForward())
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
	camera.lookAt(view);
	lumiere.setPositionVue(camera.getPosition());

	pushMatrix();
		model.glTranslate(camera.getPosition().x, camera.getPosition().y, camera.getPosition().z);
		cubeMap.afficher(projection, model, view);
	popMatrix();

	pushMatrix();
		origineDuMonde.afficher(projection, model, view);
		paysage.afficher(projection, model, view, lumiere);
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
		camera.setMoveForward(true);
	else if(key == 's' || key == 'S')
		camera.setMoveBackward(true);
	else if(key == 'a' || key == 'A')
		camera.setMoveLeft(true);
	else if(key == 'd' || key == 'D')
		camera.setMoveRight(true);
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
		camera.setMoveForward(false);
	else if(key == 's' || key == 'S')
		camera.setMoveBackward(false);
	else if(key == 'a' || key == 'A')
		camera.setMoveLeft(false);
	else if(key == 'd' || key == 'D')
		camera.setMoveRight(false);
	else if(key == 'p' || key == 'P'){
		paused = !paused;
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
	centreXFenetre = w * 0.5;
	centreYFenetre = h * 0.5;
	projection.makePerspectiveMatrix(angleChampDeVision, (double)ofGetWindowWidth()/ofGetWindowHeight(), 1.0, FAR_PLANE_DISTANCE);
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
	gui.add(vertigoEnFonction.setup("v - Effet vertigo", false));
	gui.add(vitesseCamera.setup("vitesse de deplacement", VITESSE_CAMERA_DEFAUT, 0.5, 10));
	gui.add(quantiteIntensiteLumiere.setup("lumiere ambiante", lumiere.getIntensiteLumiereAmbiante(), 0.0, 1.0));
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
		projection.makePerspectiveMatrix(angleChampDeVision, (double)ofGetWindowWidth() / ofGetWindowHeight(), 1.0, FAR_PLANE_DISTANCE);
		vitesseCamera = 1;
	}
}

void ofApp::speedChanged(float &speed) {
	camera.setVitesse(speed);
}

void ofApp::intensiteLumiereChangee(float & intensite)
{
	lumiere.setIntensiteLumiereAmbiante(intensite);
}

void ofApp::zoomIn()
{
	if(angleChampDeVision < 170.0)
	{
		angleChampDeVision += VERTIGO_DEGREE_PAR_FRAME;
		projection.makePerspectiveMatrix(angleChampDeVision, (double)ofGetWindowWidth()/ofGetWindowHeight(), 1.0, FAR_PLANE_DISTANCE);
	}
}

void ofApp::zoomOut()
{
	if(angleChampDeVision > 1.0)
	{
		angleChampDeVision -= VERTIGO_DEGREE_PAR_FRAME;
		projection.makePerspectiveMatrix(angleChampDeVision, (double)ofGetWindowWidth()/ofGetWindowHeight(), 1.0, FAR_PLANE_DISTANCE);
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