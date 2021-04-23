#include "Game.h"

///private functions
void Game::initWindow() {
    this->window = new RenderWindow(VideoMode(1000, 800), "Space Shooter", Style::Default);
    this->window->setFramerateLimit(60);
    this->window->setVerticalSyncEnabled(false);
    Image icon;
    if (!icon.loadFromFile("Textures/icon.png")) {
        cout << "ERROR::GAME::INITWINDOW::Could not load from file!!!";
    }
    this->window->setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
}

void Game::initTextures() {
    this->textures["BULLET"] = new Texture;
    this->textures["BULLET"]->loadFromFile("Textures/bullet.png");
}

void Game::initGui() {
    if (!this->font.loadFromFile("Fonts/font1.ttf"))cout << "ERROR::GAME::INITGUI::Could not load from file!!!";

    this->text.setFont(this->font);
    this->text.setCharacterSize(this->window->getSize().y / 25);
    this->text.setFillColor(Color::White);

    this->gameOverText.setFont(this->font);
    this->gameOverText.setCharacterSize(this->window->getSize().y / 10);
    this->gameOverText.setFillColor(Color::Red);
    this->gameOverText.setString("GAME OVER!!!");
    this->gameOverText.setPosition(
            float(this->window->getSize().x) / 2 - this->gameOverText.getGlobalBounds().width / 2,
            float(this->window->getSize().y) / 2 - this->gameOverText.getGlobalBounds().height / 2);

    this->playerHpBar.setSize(Vector2f(float(this->window->getSize().x) / 4, 25.f));
    this->playerHpBar.setFillColor(Color::Red);
    this->playerHpBar.setPosition(Vector2f(10.f, 10.f));

    this->playerHpBarBack = this->playerHpBar;
    this->playerHpBarBack.setFillColor(Color(25, 25, 25, 200));
}

void Game::initWorld() {
    if (!this->background.loadFromFile("Textures/bac.jpg")) cout << "ERROR::GAME::COULD NOT LOAD TEXTURE!!!\n";
    this->worldBackground.setTexture(this->background);
}

void Game::initSystems() {
    this->points = 0;
}

void Game::initPlayer() {
    this->player = new Player;
    this->player->setPosition(Vector2f(float(this->window->getSize().x) / 2 - this->player->getSize().x,
                                       float(this->window->getSize().y) / 2 - this->player->getSize().y));
}

void Game::initEnemies() {
    this->spawnTimerMax = 10.f;
    this->spawnTimer = this->spawnTimerMax;
}

///con/des
Game::Game() {
    this->initWindow();
    this->initWorld();
    this->initTextures();
    this->initGui();
    this->initSystems();
    this->initPlayer();
    this->initEnemies();

}

Game::~Game() {
    delete this->window;
    delete this->player;
    for (auto &i: this->textures)
        delete i.second;
    for (auto *i: this->bullets)
        delete i;
    for (auto *i: this->enemies)
        delete i;
}

///functions
void Game::run() {
    while (this->window->isOpen()) {
        this->updatePollEvents();
        if (this->player->getHP() > 0)
            this->update();

        this->render();
    }
}

void Game::updatePollEvents() {
    Event event{};
    while (this->window->pollEvent(event)) {
        if (event.Event::type == Event::Closed)
            this->window->close();
        if (event.Event::key.code == Keyboard::Escape)
            this->window->close();
    }
}

void Game::updateInput() {
    ///move player
    ///left
    if (Keyboard::isKeyPressed(Keyboard::A)) {
        this->player->move(-1.f, 0.f);
    }
    ///right
    if (Keyboard::isKeyPressed(Keyboard::D)) {
        this->player->move(1.f, 0.f);
    }
    ///up
    if (Keyboard::isKeyPressed(Keyboard::W)) {
        this->player->move(0.f, -1.f);
    }
    ///down
    if (Keyboard::isKeyPressed(Keyboard::S)) {
        this->player->move(0.f, 1.f);
    }

    if (Mouse::isButtonPressed(sf::Mouse::Left) and this->player->canAttack()) {
        this->bullets.push_back(
                new Bullet(this->textures["BULLET"], this->player->getPos().x + this->player->getBounds().width / 2,
                           this->player->getPos().y, 0.f, -1.f, 5.f, 5));
    }
}

void Game::updateGui() {
    stringstream ss;
    ss << "Points: " << this->points << endl;
    this->text.setString(ss.str());
    this->text.setPosition(Vector2f(this->window->getSize().x - 200.f, 10.f));

    float hpPercent = float(this->player->getHP()) / float(this->player->getHPMax());
    this->playerHpBar.setSize(
            Vector2f(float(this->window->getSize().x) / 4 * hpPercent, this->playerHpBar.getSize().y));

}

void Game::updateCollision() {
    if (this->player->getBounds().left < 0.f)
        this->player->setPosition(0.f, this->player->getBounds().top);

    else if (this->player->getBounds().left + this->player->getBounds().width >= this->window->getSize().x)
        this->player->setPosition(this->window->getSize().x - this->player->getBounds().width,
                                  this->player->getBounds().top);

    if (this->player->getBounds().top < 0.f)
        this->player->setPosition(this->player->getBounds().left, 0.f);

    else if (this->player->getBounds().top + this->player->getBounds().height >= this->window->getSize().y)
        this->player->setPosition(this->player->getBounds().left,
                                  this->window->getSize().y - this->player->getBounds().height);
}

void Game::updateBullets() {
    unsigned counter = 0;

    for (auto *bullet : this->bullets) {
        bullet->update();
        if (bullet->getBounds().top + bullet->getBounds().height < 0.f) {
            delete this->bullets.at(counter);
            this->bullets.erase(this->bullets.begin() + counter);
            --counter;
        }
        ++counter;
    }
}

void Game::updateEnemies() {
    this->spawnTimer += 0.5f;
    if (this->spawnTimer >= this->spawnTimerMax) {
        this->enemies.push_back(new Enemy(rand() % this->window->getSize().x - 50.f, -100.f));
        this->spawnTimer = 0.f;
    }

    unsigned counter = 0;

    for (auto *enemy : this->enemies) {
        enemy->update();
        if (enemy->getBounds().top > this->window->getSize().y) {
            delete this->enemies.at(counter);
            this->enemies.erase(this->enemies.begin() + counter);
            --counter;
        } else if (enemy->getBounds().intersects(this->player->getBounds())) {
            this->player->loseHp(this->enemies.at(counter)->getDamage());
            delete this->enemies.at(counter);
            this->enemies.erase(this->enemies.begin() + counter);
            --counter;
        }
        ++counter;
    }
}

void Game::updateCombat() {
    for (int i = 0; i < enemies.size(); i++) {

        bool enemy_deleted = false;
        for (int j = 0; j < this->bullets.size() and !enemy_deleted; j++) {
            if (this->enemies[i]->getBounds().intersects(this->bullets[j]->getBounds()) and
                this->enemies[i]->getHp() <= 0) {

                this->points += this->enemies[i]->getPoints();
                delete this->enemies[i];
                this->enemies.erase(this->enemies.begin() + i);

                delete this->bullets[j];
                this->bullets.erase(this->bullets.begin() + j);

                enemy_deleted = true;
            } else if (this->enemies[i]->getBounds().intersects(this->bullets[j]->getBounds())) {
                this->enemies[i]->loseHP(bullets[j]->getDamage());
                ///change enemy transparent
                int change_transparent = int(float(this->enemies[i]->getHp()) / float(this->enemies[i]->getHpMax()) * 155) + 100;
                this->enemies[i]->setTransparent(change_transparent);

                delete this->bullets[j];
                this->bullets.erase(this->bullets.begin() + j);
            }
        }
    }
}

void Game::update() {
    updateInput();
    this->updateGui();
    this->player->update();
    this->updateCollision();
    this->updateBullets();
    this->updateCombat();
    this->updateEnemies();
}

void Game::renderWorld() {
    this->window->draw(this->worldBackground);
}

void Game::renderGui() {
    this->window->draw(this->text);
    this->window->draw(this->playerHpBarBack);
    this->window->draw(this->playerHpBar);
}

void Game::render() {
    this->window->clear();

    this->renderWorld();

    if (this->player->getHP() > 0) {
        this->player->render(this->window);

        for (auto *bullet : this->bullets)
            bullet->render(this->window);
        for (auto *e : this->enemies)
            e->render(this->window);
    }
    this->renderGui();

    ///game over
    if (this->player->getHP() <= 0)
        this->window->draw(gameOverText);

    this->window->display();
}
