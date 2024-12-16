#include "Particle.h"

void Particle::render(sf::RenderWindow& window)
{
    if (isActive)
    {
        window.draw(sprite);
    }
}

