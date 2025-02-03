#include "Ragdoll.h"

ARagdoll::ARagdoll(b2World& World, float X, float Y) {
    RagdollColor = sf::Color(203, 232, 247);

    //Scale
    DBB *= Scale;
    HeadWidth *= Scale;
    HeadHeight *= Scale;
    ChestWidth *= Scale;
    ChestHeight *= Scale;
    ArmWidth *= Scale;
    ArmHeight *= Scale;
    LegWidth *= Scale;
    LegHeight *= Scale;

    //Cabeza
    bHead = Box2DHelper::CreateRectangularDynamicBody(&World, HeadWidth, HeadHeight, 2, 0.1, 0.1);
    bHead->SetTransform(b2Vec2(X, Y), 0);

    sHead.setSize(sf::Vector2f(HeadWidth, HeadHeight));
    sHead.setOrigin(HeadWidth / 2, HeadHeight / 2);
    sHead.setFillColor(RagdollColor);

    //Tronco
    bChest = Box2DHelper::CreateRectangularDynamicBody(&World, ChestWidth, ChestHeight, 2, 0.1, 0.1);
    bChest->SetTransform(b2Vec2(bHead->GetPosition().x, bHead->GetPosition().y + ChestHeight / 2 + HeadHeight / 2 - DBB), 0);

    sChest.setSize(sf::Vector2f(ChestWidth, ChestHeight));
    sChest.setOrigin(ChestWidth / 2, ChestHeight / 2);
    sChest.setFillColor(RagdollColor);
    //Brazos
    //Brazo Izquierdo
    bArmL = Box2DHelper::CreateRectangularDynamicBody(&World, ArmWidth, ArmHeight, 2, 0.1, 0.1);
    bArmL->SetTransform(b2Vec2(bHead->GetPosition().x - ChestWidth / 2, bHead->GetPosition().y + ArmHeight / 2 + HeadHeight / 2 + DBB), 0);

    sArmL.setSize(sf::Vector2f(ArmWidth, ArmHeight));
    sArmL.setOrigin(ArmWidth / 2, ArmHeight / 2);
    sArmL.setFillColor(RagdollColor);

    ////Brazo Derecho
    bArmR = Box2DHelper::CreateRectangularDynamicBody(&World, ArmWidth, ArmHeight, 2, 0.1, 0.1);
    bArmR->SetTransform(b2Vec2(bHead->GetPosition().x + ChestWidth / 2, bHead->GetPosition().y + ArmHeight / 2 + HeadHeight / 2 + DBB), 0);

    sArmR.setSize(sf::Vector2f(ArmWidth, ArmHeight));
    sArmR.setOrigin(ArmWidth / 2, ArmHeight / 2);
    sArmR.setFillColor(RagdollColor);

    //Piernas
    //Pierna Izquierda
    bLegL = Box2DHelper::CreateRectangularDynamicBody(&World, LegWidth, LegHeight, 2, 0.1, 0.1);
    bLegL->SetTransform(b2Vec2(bHead->GetPosition().x - DBB, bHead->GetPosition().y + LegHeight / 2 + ChestHeight / 2 + HeadHeight / 2 + (DBB * 3)), 0);

    sLegL.setSize(sf::Vector2f(LegWidth, LegHeight));
    sLegL.setOrigin(LegWidth / 2, LegHeight / 2);
    sLegL.setFillColor(RagdollColor);

    //Pierna Derecha
    bLegR = Box2DHelper::CreateRectangularDynamicBody(&World, LegWidth, LegHeight, 0.1, 0.1, 0.1);
    bLegR->SetTransform(b2Vec2(bHead->GetPosition().x + DBB, bHead->GetPosition().y + LegHeight / 2 + ChestHeight / 2 + HeadHeight / 2 + (DBB * 3)), 0);

    sLegR.setSize(sf::Vector2f(LegWidth, LegHeight));
    sLegR.setOrigin(LegWidth / 2, LegHeight / 2);
    sLegR.setFillColor(RagdollColor);

    //Joints
    //Cuello
    NeckDef.Initialize(bHead, bChest, b2Vec2(bHead->GetPosition().x, bHead->GetPosition().y + HeadHeight / 2 - DBB), b2Vec2(bChest->GetPosition().x, bChest->GetPosition().y - ChestHeight + DBB));
    NeckDef.length = 0.5;
    NeckDef.maxLength = 0.75;
    NeckDef.minLength = 0.25;
    NeckDef.collideConnected = true;
    NeckDJ = (b2DistanceJoint*)World.CreateJoint(&NeckDef);

    //Hombros
    //Hombro Izquierdo
    ShoulderLDef.bodyA = bChest;
    ShoulderLDef.bodyB = bArmL;
    ShoulderLDef.localAnchorA.Set(-ChestWidth / 2, -ChestHeight / 2);
    ShoulderLDef.localAnchorB.Set(ArmWidth / 2, -ArmHeight / 2);
    ShoulderLDef.collideConnected = true;

    ShoulderLDef.enableLimit = true;
    ShoulderLDef.lowerAngle = -b2_pi / 4;
    ShoulderLDef.upperAngle = b2_pi / 4;

    ShoulderLRJ = (b2RevoluteJoint*)World.CreateJoint(&ShoulderLDef);

    //Hombro Derecho
    ShoulderRDef.bodyA = bChest;
    ShoulderRDef.bodyB = bArmR;
    ShoulderRDef.localAnchorA.Set(ChestWidth / 2, -ChestHeight / 2);
    ShoulderRDef.localAnchorB.Set(-ArmWidth / 2, -ArmHeight / 2);
    ShoulderRDef.collideConnected = true;

    ShoulderRDef.enableLimit = true;
    ShoulderRDef.lowerAngle = -b2_pi / 4;
    ShoulderRDef.upperAngle = b2_pi / 4;

    ShoulderRRJ = (b2RevoluteJoint*)World.CreateJoint(&ShoulderRDef);

    //Cadera
    //Parte Izquierda
    HipLDef.bodyA = bChest;
    HipLDef.bodyB = bLegL;
    HipLDef.localAnchorA.Set(-ChestWidth / 4, ChestHeight / 2);
    HipLDef.localAnchorB.Set(LegWidth / 2, -LegHeight / 2);
    HipLDef.collideConnected = true;

    HipLDef.enableLimit = true;
    HipLDef.lowerAngle = -b2_pi / 2;
    HipLDef.upperAngle = b2_pi / 2;

    HipLRJ = (b2RevoluteJoint*)World.CreateJoint(&HipLDef);

    //Parte Derecha
    HipRDef.bodyA = bChest;
    HipRDef.bodyB = bLegR;
    HipRDef.localAnchorA.Set(ChestWidth / 4, ChestHeight / 2);
    HipRDef.localAnchorB.Set(-LegWidth / 2, -LegHeight / 2);
    HipRDef.collideConnected = true;

    HipRDef.enableLimit = true;
    HipRDef.lowerAngle = -b2_pi / 2;
    HipRDef.upperAngle = b2_pi / 2;

    HipRRJ = (b2RevoluteJoint*)World.CreateJoint(&HipRDef);
}

ARagdoll::~ARagdoll()
{
}

void ARagdoll::setOff()
{
    bHead->SetEnabled(false);
    bChest->SetEnabled(false);
    bArmR->SetEnabled(false);
    bArmL->SetEnabled(false);
    bLegR->SetEnabled(false);
    bLegL->SetEnabled(false);
    bIsEnabled = false;
}

//Aplica impulso a cada parte del ragdoll pasando la direccion del mouse como parrametro
void ARagdoll::applyImpulse(b2Vec2 Dir)
{
    bChest->ApplyLinearImpulseToCenter(Dir, true);
    bHead->ApplyLinearImpulseToCenter(Dir, true);
    bArmL->ApplyLinearImpulseToCenter(Dir, true);
    bArmR->ApplyLinearImpulseToCenter(Dir, true);
    bLegL->ApplyLinearImpulseToCenter(Dir, true);
    bLegR->ApplyLinearImpulseToCenter(Dir, true);
}

void ARagdoll::update() {
    sHead.setPosition(sf::Vector2f(bHead->GetPosition().x, bHead->GetPosition().y));
    sHead.setRotation(bHead->GetAngle() * 180 / b2_pi);
    sChest.setPosition(sf::Vector2f(bChest->GetPosition().x, bChest->GetPosition().y));
    sChest.setRotation(bChest->GetAngle() * 180 / b2_pi);
    sArmL.setPosition(sf::Vector2f(bArmL->GetPosition().x, bArmL->GetPosition().y));
    sArmL.setRotation(bArmL->GetAngle() * 180 / b2_pi);
    sArmR.setPosition(sf::Vector2f(bArmR->GetPosition().x, bArmR->GetPosition().y));
    sArmR.setRotation(bArmR->GetAngle() * 180 / b2_pi);
    sLegL.setPosition(sf::Vector2f(bLegL->GetPosition().x, bLegL->GetPosition().y));
    sLegL.setRotation(bLegL->GetAngle() * 180 / b2_pi);
    sLegR.setPosition(sf::Vector2f(bLegR->GetPosition().x, bLegR->GetPosition().y));
    sLegR.setRotation(bLegR->GetAngle() * 180 / b2_pi);
}

void ARagdoll::render(sf::RenderWindow& Window)
{
    if (bIsEnabled)
    {
        Window.draw(sHead);
        Window.draw(sChest);
        Window.draw(sArmL);
        Window.draw(sArmR);
        Window.draw(sLegL);
        Window.draw(sLegR);
    }

}