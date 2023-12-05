#pragma once

#include "GameData.h"
#include "Player.h"


using namespace GameData;

namespace GameLoop
{
	void Play(Player& player, GameSceen& gamseSceen);

	void DrawGame(Player player);
}


