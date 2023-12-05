#pragma once

#include "GameData.h"
#include "Player.h"
#include "Enemy.h"

using namespace GameData;

namespace Pause
{
	extern void ShowPause(Player player, vector<Enemy> enemies, GameSceen& currentSceen);
}