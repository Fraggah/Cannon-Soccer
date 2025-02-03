#include "Background.h"

ABackground::ABackground()
{
    Texture.loadFromFile("sprites/animatedB.png");
    Sprite.setTexture(Texture);
    Sprite.setTextureRect(TRect1);
    // La forma que encontré de bajar la opacidad es:
    // 1 - Capturar el valor del color del sprite en una variable
    // 2 - Bajar el valor del canal alfa, por defecto viene en 255
    // 3 - Setear el nuevo valor sobre el sprite original
    sf::Color Color = Sprite.getColor();
    Color.a = 140;
    Sprite.setColor(Color);
}

void ABackground::update()
{
    // Mi manera de hacer funcionar las animaciones es reseteando un reloj
    // y por cada reset le asigno  un IntRect diferente, el tiempo de reset
    // esta seteado en la variable Time
    if (Clock.getElapsedTime() > Time)
    {
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
            Sprite.setTextureRect(TRect1);
        }
        Clock.restart();
    }
}

void ABackground::render(sf::RenderWindow& window)
{
    window.draw(Sprite);
}