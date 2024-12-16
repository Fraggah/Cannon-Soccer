#include "Explosion.h"

Explosion::Explosion(float _x, float _y)
{
    textureRect1.left = 0;
    textureRect1.top = 0;
    textureRect1.width = 10;
    textureRect1.height = 10;
    textureRect2.left = 10;
    textureRect2.top = 0;
    textureRect2.width = 10;
    textureRect2.height = 10;
    textureRect2.left = 20;
    textureRect2.top = 0;
    textureRect2.width = 10;
    textureRect2.height = 10;
    x = _x;
    y = _y;
    texture.loadFromFile("sprites/explosion.png");
    sprite.setTexture(texture);
    sprite.setTextureRect(textureRect1);
    sprite.setOrigin(5, 10);
    sprite.setPosition(x, y);

    clock.restart();
}

void Explosion::update()
{

    if (clock.getElapsedTime() > time)
    {
        clock.restart();

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
            isActive = false;
        }
    }

}