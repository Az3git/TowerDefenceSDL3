#pragma once
#include <SDL3/SDL.h>
#include <vector>

class Enemy {
public:
    Enemy(const std::vector<SDL_FPoint>& waypoints, float speed = 60.0f, int hp = 20);

    void update(float dt);
    void render(SDL_Renderer* renderer) const;
    bool reachedGoal() const;
    bool isDead() const { return m_hp <= 0; }
    bool takeDamage(int dmg);
    SDL_FPoint pos() const { return m_pos; }
    int hp() const { return m_hp; }
    int maxHp() const { return m_maxHp; }

private:
    const std::vector<SDL_FPoint>* m_waypoints = nullptr;
    size_t m_nextWaypoint = 1;
    SDL_FPoint m_pos{};
    float m_speed;
    bool m_reachedGoal = false;
    int m_hp = 20;
    int m_maxHp = 20;

    static float distance2(const SDL_FPoint& a, const SDL_FPoint& b);
};
