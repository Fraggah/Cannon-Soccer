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
    //Screen set
    sf::RenderWindow Window;
    sf::View Camera;
    float FPS = 60.f;

    //Time sets
    float FrameTime = 1.0f / FPS;
    sf::Clock GoalClock;
    sf::Time Time = sf::seconds(3.f);
    sf::Clock ClickCD;
    sf::Time ClickTime = sf::milliseconds(200);
    sf::Clock ButtonCD;

    //Vectors
    std::vector<AParticle*> Particles;
    std::vector<ATransition*> Transitions;

    //Cannon
    sf::Sprite Cannon;
    sf::Texture CannonTexture;

    //Title
    sf::Sprite Title;
    sf::Texture TitleTexture;

    //Gameplay Objects
    ACrosshair Crosshair;
    AGoalText GoalText;
    ABackground Background;
    AUI UI;

    //Sounds
    AMusicManager MusicManager;
    sf::Sound ShootSound;
    sf::SoundBuffer ShootSoundBuffer;
    sf::Sound DeathSound;
    sf::SoundBuffer DeathSoundBuffer;
    sf::Sound OkSound;
    sf::SoundBuffer OkSoundBuffer;
    sf::Sound GoalSound;
    sf::SoundBuffer GoalSoundBuffer;
    sf::Sound BlockSound;
    sf::SoundBuffer BlockSoundBuffer;

    float CannonPower = 20.f;

    //Counts
    int32 Points = 0;
    int32 Ragdolls = 0;
    int32 Level = 0;
    int32 Lvl1Goals = 0;
    int32 Lvl2Goals = 0;
    int32 Lvl3Goals = 0;
    int32 Lvl4Goals = 0;

    //States
    bool bIsMenu = true;
    bool bIsTutorial = false;
    bool bIsGame = false;
    bool bIsGameOver = false;

    //Text
    sf::Font Font;
    sf::Text PressText;
    sf::Text TutorialText;
    sf::Text CopyText;    
public:
    Game();
    void Init();
    void Reset();
    bool CheckCollision(ABall* Ball, AGoal* Goal, float BallRadius, float GoalRadius);
    void Run();
};