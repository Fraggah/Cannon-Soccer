#include "Box.h"
#include "Ball.h"+
#include "GiantBall.h"
#include "Goal.h"
#include "Elice.h"
#include "Hinge.h"
#include "Ragdoll.h"
#include <vector>

class ALevelManager
{
public:
    bool bIsFinal = false;
    ABox* Boxes_l1[9];
    ABall* Balls_l1[9];
    ABox* Boxes_l2[6];
    ABall* Balls_l2[6];
    ABox* Boxes_l3[6];
    ABall* Balls_l3[6];
    ABox* Boxes_l4[5];
    ABall* Balls_l4[5];
    AGiantBall* GiantBall;
    AGoal* Goal;
    AElice* Elices_l2[3];
    AHinge* Hinges_l4[5];
    sf::Font Font;
    sf::Text FinalText;
    std::vector<ARagdoll*> Ragdolls;
    std::vector<ABox*> Boxes;
    int PointsFinal;
    int RagdollsFinal;
    ALevelManager(b2World& World);
    void level1();
    void level2();
    void level3();
    void level4();
    void final();
    void update();
    void render(sf::RenderWindow& Window);
    void clear();
};

//Esta clase maneja todos los elementos de los niveles
//Almacena todos los elementos, los activaa y dedsactiva segun el nivel
//Cada uno de los elementos esta organizado en arrays para cada nivel
//Esto permite ejecutar logica como desaparecer cuando cambian de nivel
//o detectar si las bolas de tal nivel se marcaron como reached para poder avanzar de nivel etc

//Se podria haber utilizado un sistema con tags y usar vectores en vez de arrays pero decidí que quede asi

