#include <SFML/Graphics.hpp>

class AUI {
    sf::Font font;
    sf::Text pointsText;
    sf::Text ragdollText;
    sf::Text levelText;

public:
    int points = 0;
    int level = 0;
    int ragdolls = 0;
    AUI();
    void updatePoints(int newPoints);
    void updateRagdolls(int newRagdolls);
    void updateLevel(int newLevel);
    void render(sf::RenderWindow& window);
};

//Clase para los elementos del HUD
