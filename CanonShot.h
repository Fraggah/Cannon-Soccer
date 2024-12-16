#include <SFML/Graphics.hpp>
#include "Particle.h"

class CanonShot : public Particle
{
public:
    CanonShot(float _x, float _y);
    void update() override;
};

