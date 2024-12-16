#include "Box.h"

Box::Box(b2World& mundo, float _x, float _y)
{
    x = _x;
    y = _y;
    physics = Box2DHelper::CreateRectangularStaticBody(&mundo, 5, 5);
    physics->SetTransform(b2Vec2(x, y), 0);
    sprite.setOrigin(2.5, 2.5);
    sprite.setPosition(_x, _y);
    texture.loadFromFile("sprites/block.png");
    sprite.setTexture(texture);
}

void Box::render(sf::RenderWindow& window)
{
    if (isEnabled)
    {
        window.draw(sprite);
    }
}

void Box::setOnOff(bool on)
{
    isEnabled = on;
    physics->SetEnabled(on);
}