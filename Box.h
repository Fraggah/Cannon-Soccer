#include <SFML/Graphics.hpp>
#include "Box2DHelper.h"

class Box : public Box2DHelper
{
    float x;
    float y;
    sf::Texture texture;
public:
    b2Body* physics;
    sf::Sprite sprite;
    bool isEnabled = false;
    Box(b2World& mundo, float _x, float _y);
    void render(sf::RenderWindow& window);
    void setOnOff(bool on);
};
