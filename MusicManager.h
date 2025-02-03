#pragma once

#include <SFML/Audio.hpp>

class AMusicManager
{
	sf::Music Title;
	sf::Music Tutorial;
	sf::Music Level1;
	sf::Music Level2;
	sf::Music Level3;
	sf::Music Level4;
	sf::Music Finale;
public:
	AMusicManager();
	void init();
	void play();
	void changeST(int Theme);
};

//Esto surgió de la idea de hacer un sistema de musica dinamica
//Que vaya cambiando a medida que se avanza en el juego
//Sumando instrumentos a la pista pero sin que esta se frene en ningun momento, solo en el loop

