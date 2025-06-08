#include "Enemy.h"
#include <cmath>

Enemy::Enemy(const std::vector<SDL_FPoint>& waypoints, float speed, int hp)
    : m_waypoints(&waypoints), m_speed(speed), m_hp(hp), m_maxHp(hp)
{
    m_pos = waypoints.front();
}

void Enemy::update(float dt) {
    if (m_reachedGoal || !m_waypoints) return;
    if (m_nextWaypoint >= m_waypoints->size()) {
        m_reachedGoal = true;
        return;
    }

    const SDL_FPoint& target = (*m_waypoints)[m_nextWaypoint];
    float d2 = distance2(m_pos, target);
    if (d2 < 2.0f) {
        ++m_nextWaypoint;
        if (m_nextWaypoint >= m_waypoints->size()) {
            m_reachedGoal = true;
            return;
        }
    }
    else {
        float dx = target.x - m_pos.x;
        float dy = target.y - m_pos.y;
        float len = std::sqrt(dx*dx + dy*dy);
        if (len > 0.01f) {
            m_pos.x += (dx / len) * m_speed * dt;
            m_pos.y += (dy / len) * m_speed * dt;
        }
    }
}

void Enemy::render(SDL_Renderer* renderer) const {
    SDL_SetRenderDrawColor(renderer, 220, 60, 60, 255);
    SDL_FRect rect{ m_pos.x - 8.f, m_pos.y - 8.f, 16.f, 16.f };
    SDL_RenderFillRect(renderer, &rect);
}

bool Enemy::reachedGoal() const {
    return m_reachedGoal;
}

bool Enemy::takeDamage(int dmg) {
    m_hp -= dmg;
    return m_hp <= 0;
}

float Enemy::distance2(const SDL_FPoint& a, const SDL_FPoint& b) {
    float dx = a.x - b.x, dy = a.y - b.y;
    return dx * dx + dy * dy;
}
