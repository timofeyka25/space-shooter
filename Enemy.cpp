#include "Enemy.h"

void Enemy::initVariables() {
    this->pointCount = rand() % 8 + 3;
    this->speed = float(this->pointCount) / 4;
    this->hpMax = int(this->pointCount * 2.5);
    this->hp = this->hpMax;
    this->damage = int(this->pointCount);
    this->points = int(this->pointCount);
}

void Enemy::initShape() {
    this->shape.setRadius(float(this->pointCount * 5));
    this->shape.setPointCount(this->pointCount);
    this->shape.setFillColor(Color(rand() % 255 + 1, rand() % 255 + 1, rand() % 255 + 1));
}

Enemy::Enemy(float posX, float posY) {
    this->initVariables();
    this->shape.setPosition(posX, posY);
    this->initShape();
}

Enemy::~Enemy() = default;

FloatRect Enemy::getBounds() const {
    return this->shape.getGlobalBounds();
}

int Enemy::getPoints() const {
    return this->points;
}

int Enemy::getDamage() const {
    return this->damage;
}

void Enemy::loseHP(int value) {
    this->hp -= value;
    if (this->hp < 0)
        this->hp = 0;
}

void Enemy::setTransparent(int transparent) {
    int r = this->shape.getFillColor().r;
    int g = this->shape.getFillColor().g;
    int b = this->shape.getFillColor().b;

    this->shape.setFillColor(Color(r, g, b, transparent));
}

int Enemy::getHp() const {
    return this->hp;
}

int Enemy::getHpMax() const {
    return this->hpMax;
}

void Enemy::update() {
    this->shape.move(0.f, this->speed);
}

void Enemy::render(RenderTarget *target) {
    target->draw(this->shape);
}
