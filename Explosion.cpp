#include "Explosion.h"

AExplosion::AExplosion(float _X, float _Y)
{
    TRect1.left = 0;
    TRect1.top = 0;
    TRect1.width = 10;
    TRect1.height = 10;
    TRect2.left = 10;
    TRect2.top = 0;
    TRect2.width = 10;
    TRect2.height = 10;
    TRect2.left = 20;
    TRect2.top = 0;
    TRect2.width = 10;
    TRect2.height = 10;
    X = _X;
    Y = _Y;
    Texture.loadFromFile("sprites/explosion.png");
    Sprite.setTexture(Texture);
    Sprite.setTextureRect(TRect1);
    Sprite.setOrigin(5, 10);
    Sprite.setPosition(X, Y);

    Clock.restart();
}

void AExplosion::update()
{

    if (Clock.getElapsedTime() > Time)
    {
        Clock.restart();

        if (Sprite.getTextureRect() == TRect1)
        {
            Sprite.setTextureRect(TRect2);
        }
        else if (Sprite.getTextureRect() == TRect2)
        {
            Sprite.setTextureRect(TRect3);
        }
        else if (Sprite.getTextureRect() == TRect3)
        {
            bIsActive = false;
        }
    }

}