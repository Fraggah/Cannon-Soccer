#include <SFML/Graphics.hpp>
#include "Particle.h"

class ABoxParticle : public AParticle
{
public:
    ABoxParticle(float _X, float _Y);
    void update() override;
};

//"Particula" al eliminar una caja, en realidad es una pequeña animacion
//Pero funciona como particula.
//Uitiliza la misma tecnica de animacion que Background pero sin loop