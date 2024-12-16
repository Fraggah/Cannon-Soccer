#include "LevelManager.h"

LevelManager::LevelManager(b2World& world)
{
    //Level 1
    boxes_l1[0] = new Box(world, 50, 50);
    balls_l1[0] = new Ball(world, 50, 45);
    boxes_l1[1] = new Box(world, 75, 50);
    balls_l1[1] = new Ball(world, 75, 45);
    boxes_l1[2] = new Box(world, 75, 70);
    balls_l1[2] = new Ball(world, 75, 65);
    boxes_l1[3] = new Box(world, 100, 50);
    balls_l1[3] = new Ball(world, 100, 45);
    boxes_l1[4] = new Box(world, 100, 70);
    balls_l1[4] = new Ball(world, 100, 65);
    boxes_l1[5] = new Box(world, 100, 30);
    balls_l1[5] = new Ball(world, 100, 25);
    boxes_l1[6] = new Box(world, 50, 30);
    balls_l1[6] = new Ball(world, 50, 25);
    boxes_l1[7] = new Box(world, 50, 70);
    balls_l1[7] = new Ball(world, 50, 65);
    boxes_l1[8] = new Box(world, 75, 30);
    balls_l1[8] = new Ball(world, 75, 25);
    goal = new Goal(135, 85);

    for (int i = 0; i < 9; i++)
    {
        balls_l1[i]->setOnOff(false);
        boxes_l1[i]->setOnOff(false);
    }

    //Level2
    boxes_l2[1] = new Box(world, 45, 25);
    balls_l2[1] = new Ball(world, 45, 20);
    boxes_l2[0] = new Box(world, 55, 50);
    balls_l2[0] = new Ball(world, 55, 45);
    boxes_l2[2] = new Box(world, 65, 75);
    balls_l2[2] = new Ball(world, 65, 70);
    boxes_l2[5] = new Box(world, 85, 25);
    balls_l2[5] = new Ball(world, 85, 20);
    boxes_l2[3] = new Box(world, 95, 50);
    balls_l2[3] = new Ball(world, 95, 45);
    boxes_l2[4] = new Box(world, 105, 75);
    balls_l2[4] = new Ball(world, 105, 70);

    elices_l2[0] = new Elice(world, 65, 25);
    elices_l2[1] = new Elice(world, 75, 50);
    elices_l2[2] = new Elice(world, 85, 75);

    for (int i = 0; i < 3; i++)
    {
        elices_l2[i]->setOnOff(false);
    }

    for (int i = 0; i < 6; i++)
    {
        balls_l2[i]->setOnOff(false);
        boxes_l2[i]->setOnOff(false);
        balls_l2[i]->physics->SetAwake(false);
    }

    //Level3
    gBall = new GiantBall(world, 75, 50, 75, 10);
    gBall->setOnOff(false);

    boxes_l3[0] = new Box(world, 130, 25);
    balls_l3[0] = new Ball(world, 130, 20);
    boxes_l3[1] = new Box(world, 130, 50);
    balls_l3[1] = new Ball(world, 130, 45);
    boxes_l3[2] = new Box(world, 130, 75);
    balls_l3[2] = new Ball(world, 130, 70);
    boxes_l3[3] = new Box(world, 45, 75);
    balls_l3[3] = new Ball(world, 45, 70);
    boxes_l3[4] = new Box(world, 75, 75);
    balls_l3[4] = new Ball(world, 75, 70);
    boxes_l3[5] = new Box(world, 105, 75);
    balls_l3[5] = new Ball(world, 105, 70);

    for (int i = 0; i < 6; i++)
    {
        balls_l3[i]->setOnOff(false);
        boxes_l3[i]->setOnOff(false);
        balls_l3[i]->physics->SetAwake(false);
    }

    //Level4
    boxes_l4[0] = new Box(world, 30, 35);
    balls_l4[0] = new Ball(world, 30, 30);
    boxes_l4[1] = new Box(world, 60, 35);
    balls_l4[1] = new Ball(world, 60, 30);
    boxes_l4[2] = new Box(world, 90, 35);
    balls_l4[2] = new Ball(world, 90, 30);
    boxes_l4[3] = new Box(world, 120, 35);
    balls_l4[3] = new Ball(world, 120, 30);
    boxes_l4[4] = new Box(world, 75, 25);
    balls_l4[4] = new Ball(world, 75, 20);

    hinges_l4[0] = new Hinge(world, 30, 51.1, 30, 51.1);
    hinges_l4[1] = new Hinge(world, 60, 51.1, 60, 51.1);
    hinges_l4[2] = new Hinge(world, 90, 51.1, 90, 51.1);
    hinges_l4[3] = new Hinge(world, 120, 51.1, 120, 51.1);

    for (int i = 0; i < 5; i++)
    {
        balls_l4[i]->setOnOff(false);
        boxes_l4[i]->setOnOff(false);
        balls_l4[i]->physics->SetAwake(false);
    }

    for (int i = 0; i < 4; i++)
    {
        hinges_l4[i]->setOnOff(false);
        hinges_l4[i]->physics->SetAwake(false);
    }
    font.loadFromFile("sprites/nes.otf");
    finalText.setFont(font);
    finalText.setCharacterSize(24);
    finalText.setScale(0.15f, 0.15f);
    finalText.setPosition(20, 20);
    finalText.setFillColor(sf::Color(203, 232, 247));

}

void LevelManager::level1()
{
    for (int i = 0; i < 9; i++)
    {
        balls_l1[i]->setOnOff(true);
        balls_l1[i]->physics->SetAwake(false);
        balls_l1[i]->reached = false;
    }

    for (int i = 0; i < 9; i++)
    {
        boxes_l1[i]->setOnOff(true);
    }

    boxes_l1[0]->physics->SetTransform(b2Vec2(50, 50), 0);
    balls_l1[0]->physics->SetTransform(b2Vec2(50, 45), 0);
    boxes_l1[1]->physics->SetTransform(b2Vec2(75, 50), 0);
    balls_l1[1]->physics->SetTransform(b2Vec2(75, 45), 0);
    boxes_l1[2]->physics->SetTransform(b2Vec2(75, 70), 0);
    balls_l1[2]->physics->SetTransform(b2Vec2(75, 65), 0);
    boxes_l1[3]->physics->SetTransform(b2Vec2(100, 50), 0);
    balls_l1[3]->physics->SetTransform(b2Vec2(100, 45), 0);
    boxes_l1[4]->physics->SetTransform(b2Vec2(100, 70), 0);
    balls_l1[4]->physics->SetTransform(b2Vec2(100, 65), 0);
    boxes_l1[5]->physics->SetTransform(b2Vec2(100, 30), 0);
    balls_l1[5]->physics->SetTransform(b2Vec2(100, 25), 0);
    boxes_l1[6]->physics->SetTransform(b2Vec2(50, 30), 0);
    balls_l1[6]->physics->SetTransform(b2Vec2(50, 25), 0);
    boxes_l1[7]->physics->SetTransform(b2Vec2(50, 70), 0);
    balls_l1[7]->physics->SetTransform(b2Vec2(50, 65), 0);
    boxes_l1[8]->physics->SetTransform(b2Vec2(75, 30), 0);
    balls_l1[8]->physics->SetTransform(b2Vec2(75, 25), 0);
}

void LevelManager::level2()
{
    for (int i = 0; i < 3; i++)
    {
        elices_l2[i]->setOnOff(true);
    }

    for (int i = 0; i < 6; i++)
    {
        boxes_l2[i]->setOnOff(true);
        balls_l2[i]->setOnOff(true);
        balls_l2[i]->physics->SetAwake(false);
        balls_l2[i]->reached = false;
    }

    boxes_l2[1]->physics->SetTransform(b2Vec2(45, 25), 0);
    balls_l2[1]->physics->SetTransform(b2Vec2(45, 20), 0);
    boxes_l2[0]->physics->SetTransform(b2Vec2(55, 50), 0);
    balls_l2[0]->physics->SetTransform(b2Vec2(55, 45), 0);
    boxes_l2[2]->physics->SetTransform(b2Vec2(65, 75), 0);
    balls_l2[2]->physics->SetTransform(b2Vec2(65, 70), 0);
    boxes_l2[5]->physics->SetTransform(b2Vec2(85, 25), 0);
    balls_l2[5]->physics->SetTransform(b2Vec2(85, 20), 0);
    boxes_l2[3]->physics->SetTransform(b2Vec2(95, 50), 0);
    balls_l2[3]->physics->SetTransform(b2Vec2(95, 45), 0);
    boxes_l2[4]->physics->SetTransform(b2Vec2(105, 75), 0);
    balls_l2[4]->physics->SetTransform(b2Vec2(105, 70), 0);

    elices_l2[0]->physics->SetTransform(b2Vec2(65, 25), 0);
    elices_l2[1]->physics->SetTransform(b2Vec2(75, 50), 0);
    elices_l2[2]->physics->SetTransform(b2Vec2(85, 70), 0);
}

void LevelManager::level3()
{

    gBall->setOnOff(true);
    gBall->physics->SetAwake(false);
    gBall->physics->SetTransform(b2Vec2(75, 50), 0);

    for (int i = 0; i < 6; i++)
    {
        boxes_l3[i]->setOnOff(true);
        balls_l3[i]->setOnOff(true);
        balls_l3[i]->physics->SetAwake(false);
        balls_l3[i]->reached = false;
    }

    boxes_l3[0]->physics->SetTransform(b2Vec2(130, 25), 0);
    balls_l3[0]->physics->SetTransform(b2Vec2(130, 20), 0);
    boxes_l3[1]->physics->SetTransform(b2Vec2(130, 50), 0);
    balls_l3[1]->physics->SetTransform(b2Vec2(130, 45), 0);
    boxes_l3[2]->physics->SetTransform(b2Vec2(130, 75), 0);
    balls_l3[2]->physics->SetTransform(b2Vec2(130, 70), 0);
    boxes_l3[3]->physics->SetTransform(b2Vec2(45, 75), 0);
    balls_l3[3]->physics->SetTransform(b2Vec2(45, 70), 0);
    boxes_l3[4]->physics->SetTransform(b2Vec2(75, 75), 0);
    balls_l3[4]->physics->SetTransform(b2Vec2(75, 70), 0);
    boxes_l3[5]->physics->SetTransform(b2Vec2(105, 75), 0);
    balls_l3[5]->physics->SetTransform(b2Vec2(105, 70), 0);
}

void LevelManager::level4()
{
    for (int i = 0; i < 4; i++)
    {
        hinges_l4[i]->setOnOff(true);
        hinges_l4[i]->physics->SetAwake(false);
    }

    for (int i = 0; i < 5; i++)
    {
        boxes_l4[i]->setOnOff(true);
        balls_l4[i]->setOnOff(true);
        balls_l4[i]->physics->SetAwake(false);
        balls_l4[i]->reached = false;
    }

    boxes_l4[0]->physics->SetTransform(b2Vec2(30, 35), 0);
    balls_l4[0]->physics->SetTransform(b2Vec2(30, 30), 0);
    boxes_l4[1]->physics->SetTransform(b2Vec2(60, 35), 0);
    balls_l4[1]->physics->SetTransform(b2Vec2(60, 30), 0);
    boxes_l4[2]->physics->SetTransform(b2Vec2(90, 35), 0);
    balls_l4[2]->physics->SetTransform(b2Vec2(90, 30), 0);
    boxes_l4[3]->physics->SetTransform(b2Vec2(120, 35), 0);
    balls_l4[3]->physics->SetTransform(b2Vec2(120, 30), 0);
    boxes_l4[4]->physics->SetTransform(b2Vec2(75, 25), 0);
    balls_l4[4]->physics->SetTransform(b2Vec2(75, 20), 0);

    hinges_l4[0]->physics->SetTransform(b2Vec2(30, 51.1), 0);
    hinges_l4[1]->physics->SetTransform(b2Vec2(60, 51.1), 0);
    hinges_l4[2]->physics->SetTransform(b2Vec2(90, 51.1), 0);
    hinges_l4[3]->physics->SetTransform(b2Vec2(120, 51.1), 0);

}

void LevelManager::final()
{
    finalText.setString("                 Results\n\n\nPoints : " + std::to_string(pointsFinal) + "\n\nRagdolls Shooted : " + std::to_string(ragdollsFinal) + "\n\n\n\n\n\n            Click to continue");
    isFinal = true;
}

void LevelManager::update()
{
    for (int i = 0; i < 9; i++)
    {
        balls_l1[i]->update();
    }
    for (int i = 0; i < 6; i++)
    {
        balls_l2[i]->update();
        balls_l3[i]->update();
    }
    for (int i = 0; i < 5; i++)
    {
        balls_l4[i]->update();
    }
    for (int i = 0; i < 4; i++)
    {
        hinges_l4[i]->update();
    }
    gBall->update();
    goal->update();
}

void LevelManager::render(sf::RenderWindow& window)
{
    for (int i = 0; i < 9; i++)
    {
        balls_l1[i]->render(window);
        boxes_l1[i]->render(window);
    }
    for (int i = 0; i < 3; i++)
    {
        elices_l2[i]->render(window);
    }

    for (int i = 0; i < 6; i++)
    {
        balls_l2[i]->render(window);
        boxes_l2[i]->render(window);
        balls_l3[i]->render(window);
        boxes_l3[i]->render(window);
    }
    for (int i = 0; i < 4; i++)
    {
        hinges_l4[i]->render(window);
    }
    for (int i = 0; i < 5; i++)
    {
        balls_l4[i]->render(window);
        boxes_l4[i]->render(window);
    }
    gBall->render(window);
    window.draw(goal->sprite);

    if (isFinal)
    {
        window.draw(finalText);
    }
}

void LevelManager::clear(b2World* world)
{
    for (size_t i = 0; i < ragdolls.size(); ++i) {
        Ragdoll* ragdollPtr = ragdolls[i];
        Ragdoll& ragdoll = *ragdollPtr;
        ragdoll.setOff();
    }
    for (int i = 0; i < 9; i++)
    {
        balls_l1[i]->setOnOff(false);
        boxes_l1[i]->setOnOff(false);
    }
    for (int i = 0; i < 3; i++)
    {
        elices_l2[i]->setOnOff(false);
    }

    for (int i = 0; i < 6; i++)
    {
        balls_l2[i]->setOnOff(false);
        boxes_l2[i]->setOnOff(false);
        balls_l3[i]->setOnOff(false);
        boxes_l3[i]->setOnOff(false);
    }
    for (int i = 0; i < 5; i++)
    {
        balls_l4[i]->setOnOff(false);
        boxes_l4[i]->setOnOff(false);
    }
    for (int i = 0; i < 4; i++)
    {
        hinges_l4[i]->setOnOff(false);
    }
    gBall->setOnOff(false);
}