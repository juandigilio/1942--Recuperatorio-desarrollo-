#pragma once

#include "raylib.h"
#include <vector>


using namespace std;

struct Enemy
{
    Vector2 position{};
    Vector2 velocity{};
    Vector2 direction{};
    float speedY{};
    float rotation{};
    float rotationSpeed{};
    float targetRotation{};
    float radius{};
    Texture2D texture{};
    Rectangle source{};
    bool isAlive{};
    double lastFrame{};
    int frame{};

    Vector2 GetCenter()
    {
        return { position.x + (radius), position.y + (radius) };
    }
};

namespace EnemyUtilities
{
    extern void UpdateEnemies(vector<Enemy>& enemies);
    extern void DrawEnemies(vector<Enemy>& enemies);
    extern void DeleteEnemies(vector<Enemy>& enemies);
}