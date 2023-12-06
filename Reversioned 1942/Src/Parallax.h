#pragma once

#include "raylib.h"


namespace ParallaxUtilities
{
	const int layersQnty = 3;

	struct Parallax
	{
		Texture2D texture;
		Vector2 position{ 0.0f, 0.0f };
		float speed;
	};

	extern Parallax layers[layersQnty];

	extern void UpdateParallax();

	extern void DrawParallax();

	extern void ResetParallax();

	extern void UnloadParallaxTextures();
}