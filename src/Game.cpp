#include "Game.h"
#include "Enemy.h"
#include <algorithm>
#include <cstdio> // for snprintf

Game::Game() {
    SDL_Init(SDL_INIT_VIDEO);
    m_window = SDL_CreateWindow("Tower Defence SDL3", Map::WIDTH * Map::TILE_SIZE, Map::HEIGHT * Map::TILE_SIZE, 0);
    m_renderer = SDL_CreateRenderer(m_window, nullptr);
}

Game::~Game() {
    SDL_DestroyRenderer(m_renderer);
    SDL_DestroyWindow(m_window);
    SDL_Quit();
}

void Game::run() {
    bool running = true;
    uint64_t prev = SDL_GetTicks();

    while (running) {
        handleEvents(running);

        uint64_t now = SDL_GetTicks();
        float dt = (now - prev) / 1000.0f;
        prev = now;

        update(dt, running);
        render();
        SDL_Delay(2);
    }
}

void Game::handleEvents(bool& running) {
    SDL_Event e;
    while (SDL_PollEvent(&e)) {
        if (e.type == SDL_EVENT_QUIT)
            running = false;
        else if (e.type == SDL_EVENT_MOUSE_BUTTON_UP && e.button.button == SDL_BUTTON_LEFT)
            tryPlaceTower(e.button.x, e.button.y);
    }
}

void Game::update(float dt, bool& running) {
    // === Спавн врагов ===
    m_spawnTimer += dt;
    if (m_spawnTimer >= m_spawnPeriod) {
        m_spawnTimer = 0.f;
        m_enemies.emplace_back(m_map.waypoints(), 60.0f, 20); // скорость, HP
    }

    // === Апдейт врагов ===
    for (auto& en : m_enemies)
        en.update(dt);

    // === Башни стреляют по ближайшему врагу ===
    for (auto& tower : m_towers) {
        if (tower.timer() > 0)
            tower.timer() -= dt;
        if (tower.timer() > 0)
            continue;

        Enemy* target = nullptr;
        float bestDist2 = tower.range() * tower.range();
        SDL_FPoint tcenter = tower.center();

        for (auto& en : m_enemies) {
            if (en.isDead() || en.reachedGoal()) continue;
            float dx = en.pos().x - tcenter.x;
            float dy = en.pos().y - tcenter.y;
            float dist2 = dx*dx + dy*dy;
            if (dist2 < bestDist2) {
                bestDist2 = dist2;
                target = &en;
            }
        }
        if (target) {
            m_projectiles.emplace_back(tcenter, target, 350.f, 10);
            tower.timer() = tower.cooldown();
        }
    }

    // === Апдейт снарядов ===
    for (auto& proj : m_projectiles)
        proj.update(dt);

    m_projectiles.erase(
        std::remove_if(m_projectiles.begin(), m_projectiles.end(),
            [](const Projectile& p) { return p.isDead(); }),
        m_projectiles.end()
    );

    // === Удаляем погибших врагов, даём золото и счет ===
    m_enemies.erase(
        std::remove_if(m_enemies.begin(), m_enemies.end(),
            [this](const Enemy& e) {
                if (e.isDead()) {
                    m_gold += 10;
                    m_score += 1;
                    return true;
                }
                if (e.reachedGoal()) {
                    --m_castleHP;
                    return true;
                }
                return false;
            }),
        m_enemies.end()
    );

    if (m_castleHP <= 0)
        running = false;
}

void Game::render() const {
    SDL_SetRenderDrawColor(m_renderer, 0, 30, 60, 255);
    SDL_RenderClear(m_renderer);

    // --- HUD в заголовке окна ---
    char buf[128];
    snprintf(buf, sizeof(buf), "HP: %d   Gold: %d   Score: %d", m_castleHP, m_gold, m_score);
    SDL_SetWindowTitle(m_window, buf);

    m_map.render(m_renderer);

    for (const auto& t : m_towers)
        t.render(m_renderer);
    for (const auto& e : m_enemies)
        e.render(m_renderer);
    for (const auto& p : m_projectiles)
        p.render(m_renderer);

    // --- HP бар над врагом ---
    for (const auto& e : m_enemies) {
        SDL_FRect hpbar{
            e.pos().x - 12.f,
            e.pos().y - 16.f,
            24.f * (float)e.hp() / (float)e.maxHp(),
            3.f
        };
        SDL_SetRenderDrawColor(m_renderer, 50, 230, 50, 255);
        SDL_RenderFillRect(m_renderer, &hpbar);

        SDL_FRect hpback{ e.pos().x - 12.f, e.pos().y - 16.f, 24.f, 3.f };
        SDL_SetRenderDrawColor(m_renderer, 70, 70, 70, 255);
        SDL_RenderRect(m_renderer, &hpback);
    }

    SDL_RenderPresent(m_renderer);
}

void Game::tryPlaceTower(int mouseX, int mouseY) {
    int x = mouseX / Map::TILE_SIZE;
    int y = mouseY / Map::TILE_SIZE;
    if (!m_map.isInside(x, y)) return;

    if (m_map.tileAt(x, y) != TileType::TowerSpot)
        return;

    auto it = std::find_if(m_towers.begin(), m_towers.end(),
        [x, y](const Tower& t) { return t.x() == x && t.y() == y; });
    if (it != m_towers.end())
        return;

    m_towers.emplace_back(x, y);
}
