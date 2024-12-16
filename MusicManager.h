#pragma once

#include <SFML/Audio.hpp>

class MusicManager
{
	sf::Music title;
	sf::Music tutorial;
	sf::Music level1;
	sf::Music level2;
	sf::Music level3;
	sf::Music level4;
	sf::Music finale;
public:
	MusicManager();
	void init();
	void play();
	void changeST(int theme);
};

