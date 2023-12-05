#include "Player.h"

#include <iostream>

#include "raymath.h"


using namespace std;


namespace PlayerUtilities
{
	void LoadPlayer(Player& player)
	{
        player.texture = LoadTexture("Assets/Images/ship.png");
        player.position.x = screenCenter.x - player.texture.width / 2;
        player.position.y = screenCenter.y - player.texture.height / 2;
        player.radius = player.texture.width / 2.0f;
        player.source = { 0, 0, static_cast<float>(player.texture.width), static_cast<float>(player.texture.height) };
        player.totalPoints = 0;
        player.availableLives = 3;
        player.speed = 500.0f;

        player.shoot = LoadSound("Assets/Sounds/shoot.wav");
        player.thousand = LoadSound("Assets/Sounds/crash.wav");


        for (int i = 0; i < maxBulletsQnty; i++)
        {
            player.bullets[i].texture = LoadTexture("Assets/Images/bullet.png");
            player.bullets[i].isAlive = false;
            player.bullets[i].radius = player.bullets[i].texture.width / 2.0f;
            player.bullets[i].source = { 0, 0, static_cast<float>(player.bullets[i].texture.width), static_cast<float>(player.bullets[i].texture.height) };
        }
	}

    static void Shoot(Player& player)
    {
        for (int i = 0; i < maxBulletsQnty; i++)
        {
            if (!player.bullets[i].isAlive)
            {
                player.bullets[i].position = player.GetCenter();
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

        if (player.position.x > screenWidth - player.texture.width)
        {
            player.position.x = static_cast<float>(screenWidth - player.texture.width);
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
        double y = static_cast<double>(GetMousePosition().y - static_cast<double>(player.texture.height / 2.0f)) - player.position.y;
        double x = static_cast<double>(GetMousePosition().x - static_cast<double>(player.texture.width / 2.0f)) - player.position.x;

        player.rotation = static_cast<float>(atan2(y, x)) * RAD2DEG + 90.0f;

        if (IsKeyDown(KEY_UP))
        {
            player.velocity.y = (- player.maxSpeed);
            cout << "velociti Y: " << player.velocity.y << endl;
            cout << "speed: " << player.maxSpeed << endl;
        }
        else if (IsKeyDown(KEY_DOWN))
        {
            player.velocity.y = (player.maxSpeed);
            cout << "velociti Y: " << player.velocity.y << endl;
        }
        else
        {
            player.velocity.y = 0.0f;
        }

        if (IsKeyDown(KEY_LEFT))
        {
            player.velocity.x = (-player.maxSpeed);
            cout << "velociti X: " << player.velocity.x << endl;
        }
        else if (IsKeyDown(KEY_RIGHT))
        {
            player.velocity.x = (player.maxSpeed);
            cout << "velociti X: " << player.velocity.x << endl;
        }
        else
        {
            player.velocity.x = 0.0f;
        }

        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            Shoot(player);
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
        }

        MovePlayer(player);

        for (int i = 0; i < maxBulletsQnty; i++)
        {
            BulletUtilities::MoveBullet(player.bullets[i]);
        }
	}

	void DrawPlayer(Player& player)
	{
        Rectangle dest = { player.GetCenter().x, player.GetCenter().y, static_cast<float>(player.texture.width), static_cast<float>(player.texture.height) };
        Vector2 origin = { static_cast<float>(player.texture.width / 2), static_cast<float>(player.texture.height / 2) };

        DrawTexturePro(player.texture, player.source, dest, origin, player.rotation + 90.0f, RAYWHITE);

        for (int i = 0; i < maxBulletsQnty; i++)
        {
            BulletUtilities::DrawBullet(player.bullets[i]);
        }
	}
}