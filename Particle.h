#pragma once

#include <SFML/Graphics.hpp>

class AParticle
{
protected:
    float X;
    float Y;
    sf::Sprite Sprite;
    sf::Texture Texture;
    sf::IntRect TRect1;
    sf::IntRect TRect2;
    sf::IntRect TRect3;
    sf::Clock Clock;
    sf::Time Time{ sf::milliseconds(50) };
public:
    bool bIsActive = true;
    virtual void update() = 0;
    virtual void render(sf::RenderWindow& Window);
};

//Clase padre para todas las particulas
//Para saber del uso de los IntRet leer CanonShot