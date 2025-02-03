#pragma once
#include <SFML/Graphics.hpp>
#include "Box2DHelper.h"

class ARagdoll : public Box2DHelper {
    sf::Color RagdollColor;
    float DBB = 2; //Distance between bodies
    float Scale = 0.3; //Variable para cambiar el tamaño del ragdoll completo si no me convence su tamaño final y asi evito setear cada parte
    //Cabeza
    float HeadWidth = 5;
    float HeadHeight = 5;
    b2Body* bHead;
    sf::RectangleShape sHead;
    //Tronco
    float ChestWidth = 7;
    float ChestHeight = 10;
    sf::RectangleShape sChest;
    //Brazos
    float ArmWidth = 3;
    float ArmHeight = 7;
    //Brazo Izquierdo
    b2Body* bArmL;
    sf::RectangleShape sArmL;
    ////Brazo Derecho
    b2Body* bArmR;
    sf::RectangleShape sArmR;
    //Piernas
    float LegWidth = 3;
    float LegHeight = 10;
    //Pierna Izquierda
    b2Body* bLegL;
    sf::RectangleShape sLegL;
    //Pierna Derecha
    b2Body* bLegR;
    sf::RectangleShape sLegR;
    //Joints
    //Cuello
    b2DistanceJointDef NeckDef;
    b2DistanceJoint* NeckDJ;
    //Hombros
    //Hombro Izquierdo
    b2RevoluteJointDef ShoulderLDef;
    b2RevoluteJoint* ShoulderLRJ;
    //Hombro Derecho
    b2RevoluteJointDef ShoulderRDef;
    b2RevoluteJoint* ShoulderRRJ;
    //Cadera
    //Parte Izquierda
    b2RevoluteJointDef HipLDef;
    b2RevoluteJoint* HipLRJ;
    //Parte Derecha
    b2RevoluteJointDef HipRDef;
    b2RevoluteJoint* HipRRJ;
public:
    b2Body* bChest;
    bool bIsEnabled = true;
    ARagdoll(b2World& World, float X, float Y);
    ~ARagdoll();
    void setOff();
    void applyImpulse(b2Vec2 Dir);
    void render(sf::RenderWindow& Window);
    void update();
};

//Resumo: Aqui esta la creacion del ragdoll, este mismo esta compuesto por defirentes partes
//siendo ellas una combinacion de cuerpos fisicos dinamicos joints para unirlos
//En GiantBall explico como usar un joint.