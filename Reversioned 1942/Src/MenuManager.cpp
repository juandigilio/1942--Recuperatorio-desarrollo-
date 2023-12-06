#include "MenuManager.h"

#include <iostream>
#include <vector>

#include "GameData.h"
#include "Player.h"
#include "Enemy.h"
#include "Menu.h"
#include "Credits.h"
#include "Instructions.h"
#include "Pause.h"
#include "FinalResults.h"
#include "GameLoop.h"
#include "Parallax.h"


namespace MenuManager
{
	static void StartUp()
	{
		srand(static_cast<unsigned>(time(NULL)));

		SetConfigFlags(FLAG_MSAA_4X_HINT);

		InitWindow(screenWidth, screenHeight, "2042");

		InitAudioDevice();

		Menu::InitMenu();

		PlayMusicStream(menuMusic);
	}

	static void UnloadTextures(Player& player)
	{
		GameLoop::UnloadGameLoopTextures();
		Menu::UnloadMenuTextures();
		ParallaxUtilities::UnloadParallaxTextures();
		PlayerUtilities::UnloadPlayerTextures(player);
	}

	void RunGame()
	{
		GameSceen currentSceen = GameSceen::MENU;
		Player player;
		vector<Enemy> enemies;

		StartUp();

		while (currentSceen != GameSceen::EXIT && !WindowShouldClose())
		{
			BeginDrawing();
			ClearBackground(RAYWHITE);

			switch (currentSceen)
			{
				case GameSceen::MENU:
				{
					Menu::ShowMenu(currentSceen);
					break;
				}
				case GameSceen::GAME:
				{
					GameLoop::Play(player, enemies, currentSceen);
					break;
				}
				case GameSceen::RESULTS:
				{
					FinalResults::ShowResults(player, currentSceen);
					break;
				}
				case GameSceen::PAUSE:
				{
					Pause::ShowPause(player, enemies, currentSceen);
					break;
				}
				case GameSceen::INSTRUCTIONS:
				{
					Instructions::ShowInstructions(currentSceen);
					break;
				}
				case GameSceen::CREDITS:
				{
					Credits::ShowCredits(currentSceen);
					break;
				}
				case GameSceen::EXIT:
				{
					EnemyUtilities::DeleteEnemies(enemies);
					CloseWindow();
					break;
				}
			}

			EndDrawing();
		}

		UnloadTextures(player);
	}
}