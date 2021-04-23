#include "Player.h"

void Player::initVariables() {
    this->movementSpeed = 7.5f;
    this->attackCoolDownMax = 5.f;
    this->attackCoolDown = this->attackCoolDownMax;
    this->hpMax = 100;
    this->hp = this->hpMax;
    this->sprite.setPosition(380.f, 500.f);
}

void Player::initTexture() {
    if (!this->texture.loadFromFile("Textures/ship.png"))
        cout << "ERROR::PLAYER::TEXTURE LOADING FAIL!!!" << endl;
}

void Player::initSprite() {
    this->sprite.setTexture(this->texture);
    ///resize
    this->sprite.scale(0.1f, 0.1f);
}

Player::Player() {
    this->initVariables();
    this->initTexture();
    this->initSprite();

}

Player::~Player() = default;

Vector2f Player::getPos() const {
    return this->sprite.getPosition();
}

FloatRect Player::getBounds() {
    return this->sprite.getGlobalBounds();
}

int Player::getHP() const {
    return this->hp;
}

int Player::getHPMax() const {
    return this->hpMax;
}

Vector2f Player::getSize() const {
    return this->sprite.getOrigin();
}

void Player::setPosition(const Vector2f pos) {
    this->sprite.setPosition(pos);
}

void Player::setPosition(const float x, const float y) {
    this->sprite.setPosition(x, y);
}

void Player::setHP(int HP) {
    this->hp = HP;
}

void Player::loseHp(int value) {
    this->hp -= value;
    if (this->hp < 0)
        this->hp = 0;
}

void Player::move(const float x, const float y) {
    this->sprite.move(this->movementSpeed * x, this->movementSpeed * y);
}

bool Player::canAttack() const {
    if (this->attackCoolDown >= this->attackCoolDownMax)
        return true;
    return false;
}

void Player::updateAttack() {
    if (this->attackCoolDown >= this->attackCoolDownMax)
        this->attackCoolDown = 0.f;
    if (this->attackCoolDown < this->attackCoolDownMax)
        this->attackCoolDown += 2.f;
}

void Player::update() {
    this->updateAttack();
}

void Player::render(RenderTarget *target) {
    target->draw(this->sprite);
}