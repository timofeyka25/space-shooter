#pragma once

#include "Player.h"
#include "Enemy.h"
#include "Bullet.h"
#include <map>

class Game {
private:
    RenderWindow *window;

    ///resources
    map<string, Texture *> textures;
    vector<Bullet *> bullets;

    Player *player;

    RectangleShape playerHpBar;
    RectangleShape playerHpBarBack;


    float spawnTimer;
    float spawnTimerMax;
    vector<Enemy *> enemies;

    Font font;
    Text text;

    Text gameOverText;

    Texture background;
    Sprite worldBackground;


    unsigned points;

    ///private functions
    void initWindow();

    void initTextures();

    void initGui();

    void initWorld();

    void initSystems();

    void initPlayer();

    void initEnemies();


public:
    Game();

    virtual ~Game();

    ///functions

    void run();

    void updatePollEvents();

    void updateInput();

    void updateGui();

    void updateCollision();

    void updateBullets();

    void updateEnemies();

    void updateCombat();

    void update();

    void renderWorld();

    void renderGui();

    void render();

};