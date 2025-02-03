#include "Hinge.h"

AHinge::AHinge(b2World& World, float _X1, float _Y1, float _X2, float _Y2)
{
    X1 = _X1;
    Y1 = _Y1;
    X2 = _X2;
    Y2 = _Y2;

    Physics = Box2DHelper::CreateRectangularDynamicBody(&World, 3, 25, 0.2, 0.2, 0.2);
    Physics->SetTransform(b2Vec2(X1, Y1), 0);

    Texture.loadFromFile("sprites/elicereact.png");
    Sprite.setTexture(Texture);
    Sprite.setOrigin(1.5, 12.5);

    Nail = Box2DHelper::CreateCircularStaticBody(&World, 1);
    Nail->SetTransform(b2Vec2(X2, Y2), 0);

    RevDef.Initialize(Nail, Physics, b2Vec2(Nail->GetPosition().x, Nail->GetPosition().y));

    RevRJ = (b2RevoluteJoint*)World.CreateJoint(&RevDef);
}

void AHinge::update()
{
    Sprite.setPosition(Physics->GetPosition().x, Physics->GetPosition().y);
    Sprite.setRotation(Physics->GetAngle() * 180 / b2_pi);
}

void AHinge::render(sf::RenderWindow& Window)
{
    if (bIsEnabled)
    {
        Window.draw(Sprite);
    }
}

void AHinge::setOnOff(bool On)
{
    bIsEnabled = On;
    Physics->SetEnabled(On);
    Nail->SetEnabled(On);
}