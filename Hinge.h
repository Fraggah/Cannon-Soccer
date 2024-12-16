#include <SFML/Graphics.hpp>
#include "Box2DHelper.h"

class Hinge {
    float x1;
    float y1;
    float x2;
    float y2;
    sf::Sprite sprite;
    sf::Texture texture;

public:
    b2RevoluteJointDef revDef;
    b2RevoluteJoint* revRJ;
    b2Body* nail;
    b2Body* physics;
    bool isEnabled = true;
    Hinge(b2World& mundo, float _x1, float _y1, float _x2, float _y2);
    void update();
    void render(sf::RenderWindow& window);
    void setOnOff(bool on);
};
