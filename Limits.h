#include <SFML/Graphics.hpp>
#include "Box2DHelper.h"

class Limits : public Box2DHelper
{
    b2Body* groundBody;
    b2Body* leftWallBody;
    b2Body* rightWallBody;
    sf::Sprite sprite;
    sf::Texture texture;
public:
    Limits(b2World& mundo);
    void render(sf::RenderWindow& window);
};
