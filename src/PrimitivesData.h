#pragma once

/*
*	Ce fichier contient des tableaux de sommets pour des primitives géométriques simples.
*	Les tableaux commencent toujours par le nom de la primitives qu'elle contient.	
*
*	Ce fichier contient aussi des tableaux avec des informations de réflection pour différents matériaux.
*
*	-Une fonction utilitaire qui permet de récupérer une liste de sommet à la taille désirée.
*	-Une fonction utilitaire qui permet de calculer les normales pour une liste de sommets passée en argument.
*	-Une fonction utilitaire qui retourne une liste coordonnées de texture pour une primitive passée en argument.
*	-Une fonction utilitaire qui retourne le bon tableau de donnée pour une matériaux donné en argument.
*/

#include <vector>

enum PRIMITIVES {
	CUBE,
	TETRAEDRE,
	OCTAEDRE,
	CONE,
	SPHERE
};

enum MATERIAUX {
	PLASTIQUE_NOIR,
	PLASTIQUE_BLEU,
	PLASTIQUE_VERT,
	PLASTIQUE_ROUGE,
	PLASTIQUE_BLANC,
	PLASTIQUE_JAUNE,
	RUBBER_NOIR,
	RUBBER_ROUGE,
	RUBBER_BLEU,
	EMERAUDE,
	JADE,
	OBSIDIENNE,
	PERLE,
	RUBY,
	TURQUOISE,
	LAITON,
	BRONZE,
	CHROME,
	CUIVRE,
	OR,
	ARGENT,
	SELECTION
};

std::vector<float> getSommetsPourPrimitive(PRIMITIVES primitive, int taille);

std::vector<float> getNormals(std::vector<float> sommets);

std::vector<float> getTexCoordPourPrimitive(PRIMITIVES primitive);

std::vector<float> getMateriauData(MATERIAUX materiau);

PRIMITIVES getPrimitivePourInt(int noPrimitive);

MATERIAUX getMateriauPourInt(int noMateriau);

const static float CONE_PRECISION = 500.0;
const static float CONE_HAUTEUR = 1.0;
const static float CONE_RAYON = 0.5;

const static float SPHERE_RAYON = 1.0;
const static float SPHERE_PRECISION_LAT = 240;
const static float SPHERE_PRECISION_LON = 160;

const static float CUBE_SOMMETS[] = {
	1, -1, -1,		// side
	-1, -1, -1,
	1, 1, -1,
	-1, 1, -1,
	1, 1, -1,
	-1, -1, -1,

	-1, -1, 1,		// side
	1, -1, 1,
	1, 1, 1,
	1, 1, 1,
	-1, 1, 1,
	-1, -1, 1,

	-1, 1, 1,		// side
	-1, 1, -1,
	-1, -1, -1,
	-1, -1, -1,
	-1, -1, 1,
	-1, 1, 1,

	1, 1, -1,		// side
	1, 1, 1,
	1, -1, -1,
	1, -1, 1,
	1, -1, -1,
	1, 1, 1,

	-1, -1, -1,		// bottom
	1, -1, -1,
	1, -1, 1,
	1, -1, 1,
	-1, -1, 1,
	-1, -1, -1,

	1, 1, -1,		// top
	-1, 1, -1,
	1, 1, 1,
	-1, 1, 1,
	1, 1, 1,
	-1, 1, -1
};

const static float CUBE_TEXCOORD[] = {
	0.0f, 0.0f,
	1.0f, 0.0f,
	1.0f, 1.0f,
	1.0f, 1.0f,
	0.0f, 1.0f,
	0.0f, 0.0f,

	0.0f, 0.0f,
	1.0f, 0.0f,
	1.0f, 1.0f,
	1.0f, 1.0f,
	0.0f, 1.0f,
	0.0f, 0.0f,

	1.0f, 0.0f,
	1.0f, 1.0f,
	0.0f, 1.0f,
	0.0f, 1.0f,
	0.0f, 0.0f,
	1.0f, 0.0f,

	1.0f, 0.0f,
	1.0f, 1.0f,
	0.0f, 1.0f,
	0.0f, 1.0f,
	0.0f, 0.0f,
	1.0f, 0.0f,

	0.0f, 1.0f,
	1.0f, 1.0f,
	1.0f, 0.0f,
	1.0f, 0.0f,
	0.0f, 0.0f,
	0.0f, 1.0f,

	0.0f, 1.0f,
	1.0f, 1.0f,
	1.0f, 0.0f,
	1.0f, 0.0f,
	0.0f, 0.0f,
	0.0f, 1.0f
};

const static float OCTAEDRE_SOMMETS[] = {
	-1, 0, -1,
	0, 1, 0,
	1, 0, -1,

	1, 0, -1,
	0, 1, 0,
	1, 0, 1,

	1, 0, 1,
	0, 1, 0,
	-1, 0, 1,

	-1, 0, 1,
	0, 1, 0,
	-1, 0, -1,

	0, -1, 0,
	-1, 0, -1,
	1, 0, -1,

	0, -1, 0,
	1, 0, -1,
	1, 0, 1,

	0, -1, 0,
	1, 0, 1,
	-1, 0, 1,

	0, -1, 0,
	-1, 0, 1,
	-1, 0, -1
};

const static float OCTAEDRE_TEXCOORDS[] = {
	0.5, 1.0,
    0.0, 0.0,
    1.0, 0.0,

	0.5, 1.0,
    0.0, 0.0,
    1.0, 0.0,

	0.5, 1.0,
    0.0, 0.0,
    1.0, 0.0,

	0.5, 1.0,
    0.0, 0.0,
    1.0, 0.0,

	0.5, 1.0,
    0.0, 0.0,
    1.0, 0.0,

	0.5, 1.0,
    0.0, 0.0,
    1.0, 0.0,

	0.5, 1.0,
    0.0, 0.0,
    1.0, 0.0,

	0.5, 1.0,
    0.0, 0.0,
    1.0, 0.0,
};

const static float TETRAEDRE_SOMMETS[] = {
	-1, 1, -1,
	1, 1, 1,
	1, -1, -1,

	1, 1, 1,
	-1, 1, -1,
	-1, -1, 1,

	1, 1, 1,
	-1, -1, 1,
	1, -1, -1,

	-1, 1, -1,
	1, -1, -1,
	-1, -1, 1
};

const static float TETRAEDRE_TEXCOORD[] = {
    0.5, 1.0,
    0.0, 0.0,
    1.0, 0.0,

    0.5, 1.0,
    0.0, 0.0,
    1.0, 0.0,

    0.5, 1.0,
    0.0, 0.0,
    1.0, 0.0,

    0.5, 1.0,
    0.0, 0.0,
    1.0, 0.0
};

const static float PLASTIQUE_NOIR_DATA [] = {
	0.0, 0.0, 0.0,			// reflection ambiante
	0.01, 0.01, 0.01,		// reflection diffuse
	0.5, 0.5, 0.5,			// reflection spéculaire
	0.25					// brillance
};

const static float PLASTIQUE_BLEU_DATA [] = {
	0.0, 0.1, 0.06,
	0.0, 0.50980392, 0.50980392,
	0.50196078, 0.50196078, 0.50196078,
	0.25
};

const static float PLASTIQUE_VERT_DATA [] = {
	0.0, 0.0, 0.0,
	0.1, 0.35, 0.1,
	0.1, 0.45, 0.55,
	0.25
};

const static float PLASTIQUE_ROUGE_DATA [] = {
	0.0, 0.0, 0.0,
	0.5, 0.0, 0.0,
	0.45, 0.55, 0.45,
	0.25
};

const static float PLASTIQUE_BLANC_DATA [] = {
	0.0, 0.0, 0.0,
	0.55, 0.55, 0.55,
	0.7, 0.7, 0.7,
	0.25
};

const static float PLASTIQUE_JAUNE_DATA [] = {
	0.0, 0.0, 0.0,
	0.5, 0.5, 0.0,
	0.6, 0.6, 0.5,
	0.25
};

const static float RUBBER_NOIR_DATA [] = {
	0.02, 0.02, 0.02,
	0.01, 0.01, 0.01,
	0.4, 0.4, 0.4,
	0.078125
};

const static float RUBBER_ROUGE_DATA [] = {
	0.05, 0.0, 0.0,
	0.5, 0.4, 0.4,
	0.7, 0.4, 0.4,
	0.078125
};

const static float RUBBER_BLEU_DATA [] = {
	0.0, 0.05, 0.05,
	0.4, 0.5, 0.5,
	0.4, 0.7, 0.7,
	0.078125
};

const static float EMERAUDE_DATA [] = {
	0.0215, 0.1745, 0.0215,
	0.07568, 0.61424, 0.07568,
	0.633, 0.727811, 0.633,
	0.6
};

const static float JADE_DATA [] = {
	0.135, 0.2225, 0.1575,
	0.54, 0.89, 0.63,
	0.316228, 0.316228, 0.316228,
	0.1
};

const static float OBSIDIENNE_DATA [] = {
	0.05375, 0.05, 0.06625,
	0.18275, 0.17, 0.22525,
	0.332741, 0.328634, 0.346435,
	0.3
};

const static float PERLE_DATA [] = {
	0.25, 0.20725, 0.20725,
	1, 0.829, 0.829,
	0.296648, 0.296648, 0.296648,
	0.088
};

const static float RUBY_DATA [] = {
	0.1745, 0.01175, 0.01175,
	0.61424, 0.04136, 0.04136,
	0.727811, 0.626959, 0.626959,
	0.6
};

const static float TURQUOISE_DATA [] = {
	0.1, 0.18725, 0.1745,
	0.396, 0.74151, 0.69102,
	0.297254, 0.30829, 0.306678,
	0.1
};

const static float LAITON_DATA [] = {
	0.329412, 0.223529, 0.027451,
	0.780392, 0.568627, 0.113725,
	0.992157, 0.941176, 0.807843,
	0.21794872
};

const static float BRONZE_DATA [] = {
	0.2125, 0.1275, 0.054,
	0.714, 0.4284, 0.18144,
	0.393548, 0.271906, 0.166721,
	0.2
};

const static float CHROME_DATA [] = {
	0.25, 0.25, 0.25,
	0.4, 0.4, 0.4,
	0.774597, 0.774597, 0.774597,
	0.6
};

const static float CUIVRE_DATA [] = {
	0.19125, 0.0735, 0.0225,
	0.7038, 0.27048, 0.0828,
	0.256777, 0.137622, 0.086014,
	0.1
};

const static float OR_DATA [] = {
	0.24725, 0.1995, 0.0745,
	0.75164, 0.60648, 0.22648,
	0.628281, 0.555802, 0.366065,
	0.4
};

const static float ARGENT_DATA [] = {
	0.19225, 0.19225, 0.19225,
	0.50754, 0.50754, 0.50754,
	0.508273, 0.508273, 0.508273,
	0.4
};

const static float SELECTION_DATA [] = {
	0.0, 1.0, 0.0,
	0.0, 1.0, 0.0,
	0.0, 1.0, 0.0,
	1.0
};