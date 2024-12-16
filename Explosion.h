#include <SFML/Graphics.hpp>
#include "Particle.h"

class Explosion : public Particle
{
public:
    Explosion(float _x, float _y);
    void update() override;
};
