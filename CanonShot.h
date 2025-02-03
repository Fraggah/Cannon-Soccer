#include <SFML/Graphics.hpp>
#include "Particle.h"

class ACannonShoot : public AParticle
{
public:
    ACannonShoot(float _x, float _y);
    void update() override;
};

//Lo mismo que BoxParticle...

