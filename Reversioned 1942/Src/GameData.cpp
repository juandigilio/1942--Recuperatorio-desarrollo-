#include "GameData.h"

namespace GameData
{
	const int screenWidth = 1024;
	const int screenHeight = 768;
	Vector2 screenCenter = { screenWidth / 2, screenHeight / 2 };
	bool loading = true;
	int highScore = 0;

	Music menuMusic{};
	Music gameLoopMusic{};

	Font font{};
	float fontSize{};
	float spacing = 8.0f;
	float instrucrtionsSpacing = 2.0f;

	double pauseTimer = 0.0f;
	double pauseDelay = 0.2f;
}