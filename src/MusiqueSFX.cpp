#include "MusiqueSFX.h"


MusiqueSFX::MusiqueSFX(void)
{
	ofSetWorkingDirectoryToDefault();
	musiqueAmbiance.loadSound(MUSIQUE);
	musiqueAmbiance.setLoop(true);
	sfxAmbiance.loadSound(AMBIANCE);
	sfxAmbiance.setLoop(true);
	sfxAmbiance.setVolume(0.5);
}

void MusiqueSFX::jouerMusiqueEtAmbiance()
{
	musiqueAmbiance.play();
	sfxAmbiance.play();
}

void MusiqueSFX::actionnerPauseMusiqueEtAmbiance()
{
	musiqueAmbiance.setPaused(true);
	sfxAmbiance.setPaused(true);
}

void MusiqueSFX::desactionnerPauseMusiqueEtAmbiance()
{
	musiqueAmbiance.setPaused(false);
	sfxAmbiance.setPaused(false);
}

MusiqueSFX::~MusiqueSFX(void)
{
}
