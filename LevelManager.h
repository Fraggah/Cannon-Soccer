#include "Box.h"
#include "Ball.h"+
#include "GiantBall.h"
#include "Goal.h"
#include "Elice.h"
#include "Hinge.h"
#include "Ragdoll.h"
#include <vector>

class LevelManager
{
public:
    bool isFinal = false;
    Box* boxes_l1[9];
    Ball* balls_l1[9];
    Box* boxes_l2[6];
    Ball* balls_l2[6];
    Box* boxes_l3[6];
    Ball* balls_l3[6];
    Box* boxes_l4[5];
    Ball* balls_l4[5];
    GiantBall* gBall;
    Goal* goal;
    Elice* elices_l2[3];
    Hinge* hinges_l4[5];
    sf::Font font;
    sf::Text finalText;
    std::vector<Ragdoll*> ragdolls;
    int pointsFinal;
    int ragdollsFinal;
    LevelManager(b2World& world);
    void level1();
    void level2();
    void level3();
    void level4();
    void final();
    void update();
    void render(sf::RenderWindow& window);
    void clear(b2World* world);
};

