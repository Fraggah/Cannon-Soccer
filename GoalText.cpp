#include "GoalText.h"

AGoalText::AGoalText()
{
    Sprite.setOrigin(75, 50);
    Sprite.setPosition(75, 50);
    Texture.loadFromFile("sprites/goalText.png");
    Sprite.setTexture(Texture);
    Time = sf::seconds(.9);
    Clock.restart();
}

void AGoalText::render(sf::RenderWindow& Window)
{
    ElapsedTime = Clock.getElapsedTime(); //Obtengo el tiempo en una variable
    Progress = ElapsedTime.asSeconds() * 4 / Time.asSeconds();//Calculo el porcentaje del progreso

    if (Progress > 1.0f) Progress = 1.0f; //Aseguro que el progreeso quede solo el 1

    // Escalo desde 0.1 a 1
    float Scale = 0.1f + (Progress * 0.9f);
    Sprite.setScale(Scale, Scale);

    // mismo metodo en el canal alpha, llevandolo hacia opacidad 0
    int Alpha = static_cast<int>(255 * (1.0f - Progress)); //Casteo la variable a int ya que es un float
    if (Alpha < 0) Alpha = 0; // Aseguro que no sea negativo

    Sprite.setColor(sf::Color(255, 255, 255, Alpha)); // Aplico opacidad


    //Cada vez que se resetea Clock, se inicia la animacion
    //Una vez pasado Time, deja de renderizarse.
    if (ElapsedTime < Time)
    {
        Window.draw(Sprite);
    }
}
