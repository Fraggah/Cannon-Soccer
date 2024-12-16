#include "CanonShot.h"

CanonShot::CanonShot(float _x, float _y)
{
    textureRect1.left = 0;
    textureRect1.top = 0;
    textureRect1.width = 10;
    textureRect1.height = 10;
    textureRect2.left = 10;
    textureRect2.top = 0;
    textureRect2.width = 10;
    textureRect2.height = 10;
    x = _x;
    y = _y;
    texture.loadFromFile("sprites/shot.png");
    sprite.setTexture(texture);
    sprite.setTextureRect(textureRect1);
    sprite.setOrigin(5, 5);
    sprite.setPosition(x, y);
}

void CanonShot::update()
{
    if (clock.getElapsedTime() > time)
    {
        if (sprite.getTextureRect() == textureRect1)
        {
            sprite.setTextureRect(textureRect2);
        }
        else
        {
            isActive = false;
        }
        clock.restart();
    }
}