#include "Crosshair.h"

Crosshair::Crosshair()
{
    texture.loadFromFile("sprites/croshair.png");
    sprite.setTexture(texture);
    sprite.setOrigin(2.5, 2.5);
}

void Crosshair::update(sf::Vector2f mouse)
{
    sprite.setPosition(mouse);
}

void Crosshair::render(sf::RenderWindow& window)
{
    window.draw(sprite);
}