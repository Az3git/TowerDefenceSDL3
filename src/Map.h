#pragma once
#include <SDL3/SDL.h>
#include <vector>

enum class TileType { Grass, Road, TowerSpot };

class Map {
public:
    static constexpr int TILE_SIZE = 32;
    static constexpr int WIDTH = 25;
    static constexpr int HEIGHT = 18;

    Map();
    TileType tileAt(int x, int y) const;
    bool isInside(int x, int y) const;
    void render(SDL_Renderer* renderer) const;
    const std::vector<SDL_FPoint>& waypoints() const { return m_waypoints; }

private:
    TileType m_tiles[HEIGHT][WIDTH]{};
    std::vector<SDL_FPoint> m_waypoints;
    void buildDemo();
};
