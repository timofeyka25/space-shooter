#pragma once


#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

using namespace std;
using namespace sf;

class Enemy {
private:
    unsigned pointCount;
    CircleShape shape;
    float speed;
    int hp;
    int hpMax;
    int damage;
    int points;

    void initVariables();

    void initShape();


public:
    Enemy(float posX, float posY);

    virtual ~Enemy();

    FloatRect getBounds() const;

    int getPoints() const;

    int getDamage() const;

    void loseHP(int value);

    void setTransparent(int transparent);

    int getHp() const;

    int getHpMax() const;

    void update();

    void render(RenderTarget *target);
};