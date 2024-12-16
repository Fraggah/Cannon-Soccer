#include "Background.h"

Background::Background()
{
    texture.loadFromFile("sprites/animatedB.png");
    sprite.setTexture(texture);
    sprite.setTextureRect(textureRect1);
    sf::Color color = sprite.getColor();
    color.a = 140;
    sprite.setColor(color);
}

void Background::update()
{
    if (clock.getElapsedTime() > time)
    {
        if (sprite.getTextureRect() == textureRect1)
        {
            sprite.setTextureRect(textureRect2);
        }
        else if (sprite.getTextureRect() == textureRect2)
        {
            sprite.setTextureRect(textureRect3);
        }
        else if (sprite.getTextureRect() == textureRect3)
        {
            sprite.setTextureRect(textureRect1);
        }
        clock.restart();
    }
}

void Background::render(sf::RenderWindow& window)
{
    window.draw(sprite);
}