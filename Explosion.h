#include <SFML/Graphics.hpp>
#include "Particle.h"

class AExplosion : public AParticle
{
public:
    AExplosion(float _X, float _Y);
    void update() override;
};

// Igual a CanonShot