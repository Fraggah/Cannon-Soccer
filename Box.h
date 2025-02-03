#include <SFML/Graphics.hpp>
#include "Box2DHelper.h"

class ABox : public Box2DHelper
{
    float X;
    float Y;
    sf::Texture Texture;
public:
    b2Body* Physics;
    sf::Sprite Sprite;
    bool bIsEnabled = false;
    ABox(b2World& World, float _X, float _Y);
    void render(sf::RenderWindow& Window);
    void setOnOff(bool On);
};

//Leer Ball... es lo mismo pero con menos logica.