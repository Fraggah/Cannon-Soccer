#include "Ragdoll.h"

Ragdoll::Ragdoll(b2World& mundo, float x, float y) {
    ragdollColor = sf::Color(203, 232, 247);

    //Scale
    dec *= scale;
    anchoCabeza *= scale;
    altoCabeza *= scale;
    anchoTronco *= scale;
    altoTronco *= scale;
    anchoBrazo *= scale;
    altoBrazo *= scale;
    anchoPierna *= scale;
    altoPierna *= scale;

    //Cabeza
    bCabeza = Box2DHelper::CreateRectangularDynamicBody(&mundo, anchoCabeza, altoCabeza, 2, 0.1, 0.1);
    bCabeza->SetTransform(b2Vec2(x, y), 0);

    sCabeza.setSize(sf::Vector2f(anchoCabeza, altoCabeza));
    sCabeza.setOrigin(anchoCabeza / 2, altoCabeza / 2);
    sCabeza.setFillColor(ragdollColor);

    //Tronco
    bTronco = Box2DHelper::CreateRectangularDynamicBody(&mundo, anchoTronco, altoTronco, 2, 0.1, 0.1);
    bTronco->SetTransform(b2Vec2(bCabeza->GetPosition().x, bCabeza->GetPosition().y + altoTronco / 2 + altoCabeza / 2 - dec), 0);

    sTronco.setSize(sf::Vector2f(anchoTronco, altoTronco));
    sTronco.setOrigin(anchoTronco / 2, altoTronco / 2);
    sTronco.setFillColor(ragdollColor);
    //Brazos
    //Brazo Izquierdo
    bBrazoI = Box2DHelper::CreateRectangularDynamicBody(&mundo, anchoBrazo, altoBrazo, 2, 0.1, 0.1);
    bBrazoI->SetTransform(b2Vec2(bCabeza->GetPosition().x - anchoTronco / 2, bCabeza->GetPosition().y + altoBrazo / 2 + altoCabeza / 2 + dec), 0);

    sBrazoI.setSize(sf::Vector2f(anchoBrazo, altoBrazo));
    sBrazoI.setOrigin(anchoBrazo / 2, altoBrazo / 2);
    sBrazoI.setFillColor(ragdollColor);

    ////Brazo Derecho
    bBrazoD = Box2DHelper::CreateRectangularDynamicBody(&mundo, anchoBrazo, altoBrazo, 2, 0.1, 0.1);
    bBrazoD->SetTransform(b2Vec2(bCabeza->GetPosition().x + anchoTronco / 2, bCabeza->GetPosition().y + altoBrazo / 2 + altoCabeza / 2 + dec), 0);

    sBrazoD.setSize(sf::Vector2f(anchoBrazo, altoBrazo));
    sBrazoD.setOrigin(anchoBrazo / 2, altoBrazo / 2);
    sBrazoD.setFillColor(ragdollColor);

    //Piernas
    //Pierna Izquierda
    bPiernaI = Box2DHelper::CreateRectangularDynamicBody(&mundo, anchoPierna, altoPierna, 2, 0.1, 0.1);
    bPiernaI->SetTransform(b2Vec2(bCabeza->GetPosition().x - dec, bCabeza->GetPosition().y + altoPierna / 2 + altoTronco / 2 + altoCabeza / 2 + (dec * 3)), 0);

    sPiernaI.setSize(sf::Vector2f(anchoPierna, altoPierna));
    sPiernaI.setOrigin(anchoPierna / 2, altoPierna / 2);
    sPiernaI.setFillColor(ragdollColor);

    //Pierna Derecha
    bPiernaD = Box2DHelper::CreateRectangularDynamicBody(&mundo, anchoPierna, altoPierna, 0.1, 0.1, 0.1);
    bPiernaD->SetTransform(b2Vec2(bCabeza->GetPosition().x + dec, bCabeza->GetPosition().y + altoPierna / 2 + altoTronco / 2 + altoCabeza / 2 + (dec * 3)), 0);

    sPiernaD.setSize(sf::Vector2f(anchoPierna, altoPierna));
    sPiernaD.setOrigin(anchoPierna / 2, altoPierna / 2);
    sPiernaD.setFillColor(ragdollColor);

    //Joints
    //Cuello
    cuelloDef.Initialize(bCabeza, bTronco, b2Vec2(bCabeza->GetPosition().x, bCabeza->GetPosition().y + altoCabeza / 2 - dec), b2Vec2(bTronco->GetPosition().x, bTronco->GetPosition().y - altoTronco + dec));
    cuelloDef.length = 0.5;
    cuelloDef.maxLength = 0.75;
    cuelloDef.minLength = 0.25;
    cuelloDef.collideConnected = true;
    cuelloDJ = (b2DistanceJoint*)mundo.CreateJoint(&cuelloDef);

    //Hombros
    //Hombro Izquierdo
    hombroIDef.bodyA = bTronco;
    hombroIDef.bodyB = bBrazoI;
    hombroIDef.localAnchorA.Set(-anchoTronco / 2, -altoTronco / 2);
    hombroIDef.localAnchorB.Set(anchoBrazo / 2, -altoBrazo / 2);
    hombroIDef.collideConnected = true;

    hombroIDef.enableLimit = true;
    hombroIDef.lowerAngle = -b2_pi / 4;
    hombroIDef.upperAngle = b2_pi / 4;

    hombroIRJ = (b2RevoluteJoint*)mundo.CreateJoint(&hombroIDef);

    //Hombro Derecho
    hombroDDef.bodyA = bTronco;
    hombroDDef.bodyB = bBrazoD;
    hombroDDef.localAnchorA.Set(anchoTronco / 2, -altoTronco / 2);
    hombroDDef.localAnchorB.Set(-anchoBrazo / 2, -altoBrazo / 2);
    hombroDDef.collideConnected = true;

    hombroDDef.enableLimit = true;
    hombroDDef.lowerAngle = -b2_pi / 4;
    hombroDDef.upperAngle = b2_pi / 4;

    hombroDRJ = (b2RevoluteJoint*)mundo.CreateJoint(&hombroDDef);

    //Cadera
    //Parte Izquierda
    CPIDef.bodyA = bTronco;
    CPIDef.bodyB = bPiernaI;
    CPIDef.localAnchorA.Set(-anchoTronco / 4, altoTronco / 2);
    CPIDef.localAnchorB.Set(anchoPierna / 2, -altoPierna / 2);
    CPIDef.collideConnected = true;

    CPIDef.enableLimit = true;
    CPIDef.lowerAngle = -b2_pi / 2;
    CPIDef.upperAngle = b2_pi / 2;

    CPIRJ = (b2RevoluteJoint*)mundo.CreateJoint(&CPIDef);

    //Parte Derecha
    CPDDef.bodyA = bTronco;
    CPDDef.bodyB = bPiernaD;
    CPDDef.localAnchorA.Set(anchoTronco / 4, altoTronco / 2);
    CPDDef.localAnchorB.Set(-anchoPierna / 2, -altoPierna / 2);
    CPDDef.collideConnected = true;

    CPDDef.enableLimit = true;
    CPDDef.lowerAngle = -b2_pi / 2;
    CPDDef.upperAngle = b2_pi / 2;

    CPDRJ = (b2RevoluteJoint*)mundo.CreateJoint(&CPDDef);
}

Ragdoll::~Ragdoll()
{
}

void Ragdoll::setOff()
{
    bCabeza->SetEnabled(false);
    bTronco->SetEnabled(false);
    bBrazoD->SetEnabled(false);
    bBrazoI->SetEnabled(false);
    bPiernaD->SetEnabled(false);
    bPiernaI->SetEnabled(false);
    isEnabled = false;
}

void Ragdoll::applyImpulse(b2Vec2 dir, bool flag)
{
    bTronco->ApplyLinearImpulseToCenter(dir, true);
    bCabeza->ApplyLinearImpulseToCenter(dir, true);
    bBrazoI->ApplyLinearImpulseToCenter(dir, true);
    bBrazoD->ApplyLinearImpulseToCenter(dir, true);
    bPiernaI->ApplyLinearImpulseToCenter(dir, true);
    bPiernaD->ApplyLinearImpulseToCenter(dir, true);
}

void Ragdoll::update() {
    sCabeza.setPosition(sf::Vector2f(bCabeza->GetPosition().x, bCabeza->GetPosition().y));
    sCabeza.setRotation(bCabeza->GetAngle() * 180 / b2_pi);
    sTronco.setPosition(sf::Vector2f(bTronco->GetPosition().x, bTronco->GetPosition().y));
    sTronco.setRotation(bTronco->GetAngle() * 180 / b2_pi);
    sBrazoI.setPosition(sf::Vector2f(bBrazoI->GetPosition().x, bBrazoI->GetPosition().y));
    sBrazoI.setRotation(bBrazoI->GetAngle() * 180 / b2_pi);
    sBrazoD.setPosition(sf::Vector2f(bBrazoD->GetPosition().x, bBrazoD->GetPosition().y));
    sBrazoD.setRotation(bBrazoD->GetAngle() * 180 / b2_pi);
    sPiernaI.setPosition(sf::Vector2f(bPiernaI->GetPosition().x, bPiernaI->GetPosition().y));
    sPiernaI.setRotation(bPiernaI->GetAngle() * 180 / b2_pi);
    sPiernaD.setPosition(sf::Vector2f(bPiernaD->GetPosition().x, bPiernaD->GetPosition().y));
    sPiernaD.setRotation(bPiernaD->GetAngle() * 180 / b2_pi);
}

void Ragdoll::render(sf::RenderWindow& window)
{
    if (isEnabled)
    {
        window.draw(sCabeza);
        window.draw(sTronco);
        window.draw(sBrazoI);
        window.draw(sBrazoD);
        window.draw(sPiernaI);
        window.draw(sPiernaD);
    }

}