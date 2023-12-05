#include "Enemy.h"

#include <iostream>

#include "GameData.h"


using namespace std;
using namespace GameData;


namespace EnemyUtilities
{
    static const double spawnRate = 1.0f;
    static double lastDrop = 0.0f;

    static void LoadEnemy(Enemy& enemy)
    {
        enemy.texture = LoadTexture("Assets/Images/bigAsteroid.png");
        enemy.radius = enemy.texture.width / 2.0f;
        int spawnPosibilities = screenWidth - (enemy.texture.width * 2);
        enemy.position.x = static_cast<float>(rand() % spawnPosibilities);
        enemy.position.y = 0.0f;
        enemy.velocity = { 0.0f, enemy.speed };
        enemy.source = { 0.0f, 0.0f, static_cast<float>(enemy.texture.width), static_cast<float>(enemy.texture.height) };
        enemy.isAlive = true;

        lastDrop = GetTime();
    }

    static void MoveEnemies(vector<Enemy>& enemies)
    {
        for (auto& object : enemies)
        {
            object.position.y += object.velocity.y * GetFrameTime();
        }
    }

    void UpdateEnemies(vector<Enemy>& enemies)
    {
        double elapsedTime = GetTime() - lastDrop;
       
        if (elapsedTime > spawnRate)
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
        for (auto& object : enemies)
        {
            Rectangle dest = { object.GetCenter().x, object.GetCenter().y, static_cast<float>(object.texture.width), static_cast<float>(object.texture.height) };
            Vector2 origin = { static_cast<float>(object.texture.width / 2.0f), static_cast<float>(object.texture.height / 2.0f) };

            DrawTexturePro(object.texture, object.source, dest, origin, object.rotation + 90.0f, RAYWHITE);
        }
    }

    void DeleteEnemies(vector<Enemy>& enemies)
    {
        enemies.clear();
    }
}