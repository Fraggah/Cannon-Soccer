#include "Transition.h"

Transition::Transition(sf::String level)
{
    levelString = level;
    font.loadFromFile("sprites/nes.otf");
    levelText.setFont(font);
    levelText.setString(levelString);
    levelText.setCharacterSize(24);
    levelText.setScale(.2, .2);
    levelText.setPosition(63, 45);
    levelText.setFillColor(sf::Color(203, 232, 247));
    texture.loadFromFile("sprites/transition.png");
    sprite.setTexture(texture);
    sprite.setTextureRect(textureRect1);
    sprite.setOrigin(75, 50);
    sprite.setPosition(sprite.getOrigin());
}

void Transition::update()
{
    if (clock.getElapsedTime() > sf::milliseconds(100))
    {
        sprite.setTextureRect(textureRect2);
    }
    if (clock.getElapsedTime() > sf::milliseconds(200))
    {
        sprite.setTextureRect(textureRect3);
    }
    if (clock.getElapsedTime() > sf::milliseconds(300))
    {
        sprite.setTextureRect(textureRect4);
    }
    if (clock.getElapsedTime() > sf::milliseconds(400))
    {
        sprite.setTextureRect(textureRect5);
    }
    if (clock.getElapsedTime() > sf::milliseconds(500)) //Negro
    {
        sprite.setTextureRect(textureRect6);
    }
    if (clock.getElapsedTime() > sf::milliseconds(600)) //Pasar texto
    {
        textActive = true;
    }
    if (clock.getElapsedTime() > sf::milliseconds(1400)) //Pasar texto
    {
        textActive = false;
        //quiero aqui usar un delegate y enviar una señal para utilizar una funcion de la clase main
        if (onTransitionEnd) { // intento de delegate
            onTransitionEnd();
        }
    }
    if (clock.getElapsedTime() > sf::milliseconds(1500))
    {
        sprite.setScale(-1, 1);
        sprite.setTextureRect(textureRect5);
    }
    if (clock.getElapsedTime() > sf::milliseconds(1600))
    {
        sprite.setTextureRect(textureRect4);
    }
    if (clock.getElapsedTime() > sf::milliseconds(1700))
    {
        sprite.setTextureRect(textureRect3);
    }
    if (clock.getElapsedTime() > sf::milliseconds(1800))
    {
        sprite.setTextureRect(textureRect2);
    }
    if (clock.getElapsedTime() > sf::milliseconds(1900))
    {
        sprite.setTextureRect(textureRect1);
    }
    if (clock.getElapsedTime() > sf::milliseconds(2000))
    {
        isActive = false;
    }
}

void Transition::render(sf::RenderWindow& window)
{
    if (isActive)
    {
        window.draw(sprite);
    }
    if (textActive)
    {
        window.draw(levelText);
    }
}