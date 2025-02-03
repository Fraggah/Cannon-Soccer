#include "BoxParticle.h"

ABoxParticle::ABoxParticle(float _x, float _y)
{
    TRect1.left = 0;
    TRect1.top = 0;
    TRect1.width = 5;
    TRect1.height = 5;
    TRect2.left = 5;
    TRect2.top = 0;
    TRect2.width = 5;
    TRect2.height = 5;
    X = _x;
    Y = _y;
    Texture.loadFromFile("sprites/blockdis.png");
    Sprite.setTexture(Texture);
    Sprite.setTextureRect(TRect1);
    Sprite.setOrigin(2.5, 2.5);
    Sprite.setPosition(X, Y);
}

void ABoxParticle::update()
{
    if (Clock.getElapsedTime() > Time)
    {
        if (Sprite.getTextureRect() == TRect1)
        {
            Sprite.setTextureRect(TRect2);
        }
        else
        {
            bIsActive = false; //Desactiva para no loopear
        }
        Clock.restart();
    }
}