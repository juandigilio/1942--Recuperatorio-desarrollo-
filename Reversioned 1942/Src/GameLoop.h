#pragma once

#include "GameData.h"
#include "Player.h"
#include "Enemy.h"


using namespace GameData;

namespace GameLoop
{
	void Play(Player& player, vector<Enemy>& enemies, GameSceen& gamseSceen);

	void DrawGame(Player player, vector<Enemy> enemies);
}


