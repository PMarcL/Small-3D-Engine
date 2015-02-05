#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofBackground(0);
	ofSetFrameRate(60);
	ofHideCursor();

	//Taille de la fenêtre (defaut d'Openframeworks: 1024x768)
	m_largeurFenetre = 1024;
	m_hauteurFenetre = 768;
	ofSetWindowShape(m_largeurFenetre, m_hauteurFenetre);

	//Positionnement de la souris au centre de l'écran
	SetCursorPos(m_largeurFenetre/2 + ofGetWindowPositionX(), m_hauteurFenetre/2 + ofGetWindowPositionY());
	m_centreX = m_largeurFenetre/2;
	m_centreY = m_hauteurFenetre/2;

	//Création de la matrice de projection
	m_projection.makePerspectiveMatrix(70.0, (double)m_largeurFenetre/m_hauteurFenetre, 1.0, 100.0);

	//Création de la matrice du modelview (matrice identité)
	m_modelview.makeIdentityMatrix();

	//Activation du Depth buffer
	glEnable(GL_DEPTH_TEST);

	//Création de la caméra
	m_camera = Camera(ofVec3f(6, 6, 6), ofVec3f(0, 0, 0), ofVec3f(0, 1, 0), 0.5, 0.5);

	//Création du shader
	m_shader = Shader("Shaders/shader3D.vert", "Shaders/shader3D.frag");
	m_shader.charger();

	
	m_angle = 0.0;

	m_axes = Axes(10, "Shaders/shader3D.vert", "Shaders/shader3D.frag");
}

//--------------------------------------------------------------
void ofApp::update(){
	//Calcul de la position relative de la souris (vélocité)
	int posRelX = mouseX - m_centreX;
	int posRelY = mouseY - m_centreY;

	//Souris repositionné au centre
	SetCursorPos(m_centreX + ofGetWindowPositionX(), m_centreY + ofGetWindowPositionY());

	//Mise à jour de l'orientation de la caméra
	m_camera.orienter(posRelX, posRelY);


	//Incrémentation de l'angle
	m_angle += 4.0;

	if(m_angle >= 360.0)
		m_angle -= 360.0;
}

//--------------------------------------------------------------
void ofApp::draw(){
	//Nettoyage de la fenêtre et du Depth Buffer
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
	m_camera.deplacer(key);
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

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
	m_centreX = m_largeurFenetre/2;
	m_centreY = m_hauteurFenetre/2;
	m_projection.makePerspectiveMatrix(70.0, (double)m_largeurFenetre/m_hauteurFenetre, 1.0, 100.0);
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
