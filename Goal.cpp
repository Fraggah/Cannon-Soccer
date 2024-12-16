#include "Goal.h"

Goal::Goal(float _x, float _y)
{
    radius = 5;
    x = _x;
    y = _y;
    sprite.setOrigin(5, 5);
    sprite.setPosition(_x, _y);
    texture.loadFromFile("sprites/goal.png");
    sprite.setTexture(texture);
}

void Goal::activate()
{
    isActive = true;
    clock.restart();
}

void Goal::update()
{
    if (isActive)
    {
        if (clock.getElapsedTime() > time)
        {
            sprite.setScale(1.2, 1.2);
            isActive = false;
        }
    }
    else
    {
        sprite.setScale(1, 1);
    }
}