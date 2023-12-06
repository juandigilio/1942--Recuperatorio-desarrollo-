#pragma once

#include "raylib.h"

#include "GameData.h"
#include "Bullet.h"


using namespace GameData;

static const int maxBulletsQnty = 30;

struct Player
{
    Vector2 position{};
    Vector2 velocity{};
    float targetRotation{};
    float rotation = 0.0f;
    float maxSpeed = 250.0f;

    int availableLives = 3;
    bool isAlive = true;

    Texture2D texture{};
    Rectangle source{};
    Texture2D explosionTexture{};
    Rectangle explosionSource{};
    Texture2D turretTexture{};
    Rectangle turretSource{};
    float radius{};
    float width{};
    float height{};
    int frame{};
    int explosionFrame{};
    int turretFrame{};
    double lastFrame{};
    double lastTurretFrame{};
    bool isSpeeding = false;
    bool isColliding = false;
    bool isShooting = false;
    float lastCollide = 0.0f;

    int totalPoints = 0;
    int thousandCouner = 0;
    Sound thousand{};

    Bullet bullets[maxBulletsQnty]{};
    Sound shoot{};

    Vector2 GetCenter()
    {
        return { position.x + (width / 2), position.y + (width / 2) };
    }
};

namespace PlayerUtilities
{
    extern void LoadPlayer(Player& player);

    extern void GetPlayerInput(Player& player, GameSceen& currentSceen);

    extern void UpdatePlayer(Player& player);

    extern void DrawPlayer(Player& player);

    extern bool ShowExplosion(Player& player);

    extern void UnloadPlayerTextures(Player& player);
}