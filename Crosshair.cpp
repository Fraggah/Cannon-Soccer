#include "Crosshair.h"

ACrosshair::ACrosshair()
{
    Texture.loadFromFile("sprites/croshair.png");
    Sprite.setTexture(Texture);
    Sprite.setOrigin(2.5, 2.5);
}

void ACrosshair::update(sf::Vector2f Mouse)
{
    Sprite.setPosition(Mouse);
}

void ACrosshair::render(sf::RenderWindow& Window)
{
    Window.draw(Sprite);
}