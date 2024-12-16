#include "Ball.h"

Ball::Ball(b2World& mundo, float _x, float _y)
{
    reached = false;
    radius = 2.5;
    x = _x;
    y = _y;
    physics = Box2DHelper::CreateCircularDynamicBody(&mundo, 2.5, 0.2, 0.2, 0.2);
    physics->SetTransform(b2Vec2(x, y), 0);

    sprite.setOrigin(2.5, 2.5);
    texture.loadFromFile("sprites/ball.png");
    sprite.setTexture(texture);
}

void Ball::update()
{
    sprite.setPosition(physics->GetPosition().x, physics->GetPosition().y);
    sprite.setRotation(physics->GetAngle() * 180 / b2_pi);
}

void Ball::render(sf::RenderWindow& window)
{
    if (isEnabled)
    {
        window.draw(sprite);
    }
}

void Ball::setOnOff(bool on)
{
    isEnabled = on;
    physics->SetEnabled(on);
}