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

    Vector2 GetCenter()
    {
        return { position.x + (texture.width / 2), position.y + (texture.height / 2) };
    }
};

namespace BulletUtilities
{
    extern void MoveBullet(Bullet& bullet);

    extern void DrawBullet(Bullet bullet);
}