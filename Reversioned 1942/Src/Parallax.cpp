#include "Parallax.h"

#include "GameData.h"


using namespace GameData;

namespace ParallaxUtilities
{
	const int layersQnty = 3;

	struct Parallax
	{
		Texture2D texture;
		Vector2 position{ 0.0f, 0.0f };
		float speed;
	};

	Parallax layers[layersQnty];

	bool firstTime = true;


	static void LoadParallax()
	{
		layers[0].texture = LoadTexture("Assets/Images/Parallax/water.png");
		layers[0].speed = 20.0f;
		layers[1].texture = LoadTexture("Assets/Images/Parallax/birds.png");
		layers[1].speed = 35.0f;
		layers[2].texture = LoadTexture("Assets/Images/Parallax/clouds.png");
		layers[2].speed = 70.0f;
	}

	void UpdateParallax()
	{
		if (firstTime)
		{
			LoadParallax();
			firstTime = false;
		}

		for (int i = 0; i < layersQnty; i++)
		{
			layers[i].position.y += layers[i].speed * GetFrameTime();

			if (layers[i].position.y > layers[i].texture.height)
			{
				layers[i].position.y = 0.0f;
			}
		}
	}

	void DrawParallax()
	{
		for (int i = 0; i < layersQnty; i++)
		{
			DrawTextureV(layers[i].texture, layers[i].position, RAYWHITE);
			DrawTextureV(layers[i].texture, { layers[i].position.x, layers[i].position.y - layers[i].texture.height }, RAYWHITE);
		}
	}

	void UnloadParallaxTextures()
	{
		for (int i = 0; i < layersQnty; i++)
		{
			UnloadTexture(layers[i].texture);
		}
	}
}