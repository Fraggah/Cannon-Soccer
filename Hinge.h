#include <SFML/Graphics.hpp>
#include "Box2DHelper.h"

class AHinge {
    float X1;
    float Y1;
    float X2;
    float Y2;
    sf::Sprite Sprite;
    sf::Texture Texture;

public:
    b2RevoluteJointDef RevDef;
    b2RevoluteJoint* RevRJ;
    b2Body* Nail;
    b2Body* Physics;
    bool bIsEnabled = true;
    AHinge(b2World& World, float _X1, float _Y1, float _X2, float _Y2);
    void update();
    void render(sf::RenderWindow& Window);
    void setOnOff(bool On);
};

// Similar a elice, pero en este caso utilizo un Revolute Joint
// Este tiene funciones de toracion automaticas, pero en esta ocacion
//solo girará por las fuerzas fisicas, su centro de rotacion en Nail, otro cuerpo fisico pero estatico
