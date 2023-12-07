#include "Enemy.h"

#include <iostream>

#include "GameData.h"


using namespace std;
using namespace GameData;


namespace EnemyUtilities
{
    static double lastDrop = 0.0f;

    static void LoadEnemy(Enemy& enemy)
    {
        enemy.texture = LoadTexture("Assets/Images/enemy.png");

        int spawnPosibilities = screenWidth - (enemy.texture.width / 2);

        enemy.radius = enemy.texture.width / 4.0f;
        enemy.position.x = static_cast<float>(rand() % spawnPosibilities);
        enemy.position.y = enemy.texture.height * -1.0f;

        enemy.velocity = { 0.0f, enemySpeedHardnes };

        enemy.source = { 0.0f, 0.0f, static_cast<float>(enemy.texture.width / 2.0f), static_cast<float>(enemy.texture.height) };
        enemy.rotation = 0.0f;
        enemy.rotationSpeed = 75.0f;
        enemy.frame = 0;
        enemy.lastFrame = 0.0f;

        enemy.isAlive = true;

        lastDrop = GetTime();
    }

    static void MoveEnemies(vector<Enemy>& enemies)
    {
        for (auto& enemy : enemies)
        {
            enemy.position.y += enemySpeedHardnes * GetFrameTime();
            enemy.rotation += enemy.rotationSpeed * GetFrameTime();
        }
    }

    void UpdateEnemies(vector<Enemy>& enemies)
    {
        double elapsedTime = GetTime() - lastDrop;
       
        if (elapsedTime > spawnRateHardnes)
        {
            Enemy enemy;
            LoadEnemy(enemy);
            enemies.push_back(enemy);
            lastDrop = GetTime();
        }

        MoveEnemies(enemies);
    }

    void DrawEnemies(vector<Enemy>& enemies)
    {
        const float enemyWidth = 100.0f;
        const float enemyHeight = 100.0f;

        Vector2 origin = { enemyWidth / 2.0f, enemyWidth / 2.0f };

        for (auto& enemy : enemies)
        {
            Rectangle dest = { enemy.GetCenter().x, enemy.GetCenter().y, enemyWidth, enemyHeight };
            enemy.source = { enemyWidth * enemy.frame, 0.0f, enemyWidth, enemyHeight };

            DrawTexturePro(enemy.texture, enemy.source, dest, origin, enemy.rotation + 90.0f, RAYWHITE);

            double elapsedTime = GetTime() - enemy.lastFrame;

            if (elapsedTime > 0.4f)
            {
                enemy.frame++;

                enemy.lastFrame = GetTime();

                if (enemy.frame > 1)
                {
                    enemy.frame = 0;
                }
            }
        }
    }

    void DeleteEnemies(vector<Enemy>& enemies)
    {
        enemies.clear();
    }
}