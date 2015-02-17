#pragma once

#include "ofMain.h"

const static string MUSIQUE = "Musique/november.mp3";
const static string AMBIANCE = "SFX/wind.mp3";

class MusiqueSFX
{
public:
	MusiqueSFX(void);
	~MusiqueSFX(void);

	void jouerMusiqueEtAmbiance();
	void actionnerPauseMusiqueEtAmbiance();
	void desactionnerPauseMusiqueEtAmbiance();

private:

	ofSoundPlayer musiqueAmbiance;
	ofSoundPlayer sfxAmbiance;
};

