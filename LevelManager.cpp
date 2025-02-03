#include "LevelManager.h"

ALevelManager::ALevelManager(b2World& World)
{
    //Inicializacion de todos los elementos ordenados por nivel
    //Level 1
    Boxes_l1[0] = new ABox(World, 50, 50);
    Balls_l1[0] = new ABall(World, 50, 45);
    Boxes_l1[1] = new ABox(World, 75, 50);
    Balls_l1[1] = new ABall(World, 75, 45);
    Boxes_l1[2] = new ABox(World, 75, 70);
    Balls_l1[2] = new ABall(World, 75, 65);
    Boxes_l1[3] = new ABox(World, 100, 50);
    Balls_l1[3] = new ABall(World, 100, 45);
    Boxes_l1[4] = new ABox(World, 100, 70);
    Balls_l1[4] = new ABall(World, 100, 65);
    Boxes_l1[5] = new ABox(World, 100, 30);
    Balls_l1[5] = new ABall(World, 100, 25);
    Boxes_l1[6] = new ABox(World, 50, 30);
    Balls_l1[6] = new ABall(World, 50, 25);
    Boxes_l1[7] = new ABox(World, 50, 70);
    Balls_l1[7] = new ABall(World, 50, 65);
    Boxes_l1[8] = new ABox(World, 75, 30);
    Balls_l1[8] = new ABall(World, 75, 25);
    Goal = new AGoal(135, 85);

    for (int i = 0; i < 9; i++)
    {
        Balls_l1[i]->setOnOff(false);
        Boxes_l1[i]->setOnOff(false);
        Boxes.push_back(Boxes_l1[i]);
    }

    //Level2
    Boxes_l2[1] = new ABox(World, 45, 25);
    Balls_l2[1] = new ABall(World, 45, 20);
    Boxes_l2[0] = new ABox(World, 55, 50);
    Balls_l2[0] = new ABall(World, 55, 45);
    Boxes_l2[2] = new ABox(World, 65, 75);
    Balls_l2[2] = new ABall(World, 65, 70);
    Boxes_l2[5] = new ABox(World, 85, 25);
    Balls_l2[5] = new ABall(World, 85, 20);
    Boxes_l2[3] = new ABox(World, 95, 50);
    Balls_l2[3] = new ABall(World, 95, 45);
    Boxes_l2[4] = new ABox(World, 105, 75);
    Balls_l2[4] = new ABall(World, 105, 70);

    Elices_l2[0] = new AElice(World, 65, 25);
    Elices_l2[1] = new AElice(World, 75, 50);
    Elices_l2[2] = new AElice(World, 85, 75);

    for (int i = 0; i < 3; i++)
    {
        Elices_l2[i]->setOnOff(false);
    }

    for (int i = 0; i < 6; i++)
    {
        Balls_l2[i]->setOnOff(false);
        Boxes_l2[i]->setOnOff(false);
        Boxes.push_back(Boxes_l2[i]);
        Balls_l2[i]->Physics->SetAwake(false);
    }

    //Level3
    GiantBall = new AGiantBall(World, 75, 50, 75, 10);
    GiantBall->setOnOff(false);

    Boxes_l3[0] = new ABox(World, 130, 25);
    Balls_l3[0] = new ABall(World, 130, 20);
    Boxes_l3[1] = new ABox(World, 130, 50);
    Balls_l3[1] = new ABall(World, 130, 45);
    Boxes_l3[2] = new ABox(World, 130, 75);
    Balls_l3[2] = new ABall(World, 130, 70);
    Boxes_l3[3] = new ABox(World, 45, 75);
    Balls_l3[3] = new ABall(World, 45, 70);
    Boxes_l3[4] = new ABox(World, 75, 75);
    Balls_l3[4] = new ABall(World, 75, 70);
    Boxes_l3[5] = new ABox(World, 105, 75);
    Balls_l3[5] = new ABall(World, 105, 70);

    for (int i = 0; i < 6; i++)
    {
        Balls_l3[i]->setOnOff(false);
        Boxes_l3[i]->setOnOff(false);
        Boxes.push_back(Boxes_l3[i]);
        Balls_l3[i]->Physics->SetAwake(false);
    }

    //Level4
    Boxes_l4[0] = new ABox(World, 30, 35);
    Balls_l4[0] = new ABall(World, 30, 30);
    Boxes_l4[1] = new ABox(World, 60, 35);
    Balls_l4[1] = new ABall(World, 60, 30);
    Boxes_l4[2] = new ABox(World, 90, 35);
    Balls_l4[2] = new ABall(World, 90, 30);
    Boxes_l4[3] = new ABox(World, 120, 35);
    Balls_l4[3] = new ABall(World, 120, 30);
    Boxes_l4[4] = new ABox(World, 75, 25);
    Balls_l4[4] = new ABall(World, 75, 20);

    Hinges_l4[0] = new AHinge(World, 30, 51.1, 30, 51.1);
    Hinges_l4[1] = new AHinge(World, 60, 51.1, 60, 51.1);
    Hinges_l4[2] = new AHinge(World, 90, 51.1, 90, 51.1);
    Hinges_l4[3] = new AHinge(World, 120, 51.1, 120, 51.1);

    for (int i = 0; i < 5; i++)
    {
        Balls_l4[i]->setOnOff(false);
        Boxes_l4[i]->setOnOff(false);
        Boxes.push_back(Boxes_l4[i]);
        Balls_l4[i]->Physics->SetAwake(false);
    }

    for (int i = 0; i < 4; i++)
    {
        Hinges_l4[i]->setOnOff(false);
        Hinges_l4[i]->Physics->SetAwake(false);
    }
    Font.loadFromFile("sprites/nes.otf");
    FinalText.setFont(Font);
    FinalText.setCharacterSize(24);
    FinalText.setScale(0.15f, 0.15f);
    FinalText.setPosition(20, 20);
    FinalText.setFillColor(sf::Color(203, 232, 247));



}

//Seteo del nivel 1 activacion desactivacion y demas
void ALevelManager::level1()
{
    for (int i = 0; i < 9; i++)
    {
        Balls_l1[i]->setOnOff(true);
        Balls_l1[i]->Physics->SetAwake(false);
        Balls_l1[i]->bIsReached = false;
    }

    for (int i = 0; i < 9; i++)
    {
        Boxes_l1[i]->setOnOff(true);
    }

    Boxes_l1[0]->Physics->SetTransform(b2Vec2(50, 50), 0);
    Balls_l1[0]->Physics->SetTransform(b2Vec2(50, 45), 0);
    Boxes_l1[1]->Physics->SetTransform(b2Vec2(75, 50), 0);
    Balls_l1[1]->Physics->SetTransform(b2Vec2(75, 45), 0);
    Boxes_l1[2]->Physics->SetTransform(b2Vec2(75, 70), 0);
    Balls_l1[2]->Physics->SetTransform(b2Vec2(75, 65), 0);
    Boxes_l1[3]->Physics->SetTransform(b2Vec2(100, 50), 0);
    Balls_l1[3]->Physics->SetTransform(b2Vec2(100, 45), 0);
    Boxes_l1[4]->Physics->SetTransform(b2Vec2(100, 70), 0);
    Balls_l1[4]->Physics->SetTransform(b2Vec2(100, 65), 0);
    Boxes_l1[5]->Physics->SetTransform(b2Vec2(100, 30), 0);
    Balls_l1[5]->Physics->SetTransform(b2Vec2(100, 25), 0);
    Boxes_l1[6]->Physics->SetTransform(b2Vec2(50, 30), 0);
    Balls_l1[6]->Physics->SetTransform(b2Vec2(50, 25), 0);
    Boxes_l1[7]->Physics->SetTransform(b2Vec2(50, 70), 0);
    Balls_l1[7]->Physics->SetTransform(b2Vec2(50, 65), 0);
    Boxes_l1[8]->Physics->SetTransform(b2Vec2(75, 30), 0);
    Balls_l1[8]->Physics->SetTransform(b2Vec2(75, 25), 0);
}

void ALevelManager::level2()
{
    for (int i = 0; i < 3; i++)
    {
        Elices_l2[i]->setOnOff(true);
    }

    for (int i = 0; i < 6; i++)
    {
        Boxes_l2[i]->setOnOff(true);
        Balls_l2[i]->setOnOff(true);
        Balls_l2[i]->Physics->SetAwake(false);
        Balls_l2[i]->bIsReached = false;
    }

    Boxes_l2[1]->Physics->SetTransform(b2Vec2(45, 25), 0);
    Balls_l2[1]->Physics->SetTransform(b2Vec2(45, 20), 0);
    Boxes_l2[0]->Physics->SetTransform(b2Vec2(55, 50), 0);
    Balls_l2[0]->Physics->SetTransform(b2Vec2(55, 45), 0);
    Boxes_l2[2]->Physics->SetTransform(b2Vec2(65, 75), 0);
    Balls_l2[2]->Physics->SetTransform(b2Vec2(65, 70), 0);
    Boxes_l2[5]->Physics->SetTransform(b2Vec2(85, 25), 0);
    Balls_l2[5]->Physics->SetTransform(b2Vec2(85, 20), 0);
    Boxes_l2[3]->Physics->SetTransform(b2Vec2(95, 50), 0);
    Balls_l2[3]->Physics->SetTransform(b2Vec2(95, 45), 0);
    Boxes_l2[4]->Physics->SetTransform(b2Vec2(105, 75), 0);
    Balls_l2[4]->Physics->SetTransform(b2Vec2(105, 70), 0);

    Elices_l2[0]->Physics->SetTransform(b2Vec2(65, 25), 0);
    Elices_l2[1]->Physics->SetTransform(b2Vec2(75, 50), 0);
    Elices_l2[2]->Physics->SetTransform(b2Vec2(85, 70), 0);
}

void ALevelManager::level3()
{

    GiantBall->setOnOff(true);
    GiantBall->Physics->SetAwake(false);
    GiantBall->Physics->SetTransform(b2Vec2(75, 50), 0);

    for (int i = 0; i < 6; i++)
    {
        Boxes_l3[i]->setOnOff(true);
        Balls_l3[i]->setOnOff(true);
        Balls_l3[i]->Physics->SetAwake(false);
        Balls_l3[i]->bIsReached = false;
    }

    Boxes_l3[0]->Physics->SetTransform(b2Vec2(130, 25), 0);
    Balls_l3[0]->Physics->SetTransform(b2Vec2(130, 20), 0);
    Boxes_l3[1]->Physics->SetTransform(b2Vec2(130, 50), 0);
    Balls_l3[1]->Physics->SetTransform(b2Vec2(130, 45), 0);
    Boxes_l3[2]->Physics->SetTransform(b2Vec2(130, 75), 0);
    Balls_l3[2]->Physics->SetTransform(b2Vec2(130, 70), 0);
    Boxes_l3[3]->Physics->SetTransform(b2Vec2(45, 75), 0);
    Balls_l3[3]->Physics->SetTransform(b2Vec2(45, 70), 0);
    Boxes_l3[4]->Physics->SetTransform(b2Vec2(75, 75), 0);
    Balls_l3[4]->Physics->SetTransform(b2Vec2(75, 70), 0);
    Boxes_l3[5]->Physics->SetTransform(b2Vec2(105, 75), 0);
    Balls_l3[5]->Physics->SetTransform(b2Vec2(105, 70), 0);
}

void ALevelManager::level4()
{
    for (int i = 0; i < 4; i++)
    {
        Hinges_l4[i]->setOnOff(true);
        Hinges_l4[i]->Physics->SetAwake(false);
    }

    for (int i = 0; i < 5; i++)
    {
        Boxes_l4[i]->setOnOff(true);
        Balls_l4[i]->setOnOff(true);
        Balls_l4[i]->Physics->SetAwake(false);
        Balls_l4[i]->bIsReached = false;
    }

    Boxes_l4[0]->Physics->SetTransform(b2Vec2(30, 35), 0);
    Balls_l4[0]->Physics->SetTransform(b2Vec2(30, 30), 0);
    Boxes_l4[1]->Physics->SetTransform(b2Vec2(60, 35), 0);
    Balls_l4[1]->Physics->SetTransform(b2Vec2(60, 30), 0);
    Boxes_l4[2]->Physics->SetTransform(b2Vec2(90, 35), 0);
    Balls_l4[2]->Physics->SetTransform(b2Vec2(90, 30), 0);
    Boxes_l4[3]->Physics->SetTransform(b2Vec2(120, 35), 0);
    Balls_l4[3]->Physics->SetTransform(b2Vec2(120, 30), 0);
    Boxes_l4[4]->Physics->SetTransform(b2Vec2(75, 25), 0);
    Balls_l4[4]->Physics->SetTransform(b2Vec2(75, 20), 0);

    Hinges_l4[0]->Physics->SetTransform(b2Vec2(30, 51.1), 0);
    Hinges_l4[1]->Physics->SetTransform(b2Vec2(60, 51.1), 0);
    Hinges_l4[2]->Physics->SetTransform(b2Vec2(90, 51.1), 0);
    Hinges_l4[3]->Physics->SetTransform(b2Vec2(120, 51.1), 0);

}
//Nivel Pantalla final
void ALevelManager::final()
{
    FinalText.setString("                 Results\n\n\nPoints : " + std::to_string(PointsFinal) + "\n\nRagdolls Shooted : " + std::to_string(RagdollsFinal) + "\n\n\n\n\n\n            Click to continue");
    bIsFinal = true;
}
//Update general
void ALevelManager::update()
{
    for (int i = 0; i < 9; i++)
    {
        Balls_l1[i]->update();
    }
    for (int i = 0; i < 6; i++)
    {
        Balls_l2[i]->update();
        Balls_l3[i]->update();
    }
    for (int i = 0; i < 5; i++)
    {
        Balls_l4[i]->update();
    }
    for (int i = 0; i < 4; i++)
    {
        Hinges_l4[i]->update();
    }
    for (int i = 0; i < 3; i++)
    {
        Elices_l2[i]->update(.1);
    }

    GiantBall->update();
    Goal->update();
}

void ALevelManager::render(sf::RenderWindow& Window)
{
    for (int i = 0; i < 9; i++)
    {
        Balls_l1[i]->render(Window);
        Boxes_l1[i]->render(Window);
    }
    for (int i = 0; i < 3; i++)
    {
        Elices_l2[i]->render(Window);
    }

    for (int i = 0; i < 6; i++)
    {
        Balls_l2[i]->render(Window);
        Boxes_l2[i]->render(Window);
        Balls_l3[i]->render(Window);
        Boxes_l3[i]->render(Window);
    }
    for (int i = 0; i < 4; i++)
    {
        Hinges_l4[i]->render(Window);
    }
    for (int i = 0; i < 5; i++)
    {
        Balls_l4[i]->render(Window);
        Boxes_l4[i]->render(Window);
    }
    GiantBall->render(Window);
    Window.draw(Goal->Sprite);

    if (bIsFinal)
    {
        Window.draw(FinalText);
    }
}
//Funcion para desactivar todo
void ALevelManager::clear()
{
    for (size_t i = 0; i < Ragdolls.size(); ++i) {
        ARagdoll* ragdollPtr = Ragdolls[i];
        ARagdoll& ragdoll = *ragdollPtr;
        ragdoll.setOff();
    }
    for (int i = 0; i < 9; i++)
    {
        Balls_l1[i]->setOnOff(false);
        Boxes_l1[i]->setOnOff(false);
    }
    for (int i = 0; i < 3; i++)
    {
        Elices_l2[i]->setOnOff(false);
    }

    for (int i = 0; i < 6; i++)
    {
        Balls_l2[i]->setOnOff(false);
        Boxes_l2[i]->setOnOff(false);
        Balls_l3[i]->setOnOff(false);
        Boxes_l3[i]->setOnOff(false);
    }
    for (int i = 0; i < 5; i++)
    {
        Balls_l4[i]->setOnOff(false);
        Boxes_l4[i]->setOnOff(false);
    }
    for (int i = 0; i < 4; i++)
    {
        Hinges_l4[i]->setOnOff(false);
    }
    GiantBall->setOnOff(false);
}