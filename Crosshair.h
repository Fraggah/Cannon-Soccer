#include <SFML/Graphics.hpp>

class Crosshair
{
    sf::Sprite sprite;
    sf::Texture texture;
public:
    Crosshair();
    void update(sf::Vector2f mouse);
    void render(sf::RenderWindow& window);
};
