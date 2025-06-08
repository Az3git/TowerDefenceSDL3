#pragma once
#include <SDL3/SDL.h>
#include "Map.h"

class Tower {
public:
    Tower(int x, int y);
    void render(SDL_Renderer* renderer) const;
    int x() const { return m_x; }
    int y() const { return m_y; }
    SDL_FPoint center() const;
    float range() const { return m_range; }
    float cooldown() const { return m_cooldown; }
    float& timer() { return m_timer; }

private:
    int m_x, m_y;
    float m_range = 100.f;
    float m_cooldown = 1.0f;
    float m_timer = 0.0f;
};
