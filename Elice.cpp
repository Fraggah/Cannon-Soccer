#include "Elice.h"

AElice::AElice(b2World& World, float _X, float _Y)
{
    bIsEnabled = true;
    X = _X;
    Y = _Y;
    Texture.loadFromFile("sprites/elipse.png");
    Sprite.setTexture(Texture);
    Physics = Box2DHelper::CreateRectangularKinematicBody(&World, 25, 2);
    Physics->SetTransform(b2Vec2(X, Y), 0);
    Sprite.setOrigin(12.5, 1);
}

void AElice::update(float Vel)
{
    //Creo una variable local para almacenar el valor del angulo a setear,
    //le sumo la variable Vel para que el aungulo vaya aumentando constantemete
    float NewAngle = Physics->GetAngle() + Vel;
    //Seteo directamente el angulo en Physics ya el angulo es obtenido desde el mismo cuerpo fisico que usa radianes
    Physics->SetTransform(Physics->GetPosition(), NewAngle);
    Physics->GetFixtureList()->SetDensity(0);
    Sprite.setPosition(X, Y);
    //Para SFML debo convertir el valor del angulo a grados ya que Box2D utiliza radianes
    Sprite.setRotation(Physics->GetAngle() * 180 / b2_pi);
}

void AElice::render(sf::RenderWindow& Window)
{
    if (bIsEnabled)
    {
        Window.draw(Sprite);
    }
}

void AElice::setOnOff(bool On)
{
    bIsEnabled = On;
    Physics->SetEnabled(On);
}
