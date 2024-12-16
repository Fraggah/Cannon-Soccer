#include "MusicManager.h"

MusicManager::MusicManager()
{
	init();
}

void MusicManager::init()
{
	title.openFromFile("sprites/Title.ogg");
	tutorial.openFromFile("sprites/Tutorial.ogg");
	level1.openFromFile("sprites/Level 1.ogg");
	level2.openFromFile("sprites/Level 2.ogg");
	level3.openFromFile("sprites/Level 3.ogg");
	level4.openFromFile("sprites/Level 4.ogg");
	finale.openFromFile("sprites/Final.ogg");

	title.setVolume(70);
	tutorial.setVolume(0);
	level1.setVolume(0);
	level2.setVolume(0);
	level3.setVolume(0);
	level4.setVolume(0);
	finale.setVolume(0);

	title.setLoop(true);
	tutorial.setLoop(true);
	level1.setLoop(true);
	level2.setLoop(true);
	level3.setLoop(true);
	level4.setLoop(true);
	finale.setLoop(true);
}

void MusicManager::play()
{
	title.play();
	tutorial.play();
	level1.play();
	level2.play();
	level3.play();
	level4.play();
	finale.play();
}

void MusicManager::changeST(int theme)
{
	switch(theme)
	{
	case -1:
		title.setVolume(70);
		tutorial.setVolume(0);
		level1.setVolume(0);
		level2.setVolume(0);
		level3.setVolume(0);
		level4.setVolume(0);
		finale.setVolume(0);
		break;
	case 0:
		title.setVolume(0);
		tutorial.setVolume(70);
		level1.setVolume(0);
		level2.setVolume(0);
		level3.setVolume(0);
		level4.setVolume(0);
		finale.setVolume(0);
		break;
	case 1:
		title.setVolume(0);
		tutorial.setVolume(0);
		level1.setVolume(70);
		level2.setVolume(0);
		level3.setVolume(0);
		level4.setVolume(0);
		finale.setVolume(0);
		break;
	case 2:
		title.setVolume(0);
		tutorial.setVolume(0);
		level1.setVolume(0);
		level2.setVolume(70);
		level3.setVolume(0);
		level4.setVolume(0);
		finale.setVolume(0);
		break;
	case 3:
		title.setVolume(0);
		tutorial.setVolume(0);
		level1.setVolume(0);
		level2.setVolume(0);
		level3.setVolume(70);
		level4.setVolume(0);
		finale.setVolume(0);
		break;
	case 4:
		title.setVolume(0);
		tutorial.setVolume(0);
		level1.setVolume(0);
		level2.setVolume(0);
		level3.setVolume(0);
		level4.setVolume(70);
		finale.setVolume(0);
		break;
	case 5:
		title.setVolume(0);
		tutorial.setVolume(0);
		level1.setVolume(0);
		level2.setVolume(0);
		level3.setVolume(0);
		level4.setVolume(0);
		finale.setVolume(70);
		break;
	default:
		printf("theme no existe");
		break;
	}
}