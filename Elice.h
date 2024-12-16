#include <SFML/Graphics.hpp>
#include "Box2DHelper.h"

class Elice
{
    float x;
    float y;
    sf::Sprite sprite;
    sf::Texture texture;
public:
    b2Body* physics;
    bool isEnabled;
    Elice(b2World& mundo, float _x, float _y);
    void update(float vel);
    void render(sf::RenderWindow& window);
    void setOnOff(bool on);
};
