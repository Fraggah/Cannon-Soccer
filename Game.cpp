#include "Game.h"

Game::Game()
{
    init();
}

void Game::init()
{
    window.create(sf::VideoMode(1200, 800), "Canon Socker");

    //phyWorld = new b2World(b2Vec2(0.0f, 80.0f));
    //levelmanager = new LevelManager(*phyWorld);
    //limits = new Limits(*phyWorld);

    window.setFramerateLimit(fps);
    window.setMouseCursorVisible(false);

    camera.setSize(150, 100);
    camera.setCenter(75, 50);
    window.setView(camera);

    cannonTexture.loadFromFile("sprites/cannon.png");
    canon.setOrigin(5, 5);
    canon.setTexture(cannonTexture);
    canon.setPosition(20, 85);

    titleTexture.loadFromFile("sprites/title.png");
    title.setTexture(titleTexture);

    font.loadFromFile("sprites/nes.otf");
    pressText.setFont(font);
    pressText.setCharacterSize(24);
    pressText.setScale(0.15f, 0.15f);
    pressText.setPosition(57, 70.5);
    pressText.setString("click to start");
    pressText.setFillColor(sf::Color(203, 232, 247));

    tutorialText.setFont(font);
    tutorialText.setCharacterSize(24);
    tutorialText.setScale(0.15f, 0.15f);
    tutorialText.setPosition(20, 20);
    tutorialText.setString("                Tutorial\n\n\nObjetive : Get all balls into the goal.\n\nShot Power : Depends on shooting distance.\n\nLeft Click : Launch ragdoll (-10 points).\n\nRight Click : Remove box (-500 points).\n\n\n             Click to start");
    tutorialText.setFillColor(sf::Color(203, 232, 247));

    copyText.setFont(font);
    copyText.setCharacterSize(24);
    copyText.setScale(0.15f, 0.15f);
    copyText.setPosition(49.5, 90.5);
    copyText.setString("© silvio stefanucci");
    copyText.setFillColor(sf::Color(203, 232, 247));

    musicManager.play();

    shootSoundBuffer.loadFromFile("sprites/Shoot.ogg");
    shootSound.setBuffer(shootSoundBuffer);
    deathSoundBuffer.loadFromFile("sprites/Death.ogg");
    deathSound.setBuffer(deathSoundBuffer);
    okSoundBuffer.loadFromFile("sprites/Ok.ogg");
    okSound.setBuffer(okSoundBuffer);
    goalSoundBuffer.loadFromFile("sprites/Goal.ogg");
    goalSound.setBuffer(goalSoundBuffer);
    blockSoundBuffer.loadFromFile("sprites/Block.ogg");
    blockSound.setBuffer(blockSoundBuffer);
}

void Game::reset()
{
    points = 0;
    ragdolls = 0;
    level = 0;
    lvl1goals = 0;
    lvl2goals = 0;
    lvl3goals = 0;
    lvl4goals = 0;
}

bool Game::checkCollision(Ball* ball, Goal* goal, float ballRadius, float goalRadius) {
    float dx = ball->sprite.getPosition().x - goal->sprite.getPosition().x;
    float dy = ball->sprite.getPosition().y - goal->sprite.getPosition().y;

    float distance = sqrt(pow(dx, 2) + pow(dy, 2));

    return distance <= (ballRadius + goalRadius);
}

void Game::checkGoal()
{

}

void Game::run()
{

    b2World phyWorld(b2Vec2(0.0f, 80.0f));
    LevelManager levelmanager(phyWorld);
    Limits* limits = new Limits(phyWorld);

    while (window.isOpen())
    {

        sf::Event event;
        while (window.pollEvent(event))
        {
            switch (event.type)
            {
            case sf::Event::Closed:
                window.close();
                break;
            case sf::Event::MouseButtonPressed:
                switch (event.key.code)
                {
                case sf::Mouse::Button::Left:
                    if (isMenu)
                    {
                        if (clickCD.getElapsedTime() > clickTime)
                        {
                            isTutorial = true;
                            isMenu = false;
                            clickCD.restart();
                            musicManager.changeST(0);
                            okSound.play();
                        }
                    }
                    if (isTutorial)
                    {
                        if (clickCD.getElapsedTime() > clickTime)
                        {
                            isGame = true;
                            isTutorial = false;
                            clickCD.restart();
                            Transition* transition = new Transition("Level 1");
                            transition->onTransitionEnd = [&levelmanager, &phyWorld]() {
                                levelmanager.clear(&phyWorld);
                                levelmanager.level1();
                                };
                            transitions.push_back(transition);
                            level = 1;
                            ui.updateLevel(level);
                            musicManager.changeST(1);
                            okSound.play();
                        }
                    }
                    if (isGame)
                    {
                        if (clickCD.getElapsedTime() > clickTime)
                        {
                            sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                            sf::Vector2f worldMousePos = window.mapPixelToCoords(mousePos);

                            Ragdoll* ragdoll = new Ragdoll(phyWorld, canon.getPosition().x, canon.getPosition().y - 3);
                            b2Vec2 direction1 = b2Vec2(worldMousePos.x - ragdoll->bTronco->GetPosition().x,
                                worldMousePos.y - ragdoll->bTronco->GetPosition().y);
                            float distancia = std::sqrt(direction1.x * direction1.x + direction1.y * direction1.y);
                            direction1.Normalize();
                            float potencia = cdp * distancia;
                            std::cout << distancia << std::endl;
                            ragdoll->applyImpulse(b2Vec2(direction1.x * potencia, direction1.y * potencia), true);
                            levelmanager.ragdolls.push_back(ragdoll);
                            shootSound.play();
                            ragdolls++;
                            points -= 10;

                            ui.updateRagdolls(ragdolls);
                            ui.updatePoints(points);

                            std::cout << "Ragdolls: " << levelmanager.ragdolls.size() << std::endl;

                            Particle* shot = new CanonShot(26, 79);
                            particles.push_back(shot);
                        }

                    }
                    if (isGameOver)
                    {
                        if (clickCD.getElapsedTime() > clickTime)
                        {
                            isMenu = true;
                            isGameOver = false;
                            clickCD.restart();
                            levelmanager.isFinal = false;
                            reset();
                            ui.updateLevel(level);
                            ui.updateRagdolls(ragdolls);
                            ui.updatePoints(points);
                            musicManager.changeST(-1);
                            okSound.play();
                        }
                    }
                    break;
                }
                break;
            }
        }

        //Crosshair Update
        sf::Vector2f mousePosition = window.mapPixelToCoords(sf::Mouse::getPosition(window));
        crosshair.update(mousePosition);

        //Deteccion de gol
        for (int i = 0; i < 9; i++)
        {
            if (checkCollision(levelmanager.balls_l1[i], levelmanager.goal, levelmanager.balls_l1[i]->radius, levelmanager.goal->radius) && !levelmanager.balls_l1[i]->reached) {
                std::cout << "Colisión detectada" << std::endl;
                levelmanager.goal->activate();
                goaltext.clock.restart();
                levelmanager.balls_l1[i]->reached = true;
                levelmanager.balls_l1[i]->setOnOff(false);
                points += 100;
                ui.updatePoints(points);
                lvl1goals++;
                goalSound.play();
                if (lvl1goals == 9)
                {
                    Transition* transition = new Transition("Level 2");
                    transition->onTransitionEnd = [&levelmanager, &phyWorld]() {
                        levelmanager.clear(&phyWorld);
                        levelmanager.level2();
                        };
                    transitions.push_back(transition);
                    level = 2;
                    ui.updateLevel(level);
                    lvl1goals = 0;
                    musicManager.changeST(2);
                }
            }
        }
        for (int i = 0; i < 6; i++)
        {
            if (checkCollision(levelmanager.balls_l2[i], levelmanager.goal, levelmanager.balls_l2[i]->radius, levelmanager.goal->radius) && !levelmanager.balls_l2[i]->reached) {
                std::cout << "Colisión detectada" << std::endl;
                levelmanager.goal->activate();
                goaltext.clock.restart();
                levelmanager.balls_l2[i]->reached = true;
                levelmanager.balls_l2[i]->setOnOff(false);
                points += 100;
                ui.updatePoints(points);
                lvl2goals++;
                goalSound.play();
                if (lvl2goals == 6)
                {
                    Transition* transition = new Transition("Level 3");
                    transition->onTransitionEnd = [&levelmanager, &phyWorld]() {
                        levelmanager.clear(&phyWorld);
                        levelmanager.level3();
                        };
                    transitions.push_back(transition);
                    level = 3;
                    ui.updateLevel(level);
                    lvl2goals = 0;
                    musicManager.changeST(3);
                }
            }
            if (checkCollision(levelmanager.balls_l3[i], levelmanager.goal, levelmanager.balls_l3[i]->radius, levelmanager.goal->radius) && !levelmanager.balls_l3[i]->reached) {
                std::cout << "Colisión detectada" << std::endl;
                levelmanager.goal->activate();
                goaltext.clock.restart();
                levelmanager.balls_l3[i]->reached = true;
                levelmanager.balls_l3[i]->setOnOff(false);
                points += 100;
                ui.updatePoints(points);
                lvl3goals++;
                goalSound.play();
                if (lvl3goals == 6)
                {
                    Transition* transition = new Transition("Level 4");
                    transition->onTransitionEnd = [&levelmanager, &phyWorld]() {
                        levelmanager.clear(&phyWorld);
                        levelmanager.level4();
                        };
                    transitions.push_back(transition);
                    level = 4;
                    ui.updateLevel(level);
                    lvl3goals = 0;
                    musicManager.changeST(4);
                }
            }
        }
        for (int i = 0; i < 5; i++)
        {
            if (checkCollision(levelmanager.balls_l4[i], levelmanager.goal, levelmanager.balls_l4[i]->radius, levelmanager.goal->radius) && !levelmanager.balls_l4[i]->reached) {
                std::cout << "Colisión detectada" << std::endl;
                levelmanager.goal->activate();
                goaltext.clock.restart();
                levelmanager.balls_l4[i]->reached = true;
                levelmanager.balls_l4[i]->setOnOff(false);
                points += 100;
                ui.updatePoints(points);
                lvl4goals++;
                goalSound.play();
                if (lvl4goals == 5)
                {
                    levelmanager.pointsFinal = points;
                    levelmanager.ragdollsFinal = ragdolls;
                    isGame = false;
                    isGameOver = true;
                    Transition* transition = new Transition(" End");
                    transition->onTransitionEnd = [&levelmanager, &phyWorld]() {
                        levelmanager.clear(&phyWorld);
                        levelmanager.final();
                        };
                    transitions.push_back(transition);
                    level = 4;
                    ui.updateLevel(level);
                    lvl3goals = 0;
                    clickCD.restart();
                    musicManager.changeST(5);
                }
            }
        }

        //Eliminador de Cajas
        for (int i = 0; i < 9; i++)
        {
            sf::Vector2i mousePos = sf::Mouse::getPosition(window);
            sf::Vector2f worldMousePos = window.mapPixelToCoords(mousePos);

            if (worldMousePos.x > levelmanager.boxes_l1[i]->sprite.getPosition().x - 5 &&
                worldMousePos.x < levelmanager.boxes_l1[i]->sprite.getPosition().x + 5 &&
                worldMousePos.y > levelmanager.boxes_l1[i]->sprite.getPosition().y - 5 &&
                worldMousePos.y < levelmanager.boxes_l1[i]->sprite.getPosition().y + 5 &&
                sf::Mouse::isButtonPressed(sf::Mouse::Right))
            {
                if (levelmanager.boxes_l1[i]->isEnabled)
                {
                    levelmanager.boxes_l1[i]->setOnOff(false);
                    levelmanager.balls_l1[i]->physics->SetAwake(true);
                    printf("Caja Eliminada\n");
                    Particle* particle = new BoxParticle(levelmanager.boxes_l1[i]->sprite.getPosition().x, levelmanager.boxes_l1[i]->sprite.getPosition().y);
                    particles.push_back(particle);
                    points -= 500;
                    ui.updatePoints(points);
                    blockSound.play();
                }
            }
        }
        for (int i = 0; i < 5; i++)
        {
            sf::Vector2i mousePos = sf::Mouse::getPosition(window);
            sf::Vector2f worldMousePos = window.mapPixelToCoords(mousePos);

            if (worldMousePos.x > levelmanager.boxes_l4[i]->sprite.getPosition().x - 5 &&
                worldMousePos.x < levelmanager.boxes_l4[i]->sprite.getPosition().x + 5 &&
                worldMousePos.y > levelmanager.boxes_l4[i]->sprite.getPosition().y - 5 &&
                worldMousePos.y < levelmanager.boxes_l4[i]->sprite.getPosition().y + 5 &&
                sf::Mouse::isButtonPressed(sf::Mouse::Right))
            {
                if (levelmanager.boxes_l4[i]->isEnabled)
                {
                    levelmanager.boxes_l4[i]->setOnOff(false);
                    levelmanager.balls_l4[i]->physics->SetAwake(true);
                    printf("Caja Eliminada\n");
                    Particle* particle = new BoxParticle(levelmanager.boxes_l4[i]->sprite.getPosition().x, levelmanager.boxes_l4[i]->sprite.getPosition().y);
                    particles.push_back(particle);
                    points -= 500;
                    ui.updatePoints(points);
                    blockSound.play();
                }
            }
        }
        for (int i = 0; i < 6; i++)
        {
            sf::Vector2i mousePos = sf::Mouse::getPosition(window);
            sf::Vector2f worldMousePos = window.mapPixelToCoords(mousePos);

            if (worldMousePos.x > levelmanager.boxes_l2[i]->sprite.getPosition().x - 5 &&
                worldMousePos.x < levelmanager.boxes_l2[i]->sprite.getPosition().x + 5 &&
                worldMousePos.y > levelmanager.boxes_l2[i]->sprite.getPosition().y - 5 &&
                worldMousePos.y < levelmanager.boxes_l2[i]->sprite.getPosition().y + 5 &&
                sf::Mouse::isButtonPressed(sf::Mouse::Right))
            {
                if (levelmanager.boxes_l2[i]->isEnabled)
                {
                    levelmanager.boxes_l2[i]->setOnOff(false);
                    levelmanager.balls_l2[i]->physics->SetAwake(true);
                    printf("Caja Eliminada\n");
                    Particle* particle = new BoxParticle(levelmanager.boxes_l2[i]->sprite.getPosition().x, levelmanager.boxes_l2[i]->sprite.getPosition().y);
                    particles.push_back(particle);
                    points -= 500;
                    ui.updatePoints(points);
                    blockSound.play();
                }
            }
            if (worldMousePos.x > levelmanager.boxes_l3[i]->sprite.getPosition().x - 5 &&
                worldMousePos.x < levelmanager.boxes_l3[i]->sprite.getPosition().x + 5 &&
                worldMousePos.y > levelmanager.boxes_l3[i]->sprite.getPosition().y - 5 &&
                worldMousePos.y < levelmanager.boxes_l3[i]->sprite.getPosition().y + 5 &&
                sf::Mouse::isButtonPressed(sf::Mouse::Right))
            {
                if (levelmanager.boxes_l3[i]->isEnabled)
                {
                    levelmanager.boxes_l3[i]->setOnOff(false);
                    levelmanager.balls_l3[i]->physics->SetAwake(true);
                    printf("Caja Eliminada\n");
                    Particle* particle = new BoxParticle(levelmanager.boxes_l3[i]->sprite.getPosition().x, levelmanager.boxes_l3[i]->sprite.getPosition().y);
                    particles.push_back(particle);
                    points -= 500;
                    ui.updatePoints(points);
                    blockSound.play();
                }
            }
        }

        //Reset debug
        if (buttonCD.getElapsedTime() > sf::milliseconds(200))
        {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1))
            {
                Transition* transition = new Transition("Level 1");
                transition->onTransitionEnd = [&levelmanager, &phyWorld]() {
                    levelmanager.clear(&phyWorld);
                    levelmanager.level1();
                    };
                transitions.push_back(transition);
                level = 1;
                ui.updateLevel(level);
                musicManager.changeST(3);
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2))
            {
                Transition* transition = new Transition("Level 2");
                transition->onTransitionEnd = [&levelmanager, &phyWorld]() {
                    levelmanager.clear(&phyWorld);
                    levelmanager.level2();
                    };
                transitions.push_back(transition);
                level = 2;
                ui.updateLevel(level);
                musicManager.changeST(4);
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3))
            {
                Transition* transition = new Transition("Level 3");
                transition->onTransitionEnd = [&levelmanager, &phyWorld]() {
                    levelmanager.clear(&phyWorld);
                    levelmanager.level3();
                    };
                transitions.push_back(transition);
                level = 3;
                ui.updateLevel(level);
                musicManager.changeST(5);
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num4))
            {
                Transition* transition = new Transition("Level 4");
                transition->onTransitionEnd = [&levelmanager, &phyWorld]() {
                    levelmanager.clear(&phyWorld);
                    levelmanager.level4();
                    };
                transitions.push_back(transition);
                level = 4;
                ui.updateLevel(level);
                musicManager.changeST(6);
            }
            buttonCD.restart();
        }


        //Eliminacion piso
        for (size_t i = 0; i < levelmanager.ragdolls.size(); ++i) {
            Ragdoll* ragdollPtr = levelmanager.ragdolls[i];
            Ragdoll& ragdoll = *ragdollPtr;
            ragdoll.update();

            if (ragdoll.bTronco->GetPosition().y > 88)
            {
                if (ragdoll.isEnabled)
                {
                    Particle* explosion = new Explosion(ragdoll.bTronco->GetPosition().x, 90);
                    particles.push_back(explosion);
                    deathSound.play();
                }
                ragdoll.setOff();
            }
        }

        for (auto it = levelmanager.ragdolls.begin(); it != levelmanager.ragdolls.end();)
        {
            (*it)->update();

            if (!(*it)->isEnabled)
            {
                it = levelmanager.ragdolls.erase(it);
                std::cout << "Ragdolls: " << levelmanager.ragdolls.size() << std::endl;
            }
            else
            {
                ++it;
            }
        }

        //update y eliminacion de particulas
        for (auto it = particles.begin(); it != particles.end();)
        {
            (*it)->update();

            if (!(*it)->isActive)
            {
                it = particles.erase(it);
                std::cout << "Particles: " << particles.size() << std::endl;
            }
            else
            {
                ++it;
            }
        }
        for (auto it = transitions.begin(); it != transitions.end();)
        {
            (*it)->update();

            if (!(*it)->isActive)
            {
                it = transitions.erase(it);
                std::cout << "Tr: " << transitions.size() << std::endl;
            }
            else
            {
                ++it;
            }
        }

        //levelupodate
        levelmanager.update();
        background.update();

        levelmanager.elices_l2[0]->update(.1);
        levelmanager.elices_l2[1]->update(.1);
        levelmanager.elices_l2[2]->update(.1);

        // Actualización de Motor de Físicas
        phyWorld.Step(frameTime, 8, 8);
        phyWorld.ClearForces();
        phyWorld.DebugDraw();

        // SFML Renderer
        window.clear(sf::Color::Black);
        background.render(window);
        if (isMenu)
        {
            window.draw(title);
            window.draw(pressText);
            window.draw(copyText);
        }
        if (isTutorial)
        {
            window.draw(tutorialText);
            limits->render(window);
            ui.render(window);
            window.draw(canon);
            crosshair.render(window);
        }
        if (isGame)
        {
            for (size_t i = 0; i < levelmanager.ragdolls.size(); ++i) {
                Ragdoll* ragdollPtr = levelmanager.ragdolls[i];
                Ragdoll& ragdoll = *ragdollPtr;
                ragdoll.render(window);
            }
            for (const auto& particle : particles)
            {
                particle->render(window);
            }
            levelmanager.render(window);
            window.draw(canon);
            if (goalClock.getElapsedTime() > time)
            {
                goaltext.render(window);
            }
            limits->render(window);
            ui.render(window);
            crosshair.render(window);
            for (const auto& transition : transitions)
            {
                transition->render(window);
            }
        }
        if (isGameOver)
        {
            levelmanager.render(window);
            limits->render(window);
            window.draw(canon);
            crosshair.render(window);
            for (const auto& transition : transitions)
            {
                transition->render(window);
            }
        }

        window.display();
    }
}