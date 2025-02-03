#include "Transition.h"

ATransition::ATransition(sf::String Level)
{
    LevelString = Level;
    Font.loadFromFile("sprites/nes.otf");
    LevelText.setFont(Font);
    LevelText.setString(LevelString);
    LevelText.setCharacterSize(24);
    LevelText.setScale(.2, .2);
    LevelText.setPosition(63, 45);
    LevelText.setFillColor(sf::Color(203, 232, 247));
    Texture.loadFromFile("sprites/transition.png");
    Sprite.setTexture(Texture);
    Sprite.setTextureRect(TRect1);
    Sprite.setOrigin(75, 50);
    Sprite.setPosition(Sprite.getOrigin());
}

void ATransition::update()
{
    if (Clock.getElapsedTime() > sf::milliseconds(100))
    {
        Sprite.setTextureRect(TRect2);
    }
    if (Clock.getElapsedTime() > sf::milliseconds(200))
    {
        Sprite.setTextureRect(TRect3);
    }
    if (Clock.getElapsedTime() > sf::milliseconds(300))
    {
        Sprite.setTextureRect(TRect4);
    }
    if (Clock.getElapsedTime() > sf::milliseconds(400))
    {
        Sprite.setTextureRect(TRect5);
    }
    if (Clock.getElapsedTime() > sf::milliseconds(500)) //Negro
    {
        Sprite.setTextureRect(TRect6);
    }
    if (Clock.getElapsedTime() > sf::milliseconds(600)) //Pasar texto
    {
        TextActive = true;
    }
    if (Clock.getElapsedTime() > sf::milliseconds(1400)) //Pasar texto
    {
        TextActive = false;
        if (OnTransitionEnd) { // llamo a la funcion callback
            OnTransitionEnd();
        }
    }
    if (Clock.getElapsedTime() > sf::milliseconds(1500))
    {
        Sprite.setScale(-1, 1);
        Sprite.setTextureRect(TRect5);
    }
    if (Clock.getElapsedTime() > sf::milliseconds(1600))
    {
        Sprite.setTextureRect(TRect4);
    }
    if (Clock.getElapsedTime() > sf::milliseconds(1700))
    {
        Sprite.setTextureRect(TRect3);
    }
    if (Clock.getElapsedTime() > sf::milliseconds(1800))
    {
        Sprite.setTextureRect(TRect2);
    }
    if (Clock.getElapsedTime() > sf::milliseconds(1900))
    {
        Sprite.setTextureRect(TRect1);
    }
    if (Clock.getElapsedTime() > sf::milliseconds(2000))
    {
        bIsActive = false;
    }
}

void ATransition::render(sf::RenderWindow& Window)
{
    if (bIsActive)
    {
        Window.draw(Sprite);
    }
    if (TextActive)
    {
        Window.draw(LevelText);
    }
}