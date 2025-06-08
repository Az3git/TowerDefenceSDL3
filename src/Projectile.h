#pragma once
#include <SDL3/SDL.h>
class Enemy;

class Projectile {
public:
    Projectile(SDL_FPoint start, Enemy* target, float speed, int damage);

    void update(float dt);
    void render(SDL_Renderer* renderer) const;
    bool isDead() const { return m_dead; }
    SDL_FPoint pos() const { return m_pos; }
    int damage() const { return m_damage; }
    Enemy* target() const { return m_target; }

private:
    SDL_FPoint m_pos;
    float m_speed;
    int m_damage;
    Enemy* m_target = nullptr;
    bool m_dead = false;
};
