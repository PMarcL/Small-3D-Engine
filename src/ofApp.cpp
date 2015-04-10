#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
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
	lampeDePoche = false;
	effetBrouillard = false;
	effetNoirEtBlanc = false;
	effetLignes = false;
	primitiveSelectionnee = CUBE;
	materiauSelectionne = RUBY;
	graphScene = new GraphScene();
	editeurMesh.setEchelle(10);
	noeudMateriau = new NoeudMateriau(MATERIAUX::RUBY);

	projection.makePerspectiveMatrix(angleChampDeVision, (double)ofGetWindowWidth()/ofGetWindowHeight(), 1.0, FAR_PLANE_DISTANCE);
	model.makeIdentityMatrix();
	son.jouerMusiqueEtAmbiance();
	
	mouseHandler = new MousePositionHandler();
	camera = Camera(ofVec3f(6, 6, 6), ofVec3f(0, 0, 0), ofVec3f(0, 1, 0), 0.4, 1.50, mouseHandler);
	shaderOrigine = Shader("Shaders/shader3D.vert", "Shaders/shader3D.frag");
	shaderOrigine.charger();
	graphScene->shaderIdOrigine = shaderOrigine.getProgramID();
	origineDuMonde = Axes(100, &shaderOrigine);

	shaderPrimitives = new NoeudShader(Shader("Shaders/shaderMateriaux.vert", "Shaders/shaderMateriaux.frag"));
	graphScene->ajouterEnfant(shaderPrimitives);
	shaderPrimitives->shader.charger();
	shaderPrimitives->ajouterEnfant(noeudMateriau);

	shaderTex = Shader("Shaders/shaderTexture.vert", "Shaders/shaderTexture.frag");
	shaderTex.charger();
	this->configurerUI();

	cubeMap = CubeMap(100, &shaderTex, 
		"Textures/ciel/XN.png",
		"Textures/ciel/XP.png",
		"Textures/ciel/YN.png",
		"Textures/ciel/YP.png",
		"Textures/ciel/ZN.png",
		"Textures/ciel/ZP.png");

	fbo.generateFBO(ofGetWindowWidth(), ofGetWindowHeight());

	shaderLampe = Shader("Shaders/shaderLumiere.vert", "Shaders/shaderLumiere.frag");
	shaderLampe.charger();

	positionLampe = PrimitiveGeometrique(OCTAEDRE, ARGENT, ofVec3f(0.0, 500.0, 0.0), 20.0);
	Projecteur lampeCentrale;
	lampeCentrale.position = positionLampe.getPosition();
	lampeCentrale.direction = ofVec3f(0.0, -1.0, 0.0);
	lampeCentrale.diffuse = ofVec3f(0.7, 0.7, 1.0);
	lampeCentrale.speculaire = ofVec3f(0.9, 0.9, 1.0);
	lampeCentrale.coneExterne = cos(ofDegToRad(30.0));
	lampeCentrale.coneInterne = cos(ofDegToRad(10.0));
	lumiere.ajouterProjecteur(lampeCentrale);

	positionPonctuelle = PrimitiveGeometrique(OCTAEDRE, ARGENT, ofVec3f(1000.0, 100.0, -200.0), 20.0);
	LumierePonctuelle lumierePonctuelle;
	lumierePonctuelle.position = positionPonctuelle.getPosition();
	lumierePonctuelle.ambiante = ofVec3f(0.3, 0.3, 0.3);
	lumierePonctuelle.diffuse = ofVec3f(0.6, 0.9, 0.6);
	lumierePonctuelle.speculaire = ofVec3f(0.9, 1.0, 0.9);
	lumierePonctuelle.constante = 0.000005;
	lumierePonctuelle.lineaire = 0.000009;
	lumierePonctuelle.quadratique = 0.000032;
	lumiere.ajouterLumierePonctuelle(lumierePonctuelle);
}

//--------------------------------------------------------------
void ofApp::update(){
	if(!paused){
		mouseHandler->update(mouseX, mouseY);
		camera.update();
		lumiere.mettreAJourLampeDePoche(camera.getPosition(), camera.getOrientation());
		//primitives.deplacerPrimitiveSelectionnee(getPositionDevantCamera());
		editeurMesh.deplacerSelection(getPositionDevantCamera());
		
		if(vertigoEnFonction && camera.isMovingForward())
			zoomIn();
		else if(vertigoEnFonction && angleChampDeVision > ANGLE_VISION_NORMAL)
			zoomOut();
		
		fps = to_string(ofGetFrameRate());
	}
}

//--------------------------------------------------------------
void ofApp::draw(){
	fbo.bind();
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_LIGHTING);
		camera.lookAt(view);
		lumiere.setPositionVue(camera.getPosition());
	
		pushMatrix();
			model.glTranslate(camera.getPosition().x, camera.getPosition().y, camera.getPosition().z);
			cubeMap.afficher(projection, model, view);
		popMatrix();
	
		graphScene->afficher(&projection, &view, &lumiere);
		
		origineDuMonde.afficher(projection, model, view);
		//primitives.afficher(projection, model, view, lumiere);
		paysage.afficher(projection, model, view, lumiere);
	
		/*pushMatrix();
			glUseProgram(shaderLampe.getProgramID());
				model.glTranslate(positionLampe.getPosition());
				glUniformMatrix4fv(glGetUniformLocation(shaderLampe.getProgramID(), "model"), 1, GL_FALSE, model.getPtr());
				glUniformMatrix4fv(glGetUniformLocation(shaderLampe.getProgramID(), "view"), 1, GL_FALSE, view.getPtr());
				glUniformMatrix4fv(glGetUniformLocation(shaderLampe.getProgramID(), "projection"), 1, GL_FALSE, projection.getPtr());
				positionLampe.afficher();
				popMatrix();
				pushMatrix();
				model.glTranslate(positionPonctuelle.getPosition());
				glUniformMatrix4fv(glGetUniformLocation(shaderLampe.getProgramID(), "model"), 1, GL_FALSE, model.getPtr());
				positionPonctuelle.afficher();
			glUseProgram(0);
		popMatrix();*/
	
	}
	fbo.unbind();

	if(effetBrouillard) {
		effetPleinEcran.activerEffetBrouillard();
	} else if(effetNoirEtBlanc) {
		effetPleinEcran.activerEffetNoirEtBlanc();
	} else if(effetLignes) {
		effetPleinEcran.activerEffetLignes();
	} else {
		effetPleinEcran.desactiverEffet();
	}
	
	effetPleinEcran.afficher(fbo.getColorTexture());
	
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
	else if(key == '1')
		effetBrouillard = !effetBrouillard;
	else if(key == '2')
		effetNoirEtBlanc = !effetNoirEtBlanc;
	else if(key == '3')
		effetLignes = !effetLignes;
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
	else if(key == 'x' || key == 'X'){
		//primitives.supprimerSelection();
		editeurMesh.supprimerSelection();
	}
	else if(key == 'q' || key == 'Q')
		lampeDePoche = !lampeDePoche;
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
	
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
	if(!paused)
	{
		if(button == OF_MOUSE_BUTTON_1){
			//primitives.selectionnerPrimitive(getPositionDevantCamera(), RAYON_DE_SELECTION);
			editeurMesh.selectionnerMesh((NoeudMesh*)graphScene->trouverMesh(getPositionDevantCamera(), RAYON_DE_SELECTION));
		}
		if(button == OF_MOUSE_BUTTON_3){
			//primitives.ajouterPrimitive(PrimitiveGeometrique(primitiveSelectionnee, materiauSelectionne, getPositionDevantCamera(), DIMENSION_PAR_DEFAUT));
			NoeudMesh* noeudMesh = new NoeudMesh(GenerateurMesh::genererPrimitive(primitiveSelectionnee, DIMENSION_PAR_DEFAUT));
			//NoeudMesh* noeudMesh = new NoeudMesh(GenerateurMesh::genererObj("Models/champignon.obj"));
			noeudMesh->matriceTransformations.glTranslate(editeurMesh.positionAEchelle(getPositionDevantCamera()));
			noeudMateriau->ajouterEnfant((Noeud*)noeudMesh);
		}
	}
}

ofVec3f ofApp::getPositionDevantCamera() {
	return camera.getPosition() + 75 * camera.getOrientation();
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
	if(!paused)
	{
		if(button == OF_MOUSE_BUTTON_1){
			//primitives.relacherPrimitiveSelectionnee();
			editeurMesh.relacherSelection();
		}
	}
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){
	centreXFenetre = w * 0.5;
	centreYFenetre = h * 0.5;
	projection.makePerspectiveMatrix(angleChampDeVision, (double)ofGetWindowWidth()/ofGetWindowHeight(), 1.0, FAR_PLANE_DISTANCE);
	fbo.generateFBO(w,h);
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
	effetBrouillard.addListener(this, &ofApp::effetBrouillardToggled);
	effetNoirEtBlanc.addListener(this, &ofApp::effetNoirEtBlancToggled);
	effetLignes.addListener(this, &ofApp::effetLignesToggled);
	lampeDePoche.addListener(this, &ofApp::lampeDePocheToggled);
	vitesseCamera.addListener(this, &ofApp::vitesseCameraChanged);
	typePrimitive.addListener(this, &ofApp::primitiveChanged);
	typeMateriau.addListener(this, &ofApp::materiauChanged);
	
	gui.setup("Parametres");
	gui.add(guiMessage.setup("", "Pour acceder au menu \navec la souris, \nvous devez entrer \nla touche 'p'", 200, 120));
	gui.add(paused.setup("p - Pause", false));
	gui.add(vertigoEnFonction.setup("v - Effet vertigo", false));
	gui.add(effetBrouillard.setup("1 - Effet brouillard", false));
	gui.add(effetNoirEtBlanc.setup("2 - Effet noir et blanc", false));
	gui.add(effetLignes.setup("3 - Effet lignes", false));
	gui.add(lampeDePoche.setup("q - Lamp de poche", false));
	gui.add(vitesseCamera.setup("vitesse de deplacement", VITESSE_CAMERA_DEFAUT, 0.5, 10));
	gui.add(fps.setup("fps", ""));
	gui.add(primitivesMessage.setup("", "Les prochains curseurs\npermettent de choisir\nla primitive qui sera\ncreer et le materiau qui\nla compose.", 200, 150));
	gui.add(typePrimitive.setup("Primitives", 1, 1, NB_MAX_PRIMITIVE));
	gui.add(typeMateriau.setup("Materiaux", 14, 1, NB_MAX_MATERIAU));
	gui.add(usageMessage.setup("", "Autres fonctions : ", 200, 20));
	gui.add(usageMessage2.setup("","w - avancer", 200, 20));
	gui.add(usageMessage3.setup("","s - reculer", 200, 20));
	gui.add(usageMessage4.setup("","a - bouger a gauche", 200, 20));
	gui.add(usageMessage5.setup("","d - bouger a droite", 200, 20));
	gui.add(usageMessage6.setup("","i - capture d'ecran", 200, 20));
	gui.add(usageMessage7.setup("","f - mode plein ecran", 200, 20));
	gui.add(usageMessage8.setup("","m - afficher menu", 200, 20));
	gui.add(usageMessage9.setup("","Interaction primitives :", 200, 20));
	gui.add(usageMessage10.setup("","Clique Droit - creer", 200, 20));
	gui.add(usageMessage11.setup("","Clique Droit - selection", 200, 20));
}

void ofApp::primitiveChanged(int& primitive)
{
	primitiveSelectionnee = getPrimitivePourInt(primitive);
}

void ofApp::materiauChanged(int& materiau)
{
	materiauSelectionne = getMateriauPourInt(materiau);
}

void ofApp::pauseToggled(bool &paused) {
	if (paused){
		ofShowCursor();
	}
	else {
		ofHideCursor();
		mouseHandler->resetCusor();
	}
}

void ofApp::vertigoToggled(bool &enabled) {
	if (enabled){
		vitesseCamera = 0.8;
	}
	else {
		vitesseCamera = VITESSE_CAMERA_DEFAUT;
		angleChampDeVision = ANGLE_VISION_NORMAL;
		projection.makePerspectiveMatrix(angleChampDeVision, (double)ofGetWindowWidth() / ofGetWindowHeight(), 1.0, FAR_PLANE_DISTANCE);
	}
}

void ofApp::effetBrouillardToggled(bool &enabled) {
	if (enabled){
		effetLignes = false;
		effetNoirEtBlanc = false;
	}
}

void ofApp::effetNoirEtBlancToggled(bool &enabled) {
	if (enabled){
		effetBrouillard = false;
		effetLignes = false;
	}
}

void ofApp::effetLignesToggled(bool &enabled) {
	if (enabled){
		effetBrouillard = false;
		effetNoirEtBlanc = false;
	}
}

void ofApp::lampeDePocheToggled(bool & enabled) {
	if (enabled) {
		lumiere.ajouterLampeDePoche(camera.getPosition(), camera.getOrientation());
	}
	else {
		lumiere.enleverLampeDePoche();
	}
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

void ofApp::vitesseCameraChanged(float& vitesse)
{
	camera.setVitesse(vitesse);
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