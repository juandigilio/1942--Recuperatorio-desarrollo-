#pragma once

#include "raylib.h"


namespace GameData
{
	enum class GameSceen
	{
		MENU,
		GAME,
		RESULTS,
		PAUSE,
		INSTRUCTIONS,
		CREDITS,
		EXIT,
	};

	extern const int screenWidth;
	extern const int screenHeight;
	extern Vector2 screenCenter;
	extern bool loading;
	extern int highScore;
	extern double spawnRateBase ;
	extern double spawnRateHardnes;
	extern float enemyBaseSpeed;
	extern float enemySpeedHardnes;

	extern Music menuMusic;
	extern Music gameLoopMusic;

	extern Font font;
	extern float fontSize;
	extern float spacing;
	extern float instrucrtionsSpacing;

	extern double pauseTimer;
	extern double pauseDelay;
}
