#include "Particle.h"

void AParticle::render(sf::RenderWindow& Window)
{
    if (bIsActive)
    {
        Window.draw(Sprite);
    }
}

