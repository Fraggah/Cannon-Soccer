#include <SFML/Graphics.hpp>
#include "Box2DHelper.h"

class AElice
{
    float X;
    float Y;
    sf::Sprite Sprite;
    sf::Texture Texture;
public:
    b2Body* Physics;
    bool bIsEnabled;
    AElice(b2World& World, float _X, float _Y);
    void update(float Vel);
    void render(sf::RenderWindow& Window);
    void setOnOff(bool On);
};

// Similar a Ball, pero con logica de rotacion en update()
