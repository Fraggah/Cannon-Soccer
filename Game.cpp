#include "Game.h"

Game::Game()
{
    Init();
}

void Game::Init() //Metodo de inicializacion y seteo de variables
{
    Window.create(sf::VideoMode(1200, 800), "Canon Socker");

    //phyWorld = new b2World(b2Vec2(0.0f, 80.0f));
    //levelmanager = new LevelManager(*phyWorld);
    //limits = new Limits(*phyWorld);

    Window.setFramerateLimit(FPS);
    Window.setMouseCursorVisible(false);

    Camera.setSize(150, 100);
    Camera.setCenter(75, 50);
    Window.setView(Camera);

    CannonTexture.loadFromFile("sprites/cannon.png");
    Cannon.setOrigin(5, 5);
    Cannon.setTexture(CannonTexture);
    Cannon.setPosition(20, 85);

    TitleTexture.loadFromFile("sprites/title.png");
    Title.setTexture(TitleTexture);

    Font.loadFromFile("sprites/nes.otf");
    PressText.setFont(Font);
    PressText.setCharacterSize(24);
    PressText.setScale(0.15f, 0.15f);
    PressText.setPosition(57, 70.5);
    PressText.setString("click to start");
    PressText.setFillColor(sf::Color(203, 232, 247));

    TutorialText.setFont(Font);
    TutorialText.setCharacterSize(24);
    TutorialText.setScale(0.15f, 0.15f);
    TutorialText.setPosition(20, 20);
    TutorialText.setString("                Tutorial\n\n\nObjetive : Get all balls into the goal.\n\nShot Power : Depends on shooting distance.\n\nLeft Click : Launch ragdoll (-10 points).\n\nRight Click : Remove box (-500 points).\n\n\n             Click to start");
    TutorialText.setFillColor(sf::Color(203, 232, 247));

    CopyText.setFont(Font);
    CopyText.setCharacterSize(24);
    CopyText.setScale(0.15f, 0.15f);
    CopyText.setPosition(49.5, 90.5);
    CopyText.setString("© silvio stefanucci");
    CopyText.setFillColor(sf::Color(203, 232, 247));

    MusicManager.play();

    ShootSoundBuffer.loadFromFile("sprites/Shoot.ogg");
    ShootSound.setBuffer(ShootSoundBuffer);
    DeathSoundBuffer.loadFromFile("sprites/Death.ogg");
    DeathSound.setBuffer(DeathSoundBuffer);
    OkSoundBuffer.loadFromFile("sprites/Ok.ogg");
    OkSound.setBuffer(OkSoundBuffer);
    GoalSoundBuffer.loadFromFile("sprites/Goal.ogg");
    GoalSound.setBuffer(GoalSoundBuffer);
    BlockSoundBuffer.loadFromFile("sprites/Block.ogg");
    BlockSound.setBuffer(BlockSoundBuffer);
}

void Game::Reset() //Reseteo de avance para llamar al terminar el juego
{
    Points = 0;
    Ragdolls = 0;
    Level = 0;
    Lvl1Goals = 0;
    Lvl2Goals = 0;
    Lvl3Goals = 0;
    Lvl4Goals = 0;
}

//Chequeo de colision devolviendo un bool
bool Game::CheckCollision(ABall* Ball, AGoal* Goal, float ballRadius, float GoalRadius) {
    float XDistance = Ball->Sprite.getPosition().x - Goal->Sprite.getPosition().x;
    float YDistance = Ball->Sprite.getPosition().y - Goal->Sprite.getPosition().y;

    float Distance = sqrt(pow(XDistance, 2) + pow(YDistance, 2));

    return Distance <= (ballRadius + GoalRadius);
}

void Game::Run() //Logica central
{
    //Inicializacion del mundo
    b2World World(b2Vec2(0.0f, 80.0f));
    ALevelManager LevelManager(World);
    ALimits* Limits = new ALimits(World);

    //Eventos - Inputs
    while (Window.isOpen())
    {

        sf::Event Event;
        while (Window.pollEvent(Event))
        {
            switch (Event.type)
            {
            case sf::Event::Closed:
                Window.close();
                break;
            case sf::Event::MouseButtonPressed:
                switch (Event.key.code)
                {
                case sf::Mouse::Button::Left:
                    if (bIsMenu) //Pase de menu a tutorial
                    {
                        if (ClickCD.getElapsedTime() > ClickTime)
                        {
                            bIsTutorial = true;
                            bIsMenu = false;
                            ClickCD.restart(); // cooldown del click para no spamear
                            MusicManager.changeST(0); //selecciono track musical
                            OkSound.play(); //SFX
                        }
                    }
                    if (bIsTutorial) //Pase de turorial a juego
                    {
                        if (ClickCD.getElapsedTime() > ClickTime)
                        {
                            bIsGame = true;
                            bIsTutorial = false;
                            ClickCD.restart();
                            ATransition* Transition = new ATransition("Level 1");
                            Transition->OnTransitionEnd = [&LevelManager, &World]() {
                                LevelManager.clear();
                                LevelManager.level1();
                                };
                            Transitions.push_back(Transition);
                            Level = 1;
                            UI.updateLevel(Level);
                            MusicManager.changeST(1);
                            OkSound.play();
                        }
                    }
                    if (bIsGame) //Disparo de ragdolls
                    {
                        if (ClickCD.getElapsedTime() > ClickTime)
                        {
                            //Obtengo posicion del mouse
                            sf::Vector2i MousePos = sf::Mouse::getPosition(Window);
                            sf::Vector2f WorldMousePos = Window.mapPixelToCoords(MousePos);

                            //Disparo pasando la posicion del mouse, setiendo la potencia a travez de la variable de potencia y la distancia
                            //entre el canon y el mouse
                            ARagdoll* Ragdoll = new ARagdoll(World, Cannon.getPosition().x, Cannon.getPosition().y - 3);
                            b2Vec2 Direction1 = b2Vec2(WorldMousePos.x - Ragdoll->bChest->GetPosition().x,
                                WorldMousePos.y - Ragdoll->bChest->GetPosition().y);
                            float Distance = std::sqrt(Direction1.x * Direction1.x + Direction1.y * Direction1.y);
                            Direction1.Normalize();
                            float Power = CannonPower * Distance;
                            std::cout << Distance << std::endl;
                            Ragdoll->applyImpulse(b2Vec2(Direction1.x * Power, Direction1.y * Power));
                            LevelManager.Ragdolls.push_back(Ragdoll); //Caputo en vector
                            ShootSound.play(); //SFX
                            Ragdolls++; //contador
                            Points -= 10; //Cada vez que dispara resta 10 puntos

                            //Actualizacion de numeros en UI
                            UI.updateRagdolls(Ragdolls);
                            UI.updatePoints(Points);

                            std::cout << "Ragdolls: " << LevelManager.Ragdolls.size() << std::endl;

                            AParticle* Shoot = new ACannonShoot(26, 79); //Particulas
                            Particles.push_back(Shoot);
                        }

                    }
                    if (bIsGameOver) //pase de Game over a pantalla de inicio
                    {
                        if (ClickCD.getElapsedTime() > ClickTime)
                        {
                            bIsMenu = true;
                            bIsGameOver = false;
                            ClickCD.restart();
                            LevelManager.bIsFinal = false;
                            Reset();
                            UI.updateLevel(Level);
                            UI.updateRagdolls(Ragdolls);
                            UI.updatePoints(Points);
                            MusicManager.changeST(-1);
                            OkSound.play();
                        }
                    }
                    break;
                }
                break;
            }
        }

        //Crosshair Update
        sf::Vector2f MousePosition = Window.mapPixelToCoords(sf::Mouse::getPosition(Window));
        Crosshair.update(MousePosition);

        //Deteccion de gol

        //utilice varios ciclos for, ya que cada nivel tiene una cantidad diferente de elemtos y 
        //estos elemtos estan separados en diferentes arrays
        for (int i = 0; i < 9; i++)
        {   //Cheque las colisiones entre las colas y el arco
            if (CheckCollision(LevelManager.Balls_l1[i], LevelManager.Goal, LevelManager.Balls_l1[i]->Radius, LevelManager.Goal->Radius) && !LevelManager.Balls_l1[i]->bIsReached) {
                std::cout << "Colisión detectada" << std::endl;
                LevelManager.Goal->activate();
                GoalText.Clock.restart();  //Animacion del texto reseteando el clock
                LevelManager.Balls_l1[i]->bIsReached = true; //Seteo bola como que ya hizo el gol
                LevelManager.Balls_l1[i]->setOnOff(false); //Desactivo la bola
                Points += 100; //Sumo puntos
                UI.updatePoints(Points); //Actualizo UI
                Lvl1Goals++; //Sumo cantidad de goles
                GoalSound.play(); //SFX
                if (Lvl1Goals == 9) //Si se hicieron todos los goloes paso de nivel
                {
                    ATransition* Transition = new ATransition("Level 2"); //Creo una nueva transicion y llamo al puntero a funcion
                    Transition->OnTransitionEnd = [&LevelManager, &World]() {
                        //Callbacks
                        LevelManager.clear(); 
                        LevelManager.level2();
                        };
                    Transitions.push_back(Transition);
                    Level = 2; //Actualizo nivel
                    UI.updateLevel(Level);
                    Lvl1Goals = 0; //Reseto goles del nivel pasado
                    MusicManager.changeST(2); //Cambio de track musical
                }
            }
        }
        for (int i = 0; i < 6; i++)
        {   //Mismo que arriba
            if (CheckCollision(LevelManager.Balls_l2[i], LevelManager.Goal, LevelManager.Balls_l2[i]->Radius, LevelManager.Goal->Radius) && !LevelManager.Balls_l2[i]->bIsReached) {
                std::cout << "Colisión detectada" << std::endl;
                LevelManager.Goal->activate();
                GoalText.Clock.restart();
                LevelManager.Balls_l2[i]->bIsReached = true;
                LevelManager.Balls_l2[i]->setOnOff(false);
                Points += 100;
                UI.updatePoints(Points);
                Lvl2Goals++;
                GoalSound.play();
                if (Lvl2Goals == 6)
                {
                    ATransition* Transition = new ATransition("Level 3");
                    Transition->OnTransitionEnd = [&LevelManager, &World]() {
                        LevelManager.clear();
                        LevelManager.level3();
                        };
                    Transitions.push_back(Transition);
                    Level = 3;
                    UI.updateLevel(Level);
                    Lvl2Goals = 0;
                    MusicManager.changeST(3);
                }
            }
            if (CheckCollision(LevelManager.Balls_l3[i], LevelManager.Goal, LevelManager.Balls_l3[i]->Radius, LevelManager.Goal->Radius) && !LevelManager.Balls_l3[i]->bIsReached) {
                std::cout << "Colisión detectada" << std::endl;
                LevelManager.Goal->activate();
                GoalText.Clock.restart();
                LevelManager.Balls_l3[i]->bIsReached = true;
                LevelManager.Balls_l3[i]->setOnOff(false);
                Points += 100;
                UI.updatePoints(Points);
                Lvl3Goals++;
                GoalSound.play();
                if (Lvl3Goals == 6)
                {
                    ATransition* Transition = new ATransition("Level 4");
                    Transition->OnTransitionEnd = [&LevelManager, &World]() {
                        LevelManager.clear();
                        LevelManager.level4();
                        };
                    Transitions.push_back(Transition);
                    Level = 4;
                    UI.updateLevel(Level);
                    Lvl3Goals = 0;
                    MusicManager.changeST(4);
                }
            }
        }
        for (int i = 0; i < 5; i++)
        {
            if (CheckCollision(LevelManager.Balls_l4[i], LevelManager.Goal, LevelManager.Balls_l4[i]->Radius, LevelManager.Goal->Radius) && !LevelManager.Balls_l4[i]->bIsReached) {
                std::cout << "Colisión detectada" << std::endl;
                LevelManager.Goal->activate();
                GoalText.Clock.restart();
                LevelManager.Balls_l4[i]->bIsReached = true;
                LevelManager.Balls_l4[i]->setOnOff(false);
                Points += 100;
                UI.updatePoints(Points);
                Lvl4Goals++;
                GoalSound.play();
                if (Lvl4Goals == 5)
                {
                    LevelManager.PointsFinal = Points;
                    LevelManager.RagdollsFinal = Ragdolls;
                    bIsGame = false;
                    bIsGameOver = true;
                    ATransition* Transition = new ATransition(" End");
                    Transition->OnTransitionEnd = [&LevelManager, &World]() {
                        LevelManager.clear();
                        LevelManager.final();
                        };
                    Transitions.push_back(Transition);
                    Level = 4;
                    UI.updateLevel(Level);
                    Lvl3Goals = 0;
                    ClickCD.restart();
                    MusicManager.changeST(5);
                }
            }
        }

        //Eliminador de Cajas

        //Busco si la posicion del mouse esta dentro de los limites de la caja si es asi y precio el click derecho
        //La elimino, tambien tengo redespertar a las bolas, ya que si alguna caja tiene alguna bola arriba, al ser 
        //eliminada la caja esta no reaccionará, por lo que hay que volver a despertarla.
        for (int i = 0; i < 9; i++)
        {   //Posicion del mouse
            sf::Vector2i MousePos = sf::Mouse::getPosition(Window);
            sf::Vector2f WorldMousePos = Window.mapPixelToCoords(MousePos);
                //Chequeo si estoy dentro de la caja y preciono el click derecho
            if (WorldMousePos.x > LevelManager.Boxes_l1[i]->Sprite.getPosition().x - 5 &&
                WorldMousePos.x < LevelManager.Boxes_l1[i]->Sprite.getPosition().x + 5 &&
                WorldMousePos.y > LevelManager.Boxes_l1[i]->Sprite.getPosition().y - 5 &&
                WorldMousePos.y < LevelManager.Boxes_l1[i]->Sprite.getPosition().y + 5 &&
                sf::Mouse::isButtonPressed(sf::Mouse::Right))
            {   //Chequeo si la caja esta activada
                if (LevelManager.Boxes_l1[i]->bIsEnabled)
                {
                    LevelManager.Boxes_l1[i]->setOnOff(false);      //Desactivo caja
                    LevelManager.Balls_l1[i]->Physics->SetAwake(true);  //Despierto las bolas del nivel
                    printf("Caja Eliminada\n");
                    AParticle* Particle = new ABoxParticle(LevelManager.Boxes_l1[i]->Sprite.getPosition().x, LevelManager.Boxes_l1[i]->Sprite.getPosition().y); //Emito particula en el lugar de la caja eliminada
                    Particles.push_back(Particle);
                    Points -= 500; //Resto puntos por eliminar caja
                    UI.updatePoints(Points); //Actualizo UI
                    BlockSound.play();  //SFX
                }
            }
        }
        //Mismo para arriba, tengo que volver a implementar la logica por lo que explique en los goles
        for (int i = 0; i < 5; i++)
        {
            sf::Vector2i MousePos = sf::Mouse::getPosition(Window);
            sf::Vector2f WorldMousePos = Window.mapPixelToCoords(MousePos);

            if (WorldMousePos.x > LevelManager.Boxes_l4[i]->Sprite.getPosition().x - 5 &&
                WorldMousePos.x < LevelManager.Boxes_l4[i]->Sprite.getPosition().x + 5 &&
                WorldMousePos.y > LevelManager.Boxes_l4[i]->Sprite.getPosition().y - 5 &&
                WorldMousePos.y < LevelManager.Boxes_l4[i]->Sprite.getPosition().y + 5 &&
                sf::Mouse::isButtonPressed(sf::Mouse::Right))
            {
                if (LevelManager.Boxes_l4[i]->bIsEnabled)
                {
                    LevelManager.Boxes_l4[i]->setOnOff(false);
                    LevelManager.Balls_l4[i]->Physics->SetAwake(true);
                    printf("Caja Eliminada\n");
                    AParticle* Particle = new ABoxParticle(LevelManager.Boxes_l4[i]->Sprite.getPosition().x, LevelManager.Boxes_l4[i]->Sprite.getPosition().y);
                    Particles.push_back(Particle);
                    Points -= 500;
                    UI.updatePoints(Points);
                    BlockSound.play();
                }
            }
        }
        for (int i = 0; i < 6; i++)
        {
            sf::Vector2i MousePos = sf::Mouse::getPosition(Window);
            sf::Vector2f WorldMousePos = Window.mapPixelToCoords(MousePos);

            if (WorldMousePos.x > LevelManager.Boxes_l2[i]->Sprite.getPosition().x - 5 &&
                WorldMousePos.x < LevelManager.Boxes_l2[i]->Sprite.getPosition().x + 5 &&
                WorldMousePos.y > LevelManager.Boxes_l2[i]->Sprite.getPosition().y - 5 &&
                WorldMousePos.y < LevelManager.Boxes_l2[i]->Sprite.getPosition().y + 5 &&
                sf::Mouse::isButtonPressed(sf::Mouse::Right))
            {
                if (LevelManager.Boxes_l2[i]->bIsEnabled)
                {
                    LevelManager.Boxes_l2[i]->setOnOff(false);
                    LevelManager.Balls_l2[i]->Physics->SetAwake(true);
                    printf("Caja Eliminada\n");
                    AParticle* Particle = new ABoxParticle(LevelManager.Boxes_l2[i]->Sprite.getPosition().x, LevelManager.Boxes_l2[i]->Sprite.getPosition().y);
                    Particles.push_back(Particle);
                    Points -= 500;
                    UI.updatePoints(Points);
                    BlockSound.play();
                }
            }
            if (WorldMousePos.x > LevelManager.Boxes_l3[i]->Sprite.getPosition().x - 5 &&
                WorldMousePos.x < LevelManager.Boxes_l3[i]->Sprite.getPosition().x + 5 &&
                WorldMousePos.y > LevelManager.Boxes_l3[i]->Sprite.getPosition().y - 5 &&
                WorldMousePos.y < LevelManager.Boxes_l3[i]->Sprite.getPosition().y + 5 &&
                sf::Mouse::isButtonPressed(sf::Mouse::Right))
            {
                if (LevelManager.Boxes_l3[i]->bIsEnabled)
                {
                    LevelManager.Boxes_l3[i]->setOnOff(false);
                    LevelManager.Balls_l3[i]->Physics->SetAwake(true);
                    printf("Caja Eliminada\n");
                    AParticle* Particle = new ABoxParticle(LevelManager.Boxes_l3[i]->Sprite.getPosition().x, LevelManager.Boxes_l3[i]->Sprite.getPosition().y);
                    Particles.push_back(Particle);
                    Points -= 500;
                    UI.updatePoints(Points);
                    BlockSound.play();
                }
            }
        }

        //Reset debug para probar niveles.
        if (ButtonCD.getElapsedTime() > sf::milliseconds(200))
        {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1))
            {
                ATransition* Transition = new ATransition("Level 1");
                Transition->OnTransitionEnd = [&LevelManager, &World]() {
                    LevelManager.clear();
                    LevelManager.level1();
                    };
                Transitions.push_back(Transition);
                Level = 1;
                UI.updateLevel(Level);
                MusicManager.changeST(3);
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2))
            {
                ATransition* Transition = new ATransition("Level 2");
                Transition->OnTransitionEnd = [&LevelManager, &World]() {
                    LevelManager.clear();
                    LevelManager.level2();
                    };
                Transitions.push_back(Transition);
                Level = 2;
                UI.updateLevel(Level);
                MusicManager.changeST(4);
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3))
            {
                ATransition* Transition = new ATransition("Level 3");
                Transition->OnTransitionEnd = [&LevelManager, &World]() {
                    LevelManager.clear();
                    LevelManager.level3();
                    };
                Transitions.push_back(Transition);
                Level = 3;
                UI.updateLevel(Level);
                MusicManager.changeST(5);
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num4))
            {
                ATransition* Transition = new ATransition("Level 4");
                Transition->OnTransitionEnd = [&LevelManager, &World]() {
                    LevelManager.clear();
                    LevelManager.level4();
                    };
                Transitions.push_back(Transition);
                Level = 4;
                UI.updateLevel(Level);
                MusicManager.changeST(6);
            }
            ButtonCD.restart();
        }


        //Eliminacion de ragdolls al chocar el piso

        //Basidcamente recorro el vector de ragdolls y si cumplen las condiciones las elimino
        for (size_t i = 0; i < LevelManager.Ragdolls.size(); ++i) {
            ARagdoll* RagdollPtr = LevelManager.Ragdolls[i];
            ARagdoll& Ragdoll = *RagdollPtr;
            Ragdoll.update();

            if (Ragdoll.bChest->GetPosition().y > 88) //Nivel del piso
            {
                if (Ragdoll.bIsEnabled)
                {
                    AParticle* explosion = new AExplosion(Ragdoll.bChest->GetPosition().x, 90); //Amito particulas
                    Particles.push_back(explosion);
                    DeathSound.play(); //SFX
                }
                Ragdoll.setOff();
            }
        }

        //Elimino y libero memoria
        for (auto it = LevelManager.Ragdolls.begin(); it != LevelManager.Ragdolls.end();)
        {
            (*it)->update();

            if (!(*it)->bIsEnabled)
            {
                it = LevelManager.Ragdolls.erase(it);
                std::cout << "Ragdolls: " << LevelManager.Ragdolls.size() << std::endl;
            }
            else
            {
                ++it;
            }
        }

        //update y eliminacion de particulas
        for (auto it = Particles.begin(); it != Particles.end();)
        {
            (*it)->update();

            if (!(*it)->bIsActive)
            {
                it = Particles.erase(it);
                std::cout << "Particles: " << Particles.size() << std::endl;
            }
            else
            {
                ++it;
            }
        }
        for (auto it = Transitions.begin(); it != Transitions.end();)
        {
            (*it)->update();

            if (!(*it)->bIsActive)
            {
                it = Transitions.erase(it);
                std::cout << "Tr: " << Transitions.size() << std::endl;
            }
            else
            {
                ++it;
            }
        }

        //levelupodate
        LevelManager.update();
        Background.update();

        // Actualización de Motor de Físicas
        World.Step(FrameTime, 8, 8);
        World.ClearForces();
        World.DebugDraw();

        // SFML Renderer
        Window.clear(sf::Color::Black);
        Background.render(Window);
        if (bIsMenu)
        {
            Window.draw(Title);
            Window.draw(PressText);
            Window.draw(CopyText);
        }
        if (bIsTutorial)
        {
            Window.draw(TutorialText);
            Limits->render(Window);
            UI.render(Window);
            Window.draw(Cannon);
            Crosshair.render(Window);
        }
        if (bIsGame)
        {
            for (size_t i = 0; i < LevelManager.Ragdolls.size(); ++i) {
                ARagdoll* RagdollPtr = LevelManager.Ragdolls[i];
                ARagdoll& Ragdoll = *RagdollPtr;
                Ragdoll.render(Window);
            }
            for (const auto& Particle : Particles)
            {
                Particle->render(Window);
            }
            LevelManager.render(Window);
            Window.draw(Cannon);
            if (GoalClock.getElapsedTime() > Time)
            {
                GoalText.render(Window);
            }
            Limits->render(Window);
            UI.render(Window);
            Crosshair.render(Window);
            for (const auto& Transition : Transitions)
            {
                Transition->render(Window);
            }
        }
        if (bIsGameOver)
        {
            LevelManager.render(Window);
            Limits->render(Window);
            Window.draw(Cannon);
            Crosshair.render(Window);
            for (const auto& Transition : Transitions)
            {
                Transition->render(Window);
            }
        }

        Window.display();
    }
}