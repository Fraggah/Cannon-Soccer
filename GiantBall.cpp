#include "GiantBall.h"

AGiantBall::AGiantBall(b2World& World, float _X1, float _Y1, float _X2, float _Y2)
{
    X1 = _X1;
    Y1 = _Y1;
    X2 = _X2;
    Y2 = _Y2;

    Physics = Box2DHelper::CreateCircularDynamicBody(&World, 10, 0.2, 0.2, 0.2);
    Physics->SetTransform(b2Vec2(X1, Y1), 0);

    Texture.loadFromFile("sprites/giantBall.png");
    Sprite.setTexture(Texture);
    Sprite.setOrigin(10, 10);

    Hook = Box2DHelper::CreateRectangularStaticBody(&World, 10, 10);
    Hook->SetTransform(b2Vec2(X2, Y2), 0);

    //Inicializacion de la definicion y seteo de parametros
    ChainDef.Initialize(Hook, Physics, b2Vec2(Hook->GetPosition().x, Hook->GetPosition().y), b2Vec2(Physics->GetPosition().x, Physics->GetPosition().y));
    ChainDef.length = 42;
    ChainDef.maxLength = 44;
    ChainDef.minLength = 40;
    ChainDef.collideConnected = true;
    //Creacion del joint
    ChainDJ = (b2DistanceJoint*)World.CreateJoint(&ChainDef);
}

void AGiantBall::update()
{
    Sprite.setPosition(Physics->GetPosition().x, Physics->GetPosition().y);
    Sprite.setRotation(Physics->GetAngle() * 180 / b2_pi);
    //Seteo la posicion de la linea, dandole la posicion de los cuerpos fisicos como parametros
    Line[0] = {
        sf::Vertex(sf::Vector2f(Physics->GetPosition().x,Physics->GetPosition().y), sf::Color(203, 232, 247))
    };
    Line[1] = {
    sf::Vertex(sf::Vector2f(Hook->GetPosition().x,Hook->GetPosition().y), sf::Color(203, 232, 247))
    };
}

void AGiantBall::render(sf::RenderWindow& Window)
{
    if (bIsEnabled)
    {
        Window.draw(Line, 2, sf::Lines);
        Window.draw(Sprite);
    }
}

void AGiantBall::setOnOff(bool On)
{
    bIsEnabled = On;
    Physics->SetEnabled(On);
    Hook->SetEnabled(On);
}