#include <SFML/Graphics.hpp>

class Goal
{
    float x;
    float y;
    sf::Texture texture;
    sf::Clock clock;
    sf::Time time{ sf::milliseconds(50) };
public:
    bool isActive = false;
    float radius;
    sf::Sprite sprite;
    Goal(float _x, float _y);
    void activate();
    void update();
};
