#pragma once

#include <iostream>
#include <sstream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

using namespace std;
using namespace sf;

class Player {
private:
    Sprite sprite;
    Texture texture;

    float movementSpeed;

    float attackCoolDown;
    float attackCoolDownMax;

    int hp;
    int hpMax;

    ///private functions
    void initSprite();

    void initVariables();

    void initTexture();


public:
    Player();

    virtual ~Player();

    Vector2f getPos() const;

    Vector2f getSize() const;

    FloatRect getBounds();

    int getHP() const;

    int getHPMax() const;

    void setPosition(Vector2f pos);

    void setPosition(float x, float y);

    void setHP(int HP);

    void loseHp(int value);
    ///functions

    void move(float x, float y);

    bool canAttack() const;

    void updateAttack();

    void update();

    void render(RenderTarget *target);
};