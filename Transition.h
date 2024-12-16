#include <SFML/Graphics.hpp>
#include <functional>

class Transition
{
    sf::Sprite sprite;
    sf::Texture texture;
    sf::IntRect textureRect1{ 0 , 0 , 150 , 100 };
    sf::IntRect textureRect2{ 150 , 0 , 150 , 100 };
    sf::IntRect textureRect3{ 300 , 0 , 150 , 100 };
    sf::IntRect textureRect4{ 450 , 0 , 150 , 100 };
    sf::IntRect textureRect5{ 600 , 0 , 150 , 100 };
    sf::IntRect textureRect6{ 750 , 0 , 150 , 100 };
    sf::Clock clock;
    sf::Font font;
    sf::Text levelText;
    sf::String levelString;
    bool textActive = false;
public:
    bool isActive = true;
    std::function<void()> onTransitionEnd; // Callback
    Transition(sf::String level);
    void update();
    void render(sf::RenderWindow& window);
};

