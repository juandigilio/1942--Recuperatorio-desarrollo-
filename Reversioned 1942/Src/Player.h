#pragma once

#include "raylib.h"

#include "GameData.h"
#include "Bullet.h"


using namespace GameData;

const int maxBulletsQnty = 30;

struct Player
{
    Vector2 position{};
    Vector2 velocity{};
    Vector2 direction{};
    float speed = {};
    float maxSpeed = 250.0f;
    float rotation = 0.0f;
    float interpolationFactor = 50.0f;
    float targetRotation{};
    float radius{};
    int totalPoints = 0;
    int thousandCouner = 0;
    int availableLives = 3;
    bool isColliding = false;
    float lastCollide = 0.0f;
    bool isAlive = true;
    Texture2D texture{};
    Rectangle source{};
    Sound shoot{};
    Sound thousand{};

    Bullet bullets[maxBulletsQnty]{};

    Vector2 GetCenter()
    {
        return { position.x + (texture.width / 2), position.y + (texture.height / 2) };
    }
};

namespace PlayerUtilities
{
    extern void LoadPlayer(Player& player);

    extern void GetPlayerInput(Player& player, GameSceen& currentSceen);

    extern void UpdatePlayer(Player& player);

    extern void DrawPlayer(Player& player);
}