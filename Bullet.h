#pragma once

#include <iostream>
#include <sstream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

using namespace std;
using namespace sf;

class Bullet {

private:

    Sprite shape;

    Vector2f direction;
    float movementSpeed;

    int damage;

public:

    Bullet();

    Bullet(Texture *texture, float posX, float posY, float x, float y, float movementSpeed, int damage);

    virtual ~Bullet();

    FloatRect getBounds() const;

    int getDamage() const;

    ///functions

    void update();

    void render(RenderTarget *target);
};