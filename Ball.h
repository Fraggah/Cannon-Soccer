#include <SFML/Graphics.hpp>
#include "Box2DHelper.h"

class ABall : public Box2DHelper
{
    float X;
    float Y;
    sf::Texture Texture;
public:
    b2Body* Physics;
    //Variable para marcar como que la bola alcanzo el arco.
    //Util para en la logica central contar si todas las bolas entraron en el arco
    bool bIsReached;
    //Variable para ejecutar o no logica (render, update, etc)
    bool bIsEnabled = false;
    float Radius;
    sf::Sprite Sprite;
    ABall(b2World& World, float _X, float _Y);
    void update();
    void render(sf::RenderWindow& Window);
    void setOnOff(bool on);
};

