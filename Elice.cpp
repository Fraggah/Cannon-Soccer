#include "Elice.h"

Elice::Elice(b2World& mundo, float _x, float _y)
{
    isEnabled = true;
    x = _x;
    y = _y;
    texture.loadFromFile("sprites/elipse.png");
    sprite.setTexture(texture);
    physics = Box2DHelper::CreateRectangularKinematicBody(&mundo, 25, 2);
    physics->SetTransform(b2Vec2(x, y), 0);
    sprite.setOrigin(12.5, 1);
}

void Elice::update(float vel)
{
    float newAngle = physics->GetAngle() + vel;
    physics->SetTransform(physics->GetPosition(), newAngle);
    physics->GetFixtureList()->SetDensity(0);
    sprite.setPosition(x, y);
    sprite.setRotation(physics->GetAngle() * 180 / b2_pi);
}

void Elice::render(sf::RenderWindow& window)
{
    if (isEnabled)
    {
        window.draw(sprite);
    }
}

void Elice::setOnOff(bool on)
{
    isEnabled = on;
    physics->SetEnabled(on);
}
