#include "GiantBall.h"

GiantBall::GiantBall(b2World& mundo, float _x1, float _y1, float _x2, float _y2)
{
    x1 = _x1;
    y1 = _y1;
    x2 = _x2;
    y2 = _y2;

    physics = Box2DHelper::CreateCircularDynamicBody(&mundo, 10, 0.2, 0.2, 0.2);
    physics->SetTransform(b2Vec2(x1, y1), 0);

    texture.loadFromFile("sprites/giantBall.png");
    sprite.setTexture(texture);
    sprite.setOrigin(10, 10);

    hook = Box2DHelper::CreateRectangularStaticBody(&mundo, 10, 10);
    hook->SetTransform(b2Vec2(x2, y2), 0);

    chainDef.Initialize(hook, physics, b2Vec2(hook->GetPosition().x, hook->GetPosition().y), b2Vec2(physics->GetPosition().x, physics->GetPosition().y));
    chainDef.length = 42;
    chainDef.maxLength = 44;
    chainDef.minLength = 40;
    chainDef.collideConnected = true;
    chainDJ = (b2DistanceJoint*)mundo.CreateJoint(&chainDef);
}

void GiantBall::update()
{
    sprite.setPosition(physics->GetPosition().x, physics->GetPosition().y);
    sprite.setRotation(physics->GetAngle() * 180 / b2_pi);
    line[0] = {
        sf::Vertex(sf::Vector2f(physics->GetPosition().x,physics->GetPosition().y), sf::Color(203, 232, 247))
    };
    line[1] = {
    sf::Vertex(sf::Vector2f(hook->GetPosition().x,hook->GetPosition().y), sf::Color(203, 232, 247))
    };
}

void GiantBall::render(sf::RenderWindow& window)
{
    if (isEnabled)
    {
        window.draw(line, 2, sf::Lines);
        window.draw(sprite);
    }
}

void GiantBall::setOnOff(bool on)
{
    isEnabled = on;
    physics->SetEnabled(on);
    hook->SetEnabled(on);
}