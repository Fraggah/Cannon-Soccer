#include <SFML/Graphics.hpp>
#include "Particle.h"

class BoxParticle : public Particle
{
public:
    BoxParticle(float _x, float _y);
    void update() override;
};
