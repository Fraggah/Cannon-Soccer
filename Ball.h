#include <SFML/Graphics.hpp>
#include "Box2DHelper.h"

class Ball : public Box2DHelper
{
    float x;
    float y;
    sf::Texture texture;
public:
    b2Body* physics;
    bool reached;
    bool isEnabled = false;
    float radius;
    sf::Sprite sprite;
    Ball(b2World& mundo, float _x, float _y);
    void update();
    void render(sf::RenderWindow& window);
    void setOnOff(bool on);
};

