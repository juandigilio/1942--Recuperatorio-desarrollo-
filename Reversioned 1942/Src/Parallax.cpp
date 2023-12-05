#include "Parallax.h"

#include "GameData.h"



using namespace GameData;


namespace ParallaxUtilities
{
	Texture2D gamePlayBacground;
	Vector2 layer1Pos{ 0.0f, 0.0f };
	float layer1Speed = 50.0f;
	bool firstTime = true;

	static void LoadParallax()
	{
		gamePlayBacground = LoadTexture("Assets/Images/background.png");
	}

	void UpdateParallax()
	{
		if (firstTime)
		{
			LoadParallax();
			firstTime = false;

		}

		layer1Pos.y += layer1Speed * GetFrameTime();

		if (layer1Pos.y > gamePlayBacground.height)
		{
			layer1Pos.y = 0.0f;
		}
	}

	void DrawParallax()
	{
		DrawTextureV(gamePlayBacground, layer1Pos, RAYWHITE);
		DrawTextureV(gamePlayBacground, { layer1Pos.x, layer1Pos.y - gamePlayBacground.height }, RAYWHITE);
	}
}