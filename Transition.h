#include <SFML/Graphics.hpp>
#include <functional>

class ATransition
{
    sf::Sprite Sprite;
    sf::Texture Texture;
    sf::IntRect TRect1{ 0 , 0 , 150 , 100 };
    sf::IntRect TRect2{ 150 , 0 , 150 , 100 };
    sf::IntRect TRect3{ 300 , 0 , 150 , 100 };
    sf::IntRect TRect4{ 450 , 0 , 150 , 100 };
    sf::IntRect TRect5{ 600 , 0 , 150 , 100 };
    sf::IntRect TRect6{ 750 , 0 , 150 , 100 };
    sf::Clock Clock;
    sf::Font Font;
    sf::Text LevelText;
    sf::String LevelString;
    bool TextActive = false;
public:
    bool bIsActive = true;
    std::function<void()> OnTransitionEnd; // Puntero a funcion para llamar una funcion justo en una parte de la animacion
    ATransition(sf::String Level); //String para poner el nombre del nivel a la mitad de la animacion con el callback
    void update();
    void render(sf::RenderWindow& Window);
};

//IntRect explicados en Background

