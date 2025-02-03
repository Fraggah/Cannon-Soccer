#include <SFML/Graphics.hpp>
#include "Box2DHelper.h"

class ALimits : public Box2DHelper
{
    b2Body* GroundBody;
    b2Body* LeftWallBody;
    b2Body* RightWallBody;
    sf::Sprite Sprite;
    sf::Texture Texture;
public:
    ALimits(b2World& World);
    void render(sf::RenderWindow& Window);
};

//No hay mucho para explicar, basicamente son las paredes, decidí que no haya techo por cuestion de gameplay
