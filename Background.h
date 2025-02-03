#include <SFML/Graphics.hpp>

class ABackground
{
    sf::Sprite Sprite;                          
    sf::Texture Texture;
    // Utilizo una tilemap de textura y luego recorto la parte necesaria
    // para realizar animaciones con IntRect
    sf::IntRect TRect1{ 0 , 0, 150, 100 };
    sf::IntRect TRect2{ 150 , 0, 150, 100 };
    sf::IntRect TRect3{ 300 , 0, 150, 100 };
    // Variables para setear el framerate de la animación
    sf::Clock Clock;
    sf::Time Time{ sf::milliseconds(75) };
public:
    ABackground();
    void update();
    void render(sf::RenderWindow& window);
};
