#include <iostream>
#include <cmath>
#include <SFML/Audio.hpp>
#include "LevelManager.h"
#include "Transition.h"
#include "CanonShot.h"
#include "Crosshair.h"
#include "GoalText.h"
#include "Background.h"
#include "UI.h"
#include "Limits.h"
#include "BoxParticle.h"
#include "Explosion.h"
#include "Particle.h"
#include "MusicManager.h"

class Game {
    sf::RenderWindow window;
    float fps = 60;
    float frameTime = 1.0f / fps;
    sf::Clock goalClock;
    sf::Time time = sf::seconds(3);
    sf::Clock clickCD;
    sf::Time clickTime = sf::milliseconds(200);
    sf::Clock buttonCD;
    std::vector<Particle*> particles;
    std::vector<Transition*> transitions;
    sf::View camera;
    sf::Sprite canon;
    sf::Texture cannonTexture;
    sf::Sprite title;
    sf::Texture titleTexture;
    Crosshair crosshair;
    GoalText goaltext;
    Background background;
    UI ui;
    MusicManager musicManager;
    sf::Sound shootSound;
    sf::SoundBuffer shootSoundBuffer;
    sf::Sound deathSound;
    sf::SoundBuffer deathSoundBuffer;
    sf::Sound okSound;
    sf::SoundBuffer okSoundBuffer;
    sf::Sound goalSound;
    sf::SoundBuffer goalSoundBuffer;
    sf::Sound blockSound;
    sf::SoundBuffer blockSoundBuffer;
    float cdp = 20; //constante de potencia
    int points = 0;
    int ragdolls = 0;
    int level = 0;
    int lvl1goals = 0;
    int lvl2goals = 0;
    int lvl3goals = 0;
    int lvl4goals = 0;
    bool isMenu = true;
    bool isTutorial = false;
    bool isGame = false;
    bool isGameOver = false;
    sf::Font font;
    sf::Text pressText;
    sf::Text tutorialText;
    sf::Text copyText;    
    //b2World* phyWorld;
    //LevelManager* levelmanager;
    //Limits* limits;
public:
    Game();
    void init();
    void reset();
    bool checkCollision(Ball* ball, Goal* goal, float ballRadius, float goalRadius);
    void checkGoal();
    void run();
};