cmake_minimum_required(VERSION 3.15)
project(TowerDefenceSDL3 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ─── исполняемый файл ────────────────────────────────────────────────────────
add_executable(${PROJECT_NAME}
    src/main.cpp
    src/Game.cpp
    src/Map.cpp
    src/Enemy.cpp
    src/Tower.cpp
    src/Projectile.cpp
)

# ─── пути к SDL3 (ТОЛЬКО две переменные) ─────────────────────────────────────
set(SDL3_ROOT   "${CMAKE_SOURCE_DIR}/SDL3")          # корень SDL3
set(SDL3_INCLUDES "${SDL3_ROOT}/include")            # .../include

# ─── заголовки ───────────────────────────────────────────────────────────────
target_include_directories(${PROJECT_NAME} PRIVATE
    ${SDL3_INCLUDES}          # => -IC:/TowerDefenceSDL3/SDL3/include
)

# ─── библиотеки и линковка ───────────────────────────────────────────────────
# в MinGW-архиве libSDL3.dll.a лежит прямо в SDL3/lib
target_link_directories(${PROJECT_NAME} PRIVATE
    ${SDL3_ROOT}/lib
)
target_link_libraries(${PROJECT_NAME} PRIVATE SDL3)   # => -lSDL3

# ─── копируем DLL из bin/ (у mingw именно там) ───────────────────────────────
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${SDL3_ROOT}/bin/SDL3.dll"
            "$<TARGET_FILE_DIR:${PROJECT_NAME}>"
    COMMENT "Копирую SDL3.dll рядом с exe"
)
