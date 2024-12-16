#include <SFML/Graphics.hpp>

class GoalText
{
    sf::Time elapsedTime;
    float progress;
public:
    sf::Sprite sprite;
    sf::Texture texture;
    sf::Clock clock;
    sf::Time time;
    GoalText();
    void render(sf::RenderWindow& window);
};
