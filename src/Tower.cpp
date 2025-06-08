#include "Tower.h"

Tower::Tower(int x, int y) : m_x(x), m_y(y) {}

void Tower::render(SDL_Renderer* renderer) const {
    SDL_SetRenderDrawColor(renderer, 139, 69, 19, 255);
    SDL_FRect rect{
        static_cast<float>(m_x * Map::TILE_SIZE + 4),
        static_cast<float>(m_y * Map::TILE_SIZE + 4),
        static_cast<float>(Map::TILE_SIZE - 8),
        static_cast<float>(Map::TILE_SIZE - 8)
    };
    SDL_RenderFillRect(renderer, &rect);
}

SDL_FPoint Tower::center() const {
    return {
        m_x * Map::TILE_SIZE + Map::TILE_SIZE / 2.0f,
        m_y * Map::TILE_SIZE + Map::TILE_SIZE / 2.0f
    };
}
