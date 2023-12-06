#pragma once

#include "raylib.h"


struct Bullet
{
    Vector2 position{};
    Vector2 velocity{};
    Vector2 direction{};
    float rotation{};
    float radius{};
    float speed = 360.0f;
    bool isAlive = false;
    Texture2D texture{};
    Rectangle source{};
    int frame = 0;
    double lastFrame = 0.0f;

    Vector2 GetCenter()
    {
        return { position.x + radius, position.y + radius };
    }
};

namespace BulletUtilities
{
    extern void MoveBullet(Bullet& bullet);

    extern void DrawBullet(Bullet& bullet);
}