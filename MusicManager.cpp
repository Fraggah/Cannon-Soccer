#include "MusicManager.h"

AMusicManager::AMusicManager()
{
	init();
}

//Inicializo y seteo los tracks
void AMusicManager::init()
{
	Title.openFromFile("sprites/Title.ogg");
	Tutorial.openFromFile("sprites/Tutorial.ogg");
	Level1.openFromFile("sprites/Level 1.ogg");
	Level2.openFromFile("sprites/Level 2.ogg");
	Level3.openFromFile("sprites/Level 3.ogg");
	Level4.openFromFile("sprites/Level 4.ogg");
	Finale.openFromFile("sprites/Final.ogg");

	//Solo dejo el volumen levantado de un track
	Title.setVolume(70);
	Tutorial.setVolume(0);
	Level1.setVolume(0);
	Level2.setVolume(0);
	Level3.setVolume(0);
	Level4.setVolume(0);
	Finale.setVolume(0);

	Title.setLoop(true);
	Tutorial.setLoop(true);
	Level1.setLoop(true);
	Level2.setLoop(true);
	Level3.setLoop(true);
	Level4.setLoop(true);
	Finale.setLoop(true);
}

//Reproduzco todos a la vez
void AMusicManager::play()
{
	Title.play();
	Tutorial.play();
	Level1.play();
	Level2.play();
	Level3.play();
	Level4.play();
	Finale.play();
}

//Seteo de cambio de tema, como ya todos se estan reproduciendo a la vez
//lo unico que tengo que hacer es setear acordemente sus volumenes
void AMusicManager::changeST(int Theme)
{
	switch(Theme)
	{
	case -1:
		Title.setVolume(70);
		Tutorial.setVolume(0);
		Level1.setVolume(0);
		Level2.setVolume(0);
		Level3.setVolume(0);
		Level4.setVolume(0);
		Finale.setVolume(0);
		break;
	case 0:
		Title.setVolume(0);
		Tutorial.setVolume(70);
		Level1.setVolume(0);
		Level2.setVolume(0);
		Level3.setVolume(0);
		Level4.setVolume(0);
		Finale.setVolume(0);
		break;
	case 1:
		Title.setVolume(0);
		Tutorial.setVolume(0);
		Level1.setVolume(70);
		Level2.setVolume(0);
		Level3.setVolume(0);
		Level4.setVolume(0);
		Finale.setVolume(0);
		break;
	case 2:
		Title.setVolume(0);
		Tutorial.setVolume(0);
		Level1.setVolume(0);
		Level2.setVolume(70);
		Level3.setVolume(0);
		Level4.setVolume(0);
		Finale.setVolume(0);
		break;
	case 3:
		Title.setVolume(0);
		Tutorial.setVolume(0);
		Level1.setVolume(0);
		Level2.setVolume(0);
		Level3.setVolume(70);
		Level4.setVolume(0);
		Finale.setVolume(0);
		break;
	case 4:
		Title.setVolume(0);
		Tutorial.setVolume(0);
		Level1.setVolume(0);
		Level2.setVolume(0);
		Level3.setVolume(0);
		Level4.setVolume(70);
		Finale.setVolume(0);
		break;
	case 5:
		Title.setVolume(0);
		Tutorial.setVolume(0);
		Level1.setVolume(0);
		Level2.setVolume(0);
		Level3.setVolume(0);
		Level4.setVolume(0);
		Finale.setVolume(70);
		break;
	default:
		printf("This n theme doesn't exist");
		break;
	}
}