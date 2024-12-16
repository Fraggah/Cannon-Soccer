#include "BoxParticle.h"

BoxParticle::BoxParticle(float _x, float _y)
{
    textureRect1.left = 0;
    textureRect1.top = 0;
    textureRect1.width = 5;
    textureRect1.height = 5;
    textureRect2.left = 5;
    textureRect2.top = 0;
    textureRect2.width = 5;
    textureRect2.height = 5;
    x = _x;
    y = _y;
    texture.loadFromFile("sprites/blockdis.png");
    sprite.setTexture(texture);
    sprite.setTextureRect(textureRect1);
    sprite.setOrigin(2.5, 2.5);
    sprite.setPosition(x, y);
}

void BoxParticle::update()
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