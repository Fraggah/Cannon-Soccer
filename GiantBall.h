#include <SFML/Graphics.hpp>
#include "Box2DHelper.h"

class GiantBall
{
    float x1;
    float y1;
    float x2;
    float y2;
    sf::Sprite sprite;
    sf::Texture texture;
    sf::Vertex line[2];

public:
    b2DistanceJointDef chainDef;
    b2DistanceJoint* chainDJ;
    b2Body* hook;
    b2Body* physics;
    bool isEnabled = false;
    GiantBall(b2World& mundo, float _x1, float _y1, float _x2, float _y2);
    void update();
    void render(sf::RenderWindow& window);
    void setOnOff(bool on);
};
