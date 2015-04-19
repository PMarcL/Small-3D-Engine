#include "PrimitivesData.h"
#include "ofMain.h"

void ajusterTailleSommets(vector<float>& sommets, float taille);
vector<float> genererSommetsCone();
vector<float> genererTexCoordsCone();
void genererSommetsSphere(vector<float>& sommets);
void generationDesSommetsInitiauxSphere(vector<ofVec3f>& sommets);
void triangularisationDessusSphere(vector<ofVec3f>& sommetsInit, vector<float>& sommets);
void triangularisationDessousSphere(vector<ofVec3f>& sommetsInit, vector<float>& sommets);
void triangularisationPartieCentraleSphere(vector<ofVec3f>& sommetsInit, vector<float>& sommets);
vector<float> genererTexCoordsSphere();

vector<float> getSommetsPourPrimitive(PRIMITIVES primitive, int taille) {
	vector<float> sommets;
	switch(primitive) {
	case(CUBE):
		sommets = vector<float>(CUBE_SOMMETS, CUBE_SOMMETS + sizeof(CUBE_SOMMETS) / sizeof(CUBE_SOMMETS[0]));
		break;
	case(OCTAEDRE):
		sommets = vector<float>(OCTAEDRE_SOMMETS, OCTAEDRE_SOMMETS + sizeof(OCTAEDRE_SOMMETS) / sizeof(OCTAEDRE_SOMMETS[0]));
		break;
	case(TETRAEDRE):
		sommets = vector<float>(TETRAEDRE_SOMMETS, TETRAEDRE_SOMMETS + sizeof(TETRAEDRE_SOMMETS) / sizeof(TETRAEDRE_SOMMETS[0]));
		break;
	case(CONE):
		sommets = genererSommetsCone();
		break;
	case(SPHERE):
		genererSommetsSphere(sommets);
		break;
	default:
		break;
	}

	ajusterTailleSommets(sommets, taille*0.5);
	return sommets;
}

vector<float> genererSommetsCone() {
	vector<float> sommets;
	float angleEntreSommets = (2*PI) / CONE_PRECISION;
	for(int i = 0; i < CONE_PRECISION; i++) {
		// base du cone
		sommets.push_back(0);
		sommets.push_back(0);
		sommets.push_back(0);

		sommets.push_back(CONE_RAYON * cos(i * angleEntreSommets)); 
		sommets.push_back(0);
		sommets.push_back(CONE_RAYON * sin(i * angleEntreSommets));

		sommets.push_back(CONE_RAYON * cos((i + 1) * angleEntreSommets)); 
		sommets.push_back(0);
		sommets.push_back(CONE_RAYON * sin((i + 1) * angleEntreSommets));

		// Côté du cone
		sommets.push_back(0);
		sommets.push_back(CONE_HAUTEUR);
		sommets.push_back(0);

		sommets.push_back(CONE_RAYON * cos((i + 1) * angleEntreSommets)); 
		sommets.push_back(0);
		sommets.push_back(CONE_RAYON * sin((i + 1) * angleEntreSommets));

		sommets.push_back(CONE_RAYON * cos(i * angleEntreSommets)); 
		sommets.push_back(0);
		sommets.push_back(CONE_RAYON * sin(i * angleEntreSommets));
	}

	return sommets;
}

void genererSommetsSphere(vector<float>& sommets) {
	vector<ofVec3f> sommetsInit;
	generationDesSommetsInitiauxSphere(sommetsInit);

	triangularisationDessusSphere(sommetsInit, sommets);
	triangularisationPartieCentraleSphere(sommetsInit, sommets);
	triangularisationDessousSphere(sommetsInit, sommets);
}

void generationDesSommetsInitiauxSphere(vector<ofVec3f>& sommets) {
	float deuxPI = 2 * PI;
	sommets.push_back(ofVec3f(0, SPHERE_RAYON, 0));
	for( int lat = 0; lat < SPHERE_PRECISION_LAT; lat++ )
	{
		float a1 = PI * (float)(lat+1) / (SPHERE_PRECISION_LAT+1);
		float sin1 = sin(a1);
		float cos1 = cos(a1);
 
		for( int lon = 0; lon <= SPHERE_PRECISION_LON; lon++ )
		{
			float a2 = deuxPI * (float)(lon == SPHERE_PRECISION_LON ? 0 : lon) / SPHERE_PRECISION_LON;
			float sin2 = sin(a2);
			float cos2 = cos(a2);
 
			sommets.push_back(ofVec3f(sin1 * cos2, cos1, sin1 * sin2) * SPHERE_RAYON);
		}
	}
	sommets.push_back(ofVec3f(0, -SPHERE_RAYON, 0));
}

void triangularisationDessusSphere(vector<ofVec3f>& sommetsInit, vector<float>& sommets) {
	for( int lon = 0; lon < SPHERE_PRECISION_LON; lon++ )
	{
		sommets.push_back(sommetsInit[lon+2].x);
		sommets.push_back(sommetsInit[lon+2].y);
		sommets.push_back(sommetsInit[lon+2].z);

		sommets.push_back(sommetsInit[lon+1].x);
		sommets.push_back(sommetsInit[lon+1].y);
		sommets.push_back(sommetsInit[lon+1].z);

		sommets.push_back(sommetsInit[0].x);
		sommets.push_back(sommetsInit[0].y);
		sommets.push_back(sommetsInit[0].z);
	}
}

void triangularisationPartieCentraleSphere(vector<ofVec3f>& sommetsInit, vector<float>& sommets) {
	for( int lat = 0; lat < SPHERE_PRECISION_LAT - 1; lat++ )
	{
		for( int lon = 0; lon < SPHERE_PRECISION_LON; lon++ )
		{
			int current = lon + lat * (SPHERE_PRECISION_LON + 1) + 1;
			int next = current + SPHERE_PRECISION_LON + 1;
 
			sommets.push_back(sommetsInit[current].x);
			sommets.push_back(sommetsInit[current].y);
			sommets.push_back(sommetsInit[current].z);

			sommets.push_back(sommetsInit[current + 1].x);
			sommets.push_back(sommetsInit[current + 1].y);
			sommets.push_back(sommetsInit[current + 1].z);
			
			sommets.push_back(sommetsInit[next + 1].x);
			sommets.push_back(sommetsInit[next + 1].y);
			sommets.push_back(sommetsInit[next + 1].z);
			
 
			sommets.push_back(sommetsInit[current].x);
			sommets.push_back(sommetsInit[current].y);
			sommets.push_back(sommetsInit[current].z);

			sommets.push_back(sommetsInit[next + 1].x);
			sommets.push_back(sommetsInit[next + 1].y);
			sommets.push_back(sommetsInit[next + 1].z);
			
			sommets.push_back(sommetsInit[next].x);
			sommets.push_back(sommetsInit[next].y);
			sommets.push_back(sommetsInit[next].z);
		}
	}
}

void triangularisationDessousSphere(vector<ofVec3f>& sommetsInit, vector<float>& sommets) {
	int nbSommets = sommetsInit.size();
	for( int lon = 0; lon < SPHERE_PRECISION_LON; lon++ )
	{
		sommets.push_back(sommetsInit[nbSommets - 1].x);
		sommets.push_back(sommetsInit[nbSommets - 1].y);
		sommets.push_back(sommetsInit[nbSommets - 1].z);
		
		sommets.push_back(sommetsInit[nbSommets - (lon+2) - 1].x);
		sommets.push_back(sommetsInit[nbSommets - (lon+2) - 1].y);
		sommets.push_back(sommetsInit[nbSommets - (lon+2) - 1].z);
		
		sommets.push_back(sommetsInit[nbSommets - (lon+1) - 1].x);
		sommets.push_back(sommetsInit[nbSommets - (lon+1) - 1].y);
		sommets.push_back(sommetsInit[nbSommets - (lon+1) - 1].z);
	}
}

void ajusterTailleSommets(vector<float>& sommets, float taille) {
	for(int i = 0; i < sommets.size(); i++)
		sommets[i] *= taille; 
}

vector<float> getNormals(vector<float> sommets) {
	vector<float> normals;
	for(int i = 0; i < sommets.size(); i += 9) {
		ofVec3f sommet1(sommets[i], sommets[i+1], sommets[i+2]);
		ofVec3f sommet2(sommets[i+3], sommets[i+4], sommets[i+5]);
		ofVec3f sommet3(sommets[i+6], sommets[i+7], sommets[i+8]);
		
		ofVec3f normal = sommet2 - sommet1;
		normal.cross(sommet3 - sommet1);
		normal.normalize();
		
		normals.push_back(normal.x); normals.push_back(normal.y); normals.push_back(normal.z);
		normals.push_back(normal.x); normals.push_back(normal.y); normals.push_back(normal.z);
		normals.push_back(normal.x); normals.push_back(normal.y); normals.push_back(normal.z);
	}
	return normals;
}

vector<float> getTexCoordPourPrimitive(PRIMITIVES primitive) {
	switch(primitive) {
	case(CUBE):
		return vector<float>(CUBE_TEXCOORD, CUBE_TEXCOORD + sizeof(CUBE_TEXCOORD) / sizeof(CUBE_TEXCOORD[0]));
		break;
	case(OCTAEDRE):
		return vector<float>(OCTAEDRE_TEXCOORDS, OCTAEDRE_TEXCOORDS + sizeof(OCTAEDRE_TEXCOORDS) / sizeof(OCTAEDRE_TEXCOORDS[0]));
		break;
	case(TETRAEDRE):
		return vector<float>(TETRAEDRE_TEXCOORD, TETRAEDRE_TEXCOORD + sizeof(TETRAEDRE_TEXCOORD) / sizeof(TETRAEDRE_TEXCOORD[0]));
		break;
	case(CONE):
		return genererTexCoordsCone();
	case(SPHERE):
		return genererTexCoordsSphere();
		break;
	}
}

vector<float> genererTexCoordsCone() {
	vector<float> texCoords;
	float angleEntreSommets = (2*PI) / CONE_PRECISION;
	// représente la distance entre chaque sommet autour de la base
	float distanceEntreSommets = (2*PI*CONE_RAYON) / CONE_PRECISION;
	for(int i = 0; i < CONE_PRECISION; i++) {
		// base du cone
		texCoords.push_back(1.0 / 2.0);
		texCoords.push_back(1.0 / 2.0);

		texCoords.push_back(0.5 * cos((i + 1) * angleEntreSommets));
		texCoords.push_back(0.5 * sin((i + 1) * angleEntreSommets));

		texCoords.push_back(0.5 * cos(i * angleEntreSommets));
		texCoords.push_back(0.5 * sin(i * angleEntreSommets));

		// côté du cône
		texCoords.push_back(1.0 / 2.0);
		texCoords.push_back(1.0);

		texCoords.push_back((i + 1) * distanceEntreSommets);
		texCoords.push_back(0);

		texCoords.push_back(i * distanceEntreSommets);
		texCoords.push_back(0);
	}

	return texCoords;
}

vector<float> genererTexCoordsSphere() {
	vector<float> texCoords;
	for(int i = 0; i < (6 * SPHERE_PRECISION_LON * SPHERE_PRECISION_LAT); i++) {
		texCoords.push_back(0);
		texCoords.push_back(0);
	}
	return texCoords;
}

std::vector<float> getMateriauData(MATERIAUX materiau) {
	switch(materiau) {
	case(AUCUN):
		return vector<float>(ARGENT_DATA, ARGENT_DATA + sizeof(ARGENT_DATA) / sizeof(ARGENT_DATA[0]));//Lorsqu'aucun: Argent
		break;
	case(PLASTIQUE_NOIR):
		return vector<float>(PLASTIQUE_NOIR_DATA, PLASTIQUE_NOIR_DATA + sizeof(PLASTIQUE_NOIR_DATA) / sizeof(PLASTIQUE_NOIR_DATA[0]));
		break;
	case(PLASTIQUE_BLEU):
		return vector<float>(PLASTIQUE_BLEU_DATA, PLASTIQUE_BLEU_DATA + sizeof(PLASTIQUE_BLEU_DATA) / sizeof(PLASTIQUE_BLEU_DATA[0]));
		break;
	case(PLASTIQUE_VERT):
		return vector<float>(PLASTIQUE_VERT_DATA, PLASTIQUE_VERT_DATA + sizeof(PLASTIQUE_VERT_DATA) / sizeof(PLASTIQUE_VERT_DATA[0]));
		break;
	case(PLASTIQUE_ROUGE):
		return vector<float>(PLASTIQUE_ROUGE_DATA, PLASTIQUE_ROUGE_DATA + sizeof(PLASTIQUE_ROUGE_DATA) / sizeof(PLASTIQUE_ROUGE_DATA[0]));
		break;
	case(PLASTIQUE_BLANC):
		return vector<float>(PLASTIQUE_BLANC_DATA, PLASTIQUE_BLANC_DATA + sizeof(PLASTIQUE_BLANC_DATA) / sizeof(PLASTIQUE_BLANC_DATA[0]));
		break;
	case(PLASTIQUE_JAUNE):
		return vector<float>(PLASTIQUE_JAUNE_DATA, PLASTIQUE_JAUNE_DATA + sizeof(PLASTIQUE_JAUNE_DATA) / sizeof(PLASTIQUE_JAUNE_DATA[0]));
		break;
	case(RUBBER_NOIR):
		return vector<float>(RUBBER_NOIR_DATA, RUBBER_NOIR_DATA + sizeof(RUBBER_NOIR_DATA) / sizeof(RUBBER_NOIR_DATA[0]));
		break;
	case(RUBBER_ROUGE):
		return vector<float>(RUBBER_ROUGE_DATA, RUBBER_ROUGE_DATA + sizeof(RUBBER_ROUGE_DATA) / sizeof(RUBBER_ROUGE_DATA[0]));
		break;
	case(RUBBER_BLEU):
		return vector<float>(RUBBER_BLEU_DATA, RUBBER_BLEU_DATA + sizeof(RUBBER_BLEU_DATA) / sizeof(RUBBER_BLEU_DATA[0]));
		break;
	case(EMERAUDE):
		return vector<float>(EMERAUDE_DATA, EMERAUDE_DATA + sizeof(EMERAUDE_DATA) / sizeof(EMERAUDE_DATA[0]));
		break;
	case(JADE):
		return vector<float>(JADE_DATA, JADE_DATA + sizeof(JADE_DATA) / sizeof(JADE_DATA[0]));
		break;
	case(OBSIDIENNE):
		return vector<float>(OBSIDIENNE_DATA, OBSIDIENNE_DATA + sizeof(OBSIDIENNE_DATA) / sizeof(OBSIDIENNE_DATA[0]));
		break;
	case(PERLE):
		return vector<float>(PERLE_DATA, PERLE_DATA + sizeof(PERLE_DATA) / sizeof(PERLE_DATA[0]));
		break;
	case(RUBY):
		return vector<float>(RUBY_DATA, RUBY_DATA + sizeof(RUBY_DATA) / sizeof(RUBY_DATA[0]));
		break;
	case(TURQUOISE):
		return vector<float>(TURQUOISE_DATA, TURQUOISE_DATA + sizeof(TURQUOISE_DATA) / sizeof(TURQUOISE_DATA[0]));
		break;
	case(LAITON):
		return vector<float>(LAITON_DATA, LAITON_DATA + sizeof(LAITON_DATA) / sizeof(LAITON_DATA[0]));
		break;
	case(BRONZE):
		return vector<float>(BRONZE_DATA, BRONZE_DATA + sizeof(BRONZE_DATA) / sizeof(BRONZE_DATA[0]));
		break;
	case(CHROME):
		return vector<float>(CHROME_DATA, CHROME_DATA + sizeof(CHROME_DATA) / sizeof(CHROME_DATA[0]));
		break;
	case(CUIVRE):
		return vector<float>(CUIVRE_DATA, CUIVRE_DATA + sizeof(CUIVRE_DATA) / sizeof(CUIVRE_DATA[0]));
		break;
	case(OR):
		return vector<float>(OR_DATA, OR_DATA + sizeof(OR_DATA) / sizeof(OR_DATA[0]));
		break;
	case(ARGENT):
		return vector<float>(ARGENT_DATA, ARGENT_DATA + sizeof(ARGENT_DATA) / sizeof(ARGENT_DATA[0]));
		break;
	case(SELECTION):
		return vector<float>(SELECTION_DATA, SELECTION_DATA + sizeof(SELECTION_DATA) / sizeof(SELECTION_DATA[0]));
		break;
	}
}

PRIMITIVES getPrimitivePourInt(int noPrimitive)
{
	switch(noPrimitive) {
	case(1):
		return CUBE;
		break;
	case(2):
		return TETRAEDRE;
		break;
	case(3):
		return OCTAEDRE;
		break;
	case(4):
		return CONE;
	case(5):
		return SPHERE;
		break;
	}
}

MATERIAUX getMateriauPourInt(int noMateriau)
{
	switch(noMateriau) {
	case(1):
		return PLASTIQUE_NOIR;
		break;
	case(2):
		return PLASTIQUE_BLEU;
		break;
	case(3):
		return PLASTIQUE_VERT;
		break;
	case(4):
		return PLASTIQUE_ROUGE;
		break;
	case(5):
		return PLASTIQUE_BLANC;
		break;
	case(6):
		return PLASTIQUE_JAUNE;
		break;
	case(7):
		return RUBBER_NOIR;
		break;
	case(8):
		return RUBBER_ROUGE;
		break;
	case(9):
		return RUBBER_BLEU;
		break;
	case(10):
		return EMERAUDE;
		break;
	case(11):
		return JADE;
		break;
	case(12):
		return OBSIDIENNE;
		break;
	case(13):
		return PERLE;
		break;
	case(14):
		return RUBY;
		break;
	case(15):
		return TURQUOISE;
		break;
	case(16):
		return LAITON;
		break;
	case(17):
		return BRONZE;
		break;
	case(18):
		return CHROME;
		break;
	case(19):
		return CUIVRE;
		break;
	case(20):
		return OR;
		break;
	case(21):
		return ARGENT;
		break;
	}
}