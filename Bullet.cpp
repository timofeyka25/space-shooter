#include "Bullet.h"

Bullet::Bullet() {

}

Bullet::Bullet(Texture *texture, float posX, float posY, float x, float y, float movementSpeed, int damage = 5) {
    this->shape.setTexture(*texture);
    this->shape.scale(0.05f, 0.05f);
    this->shape.setPosition(posX, posY);
    this->direction.x = x;
    this->direction.y = y;
    this->movementSpeed = movementSpeed;
    this->damage = damage;
}

Bullet::~Bullet() = default;

FloatRect Bullet::getBounds() const {
    return this->shape.getGlobalBounds();
}

int Bullet::getDamage() const {
    return this->damage;
}

void Bullet::update() {
    ///movement
    this->shape.move(this->movementSpeed * direction);
}

void Bullet::render(RenderTarget *target) {
    target->draw(this->shape);
}
