#include "Bullet.h"

#include"raymath.h"

#include "GameData.h"


using namespace GameData;


namespace BulletUtilities
{
    void MoveBullets(Bullet& bullet)
    {
        bullet.velocity = Vector2Scale(bullet.direction, bullet.speed * GetFrameTime());
        bullet.position = Vector2Add(bullet.position, bullet.velocity);

        if (bullet.position.x > screenWidth + bullet.texture.width / 2.0f)
        {
            if (bullet.firstCrossing)
            {
                bullet.position.x = (-bullet.texture.width / 2.0f);
                bullet.position.y = screenHeight - bullet.position.y;
                bullet.firstCrossing = false;
            }
            else
            {
                bullet.isAlive = false;
                bullet.firstCrossing = true;
            }
        }
        else if (bullet.position.x < 0.0f - bullet.texture.width / 2.0f)
        {
            if (bullet.firstCrossing)
            {
                bullet.position.x = screenWidth + (bullet.texture.width / 2.0f);
                bullet.position.y = screenHeight - bullet.position.y;
                bullet.firstCrossing = false;
            }
            else
            {
                bullet.isAlive = false;
            }
        }
        else if (bullet.position.y > screenHeight + bullet.texture.height / 2.0f)
        {
            if (bullet.firstCrossing)
            {
                bullet.position.x = screenWidth - bullet.position.x;
                bullet.position.y = (-bullet.texture.height / 2.0f);
                bullet.firstCrossing = false;
            }
            else
            {
                bullet.isAlive = false;
            }
        }
        else if (bullet.position.y < 0.0f - bullet.texture.height / 2.0f)
        {
            if (bullet.firstCrossing)
            {
                bullet.position.x = screenWidth - bullet.position.x;
                bullet.position.y = screenHeight + (bullet.texture.height / 2.0f);
                bullet.firstCrossing = false;
            }
            else
            {
                bullet.isAlive = false;
            }
        }
    }
}