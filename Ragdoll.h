#pragma once
#include <SFML/Graphics.hpp>
#include "Box2DHelper.h"

class Ragdoll : public Box2DHelper {
    sf::Color ragdollColor;
    float dec = 2;
    float scale = 0.3;
    //Cabeza
    float anchoCabeza = 5;
    float altoCabeza = 5;
    b2Body* bCabeza;
    sf::RectangleShape sCabeza;
    //Tronco
    float anchoTronco = 7;
    float altoTronco = 10;
    sf::RectangleShape sTronco;
    //Brazos
    float anchoBrazo = 3;
    float altoBrazo = 7;
    //Brazo Izquierdo
    b2Body* bBrazoI;
    sf::RectangleShape sBrazoI;
    ////Brazo Derecho
    b2Body* bBrazoD;
    sf::RectangleShape sBrazoD;
    //Piernas
    float anchoPierna = 3;
    float altoPierna = 10;
    //Pierna Izquierda
    b2Body* bPiernaI;
    sf::RectangleShape sPiernaI;
    //Pierna Derecha
    b2Body* bPiernaD;
    sf::RectangleShape sPiernaD;
    //Joints
    //Cuello
    b2DistanceJointDef cuelloDef;
    b2DistanceJoint* cuelloDJ;
    //Hombros
    //Hombro Izquierdo
    b2RevoluteJointDef hombroIDef;
    b2RevoluteJoint* hombroIRJ;
    //Hombro Derecho
    b2RevoluteJointDef hombroDDef;
    b2RevoluteJoint* hombroDRJ;
    //Cadera
    //Parte Izquierda
    b2RevoluteJointDef CPIDef;
    b2RevoluteJoint* CPIRJ;
    //Parte Derecha
    b2RevoluteJointDef CPDDef;
    b2RevoluteJoint* CPDRJ;
public:
    b2Body* bTronco;
    bool isEnabled = true;
    Ragdoll(b2World& mundo, float x, float y);
    ~Ragdoll();
    void setOff();
    void applyImpulse(b2Vec2 dir, bool flag);
    void render(sf::RenderWindow& window);
    void update();
};