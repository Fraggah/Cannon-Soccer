#include "Box.h"

ABox::ABox(b2World& World, float _X, float _Y)
{
    X = _X;
    Y = _Y;
    Physics = Box2DHelper::CreateRectangularStaticBody(&World, 5, 5);
    Physics->SetTransform(b2Vec2(X, Y), 0);
    Sprite.setOrigin(2.5, 2.5);
    Sprite.setPosition(_X, _Y);
    Texture.loadFromFile("sprites/block.png");
    Sprite.setTexture(Texture);
}

void ABox::render(sf::RenderWindow& Window)
{
    if (bIsEnabled)
    {
        Window.draw(Sprite);
    }
}

void ABox::setOnOff(bool on)
{
    bIsEnabled = on;
    Physics->SetEnabled(on);
}