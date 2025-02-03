#include "Goal.h"

AGoal::AGoal(float _X, float _Y)
{
    Radius = 5;
    X = _X;
    Y = _Y;
    Sprite.setOrigin(5, 5);
    Sprite.setPosition(_X, _Y);
    Texture.loadFromFile("sprites/goal.png");
    Sprite.setTexture(Texture);
}

//Paso la variable a true para que pueda ejecutar la logica del update
//Tambien reseteo el reloj, ya que este se inicia en la creacion del objeto
void AGoal::activate()
{
    bIsActive = true;
    Clock.restart();
}

//la "Animacion" consta de un pequeño aumento de la scala que se resetea
//cuando Clock llega al valor de Time
void AGoal::update()
{
    if (bIsActive)
    {
        if (Clock.getElapsedTime() > Time)
        {
            Sprite.setScale(1.2, 1.2);
            bIsActive = false;
        }
    }
    else
    {
        Sprite.setScale(1, 1);
    }
}