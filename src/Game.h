#pragma once
#include <SDL3/SDL.h>
#include <vector>
#include "Map.h"
#include "Enemy.h"
#include "Tower.h"
#include "Projectile.h"

class Game {
public:
    Game();
    ~Game();
    void run();

private:
    SDL_Window* m_window = nullptr;
    SDL_Renderer* m_renderer = nullptr;

    Map m_map;
    std::vector<Enemy> m_enemies;
    std::vector<Tower> m_towers;
    std::vector<Projectile> m_projectiles;

    float m_spawnTimer = 0.0f;
    float m_spawnPeriod = 2.0f;
    int m_castleHP = 10;
    int m_gold = 100;
    int m_score = 0;

    void handleEvents(bool& running);
    void update(float dt, bool& running);
    void render() const;
    void tryPlaceTower(int mouseX, int mouseY);
};
