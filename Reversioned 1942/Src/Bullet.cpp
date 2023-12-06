#include "Bullet.h"

#include"raymath.h"

#include "GameData.h"


using namespace GameData;


namespace BulletUtilities
{
    void MoveBullet(Bullet& bullet)
    {
        if (bullet.isAlive)
        {
            bullet.velocity = Vector2Scale(bullet.direction, bullet.speed * GetFrameTime());
            bullet.position = Vector2Add(bullet.position, bullet.velocity);

            if ((bullet.position.x > screenWidth + bullet.texture.width / 2.0f) ||
                (bullet.position.x < 0.0f - bullet.texture.width / 2.0f) ||
                (bullet.position.y > screenHeight + bullet.texture.height / 2.0f) ||
                (bullet.position.y < 0.0f - bullet.texture.height / 2.0f)
                )
            {
                bullet.isAlive = false;     
            }
        }
    }

    void DrawBullet(Bullet& bullet)
    {
        float size = bullet.radius * 2.0f;

        if (bullet.isAlive)
        {
            Vector2 origin = { bullet.radius, bullet.radius };
            Rectangle dest = { bullet.GetCenter().x, bullet.GetCenter().y, size, size };

            DrawTexturePro(bullet.texture, bullet.source, dest, origin, bullet.rotation - 90, RAYWHITE);

            switch (bullet.frame)
            {
            case 0:
            {
                bullet.source = { 0, 0, size, size };
                DrawTexturePro(bullet.texture, bullet.source, dest, origin, 0.0f, RAYWHITE);
                break;
            }
            case 1:
            {
                bullet.source = { size, 0, size, size };
                DrawTexturePro(bullet.texture, bullet.source, dest, origin, 0.0f, RAYWHITE);
                break;
            }
            case 2:
            {
                bullet.source = { size * 2, 0, size, size };
                DrawTexturePro(bullet.texture, bullet.source, dest, origin, 0.0f, RAYWHITE);
                break;
            }
            case 3:
            {
                bullet.source = { size * 3, 0, size, size };
                DrawTexturePro(bullet.texture, bullet.source, dest, origin, 0.0f, RAYWHITE);
                break;
            }
            case 4:
            {
                bullet.source = { size * 4, 0, size, size };
                DrawTexturePro(bullet.texture, bullet.source, dest, origin, 0.0f, RAYWHITE);
                break;
            }
            case 5:
            {
                bullet.source = { size * 5, 0, size, size };
                DrawTexturePro(bullet.texture, bullet.source, dest, origin, 0.0f, RAYWHITE);
                break;
            }
            }

            double elapsedTime = GetTime() - bullet.lastFrame;

            if (elapsedTime > 0.09f)
            {
                bullet.frame++;
                bullet.lastFrame = GetTime();
            }

            if (bullet.frame > 5)
            {
                bullet.frame = 0;
            }
        }
    }
}