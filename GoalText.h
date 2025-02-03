#include <SFML/Graphics.hpp>

class AGoalText
{
    sf::Time ElapsedTime;
    float Progress;
public:
    sf::Sprite Sprite;
    sf::Texture Texture;
    sf::Clock Clock;
    sf::Time Time;
    AGoalText();
    void render(sf::RenderWindow& Window);
};

//Texto que se dibuja al hacer un gol con una pequeña animacion