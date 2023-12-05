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

    void DrawBullet(Bullet bullet)
    {
        if (bullet.isAlive)
        {
            Rectangle dest = { bullet.GetCenter().x, bullet.GetCenter().y, static_cast<float>(bullet.texture.width), static_cast<float>(bullet.texture.height) };
            Vector2 origin = { static_cast<float>(bullet.texture.width / 2), static_cast<float>(bullet.texture.height / 2) };

            DrawTexturePro(bullet.texture, bullet.source, dest, origin, bullet.rotation - 90, RAYWHITE);
        }
    }
}