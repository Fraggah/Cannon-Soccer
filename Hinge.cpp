#include "Hinge.h"

Hinge::Hinge(b2World& mundo, float _x1, float _y1, float _x2, float _y2)
{
    x1 = _x1;
    y1 = _y1;
    x2 = _x2;
    y2 = _y2;

    physics = Box2DHelper::CreateRectangularDynamicBody(&mundo, 3, 25, 0.2, 0.2, 0.2);
    physics->SetTransform(b2Vec2(x1, y1), 0);

    texture.loadFromFile("sprites/elicereact.png");
    sprite.setTexture(texture);
    sprite.setOrigin(1.5, 12.5);

    nail = Box2DHelper::CreateCircularStaticBody(&mundo, 1);
    nail->SetTransform(b2Vec2(x2, y2), 0);

    revDef.Initialize(nail, physics, b2Vec2(nail->GetPosition().x, nail->GetPosition().y));

    revRJ = (b2RevoluteJoint*)mundo.CreateJoint(&revDef);
}

void Hinge::update()
{
    sprite.setPosition(physics->GetPosition().x, physics->GetPosition().y);
    sprite.setRotation(physics->GetAngle() * 180 / b2_pi);
}

void Hinge::render(sf::RenderWindow& window)
{
    if (isEnabled)
    {
        window.draw(sprite);
    }
}

void Hinge::setOnOff(bool on)
{
    isEnabled = on;
    physics->SetEnabled(on);
    nail->SetEnabled(on);
}