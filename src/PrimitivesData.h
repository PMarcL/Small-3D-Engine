#pragma once

/*
*	Ce fichier contient des tableaux de sommets pour des primitives g�om�triques simples.
*	Les tableaux commencent toujours par le nom de la primitives qu'elle contient.	
*
*	-Une fonction utilitaire qui permet de r�cup�rer une liste de sommet � la taille d�sir�e.
*	-Une fonction utilitaire qui permet de calculer les normales pour une liste de sommets pass�e en argument.
*	-Une fonction utilitaire qui retourne une liste coordonn�es de texture pour une primitive pass�e en argument.
*/

#include <vector>

enum PRIMITIVES {
	CUBE,
	TETRAEDRE,
	OCTAEDRE
};

enum MATERIAUX {

};

std::vector<float> getSommetsPourPrimitive(PRIMITIVES primitive, int taille);

std::vector<float> getNormals(std::vector<float> sommets);

std::vector<float> getTexCoordPourPrimitive(PRIMITIVES primitive);
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