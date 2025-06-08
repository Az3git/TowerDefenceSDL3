#include "Map.h"

Map::Map() { buildDemo(); }

void Map::buildDemo() {
    for (int y = 0; y < HEIGHT; ++y)
        for (int x = 0; x < WIDTH; ++x)
            m_tiles[y][x] = TileType::Grass;

    for (int y = 0; y < HEIGHT; ++y)
        m_tiles[y][WIDTH / 2] = TileType::Road;

    m_tiles[5][10] = TileType::TowerSpot;
    m_tiles[8][14] = TileType::TowerSpot;
    m_tiles[12][10] = TileType::TowerSpot;
    m_tiles[15][14] = TileType::TowerSpot;

    m_waypoints = {
        { WIDTH / 2 * TILE_SIZE + TILE_SIZE / 2.0f, 0.0f },
        { WIDTH / 2 * TILE_SIZE + TILE_SIZE / 2.0f, HEIGHT * TILE_SIZE * 1.0f }
    };
}

TileType Map::tileAt(int x, int y) const {
    if (!isInside(x, y)) return TileType::Grass;
    return m_tiles[y][x];
}

bool Map::isInside(int x, int y) const {
    return x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT;
}

void Map::render(SDL_Renderer* renderer) const {
    for (int y = 0; y < HEIGHT; ++y) {
        for (int x = 0; x < WIDTH; ++x) {
            SDL_FRect rect{
                static_cast<float>(x * TILE_SIZE),
                static_cast<float>(y * TILE_SIZE),
                static_cast<float>(TILE_SIZE),
                static_cast<float>(TILE_SIZE)
            };
            switch (m_tiles[y][x]) {
            case TileType::Grass:
                SDL_SetRenderDrawColor(renderer, 50, 120, 50, 255);
                break;
            case TileType::Road:
                SDL_SetRenderDrawColor(renderer, 200, 200, 150, 255);
                break;
            case TileType::TowerSpot:
                SDL_SetRenderDrawColor(renderer, 80, 50, 20, 255);
                break;
            }
            SDL_RenderFillRect(renderer, &rect);
        }
    }
}
