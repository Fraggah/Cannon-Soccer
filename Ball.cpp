#include "Ball.h"

ABall::ABall(b2World& World, float _X, float _Y)
{
    bIsReached = false;
    Radius = 2.5;
    X = _X;
    Y = _Y;
    //Creacion del objeto fisico
    Physics = Box2DHelper::CreateCircularDynamicBody(&World, 2.5, 0.2, 0.2, 0.2);
    Physics->SetTransform(b2Vec2(X, Y), 0);

    //Los objetos fisicos por defecto tienen el origen en el centro
    //Pero los sprites de SFML no, por lo que seteo el origen al centro 
    //para que coincidan
    Sprite.setOrigin(2.5, 2.5);
    Texture.loadFromFile("sprites/ball.png");
    Sprite.setTexture(Texture);
}

void ABall::update()
{
    //Actualizacion de Locacion y Rotacion
    Sprite.setPosition(Physics->GetPosition().x, Physics->GetPosition().y);
    Sprite.setRotation(Physics->GetAngle() * 180 / b2_pi);
}

void ABall::render(sf::RenderWindow& Window)
{
    if (bIsEnabled)
    {
        Window.draw(Sprite);
    }
}

void ABall::setOnOff(bool on)
{
    bIsEnabled = on;
    Physics->SetEnabled(on);
}