#include <SFML/Graphics.hpp>

class Background
{
    sf::Sprite sprite;
    sf::Texture texture;
    sf::IntRect textureRect1{ 0 , 0, 150, 100 };
    sf::IntRect textureRect2{ 150 , 0, 150, 100 };
    sf::IntRect textureRect3{ 300 , 0, 150, 100 };
    sf::Clock clock;
    sf::Time time{ sf::milliseconds(75) };
public:
    Background();
    void update();
    void render(sf::RenderWindow& window);
};
