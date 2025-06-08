#include "Projectile.h"
#include "Enemy.h"
#include <cmath>

Projectile::Projectile(SDL_FPoint start, Enemy* target, float speed, int damage)
    : m_pos(start), m_speed(speed), m_damage(damage), m_target(target)
{}

void Projectile::update(float dt) {
    if (m_dead || !m_target || m_target->isDead() || m_target->reachedGoal()) {
        m_dead = true;
        return;
    }
    SDL_FPoint targetPos = m_target->pos();
    float dx = targetPos.x - m_pos.x;
    float dy = targetPos.y - m_pos.y;
    float len = std::sqrt(dx*dx + dy*dy);
    if (len < 10.0f) { // 10px радиус попадания
        m_dead = true;
        m_target->takeDamage(m_damage);
        return;
    }
    m_pos.x += (dx/len) * m_speed * dt;
    m_pos.y += (dy/len) * m_speed * dt;
}
void Projectile::render(SDL_Renderer* renderer) const {
    SDL_SetRenderDrawColor(renderer, 90, 180, 255, 255);
    SDL_FRect rect{ m_pos.x - 4.f, m_pos.y - 4.f, 8.f, 8.f };
    SDL_RenderFillRect(renderer, &rect);
}
