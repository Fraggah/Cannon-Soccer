#include <SFML/Graphics.hpp>

class AGoal
{
    float X;
    float Y;
    sf::Texture Texture;
    sf::Clock Clock;
    sf::Time Time{ sf::milliseconds(50) };
public:
    bool bIsActive = false;
    float Radius;
    sf::Sprite Sprite;
    AGoal(float _X, float _Y);
    void activate();
    void update();
};

//Arco, lo interesante a destacar es la animacion del gol
//Resultado de la convinacion de metodos activate() y update()
