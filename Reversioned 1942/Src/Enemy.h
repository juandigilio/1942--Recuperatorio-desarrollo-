#pragma once

#include "raylib.h"
#include <vector>


using namespace std;

struct Enemy
{
    Vector2 position{};
    Vector2 velocity{};
    Vector2 direction{};
    float speed = 200.0f;
    float rotation = 0.0f;
    float interpolationFactor = 2.0f;
    float targetRotation{};
    float radius{};
    Texture2D texture{};
    Rectangle source{};

    Vector2 GetCenter()
    {
        return { position.x + (texture.width / 2), position.y + (texture.height / 2) };
    }
};

namespace EnemyUtilities
{
    extern void DeleteEnemies(vector<Enemy> enemies);
}