#pragma once

#include <SFML/Graphics.hpp>

class Particle
{
protected:
    float x;
    float y;
    sf::Sprite sprite;
    sf::Texture texture;
    sf::IntRect textureRect1;
    sf::IntRect textureRect2;
    sf::IntRect textureRect3;
    sf::Clock clock;
    sf::Time time{ sf::milliseconds(50) };
public:
    bool isActive = true;
    virtual void update() = 0;
    virtual void render(sf::RenderWindow& window);
};