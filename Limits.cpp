#include "Limits.h"

Limits::Limits(b2World& mundo)
{
    // Físicas del Piso
    groundBody = Box2DHelper::CreateRectangularStaticBody(&mundo, 500, 10);
    groundBody->SetTransform(b2Vec2(50.0f, 95.0f), 0);
    groundBody->GetFixtureList()->SetFriction(3);

    // Físicas de Paredes
    leftWallBody = Box2DHelper::CreateRectangularStaticBody(&mundo, 10, 100);
    leftWallBody->SetTransform(b2Vec2(5.0f, 50.0f), 0.0f);
    rightWallBody = Box2DHelper::CreateRectangularStaticBody(&mundo, 10, 100);
    rightWallBody->SetTransform(b2Vec2(145.0f, 50.0f), 0.0f);

    texture.loadFromFile("sprites/background.png");
    sprite.setTexture(texture);
}

void Limits::render(sf::RenderWindow& window)
{
    ;   window.draw(sprite);
}