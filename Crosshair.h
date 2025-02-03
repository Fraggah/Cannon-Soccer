#include <SFML/Graphics.hpp>

class ACrosshair
{
    sf::Sprite Sprite;
    sf::Texture Texture;
public:
    ACrosshair();
    void update(sf::Vector2f Mouse);
    void render(sf::RenderWindow& Window);
};

//es la mira, coloco un sprite para que siga la posicion del mouse
