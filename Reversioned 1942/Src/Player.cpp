#include "Player.h"

#include <iostream>

#include "raymath.h"

#include "Parallax.h"


using namespace std;


namespace PlayerUtilities
{
    static const float textureWidth = 100.0f;
    static const float textureHeight = 150.0f;
    static const float explosionTextureWidth = 150.0f;
    static const float explosionTextureHeight = 150.0f;
    static const float turretWidth = 25.0f;
    static const float turretHeight = 63.0f;

	void LoadPlayer(Player& player)
	{
        player.texture = LoadTexture("Assets/Images/ship.png");
        player.explosionTexture = LoadTexture("Assets/Images/shipExplosion.png");
        player.turretTexture = LoadTexture("Assets/Images/turret.png");
        player.position.x = screenCenter.x - player.texture.width / 2;
        player.position.y = static_cast<float>(screenHeight - player.texture.height);
        player.radius = textureWidth / 2.0f;
        player.width = textureWidth;
        player.height = textureHeight;
        player.source = { 0, 0, player.width, player.height };
        player.explosionSource = { 0, 0, explosionTextureWidth, explosionTextureHeight };
        player.turretSource = { 0, 0, turretWidth, turretHeight };
        player.totalPoints = 0;
        player.availableLives = 3;
        player.frame = 0;
        player.explosionFrame = 0;
        player.turretFrame = 0;
        player.lastFrame = 0.0f;
        player.lastTurretFrame = 0.0f;
        
        player.shoot = LoadSound("Assets/Sounds/shoot.wav");
        player.thousand = LoadSound("Assets/Sounds/crash.wav");

        for (int i = 0; i < maxBulletsQnty; i++)
        {
            player.bullets[i].texture = LoadTexture("Assets/Images/bullet.png");
            player.bullets[i].isAlive = false;
            player.bullets[i].radius = player.bullets[i].texture.height / 2.0f;
            player.bullets[i].source = { 0, 0, static_cast<float>(player.bullets[i].texture.width), static_cast<float>(player.bullets[i].texture.height) };
        }
	}

    static void Shoot(Player& player)
    {
        const float turretLength = 40.0f;

        for (int i = 0; i < maxBulletsQnty; i++)
        {
            if (!player.bullets[i].isAlive)
            {
                float angle = (player.rotation - 90.0f) * (PI / 180.0f);

                float x = player.GetCenter().x + turretLength * cos(angle);
                float y = player.GetCenter().y + turretLength * sin(angle);

                player.bullets[i].position.x = x;
                player.bullets[i].position.y = y;
                player.bullets[i].rotation = player.rotation;
                player.bullets[i].isAlive = true;

                player.bullets[i].direction = Vector2Subtract(GetMousePosition(), player.bullets[i].position);
                float length = Vector2Length(player.bullets[i].direction);

                player.bullets[i].direction = Vector2Divide(player.bullets[i].direction, { length, length });

                PlaySound(player.shoot);

                break;
            }
        }
    }

    static void MovePlayer(Player& player)
    {
        player.position.x += player.velocity.x * GetFrameTime();
        player.position.y += player.velocity.y * GetFrameTime();

        if (player.position.x > screenWidth - player.width)
        {
            player.position.x = static_cast<float>(screenWidth - player.width);
        }
        else if (player.position.x < 0.0f)
        {
            player.position.x = 0.0f;
        }
        else if (player.position.y > screenHeight - player.texture.height)
        {
            player.position.y = static_cast<float>(screenHeight - player.texture.height);
        }
        else if (player.position.y < 0.0f)
        {
            player.position.y = 0.0f;
        }
    }

	void GetPlayerInput(Player& player, GameSceen& currentSceen)
	{
        SetExitKey(KEY_Q);

        double y = static_cast<double>(GetMousePosition().y - static_cast<double>(player.height / 2.0f)) - player.position.y;
        double x = static_cast<double>(GetMousePosition().x - static_cast<double>(player.width / 2.0f)) - player.position.x;

        player.rotation = static_cast<float>(atan2(y, x)) * RAD2DEG + 90.0f;

        if (IsKeyDown(KEY_UP))
        {
            player.velocity.y = (- player.maxSpeed);
            player.isSpeeding = true;
        }
        else if (IsKeyDown(KEY_DOWN))
        {
            player.velocity.y = (player.maxSpeed);
            player.isSpeeding = true;
        }
        else
        {
            player.velocity.y = 0.0f;
        }

        if (IsKeyDown(KEY_LEFT))
        {
            player.velocity.x = (-player.maxSpeed);
            player.isSpeeding = true;
        }
        else if (IsKeyDown(KEY_RIGHT))
        {
            player.velocity.x = (player.maxSpeed);
            player.isSpeeding = true;
        }
        else
        {
            player.velocity.x = 0.0f;
        }

        if (player.velocity.x == 0 && player.velocity.y == 0)
        {
            player.isSpeeding = false;
        }

    
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            Shoot(player);
            player.isShooting = true;
        }

        double elapsedTime = GetTime() - pauseTimer;

        if (IsKeyDown(KEY_ESCAPE) && elapsedTime > pauseDelay)
        {
            currentSceen = GameSceen::PAUSE;
        }
	}

	void UpdatePlayer(Player& player)
	{
        if (player.totalPoints >= player.thousandCouner + 1000)
        {
            PlaySound(player.thousand);

            player.thousandCouner += 1000;

            spawnRateHardnes -= 0.1f;
            enemySpeedHardnes += 60.0f;

            for (int i = 0; i < ParallaxUtilities::layersQnty; i++)
            {
                ParallaxUtilities::layers[i].speed *= 1.4f;
            }

            if (spawnRateHardnes < 0.2f)
            {
                spawnRateHardnes = 0.2f;
            }

            if (enemySpeedHardnes > 2000.0f)
            {
                enemySpeedHardnes = 2000.0f;
            }
        }

        MovePlayer(player);

        for (int i = 0; i < maxBulletsQnty; i++)
        {
            BulletUtilities::MoveBullet(player.bullets[i]);
        }
	}

   static  void DrawTurret(Player& player)
    {
        const float rotationCenterX = 12.5f;
        const float rotationCenterY = turretHeight - 12.5f;

        Vector2 origin = { rotationCenterX, rotationCenterY };
        Rectangle dest = { player.GetCenter().x, player.GetCenter().y, turretWidth, turretHeight };

        if (player.isShooting)
        {
            switch (player.turretFrame)
            {
            case 0:
            {
                player.turretSource = { turretWidth, 0, turretWidth, turretHeight };
                break;
            }
            case 1:
            {
                player.turretSource = { turretWidth * 2, 0, turretWidth, turretHeight };
                break;
            }
            case 2:
            {
                player.turretSource = { turretWidth * 3, 0, turretWidth, turretHeight };
                break;
            }
            case 3:
            {
                player.turretSource = { turretWidth * 4, 0, turretWidth, turretHeight };
                break;
            }
            }

            double elapsedTime = GetTime() - player.lastTurretFrame;

            if (elapsedTime > 0.07f)
            {
                player.turretFrame++;

                player.lastTurretFrame = GetTime();

                if (player.turretFrame > 3)
                {
                    player.turretFrame = 0;
                    player.isShooting = false;
                }
            }
        }
        else
        {   
            player.turretSource = { 0, 0, turretWidth, turretHeight };
        }
        
        DrawTexturePro(player.turretTexture, player.turretSource, dest, origin, player.rotation, RAYWHITE);
    }

	void DrawPlayer(Player& player)
	{
        const float rotationCenterX = 50.0f;
        const float rotationCenterY = 50.0f;
        Vector2 origin = { rotationCenterX, rotationCenterY };

        if (player.isSpeeding)
        {
            Rectangle dest = { player.GetCenter().x, player.GetCenter().y, player.width, player.height };

            switch (player.frame)
            {
            case 0:
            {
                player.source = { player.width, 0, player.width, player.height };
                DrawTexturePro(player.texture, player.source, dest, origin, 0.0f, RAYWHITE);
                break;
            }
            case 1:
            {
                player.source = { player.width * 2, 0, player.width, player.height };
                DrawTexturePro(player.texture, player.source, dest, origin, 0.0f, RAYWHITE);
                break;
            }
            case 2:
            {
                player.source = { player.width * 3, 0, player.width, player.height };
                DrawTexturePro(player.texture, player.source, dest, origin, 0.0f, RAYWHITE);
                break;
            }
            case 3:
            {
                player.source = { player.width * 4, 0, player.width, player.height };
                DrawTexturePro(player.texture, player.source, dest, origin, 0.0f, RAYWHITE);
                break;
            }
            }

            double elapsedTime = GetTime() - player.lastFrame;

            if (elapsedTime > 0.07f)
            {
                player.frame++;

                player.lastFrame = GetTime();

                if (player.frame > 3)
                {
                    player.frame = 0;
                }
            }
        }
        else if (!player.isColliding)
        {
            Rectangle dest = { player.GetCenter().x, player.GetCenter().y, player.width, player.height };
            player.source = { 0, 0, player.width, player.height };

            DrawTexturePro(player.texture, player.source, dest, origin, 0.0f, RAYWHITE);
        }

        for (int i = 0; i < maxBulletsQnty; i++)
        {
            BulletUtilities::DrawBullet(player.bullets[i]);
        }

        DrawTurret(player);
	}

    bool ShowExplosion(Player& player)
    {
        const float rotationCenterX = explosionTextureWidth / 2.0f;
        const float rotationCenterY = explosionTextureHeight / 2.0f;

        float centerX = player.position.x + explosionTextureWidth / 2.0f;
        float centerY = player.position.y + explosionTextureHeight / 2.0f;

        Vector2 origin = { rotationCenterX, rotationCenterY };
        Rectangle dest = { centerX, centerY, explosionTextureWidth, explosionTextureHeight };

        switch (player.explosionFrame)
        {
            case 0:
            {
                player.source = { 0, 0, explosionTextureWidth, explosionTextureHeight };
                DrawTexturePro(player.explosionTexture, player.source, dest, origin, 0.0f, RAYWHITE);
                break;
            }
            case 1:
            {
                player.source = { explosionTextureWidth, 0, explosionTextureWidth, explosionTextureHeight };
                DrawTexturePro(player.explosionTexture, player.source, dest, origin, 0.0f, RAYWHITE);
                break;
            }
            case 2:
            {
                player.source = { explosionTextureWidth * 2, 0, explosionTextureWidth, explosionTextureHeight };
                DrawTexturePro(player.explosionTexture, player.source, dest, origin, 0.0f, RAYWHITE);
                break;
            }
            case 3:
            {
                player.source = { explosionTextureWidth * 3, 0, explosionTextureWidth, explosionTextureHeight };
                DrawTexturePro(player.explosionTexture, player.source, dest, origin, 0.0f, RAYWHITE);
                break;
            }
            case 4:
            {
                player.source = { explosionTextureWidth * 4, 0, explosionTextureWidth, explosionTextureHeight };
                DrawTexturePro(player.explosionTexture, player.source, dest, origin, 0.0f, RAYWHITE);
                break;
            }
            case 5:
            {
                player.source = { explosionTextureWidth * 5, 0, explosionTextureWidth, explosionTextureHeight };
                DrawTexturePro(player.explosionTexture, player.source, dest, origin, 0.0f, RAYWHITE);
                break;
            }
            case 6:
            {
                player.source = { explosionTextureWidth * 6, 0, explosionTextureWidth, explosionTextureHeight };
                DrawTexturePro(player.explosionTexture, player.source, dest, origin, 0.0f, RAYWHITE);
                break;
            }
            case 7:
            {
                player.source = { explosionTextureWidth * 7, 0, explosionTextureWidth, explosionTextureHeight };
                DrawTexturePro(player.explosionTexture, player.source, dest, origin, 0.0f, RAYWHITE);
                break;
            }
        }

        double elapsedTime = GetTime() - player.lastFrame;

        if (elapsedTime > 0.09f)
        {
            player.explosionFrame++;
            player.lastFrame = GetTime();
        }

        if (player.explosionFrame > 7)
        {
            player.isColliding = false;
            
            return true;
        }

        return false;
    }

    void UnloadPlayerTextures(Player& player)
    {
        for (int i = 0; i < maxBulletsQnty; i++)
        {
            UnloadTexture(player.bullets[i].texture);
        }

        UnloadTexture(player.texture);
        UnloadTexture(player.explosionTexture);
    }
}