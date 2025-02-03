#include <SFML/Graphics.hpp>
#include "Box2DHelper.h"

class AGiantBall
{
    float X1;
    float Y1;
    float X2;
    float Y2;
    sf::Sprite Sprite;
    sf::Texture Texture;
    //Creacion de una linea para representar graficamente la cadena
    //Utiliza un array
    sf::Vertex Line[2];

public:
    //Utilizacion de un DistanceJoint usado como una "cadena" que agarra una bola gigante
    //Siempre que utilizamos Joints tenemos que crear la definicion, cuya almacena datoas para la creacion del joint
    b2DistanceJointDef ChainDef;
    //Joint en si, para crearlo necesitamos previamente una definicion
    b2DistanceJoint* ChainDJ;
    //Parte fisica estatica de la cual se engancha el inicio de la cadena
    b2Body* Hook;
    //Parte fisica de la bola gicante, tambien enganchada de la cadena pero en su parte final
    b2Body* Physics;
    bool bIsEnabled = false;
    //Para el constructor pido que se pase como argunmento las posiciones de cada uno de los cuerpos, del estatico y del dinamico
    AGiantBall(b2World& World, float _X1, float _Y1, float _X2, float _Y2);
    void update();
    void render(sf::RenderWindow& Window);
    void setOnOff(bool On);
};

//Similar a Elice, pero en este caso tenemos algunos elementos mas