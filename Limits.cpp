#include "Limits.h"

ALimits::ALimits(b2World& World)
{
    GroundBody = Box2DHelper::CreateRectangularStaticBody(&World, 500, 10);
    GroundBody->SetTransform(b2Vec2(50.0f, 95.0f), 0);
    GroundBody->GetFixtureList()->SetFriction(3);

    LeftWallBody = Box2DHelper::CreateRectangularStaticBody(&World, 10, 100);
    LeftWallBody->SetTransform(b2Vec2(5.0f, 50.0f), 0.0f);
    RightWallBody = Box2DHelper::CreateRectangularStaticBody(&World, 10, 100);
    RightWallBody->SetTransform(b2Vec2(145.0f, 50.0f), 0.0f);

    Texture.loadFromFile("sprites/background.png");
    Sprite.setTexture(Texture);
}

void ALimits::render(sf::RenderWindow& Window)
{
    Window.draw(Sprite);
}