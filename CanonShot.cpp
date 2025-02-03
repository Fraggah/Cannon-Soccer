#include "CanonShot.h"

ACannonShoot::ACannonShoot(float _x, float _y)
{
    TRect1.left = 0;
    TRect1.top = 0;
    TRect1.width = 10;
    TRect1.height = 10;
    TRect2.left = 10;
    TRect2.top = 0;
    TRect2.width = 10;
    TRect2.height = 10;
    X = _x;
    Y = _y;
    Texture.loadFromFile("sprites/shot.png");
    Sprite.setTexture(Texture);
    Sprite.setTextureRect(TRect1);
    Sprite.setOrigin(5, 5);
    Sprite.setPosition(X, Y);
}

void ACannonShoot::update()
{
    if (Clock.getElapsedTime() > Time)
    {
        if (Sprite.getTextureRect() == TRect1)
        {
            Sprite.setTextureRect(TRect2);
        }
        else
        {
            bIsActive = false;
        }
        Clock.restart();
    }
}