#include "GoalText.h"

GoalText::GoalText()
{
    sprite.setOrigin(75, 50);
    sprite.setPosition(75, 50);
    texture.loadFromFile("sprites/goalText.png");
    sprite.setTexture(texture);
    time = sf::seconds(.9);
    clock.restart();
}

void GoalText::render(sf::RenderWindow& window)
{
    elapsedTime = clock.getElapsedTime();
    progress = elapsedTime.asSeconds() * 4 / time.asSeconds();

    if (progress > 1.0f)
        progress = 1.0f;

    // Escala: crece desde 0.1 hasta 1.0
    float scale = 0.1f + (progress * 0.9f);
    sprite.setScale(scale, scale);

    // Alfa: disminuye de 255 a 0
    int alpha = static_cast<int>(255 * (1.0f - progress));
    if (alpha < 0) alpha = 0; // Asegura que no sea negativo

    sprite.setColor(sf::Color(255, 255, 255, alpha)); // Aplica la transparencia

    if (elapsedTime < time)
    {
        window.draw(sprite);
    }
}
